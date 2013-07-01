/** @file as2transition.cpp
 *  @brief Transforms answer sets from answer set solvers into CCalc-style models.
 *  @author Michael Casolary
 *  @date 03/2011
 *  @author Guoqiang Jin(02/2012)
 */

/* History:
 * v2.1 - remove the reductency of the subtimestamp
 * v2.0 - Now support subtime structure.
 * v1.8 - Now exits with code 100 if no solutions are found, 101 if solutions are found, 1 if an error occurs, or 0 if there's nothing to do.
 * v1.7.3 - Fixed a bug where an unknown solver's output would be (erroneously) flagged as not having solutions due to bad text processing.
 * v1.7.2 - Optimized solution display routine, fixed extra space in solutions with no "timeless" predicates output, fixed bug where a solution with only actions wouldn't display properly.
 * v1.7.1 - Fixed a bug where bad time stamps could appear with "timeless" predicates.
 * v1.7 - Overhauled predicate detection, enabled support for new rigid and h-style predicate constructs, added option to show negated predicates.
 * v1.6.1 - Fixed bug where a time step with all false predicates would not be displayed.
 * v1.6 - Changed name to as2transition, added auto-hiding of "contribution" predicates  (and option to show them anyway).
 * v1.5 - Added capability to read output from cmodels and smodels in addition to clasp (& family), along with rudimentary ability to try to read an unknown/unidentified solver's output. Reduced memory usage and optimized handling of multiple solutions.
 * v1.4.1 - Fixed a bug with the program failing to recognize predicates beginning with "x_" inside of eq-style predicates.
 * v1.4 - Handling of eq-style predicates implemented, boolean predicates simplified, actions separated from fluents, option to print out solutions one predicate per line added.
 * v1.3.5 - (Internal) Split TimeStepInfo class off to its own file, created Predicate, Constant, and StringUtils classes, switched to using makefile to build program.
 * v1.3.1 - Program now outputs solutions as soon as they are ready to output instead of waiting until all solutions have been processed.
 * v1.3 - Added check for "x_" h-style predicates, and hide them by default. Added option to show these predicates anyway.
 * v1.2 - Added option controlling whether h-style predicates are added to solutions as a whole element or if their inner predicate is extracted and added alone.
 * v1.1 - Added support for newer clasp versions outputting "[UN]SATISFIABLE" at the end of the answer section, changed program version to explicitly store major, minor, revision.
 * v1.01 - Added version info.
 * v1.00 - First working version.
 */

#include <fstream>
#include <iostream>
#include <istream> // This and ostream are explicitly here to allow input and output regardless of source.
#include <list>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <climits> // for PATH_MAX, INT_MIN
#include <cstdlib> // for exit()
#include <cstring>
#include <unistd.h> // for realpath()

#include "TimeStepInfo.h"
#include "Predicate.h"
#include "StringUtils.h"

using namespace std;

// Program version.
#define VERSION_MAJOR 2
#define VERSION_MINOR 1
#define VERSION_REV 0

// Prototypes.
void nice_exit(int, const char*);
TimeStepInfo* getSolutionTimeStep(vector<TimeStepInfo*>&, int, int);
TimeStepInfo* makeSolutionTimeStep(vector<TimeStepInfo*>&, int, int);
bool addNewElement(vector<string>&, string&);
Constant* makeConstant(vector<Constant*>&, string&, bool=false, bool=false, bool=false);
void markConstants(vector<Constant*>&, vector<string>&, vector<string>&, vector<string>&);
bool sendToOutput(ostream&, string&, const char *);
void processAndOutputAnswerSet(ostream&, size_t, vector<TimeStepInfo*>&, vector<Constant*>&, vector<string>&, vector<string>&, bool, bool, bool, bool, bool);

/// A defined "out of range" time step used to place any non-h-style predicates.
static const int MISC_STEP = INT_MIN + 1; // The convention is that any predicate that isn't an h-style predicate goes in this "miscellaneous" time step.
/// A defined "out of range" time step used to hold any h-style predicates that lack time stamps.
extern const int TIMELESS_STEP;

/**
 * A wrapper for exit() that can output an optional custom message before leaving.
 * Outputs message to stdout if exitCode is 0, stderr otherwise. Doesn't output anything if message is NULL.
 * @param exitCode - The exit code to pass to exit.
 * @param message - A message to output to standard out before exiting (terminating newline automatically added).
 */
void nice_exit(int exitCode, const char* message)
{
	if(exitCode != 0 && message != NULL)
	{
		cerr << message << endl;
	}
	if(exitCode == 0 && message != NULL)
	{
		cout << message << endl;
	}
	exit(exitCode);
}

/**
 * Finds the correct TimeStepInfo object that is part of the current solution
 * and holds information about the predicates at timeStep.
 * @param predicates - A vector of all TimeStepInfo objects in the current solution.
 * @param timeStep - The desired time stamp to retrieve.
 * @return A pointer to the desired TimeStepInfo object, or NULL if no such object is found.
 */
TimeStepInfo* getSolutionTimeStep(vector<TimeStepInfo*>& predicates, int mainTimeStep, int subTimeStep)
{
	TimeStepInfo *retVal = NULL;
	for(size_t i = 0; i < predicates.size(); i++)
	{
		if(predicates[i]->getMainTimeStep() == mainTimeStep
		   && predicates[i]->getSubTimeStep() == subTimeStep)
		{
			retVal = predicates[i];
		}
	}
	return retVal;
}

/**
 * Finds and returns the correct TimeStepInfo object for the given timeStep, or creates one if it doesn't already exist.
 * @param predicates - A vector of all TimeStepInfo objects the current solution.
 * @param timeStep - The desired time stamp to retrieve/create.
 * @return A pointer to the desired TimeStepInfo object. Exits if memory can't be allocated.
 */
TimeStepInfo* makeSolutionTimeStep(vector<TimeStepInfo*>& predicates, int timeStep1, int timeStep2)
{
	// Try to grab the time step from the existing data structure.
	TimeStepInfo *retVal = getSolutionTimeStep(predicates, timeStep1, timeStep2);
	// If we don't have any info on that time step yet, make one and add it.
	if(retVal == NULL)
	{
		retVal = new TimeStepInfo();
		if(retVal == NULL)
		{
			nice_exit(1, "Error: Out of memory.");
		}
		retVal->setTimeStep(timeStep1, timeStep2);
		// Put the new info in the right place so the predicates stay sorted by time step.
		vector<TimeStepInfo*>::iterator vIter = predicates.begin();
		while(vIter != predicates.end())
		{
			if((*vIter)->getMainTimeStep() < retVal->getMainTimeStep()
			   || ((*vIter)->getMainTimeStep() == retVal->getMainTimeStep()
				   && (*vIter)->getSubTimeStep() < retVal->getSubTimeStep()))
			{
				++vIter;
			}
			else
			{
				// We found where this time stamp belongs, break out of the loop.
				break;
			}
		}
		// We know where to put the new time stamp info now, do so.
		predicates.insert(vIter, retVal);
		retVal = getSolutionTimeStep(predicates, timeStep1, timeStep2); // Grab it again just to be sure we got the right pointer.
	}
	return retVal;
}

/**
 * Checks the contents of vec for value, and adds it alphabetically if it isn't found.
 * @param vec - A reference to the vector to manipulate.
 * @param value - The string to try to add to vec.
 * @return True if value got added, false if it was already there.
 */
bool addNewElement(vector<string> &vec, string &value)
{
	bool retVal = false; // Start pessimistic.
	int compareVal = 0;
	vector<string>::iterator vIter = vec.begin();
	vector<string>::iterator vIterEnd = vec.end();
	while(vIter != vIterEnd)
	{
		compareVal = (*vIter).compare(value);
		if(compareVal < 0)
		{	// Too early in the vector, move to next element.
			++vIter;
		}
		else if(compareVal == 0)
		{	// There's already a match in the vector, pop out.
			break;
		}
		else
		{	// Just arrived at the right spot to insert.
			vec.insert(vIter, value);
			retVal = true;
			break;
		}
	}
	if(vIter == vIterEnd)
	{	// We made it through the whole vector without finding a place to add the element, tack it on the end.
		vec.push_back(value);
		retVal = true;
	}
	return retVal;
}

/**
 * Searches through constants for one of the name constName, returning a pointer to it if it exists, and creating one if it doesn't yet.
 * Places constants in the vector in alphabetical order.
 * @param constants - A vector of Constant objects.
 * @param constName - The base name of the constant to look for or create.
 * @param isAction - An optional parameter specifying, if the constant needs to be created, whether or not it's an action. Defaults to false.
 * @param isBoolean - An optional parameter specifying, if the constant needs to be created, whether or not it has a boolean domain. Defaults to false.
 * @param isRigid - An optional parameter specifying, if the constant needs to be created, whether or not it is rigid. Defaults to false.
 * @return A pointer to the found or created Constant object, or NULL if something goes wrong.
 */
Constant* makeConstant(vector<Constant*> &constants, string &constName, bool isAction, bool isBoolean, bool isRigid)
{
	Constant *retVal = NULL;
	vector<Constant*>::iterator vIter = constants.begin();
	vector<Constant*>::iterator vIterEnd = constants.end();
	while(vIter != vIterEnd)
	{
		if((*vIter) != NULL)
		{
			if((*vIter)->getName().compare(constName) == 0)
			{	// Found an existing match, return that.
				retVal = (*vIter);
				break;
			}
			else if((*vIter)->getName().compare(constName) > 0)
			{ 	// Found where the new constant needs to go, insert it.
				Constant *tempConstant = new Constant(constName, isAction, isBoolean, isRigid);
				constants.insert(vIter, tempConstant);
				retVal = tempConstant;
				break;
			}
		}
		++vIter;
	}
	if(vIter == vIterEnd)
	{	// We made it through the whole vector without finding a place to add the Constant, tack it on the end.
		Constant *tempConstant = new Constant(constName, isAction, isBoolean, isRigid);
		constants.push_back(tempConstant);
		retVal = tempConstant;
	}
	return retVal;
}

/**
 * Enumerates through the base constant names found thus far, setting the appropriate flags for any constants whose base names match those in actions or booleans.
 * @param constants - The vector of base constants to check.
 * @param actions - A list of base constant names that correspond to action constants.
 * @param booleans - A list of base constant names that correspond to constants with boolean domains.
 * @param rigids - A list of base constant names that correspond to rigid constants.
 */
void markConstants(vector<Constant*> &constants, vector<string> &actions, vector<string> &booleans, vector<string> &rigids)
{
	size_t i, j;
	// Go through each constant and compare its name against the names in actions and booleans.
	for(i = 0; i < constants.size(); i++)
	{
		// Check it against all actions, if there's a match set the appropriate flag.
		for(j = 0; j < actions.size(); j++)
		{
			if(constants[i]->getName().compare(actions[j]) == 0)
			{
				constants[i]->setBlnIsAction(true);
				break;
			}
		}
		// Now check against the booleans, setting the predicate's flag if a match is found.
		for(j = 0; j < booleans.size(); j++)
		{
			if(constants[i]->getName().compare(booleans[j]) == 0)
			{
				constants[i]->setBlnIsBoolean(true);
				break;
			}
		}
		// Last, check for rigid constants, setting the predicate's flag when a match is found.
		for(j = 0; j < rigids.size(); j++)
		{
			if(constants[i]->getName().compare(rigids[j]) == 0)
			{
				constants[i]->setBlnIsRigid(true);
				break;
			}
		}
	}
}

/**
 * If output isn't empty, sends it to ostOut and appends appendText to the end of the output.
 * @param ostOut - A reference to the ostream obect to use.
 * @param output - The string to output.
 * @param appendText - The characters/string (if any) that should come after output. Can be used to output a newline or something similar.
 * @return True if anything was output to ostOut, false otherwise.
 */
bool sendToOutput(ostream& ostOut, string& output, const char *appendText)
{
	bool retVal = false; // Start pessimistic.
	if(output != "")
	{	// If we actually got something to output, then put it out there.
		ostOut << output << appendText;
		retVal = true;
	}
	return retVal;
}

/**
 * Given data structures containing information about a partially-processed answer set, performs final transformations and processing and outputs the result as a CCalc-style solution.
 * @param ostOut - The ostream used for outputting information, be that to stdout, a file, or elsewhere.
 * @param sztSolutionNum - Which solution this is (starts at #1).
 * @param vecPredicates - A vector of the predicates found in this answer set, arranged by time step.
 * @param vecConstants - A vector containing base (CCalc) constant names.
 * @param vecActionPredicates - A vector containing the base names of h-style predicates that count as actions.
 * @param vecBooleanPredicates - A vector containing the base names of h-style, eq-style predicates that have boolean domains.
 * @param vecRigidPredicates - A vector containing the base names of h-style predicates that count as rigid constants.
 * @param blnAllPredicates - If true, all predicates will be displayed (vs. just displaying the ones that actually make up part of the transition system).
 * @param blnOnePredicatePerLine - If true, each predicate should be output on its own separate line (instead of bundled together by time step).
 * @param blnSeparateActions - If true, predicates that count as actions will be displayed in between the time steps of those that don't.
 * @param blnStripHPredicates - If true, pulls the "something" out of each h-style "h(something,time)" predicate and displays it without the extra h-style wrapper.
 * @param blnTransformEQPredicates - If true, transforms h-style eq-style "h(eql(something(args),value),time)" predicates into "something(args)=value" when displayed.
 */
void processAndOutputAnswerSet(ostream &ostOut, size_t sztSolutionNum, vector<TimeStepInfo*> &vecPredicates, vector<Constant*> &vecConstants, vector<string> &vecActionPredicates, vector<string> &vecBooleanPredicates, vector<string> &vecRigidPredicates, bool blnAllPredicates, bool blnOnePredicatePerLine, bool blnSeparateActions, bool blnStripHPredicates, bool blnTransformEQPredicates)
{
	bool blnTempOutputAnything = false;
	ostringstream ossTempOut(""); // Holds output for (optional) actions and misc sections.
	string tempOutput = "", strTempPredEnd = "";
	TimeStepInfo *tsiTempInfo;
	// Output the solution, formatted close to how CCalc might do it.
	// Everything has been sorted as we go, so we can just mow through our data structure.

	// Figure out what kind of post-predicate whitespace to output in the solutions.
	if(blnOnePredicatePerLine)
	{	// If we're in "one predicate per line" mode, add a newline after each predicate.
		strTempPredEnd = "\n";
	}
	else
	{	// Otherwise, just add space to the current line.
		strTempPredEnd = "  ";
	}

	// Some preprocessing first: make sure all action and boolean predicates are flagged as such.
	markConstants(vecConstants, vecActionPredicates, vecBooleanPredicates, vecRigidPredicates);
	// Output solution number.
	ostOut << "Solution " << sztSolutionNum << ":" << endl << endl;
	// If it exists, find the "timeless" step and list its elements first:
	tsiTempInfo = getSolutionTimeStep(vecPredicates, TIMELESS_STEP, TIMELESS_STEP);
	if(tsiTempInfo != NULL)
	{
		list<Predicate*>::const_iterator lIter = tsiTempInfo->getPredicatesBegin();
		list<Predicate*>::const_iterator lIterEnd = tsiTempInfo->getPredicatesEnd();
		tempOutput = "";
		blnTempOutputAnything = false;
		// Output each timeless predicate.
		while(lIter != lIterEnd)
		{
			tempOutput = (*lIter)->toPredicateString(blnStripHPredicates,blnTransformEQPredicates);
			if(sendToOutput(ostOut, tempOutput, strTempPredEnd.c_str()))
			{	// Remember if we ever output anything.
				blnTempOutputAnything = true;
			}
			++lIter;
		}
		// Put some space between the timeless predicates and the first time step if any timeless predicates were sent to output.
		if(blnTempOutputAnything)
		{
			ostOut << endl << endl;
		}
	}
	// Go through the other time steps, outputting them in order.
	for(size_t j = 0; j < vecPredicates.size(); j++)
	{	// Make sure we don't accidentally output the "misc" time step yet, and that we don't accidentally output the "timeless" step again.
		if(vecPredicates[j]->getMainTimeStep() != MISC_STEP && vecPredicates[j]->getMainTimeStep() != TIMELESS_STEP)// && vecPredicates[j]->getSubTimeStep() != 0)
		{
			// Output time step header and appropriate trailing whitespace.
			int subStampHere = vecPredicates[j]->getSubTimeStep();
			if (subStampHere != 0)
			{
				ostOut << vecPredicates[j]->getMainTimeStep();
				if (subStampHere != INT_MIN)
					ostOut << "." << vecPredicates[j]->getSubTimeStep();
				ostOut << ":" << strTempPredEnd;
			}

			list<Predicate*>::const_iterator lIter = vecPredicates[j]->getPredicatesBegin();
			list<Predicate*>::const_iterator lIterEnd = vecPredicates[j]->getPredicatesEnd();
			tempOutput = "";
			ossTempOut.str(""); // Reset the actions buffer in case it's needed.
			blnTempOutputAnything = false;
			// Output each predicate that was true at this time step.
			while(lIter != lIterEnd)
			{
				tempOutput = (*lIter)->toPredicateString(blnStripHPredicates,blnTransformEQPredicates);
				// Unless we're supposed to show actions with fluents, skip over any actions for now.
				if(!blnSeparateActions || !(*lIter)->getBlnIsAction())
				{	// Output the predicate and appropriate trailing whitespace.
					if (subStampHere != 0)
						sendToOutput(ostOut, tempOutput, strTempPredEnd.c_str());
				}
				else
				{	// This is an action predicate, save it to the actions buffer for later output.
					if(sendToOutput(ossTempOut, tempOutput, strTempPredEnd.c_str()))
					{
						blnTempOutputAnything = true;
					}
				}
				++lIter;
			}
			if (subStampHere != 0)
				ostOut << endl << endl;
			// Now output the actions if we:
			// a) are supposed to display actions separately from fluents, and
			// b) have actions to list (no use taking up space for a category that is empty).
			if(blnSeparateActions && blnTempOutputAnything && vecActionPredicates.size() > 0)
			{
				if (subStampHere != INT_MIN)
					ostOut << "  SUB-ACTIONS(" << subStampHere << "):" << strTempPredEnd;
				else
					ostOut << "  ACTIONS:" << strTempPredEnd;
				ostOut << ossTempOut.str();
				ostOut << endl << endl;
			}
		}
	}
	// If we're supposed to output it, find the "miscellaneous" time step and output all predicates stored there.
	if(blnAllPredicates)
	{
		tsiTempInfo = getSolutionTimeStep(vecPredicates, MISC_STEP, MISC_STEP);
		if(tsiTempInfo != NULL)
		{
			list<Predicate*>::const_iterator lIter = tsiTempInfo->getPredicatesBegin();
			list<Predicate*>::const_iterator lIterEnd = tsiTempInfo->getPredicatesEnd();
			tempOutput = "";
			ossTempOut.str(""); // Reset the misc buffer in case it's needed.
			blnTempOutputAnything = false;
			// Output each predicate that was true at this time step.
			while(lIter != lIterEnd)
			{
				tempOutput = (*lIter)->toPredicateString(blnStripHPredicates,blnTransformEQPredicates);
				// Save the predicate and appropriate trailing whitespace to the misc buffer.
				if(sendToOutput(ossTempOut, tempOutput, strTempPredEnd.c_str()))
				{
					blnTempOutputAnything = true;
				}
				++lIter;
			}
			// Only output the misc time step if there is anything to display.
			if(blnTempOutputAnything)
			{
				ostOut << "Other:" << strTempPredEnd;
				ostOut << ossTempOut.str();
				ostOut << endl << endl;
			}
		}
	}
	// Done with this solution, add an extra separating end line.
	ostOut << endl;
}

int main(int argc, char** argv)
{
	ifstream ifsFileIn;
	ofstream ofsFileOut;
	istream istIn(cin.rdbuf()); // Gets given a different buffer later.
	ostream ostOut(cout.rdbuf()); // Gets given a different buffer later.
	string strEXEName = "";
	string strInFile = "", strOutFile = "";
	ostringstream ossMetricsOut(""); // Records any metrics generated or found in input, to output after everything else.
	int intExitCode = 0; // What to exit with on successful program completion. 100 = No solutions, 101 = Solution(s) found.

	// The codes used to tell calling programs / the shell if we found solutions or not.
	enum ExitCodes { EXIT_NO_SOLUTIONS = 100, EXIT_SOLUTIONS = 101 };

	bool blnTemp; // Used for extracting predicate information.
	int intMainTemp; // Ditto.
	int intSubTemp;
	string strTempString = "", strTempInput = "", strTempPredicate = "";
	size_t sztTempPos = 0, sztFirstPos = 0;
	TimeStepInfo *tsiTempInfo = NULL; // Used to access & modify time step information.

	enum SolverType {SLVR_CLASP, SLVR_CMODELS, SLVR_SMODELS, SLVR_UNKNOWN}; // Tracks the best guess as to which solver's output is being processed.
	enum SolverType enmSolverType = SLVR_UNKNOWN; // Start assuming the solver is unknown.

	bool blnInAnswerSet = false; // Tracks if we're currently processing an answer set.
	bool blnEndOfAnswerSets = false; // If true, we believe there are no more answer sets to process (changes how remaining input is handled).

	bool blnAllPredicates = false; // If true, we'll show everything that comes out of the solver.
	bool blnOnePredicatePerLine = false; // If true, each predicate will appear on its own line.
	bool blnSeparateActions = true; // If false, will stop actions from being displayed separately from fluents.
	bool blnStripHPredicates = false; // If true, we'll display h(x(y,z),0) as x(y,z) in output.
	bool blnShowContribPredicates = false; // If true, we'll display h-style predicates whose inner predicate is "contribution" (usually hidden as an "internal" thing).
	bool blnShowNegPredicates = false; // If true, predicates of the form -something will be shown if their positive form is set to show as well.
	bool blnShowXPredicates = false; // If true, we'll display h-style predicates whose inner predicate starts with "x_" (e.g., "h(x_contrib(...),0)").
	bool blnTransformEQPredicates = true; // If true, turn h(eq(p(x),v),t) predicates into p(x)=v in the output (CCalc style for multi-valued), and turn h(eq(p(x)=true),t) into p(x) (CCalc style for boolean).

	size_t sztSolutionNum = 0; // The number of the solution (answer set) currently being processed. 1-based (first solution is #1).

	// Vector of TimeStepInfo object pointers that will hold all the predicates true at given time points.
	vector<TimeStepInfo*> vecPredicates;

	// Data structures to hold information about types of predicates.
	vector<string> vecActionPredicates; // Base names of any h-style predicates that count as actions.
	vector<string> vecBooleanPredicates; // Base names of any h-style predicates that have boolean domains.
	vector<string> vecRigidPredicates; // Base names of any h-style predicates that count as rigid constants.
	vector<Constant*> vecConstants; // Base constant names used to connect predicates to certain "universal" properties.

	int max_k = 0; // the max_k.... used to output....
	// Get the name this executable was called by (w/o the path, just the file name).
	if(argc > 0)
	{
		strEXEName = argv[0];
		sztTempPos = strEXEName.find_last_of('/');
		if(sztTempPos != string::npos)
		{
			strEXEName = strEXEName.substr(sztTempPos + 1); // Strip off any path to this executable.
		}
	}

	bool blnBadArgs = false; // Set to true if we get an unexpected or malformed command line argument.
	if(argc > 1)
	{
		for(int i = 1; i < argc; i++)
		{
			if(strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0)
			{	// They want to see all positive predicates, let's show them all positive predicates.
				blnAllPredicates = true;
			}
			else if(strcmp(argv[i], "-A") == 0 || strcmp(argv[i], "--ALL") == 0)
			{	// They want to see all predicates (positive and otherwise), unleash the hordes.
				blnAllPredicates = true;
				blnShowNegPredicates = true;
			}
			else if(strcmp(argv[i], "-contrib") == 0 || strcmp(argv[i], "--contrib-pred") == 0)
			{   // We're supposed to show the contribution predicates, do so.
				blnShowContribPredicates = true;
			}
			else if(strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--eq") == 0)
			{	// They want to stop us from auto-transforming eq predicates into CCalc-style representation.
				blnTransformEQPredicates = false;
			}
			else if(strcmp(argv[i], "-f") == 0)
			{	// Input file being specified.  Verify they actually gave us a file argument (and they haven't already given this option).
				i++;
				if(i < argc && strInFile == "") {
					strInFile = argv[i];
				} else {
					blnBadArgs = true;
				}
			}
			else if(strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--line") == 0)
			{	// They want us to output each predicate on its own line.
				blnOnePredicatePerLine = true;
			}
			else if(strcmp(argv[i], "-na") == 0 || strcmp(argv[i], "--no-actions") == 0)
			{	// They don't want actions grouped separately from fluents.
				blnSeparateActions = false;
			}
			else if(strcmp(argv[i], "-neg") == 0 || strcmp(argv[i], "--negated") == 0)
			{	// They want to see negated predicates as well as normal ones.
				blnShowNegPredicates = false;
			}
			else if(strcmp(argv[i], "-o") == 0)
			{	// Output file being specified.  Verify they actually gave us a file argument (and they haven't already given this option).
				i++;
				if(i < argc && strOutFile == "") {
					strOutFile = argv[i];
				} else {
					blnBadArgs = true;
				}
			}
			else if(strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--strip") == 0)
			{	// They want to extract and display the inner predicates from h-style predicates.
				blnStripHPredicates = true;
			}
			else if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
			{	// Show version information and quit.
				cout << strEXEName << " version " << VERSION_MAJOR;
				cout << "." << VERSION_MINOR;
				if(VERSION_REV > 0) { cout << "." << VERSION_REV; }
				cout << endl;
				nice_exit(0, NULL);
			}
			else if(strcmp(argv[i], "-x") == 0 || strcmp(argv[i], "--x-pred") == 0)
			{	// They want to see the intermediate "x_..." h-style predicates, so show them.
				blnShowXPredicates = true;
			}
			else
			{	// Unrecognized option (or they asked for help), set the bad args flag so usage is shown.
				blnBadArgs = true;
			}
			// If the user needs help, provide basic usage info and then exit.
			if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-?") == 0 || blnBadArgs)
			{
				cout << "Usage: " << strEXEName << " [OPTIONS] [-f IN_FILE] [-o OUT_FILE]" << endl
				          << "Transforms answer sets from answer set solvers into CCalc-style model lists." << endl
						  << "If given a value for IN_FILE, will parse that file, otherwise" << endl
						  << "will parse standard in (to support piping input)." << endl
						  << "If given a value for OUT_FILE, will output results to OUT_FILE," << endl
						  << "otherwise will output to standard out." << endl << endl
						  << "  -a  (or --all) causes " << strEXEName << " to display all positive" << endl
						  << "      predicates returned by the solver (vs. just the CCalc-equivalent ones)." << endl
						  << "  -A  (or --ALL) displays all predicates, positive and negative." << endl
						  << "  -e  (or --eq) stops " << strEXEName << " from transforming h-style" << endl
						  << "      eq or eql predicates (e.g., h(eq(p(x),v),t)) into CCalc-style " << endl
						  << "      representations (e.g., p(x)=v)." << endl
						  << "  -contrib (or --contrib-pred) will show h-style \"contribution\" and " << endl
						  << "      \"x_contrib\" predicates (usually these intermediate additive " << endl
						  << "      predicates are hidden)." << endl
						  << "  -l  (or --line) prints out each predicate on a separate line, with" << endl
						  << "      solution and time step headers also getting their own lines." << endl
						  << "  -na (or --no-actions) stops " << strEXEName << " from displaying" << endl
						  << "      action predicates separately." << endl
						  << "  -neg (or --negated) shows negated predicates (\"-x(y,z)\") alongside their" << endl
						  << "      normal counterparts (\"x(y,z)\")." << endl
						  << "  -s  (or --strip) will extract the inner predicate from h-style predicates," << endl
						  << "      displaying h(x(y,z),0) as x(y,z)." << endl
						  << "  -x  (or --x-pred) will show h-style predicates that begin with \"x_\"" << endl
						  << "      (these are usually additional intermediate predicates created during" << endl
						  << "      translation, and are hidden by default)." << endl
						  << "  --help shows this usage message." << endl
						  << "  -v  (or --version) outputs version information." << endl << endl
						  << "  Example: gringo some_asp_file.lp | clasp | " << strEXEName << endl
						  << "           would pass the answer sets generated by clasp directly" << endl
						  << "           to " << strEXEName << ", which would output the models to standard out." << endl
						  << "  Example: " << strEXEName << " -f answer_sets.txt -o models.txt" << endl
						  << "           would process the answer_sets.txt file and output the" << endl
						  << "           results to the file models.txt." << endl;
				nice_exit(0, NULL);
			}
		}
	}

	// If an input or output file was given, make sure we have the full expanded path to it.
	char chrarrFullPath[PATH_MAX+1];
	char *chrptrPath = NULL;
	if(strInFile != "")
	{
		chrptrPath = realpath(strInFile.c_str(), chrarrFullPath);
		if(chrptrPath == NULL)
		{
			strTempString = "Error: Could not locate input file \"";
			strTempString += strInFile;
			strTempString += "\".";
			nice_exit(1, strTempString.c_str());
		}
		else
		{
			strInFile = chrarrFullPath;
		}
	}
	if(strOutFile != "")
	{
		// Since the output file may not exist yet, strip it and see if the rest of the location is good.
		sztTempPos = strOutFile.find_last_of('/');
		if(sztTempPos == string::npos)
		{
			strTempString = "."; // No slashes, so the directory of the output file is the current one.
		}
		else
		{
			strTempString = strOutFile.substr(0, sztTempPos); // There were slashes, so grab the directory path w/o the file name.
		}
		chrptrPath = realpath(strTempString.c_str(), chrarrFullPath);
		if(chrptrPath == NULL)
		{
			strTempString = "Error: Invalid location for output file \"";
			strTempString += strOutFile;
			strTempString += "\".";
			nice_exit(1, strTempString.c_str());
		}
		else
		{
			strTempString = chrarrFullPath;
			// Add the file name back on.
			if(strTempString.length() > 0 && strTempString[strTempString.length()-1] != '/')
			{	// Add back a forward slash if there isn't one already.
				strTempString += "/";
			}
			sztTempPos = strOutFile.find_last_of('/');
			if(sztTempPos == string::npos)
			{
				strTempString += strOutFile; // No slashes, just add on the file name.
			}
			else
			{
				strTempString += strOutFile.substr(sztTempPos+1); // Slashes, add on file name
			}
			strOutFile = strTempString;
		}
	}

	// Now we have the input & output files (if given), let's process the input!

	// Figure out which input source we'll be using.
	if(strInFile != "")
	{
		ifsFileIn.open(strInFile.c_str());
		if(!ifsFileIn)
		{
			strTempString = "Error: Unable to open input file \"";
			strTempString += strInFile;
			strTempString += "\".";
			nice_exit(1, strTempString.c_str());
		}
		istIn.rdbuf(ifsFileIn.rdbuf());
	}
	else
	{
		istIn.rdbuf(cin.rdbuf());
	}

	// Figure out which output source we'll be using.
	if(strOutFile != "")
	{
		ofsFileOut.open(strOutFile.c_str());
		if(!ofsFileOut)
		{
			strTempString = "Error: Unable to open output file \"";
			strTempString += strOutFile;
			strTempString += "\".";
			nice_exit(1, strTempString.c_str());
		}
		ostOut.rdbuf(ofsFileOut.rdbuf());
	}
	else
	{
		ostOut.rdbuf(cout.rdbuf());
	}

	// In a loop, go looking for an answer set from the input.
	while(getline(istIn, strTempInput))
	{
		// If we aren't sure which solver's output we're processing, check for hallmarks of certain specific answer set solvers.
		// If we can verify (or guess) which solver's output we're processing, remember that value for later reference.
		if(enmSolverType == SLVR_UNKNOWN)
		{
			if(strTempInput.find("clasp") != string::npos
			   || strTempInput.find("iclingo") != string::npos)
			{	// clasp identified itself, set that we're processing clasp output.
				enmSolverType = SLVR_CLASP;
			}
			else if(strTempInput.find("cmodels") != string::npos)
			{	// cmodels identified itself, set that we're processing cmodels output.
				enmSolverType = SLVR_CMODELS;
			}
			else if(strTempInput.find("smodels") != string::npos)
			{	// smodels identified itself, set that we're processing smodels output.
				enmSolverType = SLVR_SMODELS;
			}
		}
		// Based on which solver's output we think we're processing, try to find out if we've found an answer set or reached the end of the answer sets.
		// No need to go looking for answer sets if we already know there aren't any more.
		if(!blnEndOfAnswerSets)
		{
			if(enmSolverType == SLVR_CLASP)
			{	// clasp either outputs a line starting with "Models" or "[UN]SATISFIABLE" at the end of the answer sets.
				sztFirstPos = strTempInput.find("Models");
				if(sztFirstPos == string::npos)
				{	// Didn't find "Models", try finding "[UN]SATISFIABLE".
					sztFirstPos = strTempInput.find("SATISFIABLE");
				}
				if(sztFirstPos != string::npos)
				{	// End of answer sets
					blnEndOfAnswerSets = true;
				}
				// Don't start looking for answer sets if we've already established there are no more.
				if(!blnEndOfAnswerSets)
				{	// clasp needs no preprocessing for answer sets, answer sets are headered with "Answer: " followed by a number.
					sztFirstPos = strTempInput.find("Answer:");
					if(sztFirstPos != string::npos)
					{	// Found the header for an answer set, make sure that we have a line following this and start processing it.
						if(getline(istIn, strTempInput))
						{
							blnInAnswerSet = true;
						}
					}
				}
			}
			else if(enmSolverType == SLVR_CMODELS)
			{	// cmodels ends its section of answer sets with "No Answer Set", a "Number of loops" report, or just the end of input (which we can't check for here).
				sztFirstPos = strTempInput.find("No Answer Set");
				if(sztFirstPos != string::npos)
				{	// No solutions, by default we're at the end of the answer sets.
					blnEndOfAnswerSets = true;
				}
				sztFirstPos = strTempInput.find("Number of loops");
				if(sztFirstPos != string::npos)
				{	// cmodels just spat out what little info it gives, rewind that back into input and flag the end of answer sets.
					istIn.putback('\n'); // Put back implied newline.
					for(int i = (int)strTempInput.length() - 1; i >= 0; i--)
					{
						istIn.putback(strTempInput[i]);
					}
					blnEndOfAnswerSets = true;
				}
				// Don't start looking for answer sets if we've already established there are no more.
				if(!blnEndOfAnswerSets)
				{	// cmodels gives each answer set the header "Answer: " and a number, and prepends each answer set with "Answer set: "
					sztFirstPos = strTempInput.find("Answer:");
					if(sztFirstPos != string::npos)
					{	// Found the header for an answer set, make sure that we have a line following this and start processing it.
						if(getline(istIn, strTempInput))
						{
							sztFirstPos = strTempInput.find("Answer set:");
							if(sztFirstPos != string::npos)
							{
								strTempInput = strTempInput.substr(sztFirstPos + strlen("Answer set:")); // Remove the fluff header from the answer set line.
								blnInAnswerSet = true;
							}
						}
					}
				}
			}
			else if(enmSolverType == SLVR_SMODELS)
			{	// smodels ends its answer set section with either "True" or "False".
				sztFirstPos = strTempInput.find("True");
				if(sztFirstPos == string::npos)
				{	// Didn't find "True", try finding "False".
					sztFirstPos = strTempInput.find("False");
				}
				if(sztFirstPos != string::npos)
				{
					blnEndOfAnswerSets = true;
				}
				// Don't start looking for answer sets if we've already established there are no more.
				if(!blnEndOfAnswerSets)
				{	// smodels headers each answer set with "Answer: " and a number, and the answer set itself starts with "Stable Model:"
					sztFirstPos = strTempInput.find("Answer:");
					if(sztFirstPos != string::npos)
					{	// Found the header for an answer set, make sure that we have a line following this and start processing it.
						if(getline(istIn, strTempInput))
						{
							sztFirstPos = strTempInput.find("Stable Model:");
							if(sztFirstPos != string::npos)
							{
								strTempInput = strTempInput.substr(sztFirstPos + strlen("Stable Model:")); // Remove the fluff header from the answer set line.
								blnInAnswerSet = true;
							}
						}
					}
				}
			}
			else
			{	// Solver unknown, try to guess at when an answer set starts and when the answer sets are done.
				// Guessing approach for end of answer set section: any of the known ways the other solvers end their answer set sections, or end of input (which we don't check for here).
				// First, try finding "Models" (old clasp's way of ending the section).
				sztFirstPos = strTempInput.find("Models");
				if(sztFirstPos == string::npos)
				{	// Nothing yet, try finding "[UN]SATISFIABLE" (new clasp's method).
					sztFirstPos = strTempInput.find("SATISFIABLE");
				}
				if(sztFirstPos == string::npos)
				{	// Nothing yet, try finding "No Answer Set" (cmodels's method if there aren't any answer sets).
					sztFirstPos = strTempInput.find("No Answer Set");
				}
				if(sztFirstPos == string::npos)
				{	// Nothing yet, try finding "Number of loops" (one way cmodels ends its answer set section).
					sztFirstPos = strTempInput.find("Number of loops");
				}
				if(sztFirstPos == string::npos)
				{	// Nothing yet, try finding "True" (one possibility from smodels).
					sztFirstPos = strTempInput.find("True");
				}
				if(sztFirstPos == string::npos)
				{	// Nothing yet, try finding "False" (the other possibility from smodels).
					sztFirstPos = strTempInput.find("False");
				}
				if(sztFirstPos != string::npos)
				{	// Probably found the end of the answer sets one way or another, flag it.
					blnEndOfAnswerSets = true;
				}
				// Don't start looking for answer sets if we've already established there are no more.
				if(!blnEndOfAnswerSets)
				{
					// Answer set guessing approach: something like "Answer:" or containing "Model" as the header the line before the answer set, possibly with the answer set line beginning with some fluff that ends in a colon (:).
					sztFirstPos = strTempInput.find("Answer:");
					if(sztFirstPos == string::npos)
					{	// Didn't find "Answer:", try finding "Model" (but not "Models").
						sztFirstPos = strTempInput.find("Model");
						if(sztFirstPos != string::npos && sztFirstPos == strTempInput.find("Models"))
						{	// Found "Models" (probably some kind of statistics thing), most likely a false alarm.
							sztFirstPos = string::npos;
						}
					}
					if(sztFirstPos != string::npos)
					{	// Found a possible header for an answer set, make sure that we have a line following this and try processing it.
						if(getline(istIn, strTempInput))
						{	// Try to eliminate beginning fluff by eliminating anything that ends with a colon.
							sztFirstPos = strTempInput.find(":");
							if(sztFirstPos != string::npos)
							{
								strTempInput = strTempInput.substr(sztFirstPos + 1); // Try to remove any fluff header from the answer set line.
							}
							blnInAnswerSet = true;
						}
					}
				}
			}
		}
		// If an answer set was found, process it.
		if(blnInAnswerSet && !blnEndOfAnswerSets)
		{	// If we found the start of an answer set, clear out data structures in preparation for processing.
			for(size_t i = 0; i < vecPredicates.size(); i++)
			{
				delete vecPredicates[i];
				vecPredicates.clear();
			}
			vecActionPredicates.clear();
			vecBooleanPredicates.clear();
			vecRigidPredicates.clear();
			vecConstants.clear();
			sztSolutionNum++; // Increment the solution count to the current number.
			// Now run through the answer set and grab all the predicates, putting them in their appropriate time stamp.
			strTempInput = StringUtils::trimWhitespace(strTempInput);
			do
			{
				// Get the next predicate, extract its info.
				sztFirstPos = StringUtils::findFirstWhitespace(strTempInput);
				strTempPredicate = strTempInput.substr(0, sztFirstPos);
				if(Predicate::extractHPredicateInfo(strTempPredicate, blnTemp, strTempString, intMainTemp, intSubTemp)
				   && ((max_k == 0) || (max_k > 0 && intSubTemp != max_k + 1)))
				{
					// It's an h-style predicate. Find which time step it belongs to, and make sure we have one of those.
					tsiTempInfo = makeSolutionTimeStep(vecPredicates, intMainTemp, intSubTemp);
					// Only add this predicate if it's a normal, positive predicate or we're supposed to:
					// show all predicates,
					// show "x_" predicates and it's one of those,
					// show "contribution" predicates and it's one of those, or
					// show negative predicates and it's a kind that would be shown if it were positive.
					if((blnAllPredicates && (!blnTemp || blnShowNegPredicates)) ||
					  (blnShowXPredicates && Predicate::isXHPredicate(strTempPredicate) && (!blnTemp || blnShowNegPredicates)) ||
					  (blnShowContribPredicates && Predicate::isContribHPredicate(strTempPredicate) && (!blnTemp || blnShowNegPredicates)) ||
					  (!Predicate::isXHPredicate(strTempPredicate) && !Predicate::isContribHPredicate(strTempPredicate) && (!blnTemp || blnShowNegPredicates)))
					{	// First figure out what constant this predicate represents and get/create a Constant object to represent that.
						size_t sztTempBaseNameStart, sztTempBaseNameEnd;
						// Try to find and bypass a eq-style predicate header (if any).
						sztTempBaseNameStart = strTempString.find("eq(");
						if(sztTempBaseNameStart != 0)
						{
							sztTempBaseNameStart = strTempString.find("eql(");
							if(sztTempBaseNameStart != 0)
							{
								sztTempBaseNameStart = 0; // No "eq(" or "eql(", move on as normal.
							}
							else
							{
								sztTempBaseNameStart += 4; // Skip the "eql(".
							}
						}
						else
						{
							sztTempBaseNameStart += 3; // Skip the "eq(".
						}
						sztTempBaseNameEnd = strTempString.find("(", sztTempBaseNameStart); // Try finding the start of an argument list.
						if(sztTempBaseNameEnd == string::npos)
						{	// If that fails, this inner predicate has no arguments, just grab its name.
							sztTempBaseNameEnd = strTempString.find(",", sztTempBaseNameStart);
							if(sztTempBaseNameEnd == string::npos)
							{   // If there wasn't a comma or an open paren, assume the name goes until a close paren.
								sztTempBaseNameEnd = strTempString.find(")", sztTempBaseNameStart);
							}
						}
						string strTempBaseName = strTempString.substr(sztTempBaseNameStart, sztTempBaseNameEnd - sztTempBaseNameStart);
						Constant *cnstTempConstant = makeConstant(vecConstants, strTempBaseName);
						// Now that we know we have info for this time step, add the predicate.
						if(blnStripHPredicates)
						{	// If they only wanted the inner predicate, add that.
							tsiTempInfo->addPredicate(strTempString, cnstTempConstant);
						}
						else
						{	// Otherwise, add the whole thing.
							tsiTempInfo->addPredicate(strTempPredicate, cnstTempConstant);
						}
					}
				}
				else
				{
					// It's not an h-style predicate, so put it in the "other" category.
					tsiTempInfo = makeSolutionTimeStep(vecPredicates, MISC_STEP, MISC_STEP);
					// Now that we know we have a good TimeStepInfo, add our predicate to it.
					tsiTempInfo->addPredicate(strTempPredicate);
					// Is it the definition of an action constant?
					if(strTempPredicate.find("action(") == 0
					   || strTempPredicate.find("actionConstant(") == 0)
					{	// If so, remember the base name for later.
						size_t sztTempNameStart = strTempPredicate.find("(") + 1;
						size_t sztTempNameEnd = strTempPredicate.find("(", sztTempNameStart); // Try finding the start of an argument list.
						if(sztTempNameEnd == string::npos)
						{	// If that fails, this action has no arguments, just grab its name.
							sztTempNameEnd = strTempPredicate.find_last_of(")") - 1;
						}
						else
						{	// Otherwise, we stopped on a parenthesis, so go back one character.
							sztTempNameEnd--;
						}
						// Add it to the list of actions in this solution (auto-alphabetizes and catches duplicate adds).
						string strTempName = strTempPredicate.substr(sztTempNameStart,sztTempNameEnd - sztTempNameStart + 1);
						addNewElement(vecActionPredicates, strTempName);
					}
					// else if (strTempPredicate.find("inmacroAction(") == 0 )
					// {
					// 	size_t sztTempNameStart = strTempPredicate.find_first_of("(")+1;
					// 	size_t sztTempNameEnd = strTempPredicate.find("(", sztTempNameStart);

					// 	if (sztTempNameEnd == string::npos)
					// 	{
					// 		sztTempNameEnd = strTempPredicate.find_last_of(")") - 1;
					// 	}
					// 	else
					// 	{
					// 		sztTempNameEnd--;
					// 	}
					// 	string strTempName = strTempPredicate.substr(sztTempNameStart, sztTempNameEnd - sztTempNameStart + 1);
					// 	addNewElement(vecActionPredicates, strTempName);

					// }
					// Is it the definition of a rigid constant?
					if(strTempPredicate.find("rigid(") == 0)
					{	// If so, remember the base name for later.
						size_t sztTempNameStart = strTempPredicate.find("(") + 1;
						size_t sztTempNameEnd = strTempPredicate.find("(", sztTempNameStart); // Try finding the start of an argument list.
						if(sztTempNameEnd == string::npos)
						{	// If that fails, this rigid has no arguments, just grab its name.
							sztTempNameEnd = strTempPredicate.find_last_of(")") - 1;
						}
						else
						{	// Otherwise, we stopped on a parenthesis, so go back one character.
							sztTempNameEnd--;
						}
						// Add it to the list of rigids in this solution (auto-alphabetizes and catches duplicate adds).
						string strTempName = strTempPredicate.substr(sztTempNameStart,sztTempNameEnd - sztTempNameStart + 1);
						addNewElement(vecRigidPredicates, strTempName);
					}
					// Is it the definition of something with a boolean domain?
					if(strTempPredicate.find("constant_sort(") != string::npos)
					{
						size_t sztTempSortStart = strTempPredicate.find_last_of(",") + 1;
						size_t sztTempSortEnd = strTempPredicate.find_last_of(")") - 1;
						string strTempSortName = strTempPredicate.substr(sztTempSortStart, sztTempSortEnd - sztTempSortStart + 1);
						if(strTempSortName.compare("boolean") == 0)
						{	// It's boolean, store the base name of the constant for use later.
							size_t sztTempNameStart = strTempPredicate.find("(") + 1;
							size_t sztTempNameEnd = strTempPredicate.find("(", sztTempNameStart); // Try finding the start of an argument list.
							if(sztTempNameEnd == string::npos)
							{	// If that fails, this action has no arguments, just grab its name.
								sztTempNameEnd = strTempPredicate.find_last_of(",") - 1;
							}
							else
							{	// Otherwise, we stopped on a parenthesis, so go back one character.
								sztTempNameEnd--;
							}
							// Add it to the list of boolean constants in this solution (auto-alphabetizes and catches duplicate adds).
							string strTempName = strTempPredicate.substr(sztTempNameStart,sztTempNameEnd - sztTempNameStart + 1);
							addNewElement(vecBooleanPredicates, strTempName);
						}
					}

					if (strTempPredicate.find("maxseqnumber(") != string::npos)
					{
						size_t sztParenStart = strTempPredicate.find("(") + 1;
						size_t sztParenEnd = strTempPredicate.find(")");

						if (sztParenStart != string::npos && sztParenEnd != string::npos)
						{
							StringUtils::from_string(max_k, strTempPredicate.substr(sztParenStart, sztParenEnd - sztParenStart + 1));
						}
					}

				}
				// Erase the predicate we just looked at, trim off any whitespace.
				if(sztFirstPos != string::npos)
				{
					strTempInput = strTempInput.substr(sztFirstPos);
				}
				else
				{
					strTempInput = "";
				}
				strTempInput = StringUtils::trimWhitespace(strTempInput);
			} while(strTempInput != "");
			// Send the gathered info on this answer set to the function that does some final processing and outputs the solution.
			processAndOutputAnswerSet(ostOut, sztSolutionNum, vecPredicates, vecConstants, vecActionPredicates, vecBooleanPredicates, vecRigidPredicates, blnAllPredicates, blnOnePredicatePerLine, blnSeparateActions, blnStripHPredicates, blnTransformEQPredicates);
			blnInAnswerSet = false; // No longer processing an answer set, go back to base state.
			intExitCode = EXIT_SOLUTIONS; // We found at least one answer set, set our return code to "success".
		}
		// If we've reached the end of all answer sets, save any remaining lines of solver output as metrics/timing data to repeat verbatim.
		if(blnEndOfAnswerSets)
		{	// Trim whitespace, don't save blank lines.
			strTempInput = StringUtils::trimWhitespace(strTempInput);
			if(strTempInput.length() > 0)
			{
				ossMetricsOut << strTempInput << endl;
			}
		}
	}

	// If we were using a file as the input source, close it now that we're done with input.
	if(ifsFileIn)
	{
		ifsFileIn.close();
	}

	// Did we get any solutions? If not, output a message indicating so.
	if(vecPredicates.empty())
	{
		ostOut << "No solution." << endl << endl;
		intExitCode = EXIT_NO_SOLUTIONS; // We didn't find any answer sets, so return the "no solutions" exit code.
	}

	// Output any timing and model metrics we happened to find as the last bit of output.
	strTempString = ossMetricsOut.str();
	if(strTempString.length() > 0)
	{
		ostOut << strTempString << endl;
	}

	// If we were using a file as the output destination, close it now that we're done with output.
	if(ofsFileOut)
	{
		ofsFileOut.close();
	}

	return intExitCode;
}
