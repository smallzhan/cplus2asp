#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <list>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "Attribute.h"
#include "Constant.h"
#include "Element.h"
#include "Object.h"
#include "NumberRange.h"
#include "Sort.h"
#include "Variable.h"
#include "Query.h"

#include "ElementCounter.h"
#include "SymbolTable.h"

#include "AssoList.h"

#include "utilities.h"

class ParseElement;

/**
 * Class that provides data storage and translation capabilities.
 * Encapsulates a symbol table and data structures for the declared symbols,
 * and provides methods to manipulate and translate the stored data.
 */
class Translator
{
private:
    SymbolTable symbols; ///< Data structure to track what symbols have been declared.
    std::list<Constant*> constants; ///< Holds declared constants & associated data.
    std::list<Object*> objects; ///< Holds declared objects (to populate Sort objects' domains) & associated data.
    std::list<Sort*> sorts; ///< Holds declared sorts & associated data.
    std::list<Variable*> variables; ///< Holds declared variables & associated data.
    std::list<Query*> queries; ///< Holds declared queries & associated data.
    std::ostream* ostOutPtr; ///< Used to output translation results.
    std::ostream* ostErrPtr; ///< Used to output error messages during translation.
    std::ostream* ostNullPtr; ///< Used internally to suppress output or flag when an output stream has not been set.
    std::fstream fNull; ///< Used internally to open a null file handle (for use with ostNull).
    std::ostringstream ossErr; ///< String stream used to generate & hold error messages before output.
	std::list<AssoList*> assolists;
    bool queryLabelConstStmtOutput; ///< True if the standard query label constant linking statement has been output.
public:
    int translatorNumErrors; ///< Tracks how many errors the translator module encounters while translating things.
    Query* tempQuery; ///< Helps the parser process and prepare queries for translation.

    /**
     * Default constructor. Initializes attributes to blank/empty.
     * Also sets up default internal sorts, objects, etc.
     */
    Translator();

    /* Static methods for general translation/sanitizing of element names. */

    /**
     * Transforms a C+ constant name to be compatible with ASP naming/syntax conventions.
     * Uses a consistent sanitization scheme, so calling it twice on the same
     * input will produce the same output both times.
     * @param originalName - The original base name of the constant.
     * @return A sanitized name for the constant, or "" (blank) on an error.
     */
    static std::string sanitizeConstantName(std::string& originalName);
    /**
     * Transforms a C+ object name to be compatible with ASP naming/syntax conventions.
     * Uses a consistent sanitization scheme, so calling it twice on the same
     * input will produce the same output both times.
     * @param originalName - The original base name of the object.
     * @return A sanitized name for the object, or "" (blank) on an error.
     */
    static std::string sanitizeObjectName(std::string& originalName);
    /**
     * Transforms a C+ sort name to be compatible with ASP naming/syntax conventions.
     * Uses a consistent sanitization scheme, so calling it twice on the same
     * input will produce the same output both times.
     * @param originalName - The original base name of the sort.
     * @return A sanitized name for the sort, or "" (blank) on an error.
     */
    static std::string sanitizeSortName(std::string& originalName);
    /**
     * Transforms a C+ variable name to be compatible with ASP naming/syntax conventions.
     * Uses a consistent sanitization scheme, so calling it twice on the same
     * input will produce the same output both times.
     * @param originalName - The original base name of the variable.
     * @return A sanitized name for the variable, or "" (blank) on an error.
     */
    static std::string sanitizeVariableName(std::string& originalName);

    /**
     * Transforms an arbitrary string such that the result will be compatible
     * with ASP object/predicate naming and syntax conventions.
     * Uses a consistent sanitization scheme, so calling it twice on the same
     * input will produce the same output both times.
     * @param originalString - The raw string to sanitize.
     * @return A sanitized version of the string, or "" (blank) on an error.
     */
    static std::string sanitizeString(std::string& originalString);

    /**
     * Static version of translateVariableDecl that returns the result as
     * a string instead of sending the result to an output stream.
     * Translates a Variable element into an ASP-compatible variable declaration.
     * If the variable's sort reference is NULL, will return a blank string.
     * @param transVar - The Variable element to translate.
     * @return A string containing the ASP-equivalent variable declaration,
     * or a blank string ("") on an error.
     */
    static std::string translateVariableDeclToString(Variable* transVar);

    /**
     * Creates a standardized sort name representing a range of numbers.
     * Needed when a number range is given as the binding sort of certain
     * declarations.
     * Uses a consistent naming convention, so calling it twice on the same
     * range produces identical results.
     * @param min - The lower bound of the range.
     * @param max - The upper bound of the range.
     * @return A representation of the number range suitable for use as a
     * sort name, or "" (blank) on an error.
     */
    static std::string numRangeToSortName(std::string& min, std::string& max);

    /**
     * Transforms a sort name into an acceptable variable name containing
     * as much of the original sort name as possible.
     * Uses a consistent naming convention, so calling it twice on the same
     * range produces identical results.
     * @param sortName - The sort name to transform.
     * @param sanitizeFirst - If true, will pass the sort name through
     * sanitizeSortName before transforming it.
     * @return An acceptable variable representation of the sort name, or ""
     * (blank) on an error.
     */
    static std::string sortNameToVariable(std::string& sortName, bool sanitizeFirst=false);

    /**
     * Merges two sub-formulas together into one formula using an AND operation.
     * @param first - The first sub-formula of the pair.
     * @param second - The second sub-formula of the pair.
     * @return A dynamically-declared ParseElement pointer represnting the merging of the two sub-formulas.
     */
    static ParseElement* mergeSubFormulas(ParseElement* first, ParseElement* second);

    /* Accessors that (attempt to) retrieve an instance of a declared element. */

    /**
     * Searches for a constant matching the given name and parameters in the
     * translator's data structures.
     * @param symName - The base name of the constant to find.
     * @param symParams - A vector of parameter names for the constant.
     * @return A pointer to the first matching Constant object, or NULL
     * if a match isn't found.
     */
    Constant* getConstant(std::string& symName, std::vector<std::string>& symParams);
    /**
     * Searches for an object matching the given name and parameters in the
     * translator's data structures.
     * @param symName - The base name of the object to find.
     * @param symParams - A vector of parameter names for the object.
     * @return A pointer to the first matching Object instance, or NULL
     * if a match isn't found.
     */
    Object* getObject(std::string& symName, std::vector<std::string>& symParams);
    /**
     * Searches for a sort matching the given name in the
     * translator's data structures.
     * @param symName - The base name of the sort to find.
     * @return A pointer to the first matching Sort object, or NULL
     * if a match isn't found.
     */
    Sort* getSort(std::string& symName);
    /**
     * Searches for a variable matching the given name in the
     * translator's data structures.
     * @param symName - The base name of the variable to find.
     * @return A pointer to the first matching Variable object, or NULL
     * if a match isn't found.
     */
    Variable* getVariable(std::string& symName);
    /**
     * Searches for a stored query with the given label in the translator's
     * data structures.
     * @param testLabel - The label of the query to find.
     * @return A pointer to the first matching query with the given label, or
     * NULL if a match isn't found.
     */
    Query* getQuery(std::string& testLabel);

    /**
     * Searches for a constant like one matching the given name and number of parameters in the
     * translator's data structures. Used to try to connect a constant-like
     * element to an actual constant instance.
     * @param symName - The base name of the constant to find.
     * @param numParams - The number of parameters the target constant should have.
     * @return A pointer to the first matching Constant object, or NULL
     * if a match isn't found.
     */

	Constant* getConstantLike(std::string& symName);

    Constant* getConstantLike(std::string& symName, size_t numParams);
    /**
     * Searches for an object like one matching the given name and parameters in the
     * translator's data structures. Used to try to connect an object-like
     * element to an actual object instance.
     * @param symName - The base name of the object to find.
     * @param numParams - A number of parameters the target object should have.
     * @return A pointer to the first matching Object instance, or NULL
     * if a match isn't found.
     */
    Object* getObjectLike(std::string& symName, size_t numParams);
    /**
     * Searches for a sort like one matching the given name in the
     * translator's data structures. Used to try to connect a sort-like
     * element to an actual sort instance.
     * @param symName - The base name of the sort to find.
     * @return A pointer to the first matching Sort object, or NULL
     * if a match isn't found.
     */
    Sort* getSortLike(std::string& symName);
    /**
     * Searches for a variable like one matching the given name in the
     * translator's data structures. Used to try to connect a variable-like
     * element to an actual variable instance.
     * @param symName - The base name of the variable to find.
     * @return A pointer to the first matching Variable object, or NULL
     * if a match isn't found.
     */
    Variable* getVariableLike(std::string& symName);

    /* Methods to add elements into the translator's data structures. */

    /**
     * Attempts to add a new Constant object to the translator's data structures and the symbol table.
     * The object must not already be present in the symbol table, or it will be flagged as a duplicate.
     * @param newConst - A populated Constant instance to add.
     * @return A value from SymbolTable's SymTblResult enum indicating success/failure of the add.
     */
    int addConstant(Constant* newConst);
    /**
     * Adds a new Object instance into the translator's data structures.
     * Does not check for duplicates, and does not add the object to the symbol table.
     * @param newObj - A populated Object instance to add.
     * @return A value from SymbolTable's SymTblResult enum indicating success/failure of the add.
     */
    int addObject(Object* newObj);
    /**
     * Attempts to add a new Sort object to the translator's data structures and the symbol table.
     * The object must not already be present in the symbol table, or it will be flagged as a duplicate.
     * @param newSort - A populated Sort instance to add.
     * @return A value from SymbolTable's SymTblResult enum indicating success/failure of the add.
     */
    int addSort(Sort* newSort);
    /**
     * Attempts to add a new Variable object to the translator's data structures and the symbol table.
     * The object must not already be present in the symbol table, or it will be flagged as a duplicate.
     * @param newVar - A populated Variable instance to add.
     * @return A value from SymbolTable's SymTblResult enum indicating success/failure of the add.
     */
    int addVariable(Variable* newVar);
    /**
     * Attempts to add a new Query object to the translator's data structures.
     * A query with the same label must not already be present, or it will be flagged as a duplicate.
     * @param newQuery - A populated Query instance to add.
     * @return A value from SymbolTable's SymTblResult enum indicating success/failure of the add.
     */
    int addQuery(Query* newQuery);

    /* Methods that translate elements into ASP code. */

    /**
     * Translates a Constant element into an ASP-compatible constant declaration.
     * Sends the result to ostOut.
     * @param transConst - The Constant element to translate.
     */
    void translateConstantDecl(Constant* transConst);
    /**
     * Translates an Object element into an ASP-compatible declaration of an
     * object as a member of a sort's domain.
     * Sends the result to ostOut.
     * If the sort pointer is NULL, will not output anything.
     * @param transObj - The Object element to translate.
     * @param sortObj - The Sort element the object belongs to.
     */
    void translateObjectDecl(Object* transObj, Sort* sortObj);
    /**
     * Translates a Sort element into an ASP-compatible sort declaration.
     * Sends the result to ostOut.
     * @param transSort - The Sort element to translate.
     */
    void translateSortDecl(Sort* transSort);
    /**
     * Translates a declaration of a super/sub-sort relationship into
     * ASP-compatible syntax.
     * Assumes the sorts are declared elsewhere.
     * @param transSupersort - The "parent" sort object.
     * @param transSubsort - The "child" sort object.
     */
    void translateSubsortDecl(Sort* transSupersort, Sort* transSubsort);
    /**
     * Translates a Variable element into an ASP-compatible variable declaration.
     * Sends the result to ostOut.
     * If the variable's sort reference is NULL, will not output anything.
     * @param transVar - The Variable element to translate.
     */
    void translateVariableDecl(Variable* transVar);
    /**
     * Translates a Query into an ASP-compatible query declaration.
     * Sends the result to ostOut.
     * Also ensures the standard query label linking statement has been output.
     * If the query's label or maxstep are blank, will not output anything.
     * @param transQuery - The Query element to translate.
     */
    void translateQuery(Query* transQuery);

    /**
     * Translates a causal law into ASP-compatible rule(s). Sends the result to ostOut.
     * This models a causal law of the basic form "caused head if ifBody after afterBody where whereBody."
     * Passing NULL for the various parameters will change what kind of translation is performed,
     * and the type of elements (if any) in the parameters will also affect the translation.
     * @param head - The head portion of the causal law ("caused head...").
     * @param ifBody - The part of the law's body associated with the if keyword ("...if ifBody...").
     * @param afterBody - The part of the law's body associated with the after keyword ("...after afterBody...").
     * @param whereBody - The part of the law's body associated with the where keyword ("...where whereBody.").
     */
    void translateCausalLaw(ParseElement* head, ParseElement* ifBody, ParseElement* afterBody, ParseElement* whereBody);
    /**
     * Helper wrapper to translateCausalLaw that merges ifBody and unlessBody.
     * This models a causal law of the basic form "caused head if ifBody after afterBody unless unlessBody where whereBody."
     * It's okay to pass NULL for any parameter except head.
     * @param head - The head portion of the causal law ("caused head...").
     * @param ifBody - The part of the law's body associated with the if keyword ("...if ifBody...").
     * @param afterBody - The part of the law's body associated with the after keyword ("...after afterBody...").
     * @param unlessBody - The part of the law's body associated with the unless keyword ("...unless unlessBody...").
     * @param whereBody - The part of the law's body associated with the where keyword ("...where whereBody.").
     */
    void translateCausalLaw(ParseElement* head, ParseElement* ifBody, ParseElement* afterBody, ParseElement* unlessBody, ParseElement* whereBody);

    /**
     * Translates a macro definition law into the middle representation. Sends the result to ostOut.
     * This models a macro action definition law of the basic form "M is M0 if E0; M1 if E1..."
     * @param mname - the name of the macro action definition law, which is "M"
     * @param mcont - The part of the law's body associated with the if keyword ("...M1 if E1...").
     */
    void translateMacroActionDefLaw(ParseElement* mname, std::list<std::pair<ParseElement*, ParseElement*>*>* mcont);

	/**
	 * Decide whether one macroaction instance is the instance of the macro action proto
	 * @param mactProtoType - the prototype of the macro action;
	 * @param mactInst - the instance of the macro action;
	 * @return ture if ...
	 */
	bool mactionIsInstance(std::string &mactProtoType, std::string &mactInst);

	bool testIndexofAction();
	void updateAssoLists();
    /* Translator-specific methods for general setup etc. */

    /**
     * Allocates and adds a sort with the given name to the translator's
     * internal data structures without translating or outputting it.
     * Also sets up a default Variable for the sort.
     * @param newSortName - The base name for the new sort.
     * @param subsorts - A list of Sort pointers to sorts that are subsorts of
     * of the sort to be created.
     * @return A pointer to the newly created and added sort, or NULL on an error.
     */
    Sort* createInternalSort(const char *newSortName, std::list<Sort*> subsorts);

    /**
     * Allocates and adds an object with the given name to the translator's
     * internal data structures, connecting it as a member of the given sort's domain.
     * @param newObjName - The base name for the new object.
     * @param params - A list of Sort pointers representing the parameters of the object.
     * @param ofSort - The sort the new object is a member of.
     * @return A pointer to the newly created and added object, or NULL on an error.
     */
    Object* createInternalObject(const char *newObjName, std::list<Sort*> params, Sort* ofSort);

    /**
     * Allocates and adds a number range with the given name and bounds to the translator's
     * internal data structures, connecting it as a member of the given sort's domain.
     * @param newObjName - The base name for the new object.
     * @param newMin - The lower bound of the range.
     * @param newMax - The upper bound of the range.
     * @param ofSort - The sort the new object is a member of.
     * @return A pointer to the newly created and added number range, or NULL on an error.
     */
    NumberRange* createInternalNumRange(const char *newObjName, const char *newMin, const char *newMax, Sort* ofSort);

    /**
     * Allocates a new Query instance and assigns it to tempQuery.
     * @param deallocateFirst - If true, will deallocate the contents of tempQuery before the reallocation. (Default: false)
     */
    void allocateNewTempQuery(bool deallocateFirst=false);

    /**
     * Sets a translator instance's output stream to the passed stream.
     * @param newOst - The output stream the translator should use to output
     * its translations.
     */
    void setOutput(std::ostream &newOst);

    /**
     * Sets a translator instance's error output stream to the passed stream.
     * @param newOst - The output stream the translator module should use when
     * reporting errors or other problems.
     */
    void setErrorOutput(std::ostream &newOst);

    /**
     * Outputs the contents of str to wherever the translator's output stream is aimed.
     * @param str - The text to output.
     * @param endWithNewline - If true, will append a newline character to the end of str.
     */
    void output(std::string &str, bool endWithNewline=false);

    /**
     * Outputs the contents of c_str to wherever the translator's output stream is aimed.
     * Convenience overload of the string-based version.
     * @param c_str - The text to output.
     * @param endWithNewline - If true, will append a newline character to the end of c_str.
     */
    void output(const char *c_str, bool endWithNewline=false);

    /**
     * Outputs the contents of oss to wherever the translator's output stream is aimed.
     * Convenience overload of the string-based version that allows an output string stream as an argument.
     * @param oss - The string stream to output.
     * @param endWithNewline - If true, will append a newline character to the end of oss.
     */
    void output(std::ostringstream &oss, bool endWithNewline=false);

    /**
     * Outputs the contents of str to wherever the translator's error output stream is aimed.
     * Mirrors output to the standard output stream as well.
     * @param str - The text to output.
     * @param endWithNewline - If true, will append a newline character to the end of str.
     */
    void error(std::string &str, bool endWithNewline=false);

    /**
     * Outputs the contents of c_str to wherever the translator's error output stream is aimed.
     * Mirrors output to the standard output stream as well.
     * Convenience overload of the string-based version.
     * @param c_str - The text to output.
     * @param endWithNewline - If true, will append a newline character to the end of c_str.
     */
    void error(const char *c_str, bool endWithNewline=false);

    /**
     * Outputs the contents of oss to wherever the translator's error output stream is aimed.
     * Mirrors output to the standard output stream as well.
     * Convenience overload of the string-based version allowing for an output string stream as an argument.
     * @param oss - The string stream to output.
     * @param endWithNewline - If true, will append a newline character to the end of oss.
     */
    void error(std::ostringstream &oss, bool endWithNewline=false);

    /**
     * Destructor. Deallocates all memory associated with the objects in the
     * list attributes and clears their contents.
     */
    virtual ~Translator();
};

#endif // TRANSLATOR_H
