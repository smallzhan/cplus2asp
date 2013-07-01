/** @file cplus2asp.cpp
 *  @brief Calls a tool chain of a translator, pre-processor, answer set solver, and post-processor on a CCalc program translated to ASP syntax.
 *  @author Michael Casolary
 *  @date 07/2011
 *  @author Guoqiang Jin
 *  @date 03/2012
 */

/* History:
 * v3.0 - Implemented "composite action definitions" and add the "-i" options to call "iclingo" to solve the resulting asp programs. - by Guoqiang Jin 01/2012
 * v2.3 - Implemented "-from[PROG]" and "-to[PROG]" options to give better control over running a partial tool chain.
 * v2.2.2 - Fixed bugs, "-notrans" wasn't shutting off the translator, "-gropt" and "-grsoopt" were mixed up. Set up system to track when tool chain programs have errors.
 * v2.2.1 - Fixed bug where program might get wrong values back from system calls (depending on OS).
 * v2.2 - cplus2asp now supports integrated grounder-solvers (like clingo), using the option -grso / --grounder-solver. Added automatic searching though queries with ranged maxsteps, with an option to switch to manual mode (-mm). Removed support for using piped tool chain commands. Added automated "non-interactive" mode option (-auto).
 * v2.1.2 - Tweaked status outputs to be compatible with benchmarking scripts, adjusted output messages to make more sense.
 * v2.1.1 - Renamed to cplus2asp, also renamed translator & standard file dependencies.
 * v2.1 - Skips translating any files with .f2lp or .lp extensions, not just if all files have those extensions.
 * v2.0.1 - Made file name output more friendly, ensured all steps of the tool chain work together properly.
 * v2.0 - Added ccalc2asp.bin (translator) to tool chain, including options to control its usage, and an ability to interactively guess critical constant values based on hints given in comments in the input files.
 * v1.3.5 - Fixed bug with post-processor not receiving options correctly.
 * v1.3.4 - Now passes input file to solver via standard in redirection.
 * v1.3.3 - Added option to use pipes instead of intermediate files to send data between tool chain programs (i.e., pre-v1.3 behavior).
 * v1.3.2 - Sends input files to the first tool in the tool chain that isn't disabled.
 * v1.3.1 - Fixed bug with spaces in path causing odd behavior and errors from tool chain.
 * v1.3 - Changed default post-processor to as2transition, changed default standard files to ccalc2asp_std.f2lp & ccalc2asp_additive.f2lp, changed argument handler to allow generic "const=value" arguments without needing "-c" before them, added intermediate file usage and auto-deletion, added options to pass command-line options directly to any of the tool chain programs.
 * v1.2 - Added option to un-include the standard translation files from the call to the pre-processor.
 * v1.1 - Added options to turn off programs in the tool chain.
 * v1.0 - First working version.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <cctype> // for isdigit()
#include <climits> // for PATH_MAX, INT_MIN
#include <cstdlib> // for exit()
#include <cstring>
#include <sys/types.h>
#include <unistd.h> // for realpath()

using namespace std;

#define VERSION_MAJOR 3
#define VERSION_MINOR 0
#define VERSION_REV 0

#ifndef PATH_MAX
  #define PATH_MAX 4096
#endif

/**
 * Checks if a c-string represents an integer or not.
 * The whole string must count as an integer, no spaces or other nonsense allowed. Number may start with + or -.
 * @param str - The string to test.
 * @return True if str is an integer, false otherwise.
 */
bool isInteger(const char *str)
{
    bool retVal = true; // Start optimistic.
    size_t strLength = strlen(str);
    if(strLength == 0 || !(isdigit(str[0]) || str[0] == '+' || str[0] == '-'))
    { // Must be >0 length and start with a digit, +, or -.
        retVal = false;
    }
    else
    {
        // The rest of the string must be digits.
        for(unsigned int i = 1; i < strLength; i++)
        {
            if(!isdigit(str[i]))
            {
                retVal = false;
                break;
            }
        }
    }
    return retVal;
}

/**
 * Attempts to transform a string into a numeric representation of itself.
 * For numbers, fmt should be dec, hex, or oct.
 * @param val - A reference to the recipient of the generated number.
 * @param s - The string to convert.
 * @param fmt - An optional parameter that specifies what kind of numeric conversion to attempt. If not given, will default to std::dec.
 * @return True if s could be converted into a number using fmt, false if there was a problem performing the conversion.
 */
template <class T>
bool from_string(T& val, const std::string& s, std::ios_base& (*fmt)(std::ios_base&)=std::dec)
{
    std::istringstream iss(s);
    return !((iss >> fmt >> val).fail());
}

/**
 * Transforms something (usually a number) into a string representation of itself.
 * For integers, fmt should be dec, hex, or oct. For floating-point numbers, fmt should be fixed or scientific.
 * Precision will help control the precision of floating-point numbers.
 * @param val - The number to transform into a string.
 * @param fmt - An optional parameter controlling what kind of number val should be treated as. Defaults to std::dec.
 * @param precision - The decimal precision to use with floating-point numbers. Defaults to -1.
 * @return The string version of val on success, a blank string on failure.
 */
template <class T>
std::string to_string(T val, std::ios_base& (*fmt)(std::ios_base&)=std::dec, int precision=-1)
{
    std::stringstream ss;
    if(precision > -1)
    {
        ss.precision(precision);
    }
    ss << fmt << val;
    return ss.str();
}

/**
 * A wrapper for exit() that can output an optional custom message before leaving.
 * Outputs to stdout if exitCode is 0, stderr otherwise.
 * @param exitCode - The exit code to pass to exit.
 * @param message - A message to output to standard out before exiting (terminating newline automatically added).
 */
void nice_exit(int exitCode, const char* message)
{
    if(exitCode == 0 && message != NULL)
    {
        cout << message << endl;
    }
    else if(exitCode != 0 && message != NULL)
    {
        cerr << message << endl;
    }
    exit(exitCode);
}

int main(int argc, char** argv)
{
    // Temporary variables.
    size_t sztTempPos;
    string strTempString;
    string strTempCommand;
    // Other variables.
    string strEXEName = ""; // Name of this executable.
    string strPathToEXE = ""; // Path to this executable.
    vector<string> vecOriginalInputFileNames; // List of input files as specified by the user (i.e., no realpath etc. applied).
    vector<string> vecInputFiles; // List of files to pass to the first program in the tool chain.
    vector<string> vecSkipInputFiles; // List of files that should be skipped by the translator.
    vector<string> vecConstants; // List of constants to pass to the grounder.
    ifstream fin; // Used to read input/intermediate files to look for "hint" directives.
    ostringstream ossStrOut; // Used for complex string creation.
    int intSystemResult = 0; // Holds what comes back from system().

    bool blnIncludeAdditive = false; // If true, include the additive standard file in the call to f2lp.
    bool blnMaxAdditiveDefined = false; // Set to true when they define the constant maxAdditive in a command-line argument.
    bool blnMaxstepDefined = false; // Set to true when they define the constant maxstep in a command-line argument.
    bool blnQueryDefined = false; // Set to true when they define the constant query in a command-line argument.
	bool usingIclingo = false; // using the incremental solver iclingo instead of clasp.
    int intCurQuery = -1; // Set to the value of the query constant.
    string strOriginalMaxstep = ""; // Set to the value of the maxstep constant.
    int intCurMaxstep = -1; // Used when maxstep is a range.
    int intMaxMaxstep = -1; // Also used for ranged maxstep.

    // Return codes from known tool chain programs indicating their final status.
    enum FoundSolutionFlags { TRANSLATOR_OK = 0, PRE_PROCESSOR_OK = 0, CLASP_FOUND_SOLUTIONS = 10, CLINGO_FOUND_SOLUTIONS = 10, AS2TRANSITION_FOUND_SOLUTIONS = 101 };

    string strTranslatorCommand = "cplus2asp.bin"; // Command to use to invoke the translator.
    string strPreProcessCommand = "f2lp"; // Command to use to invoke the pre-processor.
    string strGrounderCommand = "gringo"; // Command to use to invoke a grounder (like gringo).
    string strGrounderSolverCommand = "clingo"; // Command to use to invoke a combined grounder/solver (like clingo).
    string strSolverCommand = "clasp"; // Command to use to invoke a solver (like clasp).
    string strPostProcessCommand = "as2transition"; // Command to use to invoke the answer set post-processor.
	string strTrans2IncCommand = "normal2inc";
	string strIncSolverCommand = "iclingo";
    int intNumSolutions = 1; // How many solutions to ask the solver to find.
    string strTranslatorOpts = ""; // User-supplied command-line arguments to pass to the pre-processor (if any).
    string strPreProcessOpts = ""; // User-supplied command-line arguments to pass to the pre-processor (if any).
    string strGrounderOpts = ""; // User-supplied command-line arguments to pass to the grounder (if any).
    string strGrounderSolverOpts = ""; // User-supplied command-line arguments to pass to the combined grounder/solver (if any).
    string strSolverOpts = ""; // User-supplied command-line arguments to pass to the solver (if any).
    string strPostProcessOpts = ""; // User-supplied command-line arguments to pass to the post-processor (if any).

    bool blnToolChainError = false; // Set to true if any of the tool chain programs return an error code.
    bool blnCreatedIntermediateFiles = false; // If true, we created at least one intermediate file in need of deletion.
    bool blnFoundSolutions = false; // Set to true if the solver or post-processor indicates solutions were found.
    bool blnGrounderSolver = false; // If true, we're using an integrated grounder & solver (like clingo).
    bool blnInteractive = true; // If true, will prompt user if additional information/input is neccessary. If false, will not interact with user.
    bool blnKeepF2LPFiles = false; // If true, we won't delete f2lp's "intermediate" files after calling it.
    bool blnKeepIntermediateFiles = false; // If true, we won't delete the "intermediate" files we create from each step of the process.
    bool blnManualMaxstepRangeAdvance = false; // If true, user will be asked to continue on each iteration of a query with a ranged maxstep. By default, the range is auto-explored until at least one solution is found.
    bool blnNoStdFiles = false; // If true, don't include the standard translation files in the call to the pre-processor.
    bool blnNoTranslator = false; // If true, don't call the translator as part of the tool chain.
    bool blnNoPreProcess = false; // If true, we won't call a pre-processor.
    bool blnNoGrounder = false; // If true, we won't call a grounder.
    bool blnNoSolver = false; // If true, we won't call a solver.
    bool blnNoPostProcess = false; // If true, we won't call a post-processor.

    string strCCalc2ASPStdFile = "cplus2asp_std.f2lp"; // The "standard" CCalc to ASP translation support file.
    string strCCalc2ASPAdditiveFile = "cplus2asp_additive.f2lp"; // The CCalc to ASP translation support file for additive fluents/actions.
    string strCCalc2ASPMacroFile = "cplus2asp_macro.f2lp"; // The CCalc to ASP translation sopport file for macro actions.
    string strIntermediateTransFile = ".cplus2asp_trans.out"; // Name of the intermediate output from the translator.
    string strIntermediatePreFile = ".cplus2asp_pre.out"; // Name of our intermediate output from the pre-processor.
    string strIntermediateGrFile = ".cplus2asp_gr.out"; // Name of our intermediate output from the grounder.
    string strIntermediateGrSoFile = ".cplus2asp_grso.out"; // Name of our intermediate output from a combined grounder/solver.
    string strIntermediateSoFile = ".cplus2asp_so.out"; // Name of our intermediate output from the solver.
	string strIntermediateIncFile = ".cplus2asp_inc.out";

    char chrarrFullPath[PATH_MAX+1]; // Used to temporarily hold paths to input files.
    char *chrptrPath = NULL; // Used to capture the results from realpath.

    // Get the name this executable was called by (w/o the path, just the file name), and the path to it (to use with the standard translation files).
    if(argc > 0)
    {
        chrptrPath = realpath(argv[0], chrarrFullPath);
        if(chrptrPath == NULL)
        {   // What? Well, we don't have the executable's path, so we can't continue.
			cout << "argv[0] is " << argv[0] << " chrarrFullpath is " << chrarrFullPath << endl;
            nice_exit(1, "Error: Problem locating required program files.");
        }
        else
        {   // Split the results from realpath into the executable name and the path to it.
            strTempString = chrarrFullPath;
            sztTempPos = strTempString.find_last_of('/');
            if(sztTempPos != string::npos)
            {
                strEXEName = strTempString.substr(sztTempPos + 1); // Strip off any path to this executable.
                strPathToEXE = strTempString.substr(0, sztTempPos); // Save the path (minus trailing '/') too.
            }
            else
            {   // What, no path?  Okay, try using "" as the path then.
                strEXEName = strTempString;
                strPathToEXE = "";
            }
        }
    }

    // Process command-line arguments.

    bool blnBadArgs = false; // Set to true if we get an unexpected or malformed command line argument.
    bool blnShowHelp = false; // Set to true if the user passes "--help" to the program as an argument.
    if(argc > 1)
    {
        for(int i = 1; i < argc; i++)
        {
            if(strcmp(argv[i], "-add") == 0 || strcmp(argv[i], "--additive") == 0)
            {   // Additive standard file needed.
                blnIncludeAdditive = true;
            }
            else if(strcmp(argv[i], "-auto") == 0 || strcmp(argv[i], "--automated") == 0)
            {   // This is supposed to be an automated run, don't ask the user for anything.
                blnInteractive = false;
            }
            else if(strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--const") == 0)
            {   // Specifying a constant, grab the next argument (if it exists) and store that.
                if(i + 1 < argc)
                {
                    i++;
                    // Make sure this argument has an equals sign (to be of "const=value" form).
                    if(strstr(argv[i],"=") != NULL)
                    {
                        vecConstants.push_back(argv[i]);
                        if(vecConstants.back().find("maxAdditive") != string::npos)
                        {   // The constant was maxAdditive, remember that it's been defined.
                            blnMaxAdditiveDefined = true;
                        }
                        else if(vecConstants.back().find("maxstep") != string::npos)
                        {   // The constant was maxstep, remember that it's been defined.
                            blnMaxstepDefined = true;
                            strOriginalMaxstep = vecConstants.back().substr(vecConstants.back().find("=")+1, string::npos);
                            vecConstants.pop_back(); // Remove maxstep, we manually re-insert it later.
                        }
                        else if(vecConstants.back().find("query") != string::npos)
                        {   // The constant was query, remember that it's been defined.
                            blnQueryDefined = true;
                            string tempQueryVal = vecConstants.back().substr(vecConstants.back().find("=")+1, string::npos);
                            from_string(intCurQuery, tempQueryVal);
                        }
                    }
                    else
                    {   // What came after "-c" wasn't a "const=value" argument, flag a bad arg.
                        blnBadArgs = true;
                    }
                }
                else
                {   // Set up for a constant without actually giving one, bad command line.
                    blnBadArgs = true;
                }
            }
            else if(strcmp(argv[i], "-fromgr") == 0 || strcmp(argv[i], "--from-grounder") == 0)
            {   // Don't run anything before the grounder.
                blnNoTranslator = blnNoPreProcess = true;
                blnNoGrounder = false;
            }
            else if(strcmp(argv[i], "-fromgrso") == 0 || strcmp(argv[i], "--from-grounder-solver") == 0)
            {   // Don't run anything before the combined grounder/solver.
                blnNoTranslator = blnNoPreProcess = blnNoGrounder = blnNoSolver = true;
                blnGrounderSolver = true;
            }
            else if(strcmp(argv[i], "-frompre") == 0 || strcmp(argv[i], "--from-pre-processor") == 0)
            {   // Don't run anything before the pre-processor.
                blnNoTranslator = true;
                blnNoPreProcess = false;
            }
            else if(strcmp(argv[i], "-frompost") == 0 || strcmp(argv[i], "--from-post-processor") == 0)
            {   // Don't call anything before the post-processor (equivalent to "-justpost")
                blnNoTranslator = blnNoPreProcess = blnNoGrounder = blnNoSolver = true;
                blnNoPostProcess = false;
            }
            else if(strcmp(argv[i], "-fromso") == 0 || strcmp(argv[i], "--from-solver") == 0)
            {   // Don't run anything before the solver.
                blnNoTranslator = blnNoPreProcess = blnNoGrounder = true;
                blnNoSolver = false;
            }
            else if(strcmp(argv[i], "-fromtrans") == 0 || strcmp(argv[i], "--from-translator") == 0)
            {   // Don't call anything before the translator (basically a no-op option).
                blnNoTranslator = false;
            }
            else if(strcmp(argv[i], "-gr") == 0 || strcmp(argv[i], "--grounder") == 0)
            {   // They're giving us a specific executable to use as the grounder instead of the default. Make sure a second argument follows, and save the new grounder.
                if(i + 1 < argc)
                {
                    i++;
                    strGrounderCommand = argv[i];
                }
                else
                {   // Set up for a second argument without actually giving one, bad command line.
                    blnBadArgs = true;
                }
            }
            else if(strcmp(argv[i], "-gropt") == 0 || strcmp(argv[i], "--grounder-opts") == 0)
            {   // We've been given some command-line options to pass to the grounder, remember them for later.
                if(i + 1 < argc)
                {
                    i++;
                    strGrounderOpts = argv[i];
                }
                else
                {
                    blnBadArgs = true; // Set up for receiving an argument but none given, bad command line.
                }
            }
            else if(strcmp(argv[i], "-grso") == 0 || strcmp(argv[i], "--grounder-solver") == 0)
            {   // They're giving us a specific executable to use as the combined grounder & solver. Make sure a second argument follows, and save it as the path to the combined grounder/solver.
                if(i + 1 < argc)
                {
                    i++;
                    strGrounderSolverCommand = argv[i];
                    blnNoGrounder = true; // Pretend like there's no individual grounder or solver.
                    blnNoSolver = true;
                    blnGrounderSolver = true; // Flag that we need to treat the solver like a grounder as well.
                }
                else
                {   // Set up for a second argument without actually giving one, bad command line.
                    blnBadArgs = true;
                }
            }
            else if(strcmp(argv[i], "-grsoopt") == 0 || strcmp(argv[i], "--grounder-solver-opts") == 0)
            {   // We've been given some command-line options to pass to the combined grounder/solver, remember them for later.
                if(i + 1 < argc)
                {
                    i++;
                    strGrounderSolverOpts = argv[i]; // Save them in solver options.
                }
                else
                {
                    blnBadArgs = true; // Set up for receiving an argument but none given, bad command line.
                }
            }
            else if(strcmp(argv[i], "-justgr") == 0 || strcmp(argv[i], "--just-grounder") == 0)
            {   // Just call the grounder program, no others.
                blnNoTranslator = blnNoPreProcess = blnNoSolver = blnNoPostProcess = true;
                blnNoGrounder = false;
            }
            else if(strcmp(argv[i], "-justgrso") == 0 || strcmp(argv[i], "--just-grounder-solver") == 0)
            {   // Just call the combined grounder/solver program, no others.
                blnNoTranslator = blnNoPreProcess = blnNoGrounder = blnNoSolver = blnNoPostProcess = true;
                blnGrounderSolver = true;
            }
            else if(strcmp(argv[i], "-justpre") == 0 || strcmp(argv[i], "--just-pre-processor") == 0)
            {   // Just call the pre-processor program, no others.
                blnNoTranslator = blnNoGrounder = blnNoSolver = blnNoPostProcess = true;
                blnNoPreProcess = false;
            }
            else if(strcmp(argv[i], "-justpost") == 0 || strcmp(argv[i], "--just-post-processor") == 0)
            {   // Just call the post-processor program, no others.
                blnNoTranslator = blnNoPreProcess = blnNoGrounder = blnNoSolver = true;
                blnNoPostProcess = false;
            }
            else if(strcmp(argv[i], "-justso") == 0 || strcmp(argv[i], "--just-solver") == 0)
            {   // Just call the solver program, no others.
                blnNoTranslator = blnNoPreProcess = blnNoGrounder = blnNoPostProcess = true;
                blnNoSolver = false;
            }
            else if(strcmp(argv[i], "-justtrans") == 0 || strcmp(argv[i], "--just-translator") == 0)
            {   // Just call the translator program, no others.
                blnNoPreProcess = blnNoGrounder = blnNoSolver = blnNoPostProcess = true;
                blnNoTranslator = false;
            }
            else if(strcmp(argv[i], "-mm") == 0 || strcmp(argv[i], "--manual-maxstep") == 0)
            {   // The user wants to manually advance ranged maxstep queries, let them.
                blnManualMaxstepRangeAdvance = true;
            }
            else if(strcmp(argv[i], "-nodel") == 0 || strcmp(argv[i], "--no-delete") == 0)
            {   // Shut off deleting intermediate files.
                blnKeepF2LPFiles = true;
                blnKeepIntermediateFiles = true;
            }
            else if(strcmp(argv[i], "-nogr") == 0 || strcmp(argv[i], "--no-grounder") == 0)
            {   // Shut off calling the grounder program.
                blnNoGrounder = true;
            }
            else if(strcmp(argv[i], "-nogrso") == 0 || strcmp(argv[i], "--no-grounder-solver") == 0)
            {   // Shut off calling the combined grounder/solver program.
                blnNoGrounder = false;
            }
            else if(strcmp(argv[i], "-nopre") == 0 || strcmp(argv[i], "--no-pre-processor") == 0)
            {   // Shut off calling the pre-processor program.
                blnNoPreProcess = true;
            }
            else if(strcmp(argv[i], "-nopost") == 0 || strcmp(argv[i], "--no-post-processor") == 0)
            {   // Shut off calling the post-processor program.
                blnNoPostProcess = true;
            }
            else if(strcmp(argv[i], "-noso") == 0 || strcmp(argv[i], "--no-solver") == 0)
            {   // Shut off calling the solver program.
                blnNoSolver = true;
            }
            else if(strcmp(argv[i], "-nostd") == 0 || strcmp(argv[i], "--no-standard") == 0)
            {   // Shut off including the CCalc to ASP standard files.
                blnNoStdFiles = true;
            }
            else if(strcmp(argv[i], "-notrans") == 0 || strcmp(argv[i], "--no-translator") == 0)
            {   // Shut off calling the translator program.
                blnNoTranslator = true;
            }
            else if(strcmp(argv[i], "-pipe") == 0 || strcmp(argv[i], "--use-pipes") == 0)
            {   // Use pipes instead of intermediate files to pass data between tool chain programs.
                // No longer supported, too much trouble to manage the dynamic tool chain and this.
                cerr << "Warning: \"" << argv[i] << "\" option no longer supported, it will be ignored." << endl;
            }
            else if(strcmp(argv[i], "-post") == 0 || strcmp(argv[i], "--post-processor") == 0)
            {   // They're giving us a specific executable to use as the answer set post-processor instead of the default. Make sure a second argument follows, and save the new post-processor.
                if(i + 1 < argc)
                {
                    i++;
                    strPostProcessCommand = argv[i];
                }
                else
                {   // Set up for a second argument without actually giving one, bad command line.
                    blnBadArgs = true;
                }
            }
            else if(strcmp(argv[i], "-postopt") == 0 || strcmp(argv[i], "--post-processor-opts") == 0)
            {   // We've been given some command-line options to pass to the post-processor, remember them for later.
                if(i + 1 < argc)
                {
                    i++;
                    strPostProcessOpts = argv[i];
                }
                else
                {
                    blnBadArgs = true; // Set up for receiving an argument but none given, bad command line.
                }
            }
            else if(strcmp(argv[i], "-pre") == 0 || strcmp(argv[i], "--pre-processor") == 0)
            {   // They're giving us a specific executable to use as the pre-processor instead of the default. Make sure a second argument follows, and save the new pre-processor.
                if(i + 1 < argc)
                {
                    i++;
                    strPreProcessCommand = argv[i];
                }
                else
                {   // Set up for a second argument without actually giving one, bad command line.
                    blnBadArgs = true;
                }
            }
            else if(strcmp(argv[i], "-preopt") == 0 || strcmp(argv[i], "--pre-processor-opts") == 0)
            {   // We've been given some command-line options to pass to the pre-processor, remember them for later.
                if(i + 1 < argc)
                {
                    i++;
                    strPreProcessOpts = argv[i];
                }
                else
                {
                    blnBadArgs = true; // Set up for receiving an argument but none given, bad command line.
                }
            }
            else if(strcmp(argv[i], "-so") == 0 || strcmp(argv[i], "--solver") == 0)
            {   // They're giving us a specific executable to use as the solver instead of the default. Make sure a second argument follows, and save the new solver.
                if(i + 1 < argc)
                {
                    i++;
                    strSolverCommand = argv[i];
                }
                else
                {   // Set up for a second argument without actually giving one, bad command line.
                    blnBadArgs = true;
                }
            }
            else if(strcmp(argv[i], "-soopt") == 0 || strcmp(argv[i], "--solver-opts") == 0)
            {   // We've been given some command-line options to pass to the post-processor, remember them for later.
                if(i + 1 < argc)
                {
                    i++;
                    strSolverOpts = argv[i];
                }
                else
                {
                    blnBadArgs = true; // Set up for receiving an argument but none given, bad command line.
                }
            }
            else if(strcmp(argv[i], "-togr") == 0 || strcmp(argv[i], "--to-grounder") == 0)
            {   // Stop the tool chain after running the grounder.
                blnNoSolver = blnNoPostProcess = true;
                blnNoGrounder = false;
            }
            else if(strcmp(argv[i], "-togrso") == 0 || strcmp(argv[i], "--to-grounder-solver") == 0)
            {   // Stop the tool chain after running the combined grounder/solver.
                blnNoPostProcess = true;
                blnGrounderSolver = true;
            }
            else if(strcmp(argv[i], "-topre") == 0 || strcmp(argv[i], "--to-pre-processor") == 0)
            {   // Stop the tool chain after running the pre-processor.
                blnNoGrounder = blnNoSolver = blnNoPostProcess = true;
                blnNoPreProcess = false;
            }
            else if(strcmp(argv[i], "-topost") == 0 || strcmp(argv[i], "--to-post-processor") == 0)
            {   // Stop the tool chain after running the post-processor (basically a no-op option).
                blnNoPostProcess = false;
            }
            else if(strcmp(argv[i], "-toso") == 0 || strcmp(argv[i], "--to-solver") == 0)
            {   // Stop the tool chain after running the solver.
                blnNoPostProcess = true;
                blnNoSolver = false;
            }
            else if(strcmp(argv[i], "-totrans") == 0 || strcmp(argv[i], "--to-translator") == 0)
            {   // Stop the tool chain after running the translator (equivalent to "-justtrans")
                blnNoPreProcess = blnNoGrounder = blnNoSolver = blnNoPostProcess = true;
                blnNoTranslator = false;
            }
            else if(strcmp(argv[i], "-trans") == 0 || strcmp(argv[i], "--translator") == 0)
            {   // They're giving us a specific executable to use as the translator instead of the default. Make sure a second argument follows, and save the new translator.
                if(i + 1 < argc)
                {
                    i++;
                    strTranslatorCommand = argv[i];
                }
                else
                {   // Set up for a second argument without actually giving one, bad command line.
                    blnBadArgs = true;
                }
            }
            else if(strcmp(argv[i], "-transopt") == 0 || strcmp(argv[i], "--translator-opts") == 0)
            {   // We've been given some command-line options to pass to the translator, remember them for later.
                if(i + 1 < argc)
                {
                    i++;
                    strTranslatorOpts = argv[i];
                }
                else
                {
                    blnBadArgs = true; // Set up for receiving an argument but none given, bad command line.
                }
            }
            else if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
            {   // Show version information and quit.
                cout << strEXEName << " version " << VERSION_MAJOR;
                cout << "." << VERSION_MINOR;
                if(VERSION_REV > 0) { cout << "." << VERSION_REV; }
                cout << endl;
                nice_exit(0, NULL);
            }
            else if(strcmp(argv[i], "-?") == 0 || strcmp(argv[i], "--help") == 0)
            {   // They need help, give them help.
                blnShowHelp = true;
            }
			else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--incremental") == 0)
			{
				usingIclingo = true;
			}
            else
            {   // If there's no "header" on the argument, it's either a constant declaration, an input file, or the number of solutions.
                if(isInteger(argv[i]))
                {   // It looks like a number, atoi it and save that as the desired number of solutions.
                    intNumSolutions = atoi(argv[i]);
                    if(intNumSolutions < 0)
                    {
                        cerr << "Warning: Number of solutions cannot be negative, defaulting to 1." << endl;
                        intNumSolutions = 1;
                    }
                }
                else if(strstr(argv[i],"=") != NULL)
                {   // Found an equals sign in the argument, it's probably a "const=value" declaration.
                    vecConstants.push_back(argv[i]);
                    // Check if it's any of the "special" constants we expect to have defined.
                    if(vecConstants.back().find("maxAdditive") != string::npos)
                    {   // The constant was maxAdditive, remember that it's been defined.
                        blnMaxAdditiveDefined = true;
                    }
                    else if(vecConstants.back().find("maxstep") != string::npos)
                    {   // The constant was maxstep, remember that it's been defined.
                        blnMaxstepDefined = true;
                        strOriginalMaxstep = vecConstants.back().substr(vecConstants.back().find("=")+1, string::npos);
                        vecConstants.pop_back(); // Remove maxstep, we manually re-insert it later.
                    }
                    else if(vecConstants.back().find("query") != string::npos)
                    {   // The constant was query, remember that it's been defined.
                        blnQueryDefined = true;
                        string tempQueryVal = vecConstants.back().substr(vecConstants.back().find("=")+1, string::npos);
                        from_string(intCurQuery, tempQueryVal);
                    }
                }
                else
                {   // If it's not a number, it's probably an input file. Make sure it exists, and then save it to the list.
                    chrptrPath = realpath(argv[i], chrarrFullPath);
                    if(chrptrPath == NULL)
                    {
                        // If realpath didn't give us a result, it might be a bad arg. Check if it starts with a dash (-).
                        if(argv[i][0] == '-')
                        {   // Starts with a dash, probably a bad argument.
                            blnBadArgs = true;
                        }
                        else
                        {   // Didn't start with a dash, so it's probably just a bad input file.
                            strTempString = "Error: Could not locate input file \"";
                            strTempString += argv[i];
                            strTempString += "\".";
                            nice_exit(1, strTempString.c_str());
                        }
                    }
                    else
                    {
                        vecOriginalInputFileNames.push_back(argv[i]);
                        vecInputFiles.push_back(chrarrFullPath);
                    }
                }
            }
            // If the user needs help, provide basic usage info and then exit.
            if(blnShowHelp || blnBadArgs)
            {
              cout << "Usage: " << strEXEName << " INPUT_FILES [OPTIONS] [CONSTANTS] [NUM_SOLUTIONS]" << endl
                   << "Calls cplus2asp.bin (translator), f2lp (pre-processor), gringo (grounder)," << endl
                   << "clasp (solver), and as2transition (post-processor) on the input files" << endl
                   << "(CCalc-style files that have been translated to ASP/f2lp syntax)," << endl
                   << "adding \"standard\" CCalc to ASP translation support files and" << endl
                   << "outputting the results from as2transition." << endl
                   << "  INPUT_FILES is a series of files in CCalc, ASP, or f2lp syntax." << endl
                   << "              At least one input file is required." << endl
                   << "              Any input files that have extensions \".f2lp\" or \".lp\"" << endl
                   << "              will automatically not be passed to the translator." << endl
                   << "  OPTIONS are optional arguments that change the program's behavior." << endl
                   << "  CONSTANTS are constant definitions that are passed to the grounder." << endl
                   << "            There are three special constants that are often seen in" << endl
                   << "            CCalc programs, and so can be useful to manually set." << endl
                   << "            These are not required to be defined if special \"hint\"" << endl
                   << "            comments are placed in the output from the translator." << endl
                   << "            maxAdditive - The maximum additive integer (only needed if" << endl
                   << "                          using additive fluents/actions)." << endl
                   << "            maxstep - The maximum time step to consider." << endl
                   << "            query - The query number (i.e., label) to select." << endl
                   << "  NUM_SOLUTIONS is the desired number of solutions for the solver to find." << endl
                   << "                This should be a non-negative integer (0 or greater)." << endl
                   << "                If not specified, defaults to 1." << endl
                   << endl
                   << "Normal Program Options:" << endl
                   << "  -add" << endl
                   << "  --additive includes the standard additive translation support file so that" << endl
                   << "             the input files can use additive fluents/actions. Automatically" << endl
                   << "             included if the constant maxAdditive is defined." << endl
                   << "  -auto" << endl
                   << "  --automated makes the program run in automated mode, so it won't prompt" << endl
                   << "              or ask for any information from the user." << endl
                   << "  CONST=VALUE" << endl
                   << "  -c CONST=VALUE" << endl
                   << "  --const CONST=VALUE declares a constant & value pair to pass to gringo." << endl
                   << "                      You will probably need to at least declare values for" << endl
                   << "                      the constants maxstep, query, and possibly maxAdditive." << endl
                   << "  -mm" << endl
                   << "  --manual-maxstep allows the user to manually control the iterations of" << endl
                   << "                   queries with ranged maxsteps. Obviously, this is" << endl
                   << "                   incompatible with the \"-auto\" option." << endl
                   << "  --help shows this usage message." << endl
                   << "  -v" << endl
                   << "  --version outputs version information." << endl
                   << endl
                   << "Extra Program Options:" << endl
                   << "  Options with [PROG] or [PROGRAM] in their name affect individual" << endl
                   << "  programs in the tool chain, depending on [PROG] or [PROGRAM]'s value." << endl
                   << "  Any option with [PROG] in its name should have [PROG] replaced with one of:" << endl
                   << "    gr (grounder), pre (pre-processor), post (post-processor), so (solver)," << endl
                   << "    trans (translator), or grso (combined grounder & solver)." << endl
                   << "  Replace [PROGRAM] in the applicable options with one of the following:" << endl
                   << "    grounder, pre-processor, post-processor, solver, translator," << endl
                   << "    or grounder-solver." << endl
                   << endl
                   << "  -[PROG] PATH" << endl
                   << "  --[PROGRAM] PATH gives a new path to the desired tool chain program." << endl
                   << "  -[PROG]opt \"OPTIONS\"" << endl
                   << "  --[PROGRAM]-opts \"OPTIONS\" passes OPTIONS to the given tool chain program." << endl
                   << "  -from[PROG]" << endl
                   << "  --from-[PROGRAM] starts running the tool chain from the given program." << endl
                   << "  -just[PROG]" << endl
                   << "  --just-[PROGRAM] removes all but the given program from the tool chain." << endl
                   << "  -nodel" << endl
                   << "  --no-delete stops the program from deleting intermediate files created" << endl
                   << "              during processing, grounding, and solving." << endl
                   << "  -no[PROG]" << endl
                   << "  --no-[PROGRAM] removes the given program from the tool chain." << endl
                   << "  -nostd" << endl
                   << "  --no-standard removes the standard translation files from the call to the" << endl
                   << "                pre-processor. Useful if supplying different \"standard\"" << endl
                   << "                files, or for debugging of input file errors." << endl
                   << "  -to[PROG]" << endl
                   << "  --to-[PROGRAM] stops running the tool chain after the given program." << endl
                   << endl
                   << "  Example: " << strEXEName << " myProgram.cp" << endl
                   << "           would translate and process the file \"myProgram.cp\"," << endl
                   << "           interactively asking which query from the file to run, returning" << endl
                   << "           the first solution found (if any)." << endl
                   << "  Example: " << strEXEName << " myProgram.cp query=1 2" << endl
                   << "           does the same as above, except it automatically runs Query 1" << endl
                   << "           (assuming it can find or derive maxstep), and tries to find two" << endl
                   << "           solutions to the query." << endl
                   << "  Example: " << strEXEName << " myProgram.cp query=1 maxstep=3 -so cmodels 2" << endl
                   << "           would do the same as above, but it changes the solver to cmodels" << endl
                   << "           and forces maxstep to be 3." << endl
                   << "  Example: " << strEXEName << " myProgram.f2lp --just-pre-processor" << endl
                   << "           skips running the translator because the input file has" << endl
                   << "           the .f2lp extension, just running f2lp (the pre-processor)" << endl
                   << "           on the contents of \"myProgram.f2lp\", outputting the results." << endl;
              nice_exit(0, NULL);
            }
        }
    }

    // Run some sanity checks before continuing.

    // Did they give us at least one input file?
    if(vecInputFiles.empty())
    {
        nice_exit(1,"Error: No input files given. Use \"--help\" to see basic usage info.");
    }

    // Are we going to do anything?
    if(blnNoTranslator && blnNoPreProcess && blnNoGrounder && blnNoSolver && blnNoPostProcess && !blnGrounderSolver)
    {
        nice_exit(1,"Error: Tool chain empty (everything is disabled).");
    }

    // Did they ask for non-interactivity but still manual maxstep mode?
    if(!blnInteractive && blnManualMaxstepRangeAdvance)
    {
        cerr << "Error: Can't manually control maxstep in automated mode, defaulting to non-interactive maxstep iteration." << endl;
        blnManualMaxstepRangeAdvance = false;
    }

    // Did they ask us to do two conflicting things with the standard files?
    if(blnIncludeAdditive && blnNoStdFiles)
    {
        cerr << "Warning: Option \"-nostd\" used, additive translation file not included." << endl;
    }

    // Do we need to quietly add the additive standard file?
    if(blnMaxAdditiveDefined && !blnIncludeAdditive && !blnNoStdFiles)
    {   // maxAdditive was defined, but we didn't include the additive standard file.
        // They probably meant to, so include it anyway.
        blnIncludeAdditive = true;
    }

    // Check if we need the translator or not based on file extensions.
    if(!blnNoTranslator)
    {
        bool blnAllF2LPInput = true; // Start optimistic.
        string strFileExtension = "";
        size_t sztDotPos;
        for(size_t i = 0; i < vecInputFiles.size(); i++)
        {
            sztDotPos = vecInputFiles[i].find_last_of('.');
            if(sztDotPos != string::npos)
            {
                strFileExtension = vecInputFiles[i].substr(sztDotPos, string::npos);
                if(strFileExtension != ".lp" && strFileExtension != ".f2lp")
                {   // A file had a non-f2lp extension, we probably need the translator.
                    blnAllF2LPInput = false;
                }
                else
                {   // It's a skippable file, add it to the list. (Use the original name for ease of output.)
                    vecSkipInputFiles.push_back(vecOriginalInputFileNames[i]);
                }
            }
            else
            {   // A file had no extension, we can't assume we won't need the translator.
                blnAllF2LPInput = false;
            }
        }
        if(blnAllF2LPInput)
        {   // If all input files had f2lp-style extensions, we can skip the translator.
            blnNoTranslator = true;
            cerr << "All input files appear to be in f2lp format, skipping translator." << endl;
        }
        else if(!vecSkipInputFiles.empty())
        {   // If at least one file is being skipped, announce it.
            cerr << "Skipping translating" << (vecSkipInputFiles.size() == 1 ? " file" : " files");
            for(size_t i = 0; i < vecSkipInputFiles.size(); i++)
            {
                if(vecSkipInputFiles.size() > 2 && i > 0)
                {
                    cerr << ",";
                }
                if(vecSkipInputFiles.size() > 1 && i == vecSkipInputFiles.size() - 1)
                {
                    cerr << " and";
                }
                cerr << " \"" << vecSkipInputFiles[i] << "\"";
            }
            cerr << "." << endl;
        }
    }

    // Call the tool chain on the inputs.

    ossStrOut.str("");
    // Running the translator.
    if(!blnNoTranslator)
    {
        ossStrOut << "\"" << strTranslatorCommand << "\""; // Add the translator to the tool chain.
        if(!strTranslatorOpts.empty())
        {
            ossStrOut << " " << strTranslatorOpts; // Add command-line options if the user supplied any (no quotes, that'll mess up the options).
        }

        size_t skipIndex = 0;
        for(unsigned int i = 0; i < vecInputFiles.size(); i++)
        {   // Add the input files one at a time.
            if(skipIndex >= vecSkipInputFiles.size() || vecOriginalInputFileNames[i] != vecSkipInputFiles[skipIndex])
            {
                ossStrOut << " \"" << vecInputFiles[i] << "\"";
            }
            else
            {   // This file shouldn't be passed to the translator, skip it and move on the next one.
                skipIndex++;
            }
        }

        // Call the translator, saving its results to an intermediate file if necessary.
        if(!blnNoPreProcess || !blnNoGrounder || !blnNoSolver || blnGrounderSolver || !blnNoPostProcess)
        {
            ossStrOut << " >\"" << strIntermediateTransFile << "\""; // Add command to output results to an intermediate file (if we're passing the results on to something else).
            blnCreatedIntermediateFiles = true;
        }
        strTempCommand = ossStrOut.str();
        intSystemResult = system(strTempCommand.c_str()); // Call the pre-processor.
        if(WEXITSTATUS(intSystemResult) != TRANSLATOR_OK)
        {
            blnToolChainError = true; // Something went wrong, stop the tool chain.
        }
        ossStrOut.str("");
    }

    // If any of the "critical" constants aren't defined and one of the
    // "active" tool chain programs is going to need the constants, try
    // finding "hint" comments in the input that we can use to fill in details.
    if(!blnToolChainError && (!blnMaxstepDefined || !blnQueryDefined || !blnMaxAdditiveDefined) && (!blnNoGrounder || blnGrounderSolver))
    {
        int fileIndex = 0;
        string tempLine = "";
        string findText = "";
        size_t tempPos, tempPos2;
        int tempInt;
        pair<int, string> tempPair; // Holds a label and maxstep, respectively.
        vector< pair<int, string> > queryHints; // Keeps track of query label & maxstep definitions.
        // Go through the input file(s) looking for special "hint" comments
        // that tell us the value of maxAdditive, maxstep, and/or query.
        // Loop through the file(s) looking for hints for any undefined constants.
        if(!blnNoTranslator)
        {   // Start with the output from the translator.
            fileIndex = -1;
        }
        do
        {
            if(fileIndex < 0)
            {
                fin.open(strIntermediateTransFile.c_str());
            }
            else
            {   // Also look through any other input files.
                if((size_t)fileIndex >= vecInputFiles.size())
                {   // If we ran out of files, break out.
                    break;
                }
                fin.open(vecInputFiles[fileIndex].c_str());
            }
            if(fin.fail())
            {   // If at any point we fail to open an input file, just skip this step.
                break;
            }
            while(!fin.eof())
            {   // Go line by line looking for specially-formatted comments.
                getline(fin, tempLine);
                if(!tempLine.empty())
                {
                    if(!blnMaxAdditiveDefined)
                    {   // Look for a maxAdditive hint comment.
                        // If one is found, set maxAdditive and flag that we need to
                        // include the additive standard file.
                        findText = "% [MaxAdditive:";
                        tempPos = tempLine.find(findText);
                        if(tempPos != string::npos)
                        {
                            tempPos += findText.length();
                            tempPos2 = tempLine.find("]", tempPos);
                            if(tempPos2 != string::npos && tempPos2 > tempPos)
                            {
                                strTempString = tempLine.substr(tempPos, tempPos2 - tempPos);
                                if(from_string(tempInt, strTempString.c_str()))
                                {
                                    // Found maxAdditive, set it and flag that we need the additive standard file.
                                    cerr << "maxAdditive hint found, auto-setting maxAddtive to " << tempInt << "." << endl;
                                    strTempString = "maxAdditive=";
                                    strTempString += to_string(tempInt);
                                    vecConstants.push_back(strTempString);
                                    blnMaxAdditiveDefined = true;
                                    blnIncludeAdditive = true;
                                }
                            }
                        }
                    }
                    if(!blnMaxstepDefined || !blnQueryDefined)
                    {   // Look for a query hint comment.
                        // Collect any that are found that define both label and maxstep.
                        findText = "% [Query: Label:";
                        tempPos = tempLine.find(findText);
                        if(tempPos != string::npos)
                        {
                            tempPos += findText.length();
                            tempPos2 = tempLine.find(",", tempPos);
                            if(tempPos2 != string::npos && tempPos2 > tempPos)
                            {
                                strTempString = tempLine.substr(tempPos, tempPos2 - tempPos);
                                if(from_string(tempInt, strTempString))
                                {
                                    // Found a query's label, set it in tempPair and look for maxstep.
                                    tempPair.first = tempInt;
                                    findText = "Maxstep:";
                                    tempPos = tempLine.find(findText, tempPos2);
                                    if(tempPos != string::npos)
                                    {
                                        tempPos += findText.length();
                                        tempPos2 = tempLine.find("]", tempPos);
                                        if(tempPos2 != string::npos && tempPos2 > tempPos)
                                        {
                                            // Found the maxstep as well, set it in tempPair and add it to the collection of query hints.
                                            tempPair.second = tempLine.substr(tempPos, tempPos2 - tempPos);
                                            // Turn any funny range symbols back into normal dots (..).
                                            if(tempPair.second.find("::") != std::string::npos)
                                            {
                                                tempPair.second.replace(tempPair.second.find("::"), 2, "..");
                                            }
                                            queryHints.push_back(tempPair);
                                            // If we already know which query we want, check if this is that query's maxstep, set maxstep directly if it isn't already set.
                                            if(blnQueryDefined && !blnMaxstepDefined && intCurQuery == tempPair.first)
                                            {
                                                strOriginalMaxstep = tempPair.second;
                                                blnMaxstepDefined = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            fin.close();
            fin.clear();
            fileIndex++;
        } while((size_t)fileIndex < vecInputFiles.size());

        // If at least one of maxstep and query still aren't defined and, we found query hints,
        // and we're allowed to be interactive, set up a prompt to have the user pick values to fill in.
        if((!blnMaxstepDefined || !blnQueryDefined) && !queryHints.empty() && blnInteractive)
        {
            // Remove any existing definitions of maxstep and query, they're probably malformed.
            for(vector<string>::iterator vIter = vecConstants.begin(); vIter != vecConstants.end(); ++vIter)
            {
                if(blnMaxstepDefined && (*vIter).find("maxstep") == 0)
                {
                    vIter = vecConstants.erase(vIter);
                    --vIter;
                    blnMaxstepDefined = false;
                }
                if(blnQueryDefined && (*vIter).find("query") == 0)
                {
                    vIter = vecConstants.erase(vIter);
                    --vIter;
                    blnQueryDefined = false;
                }
            }
            bool goodInput = false;
            cout << "The following queries were found in the input file(s):" << endl;
            for(size_t i = 0; i < queryHints.size(); i++)
            {
                cout << queryHints[i].first << ": Query " << queryHints[i].first << ", maxstep = " << queryHints[i].second << endl;
            }
            cout << "S: Perform satisfiability check (no query, maxstep=0)" << endl;
            cout << "X: Ignore these and do not run a query" << endl;
            while(!goodInput)
            {
                cout << endl << "Which query would you like to run? ";
                getline(cin, tempLine);
                if(tempLine == "X" || tempLine == "x")
                {   // If they chose "X", just pass through and hope for the best.
                    goodInput = true;
                }
                else if(tempLine == "S" || tempLine == "s")
                {   // Perform a satisfiability check. Define query to be a bogus value, maxstep=0
                    strTempString = "query=none";
                    vecConstants.push_back(strTempString);
                    intCurQuery = -1;
                    blnQueryDefined = true;
                    strOriginalMaxstep = "0";
                    blnMaxstepDefined = true;
                    goodInput = true;
                }
                else if(from_string(tempInt, tempLine))
                {   // If they chose a query, fill in any missing info from the hint.
                    for(size_t i = 0; i < queryHints.size(); i++)
                    {
                        if(queryHints[i].first == tempInt)
                        {
                            if(!blnMaxstepDefined)
                            {
                                strOriginalMaxstep = queryHints[i].second;
                                blnMaxstepDefined = true;
                            }
                            if(!blnQueryDefined)
                            {
                                strTempString = "query=";
                                strTempString += to_string(queryHints[i].first);
                                vecConstants.push_back(strTempString);
                                intCurQuery = queryHints[i].first;
                                blnQueryDefined = true;
                            }
                            goodInput = true;
                        }
                    }
                }
                if(!goodInput)
                {
                    cout << "Error: Bad option, please select one of the available choices." << endl;
                }
            }
        }

        // Some final sanity checking now that all "critical" constants should be defined.
        if(!blnMaxAdditiveDefined && blnIncludeAdditive && (!blnNoGrounder || blnGrounderSolver))
        {   // maxAdditive wasn't defined but we're supposed to include the additive standard file.
            cerr << "% Warning: maxAdditive not defined, program probably won't work." << endl;
        }
        if(!blnMaxstepDefined && (!blnNoGrounder || blnGrounderSolver))
        {   // maxstep wasn't defined, this will probably not end well.
            cerr << "% Warning: maxstep not defined, program probably won't work." << endl;
        }
        if(!blnQueryDefined && (!blnNoGrounder || blnGrounderSolver))
        {   // query wasn't defined, this may not end well.
            cerr << "% Caution: query not defined, program may not produce desired solutions." << endl;
        }
    }

    // Running the pre-processor.
    if(!blnToolChainError && !blnNoPreProcess)
    {
        ossStrOut << "\"" << strPreProcessCommand << "\""; // Add the pre-processor to the tool chain.
        if(!strPreProcessOpts.empty())
        {
            ossStrOut << " " << strPreProcessOpts; // Add command-line options if the user supplied any (no quotes, that'll mess up the options).
        }

        if(!blnNoStdFiles)
        {
            ossStrOut << " \"" << strPathToEXE << "/" << strCCalc2ASPStdFile << "\""; // Add the standard translation file.
            ossStrOut << " \"" << strPathToEXE << "/" << strCCalc2ASPMacroFile << "\"";
        }
        if(blnIncludeAdditive && !blnNoStdFiles)
        {
            ossStrOut << " \"" << strPathToEXE << "/" << strCCalc2ASPAdditiveFile << "\""; // The additive standard file (if needed).
        }

        if(!blnNoTranslator)
        {   // If we already ran a translator, run the pre-processor on its output and the skipped files.
            for(size_t i = 0; i < vecSkipInputFiles.size(); i++)
            {
                ossStrOut << " \"" << vecSkipInputFiles[i] << "\"";
            }
            ossStrOut << " \"" << strIntermediateTransFile << "\"";
        }
        else
        {   // If we didn't run a translator, just pass the input files directly to the pre-processor.
            for(size_t i = 0; i < vecInputFiles.size(); i++)
            {   // Add the input files one at a time.
                ossStrOut << " \"" << vecInputFiles[i] << "\"";
            }
        }

        // Call the pre-processor, saving its results to an intermediate file if necessary.
        if(!blnNoGrounder || !blnNoSolver || blnGrounderSolver || !blnNoPostProcess)
        {
            ossStrOut << " >\"" << strIntermediatePreFile << "\""; // Add command to output results to an intermediate file (if we're passing the results on to something else).
            blnCreatedIntermediateFiles = true;
        }
        strTempCommand = ossStrOut.str();
        intSystemResult = system(strTempCommand.c_str()); // Call the pre-processor.
        ossStrOut.str("");
    }

	// Set up multi-pass solving if maxstep is a number range.
	if(blnMaxstepDefined)
	{
		size_t rangeLoc = strOriginalMaxstep.find("..");
		if(rangeLoc != string::npos)
		{
			strTempString = strOriginalMaxstep.substr(0, rangeLoc);
			from_string(intCurMaxstep, strTempString);
			strTempString = strOriginalMaxstep.substr(rangeLoc + 2, string::npos);
			from_string(intMaxMaxstep, strTempString);
		}
		else
		{   // Not using a number range, just run the tool chain once.
			from_string(intCurMaxstep, strOriginalMaxstep);
			intMaxMaxstep = intCurMaxstep;
		}
	}
	else
	{   // Not a proper query, set to run just once.
		intCurMaxstep = intMaxMaxstep = -1;
	}

	if (usingIclingo)
	{
		// Remind user of how many solutions we're looking for.
		cout << "% Searching for ";
		if(intNumSolutions == 0)
		{
			cout << "all solutions." << endl;
		}
		else
		{
			cout << intNumSolutions << (intNumSolutions == 1 ? " solution." : " solutions.") << endl;
		}
		// Only run an individual grounder or solver if an integrated grounder/solver isn't being used.
		// Running the grounder.
		if(!blnToolChainError && !blnNoGrounder)
		{
			ossStrOut << "\"" << strTrans2IncCommand << "\""; // Add grounder to tool chain.

			if(blnNoTranslator && blnNoPreProcess)
			{   // If we didn't run a translator or pre-processor, just pass the input files directly to the grounder (and hope for the best).
				for(unsigned int i = 0; i < vecInputFiles.size(); i++)
				{   // Add the input files one at a time.
					ossStrOut << " \"" << vecInputFiles[i] << "\"";
				}
			}
			else if(!blnNoPreProcess)
			{   // If we already ran a pre-processor, run the grounder on its output.
				ossStrOut << " <\"" << strIntermediatePreFile << "\"";
			}
			else if(!blnNoTranslator)
			{   // Odd, but if we already ran a translator (and just the translator), trust that its output is what we should be sending to the grounder.
				ossStrOut << " <\"" << strIntermediateTransFile << "\"";
			}

			// Call the grounder, saving its results to an intermediate file if necessary.
			if(!blnNoSolver || !blnNoPostProcess)
			{
				ossStrOut << " >\"" << strIntermediateIncFile << "\""; // Add command to output results to an intermediate file (if we're passing the results on to something else).
				blnCreatedIntermediateFiles = true;
			}
			strTempCommand = ossStrOut.str();
			intSystemResult = system(strTempCommand.c_str()); // Call the grounder.
			ossStrOut.str("");
		}
		// Running the solver.
		if(!blnToolChainError && !blnNoSolver)
		{
			ossStrOut << "\"" << strIncSolverCommand << "\" " << intNumSolutions << " --imax=" << intMaxMaxstep << " "; // Add solver to tool chain.

			if(blnNoTranslator && blnNoPreProcess && blnNoGrounder)
			{   // If nothing came before the solver, pass the first input file directly to it.
				ossStrOut << " <\"" << vecInputFiles[0] << "\"";
			}
			else if(!blnNoGrounder)
			{   // If we already ran a grounder, run the solver on its output.
				ossStrOut << " <\"" << strIntermediateIncFile << "\"";
			}
			else if(!blnNoPreProcess)
			{   // Odd, but if we already ran a pre-processor but no grounder, trust that the pre-processor's output is what we should be sending to the solver.
				ossStrOut << " <\"" << strIntermediatePreFile << "\"";
			}
			else if(!blnNoTranslator)
			{   // Odder, but if we already ran a translator (and just the translator), trust that its output is what we should be sending to the solver.
				ossStrOut << " <\"" << strIntermediateTransFile << "\"";
			}

			// Call the solver, saving its results to an intermediate file if necessary.
			if(!blnNoPostProcess)
			{
				ossStrOut << " >\"" << strIntermediateSoFile << "\""; // Add command to output results to an intermediate file (if we're passing the results on to something else).
				blnCreatedIntermediateFiles = true;
			}
			strTempCommand = ossStrOut.str();
			intSystemResult = system(strTempCommand.c_str()); // Call the solver.
			if(WEXITSTATUS(intSystemResult) == CLASP_FOUND_SOLUTIONS)
			{
				blnFoundSolutions = true; // clasp found solutions.
			}
			ossStrOut.str("");
		}

		// Running the post-processor.
		if(!blnToolChainError && !blnNoPostProcess)
		{
			ossStrOut << strPostProcessCommand; // Add post-processor to tool chain.
			if(!strPostProcessOpts.empty())
			{
				ossStrOut << " " << strPostProcessOpts; // Add command-line options if the user supplied any.
			}

			if(blnNoPreProcess && blnNoGrounder && blnNoSolver && !blnGrounderSolver)
			{   // If nothing ran before the post-processor, pass it the first input file.
				ossStrOut << " -f \"" << vecInputFiles[0] << "\"";
			}
			else if(!blnNoSolver)
			{   // If we already ran a solver, run the post-processor on its output.
				ossStrOut << " -f \"" << strIntermediateSoFile << "\"";
			}
			else if(blnGrounderSolver)
			{   // If we already ran a combined grounder/solver, run the post-processor on its output.
				ossStrOut << " -f \"" << strIntermediateGrSoFile << "\"";
			}
			else if(!blnNoGrounder)
			{   // Odd, but if we already ran a grounder w/o solver, run the post-processor on its output.
				ossStrOut << " -f \"" << strIntermediateGrFile << "\"";
			}
			else if(!blnNoPreProcess)
			{   // Even odder, but if we ran a pre-processor w/o a grounder or solver, trust that the pre-processor's output is what we should be sending to the post-processor.
				ossStrOut << " -f \"" << strIntermediatePreFile << "\"";
			}
			else if(!blnNoTranslator)
			{   // Still odder, but if we already ran a translator (and just the translator), trust that the its output is what we should be sending to the post-processor.
				ossStrOut << " -f \"" << strIntermediateTransFile << "\"";
			}

			// Call the post-processor.
			strTempCommand = ossStrOut.str();
			intSystemResult = system(strTempCommand.c_str()); // Call the post-processor.
			if(WEXITSTATUS(intSystemResult) == AS2TRANSITION_FOUND_SOLUTIONS)
			{
				blnFoundSolutions = true; // as2transition found solutions.
			}
			ossStrOut.str("");
		}
	}
	else {



		// Run the rest of the tool chain at least once
		do
		{
			if(!blnToolChainError && (!blnNoSolver || blnGrounderSolver))
			{
				if(blnQueryDefined && blnMaxstepDefined)
				{
					if(intCurQuery == -1 && strOriginalMaxstep == "0")
					{   // Satisfiability check.
						cout << endl << "% Running satisfiability check." << endl;
					}
					else
					{   // Normal query.
						cout << endl << "% Running Query " << intCurQuery << " with maxstep=" << intCurMaxstep << "." << endl;
					}
				}
				// Remind user of how many solutions we're looking for.
				cout << "% Searching for ";
				if(intNumSolutions == 0)
				{
					cout << "all solutions." << endl;
				}
				else
				{
					cout << intNumSolutions << (intNumSolutions == 1 ? " solution." : " solutions.") << endl;
				}
			}
			// Only run an individual grounder or solver if an integrated grounder/solver isn't being used.
			if(!blnToolChainError && !blnGrounderSolver)
			{
				// Running the grounder.
				if(!blnToolChainError && !blnNoGrounder)
				{
					ossStrOut << "\"" << strGrounderCommand << "\""; // Add grounder to tool chain.
					if(!strGrounderOpts.empty())
					{
						ossStrOut << " " << strGrounderOpts; // Add command-line options if the user supplied any.
					}

					for(unsigned int i = 0; i < vecConstants.size(); i++)
					{   // Add the constant definitions one at a time.
						ossStrOut << " -c " << vecConstants[i];
					}

					// Add the current maxstep in if it exists.
					if(blnMaxstepDefined)
					{
						ossStrOut << " -c maxstep=" << intCurMaxstep;
					}

					if(blnNoTranslator && blnNoPreProcess)
					{   // If we didn't run a translator or pre-processor, just pass the input files directly to the grounder (and hope for the best).
						for(unsigned int i = 0; i < vecInputFiles.size(); i++)
						{   // Add the input files one at a time.
							ossStrOut << " \"" << vecInputFiles[i] << "\"";
						}
					}
					else if(!blnNoPreProcess)
					{   // If we already ran a pre-processor, run the grounder on its output.
						ossStrOut << " <\"" << strIntermediatePreFile << "\"";
					}
					else if(!blnNoTranslator)
					{   // Odd, but if we already ran a translator (and just the translator), trust that its output is what we should be sending to the grounder.
						ossStrOut << " <\"" << strIntermediateTransFile << "\"";
					}

					// Call the grounder, saving its results to an intermediate file if necessary.
					if(!blnNoSolver || !blnNoPostProcess)
					{
						ossStrOut << " >\"" << strIntermediateGrFile << "\""; // Add command to output results to an intermediate file (if we're passing the results on to something else).
						blnCreatedIntermediateFiles = true;
					}
					strTempCommand = ossStrOut.str();
					intSystemResult = system(strTempCommand.c_str()); // Call the grounder.
					ossStrOut.str("");
				}
				// Running the solver.
				if(!blnToolChainError && !blnNoSolver)
				{
					ossStrOut << "\"" << strSolverCommand << "\" " << intNumSolutions; // Add solver to tool chain.
					if(!strSolverOpts.empty())
					{
						ossStrOut << " " << strSolverOpts; // Add command-line options if the user supplied any.
					}

					if(blnNoTranslator && blnNoPreProcess && blnNoGrounder)
					{   // If nothing came before the solver, pass the first input file directly to it.
						ossStrOut << " <\"" << vecInputFiles[0] << "\"";
					}
					else if(!blnNoGrounder)
					{   // If we already ran a grounder, run the solver on its output.
						ossStrOut << " <\"" << strIntermediateGrFile << "\"";
					}
					else if(!blnNoPreProcess)
					{   // Odd, but if we already ran a pre-processor but no grounder, trust that the pre-processor's output is what we should be sending to the solver.
						ossStrOut << " <\"" << strIntermediatePreFile << "\"";
					}
					else if(!blnNoTranslator)
					{   // Odder, but if we already ran a translator (and just the translator), trust that its output is what we should be sending to the solver.
						ossStrOut << " <\"" << strIntermediateTransFile << "\"";
					}

					// Call the solver, saving its results to an intermediate file if necessary.
					if(!blnNoPostProcess)
					{
						ossStrOut << " >\"" << strIntermediateSoFile << "\""; // Add command to output results to an intermediate file (if we're passing the results on to something else).
						blnCreatedIntermediateFiles = true;
					}
					strTempCommand = ossStrOut.str();
					intSystemResult = system(strTempCommand.c_str()); // Call the solver.
					if(WEXITSTATUS(intSystemResult) == CLASP_FOUND_SOLUTIONS)
					{
						blnFoundSolutions = true; // clasp found solutions.
					}
					ossStrOut.str("");
				}
			}
			// Running a combined grounder/solver (instead of individual grounder & solver programs).
			else if(!blnToolChainError)
			{
				ossStrOut << "\"" << strGrounderSolverCommand << "\" " << intNumSolutions; // Add combined grounder/solver to tool chain.
				// Be nice and include all combinations of grounder and solver options for maximum flexibility.
				if(!strGrounderOpts.empty())
				{
					ossStrOut << " " << strGrounderOpts;
				}
				if(!strSolverOpts.empty())
				{
					ossStrOut << " " << strSolverOpts;
				}
				if(!strGrounderSolverOpts.empty())
				{
					ossStrOut << " " << strGrounderSolverOpts; // Add command-line options if the user supplied any.
				}

				for(unsigned int i = 0; i < vecConstants.size(); i++)
				{   // Add the constant definitions one at a time.
					ossStrOut << " -c " << vecConstants[i];
				}

				// Add the current maxstep in if it exists.
				if(blnMaxstepDefined)
				{
					ossStrOut << " -c maxstep=" << intCurMaxstep;
				}

				if(blnNoTranslator && blnNoPreProcess)
				{   // If nothing came before the grounder/solver, pass the first input file directly to it.
					ossStrOut << " <\"" << vecInputFiles[0] << "\"";
				}
				else if(!blnNoPreProcess)
				{   // If we already ran a pre-processor, send the pre-processor's output to the grounder/solver.
					ossStrOut << " <\"" << strIntermediatePreFile << "\"";
				}
				else if(!blnNoTranslator)
				{   // Odd, but if we already ran a translator (and just the translator), trust that its output is what we should be sending to the grounder/solver.
					ossStrOut << " <\"" << strIntermediateTransFile << "\"";
				}

				// Call the grounder/solver, saving its results to an intermediate file if necessary.
				if(!blnNoPostProcess)
				{
					ossStrOut << " >\"" << strIntermediateGrSoFile << "\""; // Add command to output results to an intermediate file (if we're passing the results on to something else).
					blnCreatedIntermediateFiles = true;
				}
				strTempCommand = ossStrOut.str();
				intSystemResult = system(strTempCommand.c_str()); // Call the grounder/solver.
				cout << "call grounder/solver: " << strTempCommand << endl;
				if(WEXITSTATUS(intSystemResult) == CLINGO_FOUND_SOLUTIONS)
				{
					blnFoundSolutions = true; // clingo found solutions.
				}
				ossStrOut.str("");
			}
			// Running the post-processor.
			if(!blnToolChainError && !blnNoPostProcess)
			{
				ossStrOut << strPostProcessCommand; // Add post-processor to tool chain.
				if(!strPostProcessOpts.empty())
				{
					ossStrOut << " " << strPostProcessOpts; // Add command-line options if the user supplied any.
				}

				if(blnNoPreProcess && blnNoGrounder && blnNoSolver && !blnGrounderSolver)
				{   // If nothing ran before the post-processor, pass it the first input file.
					ossStrOut << " -f \"" << vecInputFiles[0] << "\"";
				}
				else if(!blnNoSolver)
				{   // If we already ran a solver, run the post-processor on its output.
					ossStrOut << " -f \"" << strIntermediateSoFile << "\"";
				}
				else if(blnGrounderSolver)
				{   // If we already ran a combined grounder/solver, run the post-processor on its output.
					ossStrOut << " -f \"" << strIntermediateGrSoFile << "\"";
				}
				else if(!blnNoGrounder)
				{   // Odd, but if we already ran a grounder w/o solver, run the post-processor on its output.
					ossStrOut << " -f \"" << strIntermediateGrFile << "\"";
				}
				else if(!blnNoPreProcess)
				{   // Even odder, but if we ran a pre-processor w/o a grounder or solver, trust that the pre-processor's output is what we should be sending to the post-processor.
					ossStrOut << " -f \"" << strIntermediatePreFile << "\"";
				}
				else if(!blnNoTranslator)
				{   // Still odder, but if we already ran a translator (and just the translator), trust that the its output is what we should be sending to the post-processor.
					ossStrOut << " -f \"" << strIntermediateTransFile << "\"";
				}

				// Call the post-processor.
				strTempCommand = ossStrOut.str();
				intSystemResult = system(strTempCommand.c_str()); // Call the post-processor.
				if(WEXITSTATUS(intSystemResult) == AS2TRANSITION_FOUND_SOLUTIONS)
				{
					blnFoundSolutions = true; // as2transition found solutions.
				}
				ossStrOut.str("");
			}
			// If there's more potential runs, see if we should increment maxstep and continue.
			if(!blnToolChainError && blnQueryDefined && blnMaxstepDefined && intCurMaxstep < intMaxMaxstep && (!blnNoSolver || blnGrounderSolver))
			{
				// If we're supposed to, ask the user if they want to continue.
				if(blnInteractive && blnManualMaxstepRangeAdvance)
				{
					cout << endl << "Finished running query with maxstep=" << intCurMaxstep << "." << endl;
					cout << "Run again with maxstep=" << intCurMaxstep + 1 << " (y/n)? ";
					getline(cin, strTempString);
					if(strTempString[0] != 'y' && strTempString[0] != 'Y')
					{   // They said no, stop here.
						break;
					}
				}
				else if(blnFoundSolutions)
				{   // We're in auto continue mode and we just found solution(s), stop here.
					break;
				}
				intCurMaxstep++; // We've completed a run, increment maxstep and see if we need to do it again.
			}
			else
			{   // This wasn't a proper query in the first place (or maxstep wasn't ranged), only run the tool chain once.
				break;
			}
		} while(!blnToolChainError && blnQueryDefined && blnMaxstepDefined && intCurMaxstep <= intMaxMaxstep && (!blnNoSolver || blnGrounderSolver));
	}

    // If we're supposed to delete f2lp's intermediate files, do so now.
    if(!blnNoPreProcess && !blnKeepF2LPFiles)
    {
        ossStrOut << "rm .f2lp_input.fof .solver_input.lp";
        strTempCommand = ossStrOut.str();
        //intSystemResult = system(strTempCommand.c_str()); // Delete f2lp's intermediate files.
        ossStrOut.str("");
    }
    // If we're supposed to delete the intermediate files we created (& we made any), do so.
    if(!blnKeepIntermediateFiles && blnCreatedIntermediateFiles)
    {
        ossStrOut << "rm";
        if(!blnNoTranslator && (!blnNoPreProcess || !blnNoGrounder || !blnNoSolver || blnGrounderSolver || !blnNoPostProcess))
        {
            ossStrOut << " \"" << strIntermediateTransFile << "\"";
        }
        if(!blnNoPreProcess && (!blnNoGrounder || !blnNoSolver || blnGrounderSolver || !blnNoPostProcess))
        {
            ossStrOut << " \"" << strIntermediatePreFile << "\"";
        }
        if(!blnNoGrounder && (!blnNoSolver || !blnNoPostProcess))
        {
            ossStrOut << " \"" << strIntermediateGrFile << "\"";
        }
        if(!blnNoSolver && !blnNoPostProcess)
        {
            ossStrOut << " \"" << strIntermediateSoFile << "\"";
        }
        if(blnGrounderSolver && !blnNoPostProcess)
        {
            ossStrOut << " \"" << strIntermediateGrSoFile << "\"";
        }
        strTempCommand = ossStrOut.str();
        //intSystemResult = system(strTempCommand.c_str()); // Remove any intermediate files we made.
        ossStrOut.str("");
    }

    return 0;
}
