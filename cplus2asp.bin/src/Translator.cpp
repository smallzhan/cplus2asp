#include "Translator.h"
#include "parser_types.h"

/// When converting a number range to a sort name, this is the prefix that will be attached.
#define NUMRANGE_TO_SORT_PREFIX "numRange"
/// The prefix to stick on constant names when they need to be sanitized.
#define SANITIZE_CONST_PREFIX "saniConst_"
/// The prefix to stick on object names when they need to be sanitized.
#define SANITIZE_OBJ_PREFIX "saniObj_"
/// The prefix to stick on sort names when they need to be sanitized.
#define SANITIZE_SORT_PREFIX "saniSort_"
/// The prefix to stick on variable names when they need to be sanitized.
#define SANITIZE_VAR_PREFIX "SaniVar_"
/// The prefix used to variable-ify sort names.
#define SORT_TO_VAR_PREFIX "V_"
/// What to use to replace "bad" characters in a string that needs to be sanitized.
#define SANITIZE_STR_REPLACE "x"

/* Static class methods */

// Santitizes a constant name so it's compatible with ASP naming conventions.
std::string Translator::sanitizeConstantName(std::string& originalName)
{
    std::string tempStr = "";
    // If the name starts with an underscore, number, or upper-case letter,
    // prepend a sanitizing prefix, otherwise just use the original name.
    // Does not check originalName for "invalid" characters.
    if(originalName.length() > 0)
    {
        if(originalName[0] == '_' || utils::isDigit(originalName[0]) || utils::isUppercase(originalName[0]))
        {
            tempStr += SANITIZE_CONST_PREFIX;
            tempStr += originalName;
        }
        else
        {
            tempStr += originalName;
        }
    }
    return tempStr;
}

// Santitizes an object name so it's compatible with ASP naming conventions.
std::string Translator::sanitizeObjectName(std::string& originalName)
{
    std::string tempStr = "";
    // If the name starts with an underscore or upper-case letter,
    // prepend a sanitizing prefix, otherwise just use the original name.
    // Checks for math symbols that need transforming.
    if(originalName.length() > 0)
    {
        if(originalName[0] == '_' || utils::isUppercase(originalName[0]))
        {
            tempStr += SANITIZE_OBJ_PREFIX;
            tempStr += originalName;
        }
        else
        {
            tempStr += originalName;
        }
        // Turn CCalc integer division into ASP integer division.
        size_t transPos = tempStr.find("//");
        while(transPos != std::string::npos)
        {
            tempStr.replace(transPos, 2, "/");
            transPos = tempStr.find("//");
        }
        // Turn CCalc "mod" into ASP modulus.
        transPos = tempStr.find("mod");
        while(transPos != std::string::npos)
        {
            tempStr.replace(transPos, 3, "\\");
            transPos = tempStr.find("mod");
        }
    }
    return tempStr;
}

// Santitizes a sort name so it's compatible with ASP naming conventions.
std::string Translator::sanitizeSortName(std::string& originalName)
{
    std::string tempStr = "";
    // If the name starts with an underscore, number, or upper-case letter,
    // prepend a sanitizing prefix, otherwise just use the original name.
    // Checks original name for "*" and turns it into "_star".
    if(originalName.length() > 0)
    {
        if(originalName[0] == '_' || utils::isDigit(originalName[0]) || utils::isUppercase(originalName[0]))
        {
            tempStr += SANITIZE_SORT_PREFIX;
        }
        for(size_t i = 0; i < originalName.length(); i++)
        {
            if(originalName[i] == '*')
            {
                tempStr += "_star";
            }
            else
            {
                tempStr += originalName[i];
            }
        }
    }
    return tempStr;
}

// Santitizes a variable name so it's compatible with ASP naming conventions.
std::string Translator::sanitizeVariableName(std::string& originalName)
{
    std::string tempStr = "";
    // If the name starts with an underscore, number, or lower-case letter,
    // prepend a sanitizing prefix, otherwise just use the original name.
    // Does not check originalName for "invalid" characters.
    if(originalName.length() > 0)
    {
        if(originalName[0] == '_' || utils::isDigit(originalName[0]) || utils::isLowercase(originalName[0]))
        {
            tempStr += SANITIZE_VAR_PREFIX;
            tempStr += originalName;
        }
        else
        {
            tempStr += originalName;
        }
    }
    return tempStr;
}

// Sanitizes an arbitrary string so it's compatible with ASP syntax for predicates.
std::string Translator::sanitizeString(std::string& originalString)
{
    std::string tempStr = "";
    if(originalString.length() > 0)
    {
        // If the string starts with an underscore or upper-case letter,
        // prepend a sanitizing prefix.
        if(originalString[0] == '_' || utils::isUppercase(originalString[0]))
        {
            tempStr += SANITIZE_STR_REPLACE;
        }
        // If any characters in the string are not alphanumeric or underscores,
        // replace them with a sanitized character.
        for(size_t i = 0; i < originalString.length(); i++)
        {
            if(originalString[i] != '_' && !utils::isLetter(originalString[i]) && !utils::isDigit(originalString[i]))
            {
                tempStr += SANITIZE_STR_REPLACE;
            }
            else
            {
                tempStr += originalString[i];
            }
        }
    }
    return tempStr;
}

// Static version of translateVariableDecl that returns the result as a string instead of sending the result to an output stream.
std::string Translator::translateVariableDeclToString(Variable* transVar)
{
    std::ostringstream retStream;
    // Sanity check: make sure the variable isn't NULL and neither is its sort.
    if(transVar != NULL && transVar->sortRef != NULL)
    {
        // Variable declarations are just domain variable declarations.
        retStream << "#domain " << transVar->sortRef->fullTransName() << "(";
        retStream << transVar->fullTransName() << ")." << std::endl;
    }
    return retStream.str();
}

// Returns a standardized sort name representing a range of numbers.
std::string Translator::numRangeToSortName(std::string& min, std::string& max)
{
    std::string tempStr = NUMRANGE_TO_SORT_PREFIX;
    tempStr += "_";
    tempStr += Translator::sanitizeString(min);
    tempStr += "_";
    tempStr += Translator::sanitizeString(max);
    return tempStr;
}

// Turns a sort name into a variable version of itself.
std::string Translator::sortNameToVariable(std::string& sortName, bool sanitizeFirst)
{
    std::string tempStr = "";
    std::string baseName = "";
    if(sanitizeFirst)
    {
        baseName = Translator::sanitizeSortName(sortName);
    }
    else
    {
        baseName = sortName;
    }
    // Prepend a variable-compatible prefix to the sort name, then call
    // the variable name sanitizer on the result to ensure it's a good name.
    if(baseName.length() > 0)
    {
        tempStr += SORT_TO_VAR_PREFIX;
        tempStr += baseName;
        tempStr = Translator::sanitizeVariableName(tempStr);
    }
    return tempStr;
}

// Merges two sub-formulas together into one formula.
ParseElement* Translator::mergeSubFormulas(ParseElement* first, ParseElement* second)
{
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_AND;
    tempPE->preOp = first;
    tempPE->postOp = second;
    return tempPE;
}

/* Normal class methods */

// Default constructor. Initializes attributes to blank/empty.
Translator::Translator()
{
    // Open a null file output and set ostNull to it.
    fNull.open("/dev/null");
    ostNullPtr = new std::ostream(fNull.rdbuf());
    // Start ostOutPtr and ostErrPtr using fNull as well.
    ostOutPtr = new std::ostream(ostNullPtr->rdbuf());
    ostErrPtr = new std::ostream(ostNullPtr->rdbuf());
    // Allocate an initial tempQuery.
    tempQuery = new Query();
    // Set up default internal sorts & their objects.
    Sort* newSort = NULL;
    Object* newObj = NULL;
    std::list<Sort*> internalSortList; // Used when some kind of parameter list is required.
    std::string tempName;
    // Create the boolean* (and, by extension, the boolean) domains.
    newSort = this->createInternalSort("boolean*", internalSortList);
    tempName = "boolean";
    newSort = this->getSort(tempName);
    // Create "true" and "false" members of the boolean sort.
    newObj = this->createInternalObject("true", internalSortList, newSort);
    newObj = this->createInternalObject("false", internalSortList, newSort);
    // Create astep, the action time sort.
    newSort = this->createInternalSort("astep", internalSortList);
    // Attach "0..maxstep-1" range to astep.
    newObj = this->createInternalNumRange("0..maxstep-1", "0", "maxstep-1", newSort);
    // Create step, the fluent time sort (supersort of astep).
    internalSortList.push_back(newSort);
    newSort = this->createInternalSort("step", internalSortList);
    internalSortList.clear();
    // Add "maxstep" object to step's domain.
    newObj = this->createInternalObject("maxstep", internalSortList, newSort);
    // Create additiveInteger, the integer sort for additive constants.
    newSort = this->createInternalSort("additiveInteger", internalSortList);
    // Attach "-maxAdditive..maxAdditive" range to additiveInteger.
    newObj = this->createInternalNumRange("-maxAdditive..maxAdditive", "-maxAdditive", "maxAdditive", newSort);
    // Create nnAdditiveInteger, the positive integer sort for additive constants.
    newSort = this->createInternalSort("nnAdditiveInteger", internalSortList);
    // Attach "0..maxAdditive" range to nnAdditiveInteger.
    newObj = this->createInternalNumRange("0..maxAdditive", "0", "maxAdditive", newSort);
    // Set up internal constant sorts.
    internalSortList.clear();
    std::list<Sort*> subsortList;
    // Action sorts.
    newSort = this->createInternalSort("abAction", internalSortList);
    subsortList.push_back(newSort);
    newSort = this->createInternalSort("attribute", internalSortList);
    subsortList.push_back(newSort);
    newSort = this->createInternalSort("exogenousAction", internalSortList);
    subsortList.push_back(newSort);
    newSort = this->createInternalSort("additiveAction", internalSortList);
    subsortList.push_back(newSort);
    newSort = this->createInternalSort("macroAction", internalSortList);
    subsortList.push_back(newSort);
    // The "action" grouped meta-sort.
    newSort = this->createInternalSort("action", subsortList);
    subsortList.clear();
    // Fluent sorts.
    newSort = this->createInternalSort("inertialFluent", internalSortList);
    subsortList.push_back(newSort);
    newSort = this->createInternalSort("additiveFluent", internalSortList);
    subsortList.push_back(newSort);
    // simpleFluent has inertialFluent and additiveFluent as its subsorts.
    newSort = this->createInternalSort("simpleFluent", subsortList);
    subsortList.clear();
    subsortList.push_back(newSort);
    newSort = this->createInternalSort("sdFluent", internalSortList);
    subsortList.push_back(newSort);
    // Rigids aren't technically "fluents" after translation, but in CCalc they still are.
    newSort = this->createInternalSort("rigid", internalSortList);
    subsortList.push_back(newSort);
    // The "fluent" grouped meta-sort.
    newSort = this->createInternalSort("fluent", subsortList);
    subsortList.clear();

    // Add the contribution constant for additive actions.
    std::string contrib_string("contribution");
    Constant* contribution = new Constant(contrib_string,Translator::sanitizeConstantName(contrib_string));
    std::string action("action");
    contribution->params.push_back(getSort(action));
    std::string additiveAction("additiveAction");
    contribution->params.push_back(getSort(additiveAction));
    contribution->constType = Constant::CONST_ACTION;
    tempName = "additiveInteger";
    contribution->domain = getSort(tempName);
    addConstant(contribution);

    // Add the contribution constant for additive fluents.
    contribution = new Constant(contrib_string,Translator::sanitizeConstantName(contrib_string));
    contribution->params.push_back(getSort(action));
    std::string additiveFluent("additiveFluent");
    contribution->params.push_back(getSort(additiveFluent));
    contribution->constType = Constant::CONST_ACTION;
    contribution->domain = getSort(tempName);
    addConstant(contribution);

}

// Searches for a Constant object matching the given name and parameters.
Constant* Translator::getConstant(std::string& symName, std::vector<std::string>& symParams)
{
    Constant* retVal = NULL;
    std::list<Constant*>::iterator cIter = constants.begin();
    while(cIter != constants.end())
    {
        if((*cIter)->name == symName && (*cIter)->params.size() == symParams.size())
        {
            bool paramsMatch = true;
            for(size_t i = 0; i < (*cIter)->params.size() && i < symParams.size(); i++)
            {
                if((*cIter)->params[i]->name != symParams[i])
                {
                    paramsMatch = false;
                    break;
                }
            }
            if(paramsMatch)
            {
                retVal = *cIter;
                break;
            }
        }
        ++cIter;
    }
    return retVal;
}

// Searches for a Object object matching the given name and parameters.
Object* Translator::getObject(std::string& symName, std::vector<std::string>& symParams)
{
    Object* retVal = NULL;
    std::list<Object*>::iterator oIter = objects.begin();
    while(oIter != objects.end())
    {
        if((*oIter)->name == symName && (*oIter)->params.size() == symParams.size())
        {
            bool paramsMatch = true;
            for(size_t i = 0; i < (*oIter)->params.size() && i < symParams.size(); i++)
            {
                if((*oIter)->params[i]->name != symParams[i])
                {
                    paramsMatch = false;
                    break;
                }
            }
            if(paramsMatch)
            {
                retVal = *oIter;
                break;
            }
        }
        ++oIter;
    }
    return retVal;
}

// Searches for a Sort object matching the given name.
Sort* Translator::getSort(std::string& symName)
{
    Sort* retVal = NULL;
    std::list<Sort*>::iterator sIter = sorts.begin();
    while(sIter != sorts.end())
    {
        if((*sIter)->name == symName)
        {
            retVal = *sIter;
            break;
        }
        ++sIter;
    }
    return retVal;
}

// Searches for a Variable object matching the given name.
Variable* Translator::getVariable(std::string& symName)
{
    Variable* retVal = NULL;
    std::list<Variable*>::iterator vIter = variables.begin();
    while(vIter != variables.end())
    {
        if((*vIter)->name == symName)
        {
            retVal = *vIter;
            break;
        }
        ++vIter;
    }
    return retVal;
}

// Searches for a Query object with the given label
Query* Translator::getQuery(std::string& testLabel)
{
    Query* retVal = NULL;
    std::list<Query*>::iterator qIter = queries.begin();
    while(qIter != queries.end())
    {
        if((*qIter)->label == testLabel)
        {
            retVal = *qIter;
            break;
        }
        ++qIter;
    }
    return retVal;
}

// Searches for a Constant object matching the given name and number of parameters.
Constant* Translator::getConstantLike(std::string& symName, size_t numParams)
{
    Constant* retVal = NULL;
    std::list<Constant*>::iterator cIter = constants.begin();
    while(cIter != constants.end())
    {
        if((*cIter)->name == symName && (*cIter)->params.size() == numParams)
        {
            retVal = *cIter;
            break;
        }
        ++cIter;
    }
    return retVal;
}

Constant* Translator::getConstantLike(std::string& symName)
{
	size_t sztLeftParan = symName.find_first_of("(");
	size_t sztRightParan = symName.find_last_of(")");

	if (sztLeftParan == std::string::npos)
		return getConstantLike(symName, 0);
	else
	{
		size_t numParam = 1;
		std::string basename = symName.substr(0, sztLeftParan);

		size_t sztCommaPos = symName.find_first_of(",", sztLeftParan + 1);

		while (sztCommaPos != std::string::npos)
		{
			numParam++;
			sztCommaPos = symName.find_first_of(",", sztCommaPos + 1);
		}

		return getConstantLike(basename, numParam);
	}
}

// Searches for a Object object matching the given name and number of parameters.
Object* Translator::getObjectLike(std::string& symName, size_t numParams)
{
    Object* retVal = NULL;
    std::list<Object*>::iterator oIter = objects.begin();
    while(oIter != objects.end())
    {
        if((*oIter)->name == symName && (*oIter)->params.size() == numParams)
        {
            retVal = *oIter;
            break;
        }
        ++oIter;
    }
    return retVal;
}

// Searches for a Sort object like one matching the given name.
// No difference between this and getSort, just call that.
Sort* Translator::getSortLike(std::string& symName)
{
    Sort* retVal = this->getSort(symName);
    return retVal;
}

// Searches for a Variable object like one matching the given name.
// No difference between this and getVariable, just call that.
Variable* Translator::getVariableLike(std::string& symName)
{
    Variable* retVal = this->getVariable(symName);
    return retVal;
}

// Attempts to add a new Constant object to the translator's data structures and the symbol table.
int Translator::addConstant(Constant* newConst)
{
    int retVal = SymbolTable::ADDSYM_ERR; // Start pessimistic.
    if(newConst != NULL)
    {
        // Try adding it into the symbol table, and then into local data structures if successful.
        std::vector<std::string> paramNames = utils::elementVectorToNameVector(newConst->params);
        retVal = symbols.addSymbol(newConst->name, paramNames, SymbolNode::SYM_CONST);
        if(retVal == SymbolTable::ADDSYM_OK)
        {
            // Connect the symbol definition to the actual Element instance, then save the Element.
            SymbolNode* tempSym = symbols.getLastSymbol();
            tempSym->symbolElement = newConst;
            constants.push_back(newConst);
        }

    }
    return retVal;
}

// Adds a new Object instance to the translator's data structures.
int Translator::addObject(Object* newObj)
{
    int retVal = SymbolTable::ADDSYM_ERR; // Start pessimistic.
    if(newObj != NULL)
    {
        // Duplicate objects can exist, so forego adding it to the symbol table
        // and just add it naively to the translator's data structures.
        objects.push_back(newObj);
        retVal = SymbolTable::ADDSYM_OK;
    }
    return retVal;
}

// Attempts to add a new Sort object to the translator's data structures and the symbol table.
int Translator::addSort(Sort* newSort)
{
    int retVal = SymbolTable::ADDSYM_ERR; // Start pessimistic.
    if(newSort != NULL)
    {
        // Try adding it into the symbol table, and then into local data structures if successful.
        std::vector<std::string> paramNames; // Sorts don't have parameters, pass an empty vector.
        retVal = symbols.addSymbol(newSort->name, paramNames, SymbolNode::SYM_SORT);
        if(retVal == SymbolTable::ADDSYM_OK)
        {
            // Connect the symbol definition to the actual Element instance, then save the Element.
            SymbolNode* tempSym = symbols.getLastSymbol();
            tempSym->symbolElement = newSort;
            sorts.push_back(newSort);
        }
    }
    return retVal;
}

// Attempts to add a new Variable object to the translator's data structures and the symbol table.
int Translator::addVariable(Variable* newVar)
{
    int retVal = SymbolTable::ADDSYM_ERR; // Start pessimistic.
    if(newVar != NULL)
    {
        // Try adding it into the symbol table, and then into local data structures if successful.
        std::vector<std::string> paramNames; // Variables don't have parameters, pass an empty vector.
        retVal = symbols.addSymbol(newVar->name, paramNames, SymbolNode::SYM_VAR);
        if(retVal == SymbolTable::ADDSYM_OK)
        {
            // Connect the symbol definition to the actual Element instance, then save the Element.
            SymbolNode* tempSym = symbols.getLastSymbol();
            tempSym->symbolElement = newVar;
            variables.push_back(newVar);
        }
    }
    return retVal;
}

// Attempts to add a new Query object to the translator's data structures.
int Translator::addQuery(Query* newQuery)
{
    int retVal = SymbolTable::ADDSYM_ERR; // Start pessimistic.
    if(newQuery != NULL)
    {
        // Do some basic sanity checks, then try adding it into local data structures.
        if(newQuery->label == "")
        {
            newQuery->label = "0"; // An unlabeled query defaults to being query 0.
        }
        if(newQuery->maxstep != "")
        {
            if(this->getQuery(newQuery->label) == NULL)
            {
                queries.push_back(newQuery);
                retVal = SymbolTable::ADDSYM_OK;
            }
            else
            {   // A query with this label already exists, flag the dupe.
                retVal = SymbolTable::ADDSYM_DUP;
            }
        }
        else
        {   // Queries have to define maxstep.
            retVal = SymbolTable::ADDSYM_BAD;
        }
    }
    return retVal;
}

// Translates a Constant element into an ASP-compatible constant declaration.
void Translator::translateConstantDecl(Constant* transConst)
{
    // Sanity check: make sure the element isn't NULL.
    if(transConst != NULL)
    {
        bool needDynamicParams = false; // Set to true if two or more of the constant's parameters (if any) are the same.
        ElementCounter eCount; // Used to track occurrences of identical parameters (to avoid name clashes).
        std::vector<std::string> paramVarNames; // Holds unique parameter variable names for translation.
        std::string fullDeclConstName = ""; // Holds the results of transforming the constant's name and parameters.
		std::string fullName = transConst->fullName();
        // Transform the type of the constant into a string representation.
        std::string constTypeName = Constant::constTypeToString(transConst->constType);
        // Ouput the class of constant, then its translated name.
        (*ostOutPtr) << constTypeName << "(";
        fullDeclConstName += transConst->transName;
        // Transform any parameters into sort variables.
        if(!transConst->params.empty())
        {
            fullDeclConstName += "(";
            std::string tempVarName;
            // Use an occurrence counter to get guaranteed unique variable
            // names representing the sorts that comprise the parameters
            // of this constant.
            for(size_t i = 0; i < transConst->params.size(); i++)
            {
                eCount.push_back(transConst->params[i]);
                if(((Sort*)eCount.elementsBack())->sortVar != NULL)
                {
                    tempVarName = ((Sort*)eCount.elementsBack())->sortVar->fullTransName();
                }
                else
                {
                    tempVarName = "NULL";
                }
                paramVarNames.push_back(tempVarName);
                // Add the occurrence count to the variable name if we've
                // seen this sort before.
                if(eCount.countsBack() > 0)
                {
                    paramVarNames.back() += "_";
                    paramVarNames.back() += utils::to_string(eCount.countsBack());
                    needDynamicParams = true;
                }
                if(i > 0)
                {   // Separate parameter names if there's more than one.
                    fullDeclConstName += ",";
                }
                fullDeclConstName += paramVarNames.back();
            }
            fullDeclConstName += ")";
        }
        // Now that we've created the full declarable constant name, use that.
        (*ostOutPtr) << fullDeclConstName << ")";

		if (constTypeName == "macroAction")
		{
			bool inlist = false;
			for (std::list<AssoList*>::iterator it = assolists.begin(); it !=
					 assolists.end(); ++it)
			{
				if ((*it)->getListName() == fullName)
				{
					inlist = true;
					break;
				}
			}

			if (!inlist)
			{
				AssoList *tempList = new AssoList(fullName);
				assolists.push_back(tempList);
			}
		}
        // If we had to dynamically use "extra" variables to avoid name clashes, bind them locally now.
        if(needDynamicParams)
        {
            (*ostOutPtr) << " <- ";
            size_t j = 0;
            for(size_t i = 0; i < eCount.size(); i++)
            {
                if(eCount.countAt(i) > 0)
                {
                    if(j > 0)
                    {   // Separate multiple local variable bindings.
                        (*ostOutPtr) << " & ";
                    }
                    (*ostOutPtr) << transConst->params[i]->fullTransName();
                    (*ostOutPtr) << "(" << paramVarNames[i] << ")";
                    j++;
                }
            }
        }
        (*ostOutPtr) << "."<< std::endl;

        // Output the line connecting a constant to its domain.
        if(transConst->domain != NULL)
        {
            (*ostOutPtr) << "constant_sort(" << fullDeclConstName << ",";
            (*ostOutPtr) << transConst->domain->fullTransName() << ")";
            // If we had to dynamically use "extra" variables to avoid name clashes, bind them locally now.
            if(needDynamicParams)
            {
                (*ostOutPtr) << " <- ";
                size_t j = 0;
                for(size_t i = 0; i < eCount.size(); i++)
                {
                    if(eCount.countAt(i) > 0)
                    {
                        if(j > 0)
                        {   // Separate multiple local variable bindings.
                            (*ostOutPtr) << " & ";
                        }
                        (*ostOutPtr) << transConst->params[i]->fullTransName();
                        (*ostOutPtr) << "(" << paramVarNames[i] << ")";
                        j++;
                    }
                }
            }
            (*ostOutPtr) << "."<< std::endl;
        }
        // If the constant is an attribute, connect the attribute to its action.
        if(transConst->constType == Constant::CONST_ATTRIBUTE)
        {
            // Sanity check: attributeOf can't be NULL.
            if(((Attribute*)transConst)->attributeOf != NULL)
            {
                (*ostOutPtr) << "action_attribute(";
                // Perform the same variable replacement magic on the attribute's action.
                Constant *aConst = ((Attribute*)transConst)->attributeOf;
                std::string aFullDeclConstName = aConst->transName;
                bool aNeedDynamicParams = false;
                ElementCounter aCount;
                std::vector<std::string> aParamVarNames;
                if(!aConst->params.empty())
                {
                    aFullDeclConstName += "(";
                    std::string aTempVarName;
                    // Use an occurrence counter to get guaranteed unique variable
                    // names representing the sorts that comprise the parameters
                    // of this constant.
                    for(size_t i = 0; i < aConst->params.size(); i++)
                    {
                        aCount.push_back(aConst->params[i]);
                        if(((Sort*)aCount.elementsBack())->sortVar != NULL)
                        {
                            aTempVarName = ((Sort*)aCount.elementsBack())->sortVar->fullTransName();
                        }
                        else
                        {
                            aTempVarName = "NULL";
                        }
                        aParamVarNames.push_back(aTempVarName);
                        // Add the occurrence count to the variable name if we've
                        // seen this sort before.
                        if(aCount.countsBack() > 0)
                        {
                            aParamVarNames.back() += "_";
                            aParamVarNames.back() += utils::to_string(aCount.countsBack());
                            aNeedDynamicParams = true;
                        }
                        if(i > 0)
                        {   // Separate parameter names if there's more than one.
                            aFullDeclConstName += ",";
                        }
                        aFullDeclConstName += aParamVarNames.back();
                    }
                    aFullDeclConstName += ")";
                }
                (*ostOutPtr) << aFullDeclConstName;
                (*ostOutPtr) << ",";
                (*ostOutPtr) << fullDeclConstName;
                (*ostOutPtr) << ")";
                // If we had to dynamically use "extra" variables to avoid name clashes, bind them locally now.
                size_t j = 0;
                if(needDynamicParams)
                {
                    (*ostOutPtr) << " <- ";
                    for(size_t i = 0; i < eCount.size(); i++)
                    {
                        if(eCount.countAt(i) > 0)
                        {
                            if(j > 0)
                            {   // Separate multiple local variable bindings.
                                (*ostOutPtr) << " & ";
                            }
                            (*ostOutPtr) << transConst->params[i]->fullTransName();
                            (*ostOutPtr) << "(" << paramVarNames[i] << ")";
                            j++;
                        }
                    }
                }
                if(aNeedDynamicParams)
                {
                    if(!needDynamicParams)
                    {
                        (*ostOutPtr) << " <- ";
                    }
                    for(size_t i = 0; i < aCount.size(); i++)
                    {
                        if(aCount.countAt(i) > 0)
                        {
                            if(j > 0)
                            {   // Separate multiple local variable bindings.
                                (*ostOutPtr) << " & ";
                            }
                            (*ostOutPtr) << aConst->params[i]->fullTransName();
                            (*ostOutPtr) << "(" << aParamVarNames[i] << ")";
                            j++;
                        }
                    }
                }
                (*ostOutPtr) << "." << std::endl;
            }
        }
    }
}

// Translates an Object element into an ASP-compatible declaration of an
// object as a member of a sort's domain.
void Translator::translateObjectDecl(Object* transObj, Sort* sortObj)
{
    // Sanity check: make sure the object isn't NULL, and neither is its sort.
    if(transObj != NULL && sortObj != NULL)
    {
        // An object delcaration is the sort's name, and then the object
        // name in parentheses.
        bool needDynamicParams = false; // Set to true if two or more of the object's parameters (if any) are the same.
        ElementCounter eCount; // Used to track occurrences of identical parameters (to avoid name clashes).
        std::vector<std::string> paramVarNames; // Holds unique parameter variable names for translation.
        (*ostOutPtr) << sortObj->fullTransName() << "(";
        if(transObj->objType == Object::OBJ_RANGE)
        {   // Number range, ensure we get its translated name.
            (*ostOutPtr) << ((NumberRange*)transObj)->fullTransName();
        }
        else
        {   // Just a plain object. Use its name and transform its parameters
            // into sort variables.
            (*ostOutPtr) << transObj->transName;
            if(!transObj->params.empty())
            {
                (*ostOutPtr) << "(";
                std::string tempVarName;
                // Use an occurrence counter to get guaranteed unique
                // variable names representing the sorts that comprise
                // the parameters of this object.
                for(size_t i = 0; i < transObj->params.size(); i++)
                {
                    eCount.push_back(transObj->params[i]);
                    if(((Sort*)eCount.elementsBack())->sortVar != NULL)
                    {
                        tempVarName = ((Sort*)eCount.elementsBack())->sortVar->fullTransName();
                    }
                    else
                    {
                        tempVarName = "NULL";
                    }
                    paramVarNames.push_back(tempVarName);
                    // Add the occurrence count to the variable name if we've
                    // seen this sort before.
                    if(eCount.countsBack() > 0)
                    {
                        paramVarNames.back() += "_";
                        paramVarNames.back() += utils::to_string(eCount.countsBack());
                        needDynamicParams = true;
                    }
                    if(i > 0)
                    {   // Separate parameter names if there's more than one.
                        (*ostOutPtr) << ",";
                    }
                    (*ostOutPtr) << paramVarNames.back();
                }
                (*ostOutPtr) << ")";
            }
        }
        (*ostOutPtr) << ")";
        // If we had to dynamically use "extra" variables to avoid name clashes, bind them locally now.
        if(needDynamicParams)
        {
            (*ostOutPtr) << " <- ";
            size_t j = 0;
            for(size_t i = 0; i < eCount.size(); i++)
            {
                if(eCount.countAt(i) > 0)
                {
                    if(j > 0)
                    {   // Separate multiple local variable bindings.
                        (*ostOutPtr) << " & ";
                    }
                    (*ostOutPtr) << transObj->params[i]->fullTransName();
                    (*ostOutPtr) << "(" << paramVarNames[i] << ")";
                    j++;
                }
            }
        }
        (*ostOutPtr) << "." << std::endl;
    }
}

// Translates a Sort element into an ASP-compatible sort declaration.
void Translator::translateSortDecl(Sort* transSort)
{
    // Sanity check: make sure the sort isn't NULL.
    if(transSort != NULL)
    {
        // A translated sort declaration involves three things:
        // Declare the sort name.
        (*ostOutPtr) << "sort(" << transSort->fullTransName() << ")." << std::endl;
        // The sort's default variable and the line connecting the sort
        // to its objects (if the variable reference isn't NULL).
        if(transSort->sortVar != NULL)
        {
            (*ostOutPtr) << "#domain " << transSort->fullTransName() << "(";
            (*ostOutPtr) << transSort->sortVar->fullTransName() << ")." << std::endl;
            (*ostOutPtr) << "sort_object(" << transSort->fullTransName() << ",";
            (*ostOutPtr) << transSort->sortVar->fullTransName() << ")." << std::endl;
        }
        else
        {
            /// @todo Error if sortVar == NULL.
        }
        // If the sort has subsorts, add lines indicating that all members of
        // the subsorts are also members of the sort.
        if(!transSort->subsorts.empty())
        {
            for(size_t i = 0; i < transSort->subsorts.size(); i++)
            {
                Translator::translateSubsortDecl(transSort, transSort->subsorts[i]);
            }
        }
    }
}

// Translates a declaration of a super/sub-sort relationship between two sorts.
void Translator::translateSubsortDecl(Sort* transSupersort, Sort* transSubsort)
{
    if(transSupersort != NULL && transSubsort != NULL)
    {
        if(transSubsort->sortVar != NULL)
        {
            (*ostOutPtr) << transSupersort->fullTransName() << "(";
            (*ostOutPtr) << transSubsort->sortVar->fullTransName() << ")." << std::endl;
        }
        else
        {
            /// @todo Error if transSubsort's sortVar == NULL.
        }
    }
}

// Translates a Variable element into an ASP-compatible variable declaration.
void Translator::translateVariableDecl(Variable* transVar)
{
    // We've got a version that already creates a string of the declaration,
    // just use that and send it to output.
    (*ostOutPtr) << Translator::translateVariableDeclToString(transVar);
}

// Translates a Query into an ASP-compatible query declaration.
void Translator::translateQuery(Query* transQuery)
{
    if(transQuery != NULL && transQuery->label != "" && transQuery->maxstep != "")
    {
        std::ostringstream ossOutputBuffer; // Holds translated output so things can be easily added on before or after the normal output.
        // First, check if the query label constant linking statement has been output, do so if it hasn't.
        if(!queryLabelConstStmtOutput)
        {
            (*ostOutPtr) << "query_label(query). % Selects which query to activate in a based on the value of the const \"query\"." << std::endl;
            queryLabelConstStmtOutput = true;
        }
        // Output special "hint" flags/comments for this query.
        std::string hintMaxstep = transQuery->maxstep;
        // f2lp does weird things with periods in comments, so replace the dots in a ranged maxstep with something else.
        if(hintMaxstep.find("..") != std::string::npos)
        {
            hintMaxstep.replace(hintMaxstep.find(".."), 2, "::");
        }
        (*ostOutPtr) << "% [Query: Label:" << transQuery->label << ", Maxstep:" << hintMaxstep << "]" << std::endl;
        // For each item in queryConditions, output an ASP-style constraint for it.
        for(std::list<ParseElement*>::iterator lIter = transQuery->queryConditions.begin(); lIter != transQuery->queryConditions.end(); ++lIter)
        {
            ossOutputBuffer << "false <- query_label(" << transQuery->label << ") & not (" << (*lIter)->translate() << ")";
            // Add any extra clauses created during translation.
            if(!(*lIter)->extraClauses.empty())
            {
                ossOutputBuffer << " & ";
            }
            for(std::list<std::string>::iterator ecIter = (*lIter)->extraClauses.begin(); ecIter != (*lIter)->extraClauses.end(); ++ecIter)
            {
                if(ecIter != (*lIter)->extraClauses.begin())
                {
                    ossOutputBuffer << " & ";
                }
                ossOutputBuffer << *ecIter;
            }
            ossOutputBuffer << "." << std::endl;
            // Output any preStatements before the constraint.
            if(!(*lIter)->preStatements.empty())
            {
                for(std::list<std::string>::iterator psIter = (*lIter)->preStatements.begin(); psIter != (*lIter)->preStatements.end(); ++psIter)
                {
                    (*ostOutPtr) << *psIter;
                }

            }
            (*ostOutPtr) << ossOutputBuffer.str();
            ossOutputBuffer.str("");
        }
    }
}

// Translates a causal law into ASP-compatible rule(s).
void Translator::translateCausalLaw(ParseElement* head, ParseElement* ifBody, ParseElement* afterBody, ParseElement* whereBody)
{
    // Sanity check: all laws have to have a head
    if(head != NULL)
    {
        // Figure out which time steps to use for the various parts of the law.
        // The initialized values default to "static law" (i.e., fluents only, no "after").
        bool useOneTimeStep = true; // If true, head will have time stamp t, (it'll have t+1 otherwise).
        bool useActionTime = false; // Whether to use astep (true) or step (false) as the time stamp sort.
        bool needsNotNot = true; // True if the head isn't "false" and useOneTimeStep is true. Only used if the law has a body.
        std::ostringstream ossOutputBuffer; // Holds translated output so things can be easily added on before or after the normal output.
        std::string tempTimeStamp; // Used to build up the time stamp that will be applied to the formulas of the causal law.
        if(afterBody != NULL)
        {   // The presence of "after" is always a dead giveaway.
            useOneTimeStep = false;
            useActionTime = true;
        }
        if(ifBody != NULL && afterBody == NULL && !head->hasFluents() && head->hasActions() && !ifBody->hasFluents() && ifBody->hasActions())
        {   // If "after" isn't here and head & ifBody only have actions, it's an "action dynamic law". Still one time step, but use action time.
            useActionTime = true;
        }
        if(!head->hasFluents() && head->hasActions() && (ifBody == NULL || (!ifBody->hasFluents() && !ifBody->hasActions())))
        {   // Nothing but actions. Again, "action dynamic law".
            useActionTime = true;
        }
        // Now check if we actually need "not not (...)" encasing the law's body (if it has one).
        if(!useOneTimeStep && ifBody == NULL)
        {   // Cycles can only happen when stuff in the head is the same time-wise as something in the body (i.e., useOneTimeStep is true or ifBody is present)
            needsNotNot = false;
        }
        if(head->elemType == ParseElement::PELEM_OBJLIKE && ( ((ObjectLikeElement*)head)->baseName == "false" || ( ((ObjectLikeElement*)head)->objRef != NULL && ((ObjectLikeElement*)head)->objRef->fullName() == "false" ) ) )
        {   // If the head is the "false" object, there's no way to cause a cycle, we don't need the wrapper.
            needsNotNot = false;
        }
        // Grab a link to the correct time sort & its default variable.
        std::string timeSortName;
        if(useActionTime)
        {
            timeSortName = "astep";
        }
        else
        {
            timeSortName = "step";
        }
        Sort* timeSort = this->getSort(timeSortName);
        Variable* timeVar = timeSort->sortVar;

        // Translate!
        ParseElement::extraClauseCount = 0; // Reset the extra clause counter.
        // The head
        tempTimeStamp = timeVar->fullTransName();
        if(!useOneTimeStep)
        {
            tempTimeStamp += "+1";
        }
        head->propogateTimeStamp(tempTimeStamp);
        /// @todo If head and ifBody are: not NULL, both const-like or both UOP_NOT(const-like), make a choice rule out of head and translate that.
        if(head->elemType == ParseElement::PELEM_VARLIKE && ((VariableLikeElement*)head)->isConstantVariable())
        {   // Treat bare constant variables as though they were constants.
            ossOutputBuffer << ((VariableLikeElement*)head)->translateAsConstant("true");
        }
        else
        {
            ossOutputBuffer << head->translate();
        }

        // The body, if there is one.
        if(ifBody != NULL || afterBody != NULL || whereBody != NULL || ParseElement::extraClauseCount > 0)
        {
            ossOutputBuffer << " <- ";
            // "if" part of body, if there is one.
            if(ifBody != NULL)
            {
                // If we're translating a law that needs a "not not (...)" body wrapper to break cycles, add it.
                if(needsNotNot)
                {
                    ossOutputBuffer << "not not (";
                }
                // No changes needed to time stamp for ifBody
                ifBody->propogateTimeStamp(tempTimeStamp);
                if(ifBody->elemType == ParseElement::PELEM_VARLIKE && ((VariableLikeElement*)ifBody)->isConstantVariable())
                {   // Treat bare constant variables as though they were constants.
                    ossOutputBuffer << ((VariableLikeElement*)ifBody)->translateAsConstant("true");
                }
                else
                {
                    ossOutputBuffer << ifBody->translate();
                }
                // Finish the "not not (...)" wrapper if it got started.
                if(needsNotNot)
                {
                    ossOutputBuffer << ")";
                }
            }

            // "after" part of body, if there is one.
            if(afterBody != NULL)
            {
                if(ifBody != NULL)
                {
                    ossOutputBuffer << " & ";
                }
                // If we need a "not not (...)" wrapper and head has the same time as afterBody, put the wrapper here.
                if(needsNotNot && useOneTimeStep)
                {
                    ossOutputBuffer << "not not (";
                }
                // Change time step to just "t" (vs. potentially "t+1").
                tempTimeStamp = timeVar->fullTransName();
                afterBody->propogateTimeStamp(tempTimeStamp);
                if(afterBody->elemType == ParseElement::PELEM_VARLIKE && ((VariableLikeElement*)afterBody)->isConstantVariable())
                {   // Treat bare constant variables as though they were constants.
                    ossOutputBuffer << ((VariableLikeElement*)afterBody)->translateAsConstant("true");
                }
                else
                {
                    ossOutputBuffer << afterBody->translate();
                }
                // Finish the "not not (...)" wrapper if it got started.
                if(needsNotNot && useOneTimeStep)
                {
                    ossOutputBuffer << ")";
                }
            }

            // "where" part of body, if there is one.
            if(whereBody != NULL)
            {
                if(ifBody != NULL || afterBody != NULL)
                {
                    ossOutputBuffer << " & ";
                }
                // Change time step to just "t". The where body should never need time stamps, but just in case.
                tempTimeStamp = timeVar->fullTransName();
                whereBody->propogateTimeStamp(tempTimeStamp);
                if(whereBody->elemType == ParseElement::PELEM_VARLIKE && ((VariableLikeElement*)whereBody)->isConstantVariable())
                {   // Treat bare constant variables as though they were constants.
                    ossOutputBuffer << ((VariableLikeElement*)whereBody)->translateAsConstant("true");
                }
                else
                {
                    ossOutputBuffer << whereBody->translate();
                }
            }

            // Last but not least, any extra clauses created during translation.
            if(!head->extraClauses.empty())
            {
                if(ifBody != NULL || afterBody != NULL || whereBody != NULL)
                {
                    ossOutputBuffer << " & ";
                }
                for(std::list<std::string>::iterator lIter = head->extraClauses.begin(); lIter != head->extraClauses.end(); ++lIter)
                {
                    if(lIter != head->extraClauses.begin())
                    {
                        ossOutputBuffer << " & ";
                    }
                    ossOutputBuffer << *lIter;
                }
            }
            if(ifBody != NULL && !ifBody->extraClauses.empty())
            {
                if(ifBody != NULL || afterBody != NULL || whereBody != NULL || !head->extraClauses.empty())
                {
                    ossOutputBuffer << " & ";
                }
                for(std::list<std::string>::iterator lIter = ifBody->extraClauses.begin(); lIter != ifBody->extraClauses.end(); ++lIter)
                {
                    if(lIter != ifBody->extraClauses.begin())
                    {
                        ossOutputBuffer << " & ";
                    }
                    ossOutputBuffer << *lIter;
                }
            }
            if(afterBody != NULL && !afterBody->extraClauses.empty())
            {
                if(ifBody != NULL || afterBody != NULL || whereBody != NULL || !head->extraClauses.empty() || !ifBody->extraClauses.empty())
                {
                    ossOutputBuffer << " & ";
                }
                for(std::list<std::string>::iterator lIter = afterBody->extraClauses.begin(); lIter != afterBody->extraClauses.end(); ++lIter)
                {
                    if(lIter != afterBody->extraClauses.begin())
                    {
                        ossOutputBuffer << " & ";
                    }
                    ossOutputBuffer << *lIter;
                }
            }
            if(whereBody != NULL && !whereBody->extraClauses.empty())
            {
                if(ifBody != NULL || afterBody != NULL || whereBody != NULL || !head->extraClauses.empty() || !ifBody->extraClauses.empty() || !afterBody->extraClauses.empty())
                {
                    ossOutputBuffer << " & ";
                }
                for(std::list<std::string>::iterator lIter = whereBody->extraClauses.begin(); lIter != whereBody->extraClauses.end(); ++lIter)
                {
                    if(lIter != whereBody->extraClauses.begin())
                    {
                        ossOutputBuffer << " & ";
                    }
                    ossOutputBuffer << *lIter;
                }
            }
        }

        // handle the static law in the macro action...
        if (ifBody != NULL && afterBody == NULL && whereBody == NULL)
        {
            std::string staticLawStr = ossOutputBuffer.str();
            unsigned idx = staticLawStr.find("V_step");
            while (idx != std::string::npos)
            {
                staticLawStr.replace(idx, 6, "V_astep,V_inseq");
                idx = staticLawStr.find("V_step", idx);
            }

            ossOutputBuffer << ".\n" << staticLawStr;
        }

        else if (afterBody != NULL) // fluent dynamic law...
        {
            std::string fluentDynLaw = ossOutputBuffer.str();
            std::string afterBodyName = afterBody->fullName();
            std::vector<std::string> bodyElems;
            bodyElems.clear();
            unsigned idx = 0;
            idx = afterBodyName.find("&");
            while (idx != std::string::npos)
            {
                std::string elem = afterBodyName.substr(0, idx);
                int beg = elem.find_first_not_of("\n \t");
                int end = elem.find_last_not_of("\n \t");
                bodyElems.push_back(elem.substr(beg, end-beg+1));
                afterBodyName = afterBodyName.substr(idx+1);
                idx = afterBodyName.find("&");
            }

            int beg = afterBodyName.find_first_not_of("\n \t");
            int end = afterBodyName.find_last_not_of("\n \t.");
            bodyElems.push_back(afterBodyName.substr(beg, end-beg+1));

            int actionnums = 0;
            std::string primaryaction;
            for (std::vector<std::string>::iterator it = bodyElems.begin();
                 it != bodyElems.end(); ++it)
            {
                unsigned paren = it->find_first_of("(");
                if (paren == std::string::npos)
                {
                    Constant* elemconst = getConstantLike((*it), 0);
                    if (elemconst != NULL)
                    {

                        if (elemconst->constType == Constant::CONST_EXOGENOUSACTION
							|| elemconst->constType == Constant::CONST_ACTION)
                        {
                            if (actionnums == 0)
                            {
                                primaryaction = *it;
                            }
                            actionnums++ ;
                        }
                    }
                }
                else
                {
					Constant *elemconst = getConstantLike((*it));
                    if (elemconst != NULL)
                    {

                        if (elemconst->constType == Constant::CONST_EXOGENOUSACTION
							|| elemconst->constType == Constant::CONST_ACTION)
                        {
                            if (actionnums == 0)
                            {
                                primaryaction = *it;
                            }
                            actionnums++;
                        }
                    }
                }
            }
            if (actionnums == 1)
            {
                unsigned loc = fluentDynLaw.find(" <-");
                //std::string headofbody = fluentDynLaw.substr(0, loc);
                std::string bodyofbody = fluentDynLaw.substr(loc);

				// head->propogateTimeStamp("V_astep,1");
				// loc = bodyofbody.find("V_astep");
				// while (loc != std::string::npos)
                // {
                //     bodyofbody.replace(loc, 7, "V_astep,0");
                //     loc = bodyofbody.find("V_astep", loc+9);
                // }
				// ossOutputBuffer << ".\n" << head->translate() << bodyofbody;

                head->propogateTimeStamp("V_astep,V_inseq+1");
                loc = bodyofbody.find("V_astep");
                while (loc != std::string::npos)
                {
                    bodyofbody.replace(loc, 7, "V_astep,V_inseq");
                    loc = bodyofbody.find("V_astep", loc+15);
                }

                ossOutputBuffer << ".\n" << head->translate() << bodyofbody << " & V_inseq < K_star";

				head->propogateTimeStamp("V_astep+1");
				loc = bodyofbody.find("V_inseq");
				while (loc != std::string::npos)
				{
					bodyofbody.replace(loc, 7, "K_star");
					loc = bodyofbody.find("V_inseq", loc+6);
				}
				ossOutputBuffer << ".\n" << head->translate() << bodyofbody;

				head->propogateTimeStamp("V_astep,1");
				loc = fluentDynLaw.find("<-");
				bodyofbody = fluentDynLaw.substr(loc);
				loc = bodyofbody.find(primaryaction);
				if (loc != std::string::npos)
				{
					loc = bodyofbody.find("V_astep", loc);
					bodyofbody.replace(loc, 7, "V_astep,0");
				}
				ossOutputBuffer << ".\n" << head->translate() << bodyofbody;
            }
            else if (actionnums > 1)
            {
                if (head->translate() == "false")  // that's "nonexecutable ..."
                {
                    if (bodyElems.size() == 2)
                    {
                        ossOutputBuffer << ".\n" << "noncon(" << bodyElems[0] << ","
                                        << bodyElems[1] << ").\n" << "noconof("
                                        << bodyElems[0] << ")." << "noconof("
                                        << bodyElems[1] << ")";
                    }

                }
            }

        }

        ossOutputBuffer << "." << std::endl;

        // Before outputting the translated causal law, collect and output any "preStatements" created during translation.
        if(!head->preStatements.empty())
        {
            for(std::list<std::string>::iterator lIter = head->preStatements.begin(); lIter != head->preStatements.end(); ++lIter)
            {
                (*ostOutPtr) << *lIter;
            }

        }
        if(ifBody != NULL && !ifBody->preStatements.empty())
        {
            for(std::list<std::string>::iterator lIter = ifBody->preStatements.begin(); lIter != ifBody->preStatements.end(); ++lIter)
            {
                (*ostOutPtr) << *lIter;
            }
        }
        if(afterBody != NULL && !afterBody->preStatements.empty())
        {
            for(std::list<std::string>::iterator lIter = afterBody->preStatements.begin(); lIter != afterBody->preStatements.end(); ++lIter)
            {
                (*ostOutPtr) << *lIter;
            }
        }
        if(whereBody != NULL && !whereBody->preStatements.empty())
        {
            for(std::list<std::string>::iterator lIter = whereBody->preStatements.begin(); lIter != whereBody->preStatements.end(); ++lIter)
            {
                (*ostOutPtr) << *lIter;
            }
        }
        // Now output the translated law.
        (*ostOutPtr) << ossOutputBuffer.str();
    }
}

// Convenience method that handles unlessBody and then merges afterBody and "not unlessBody", calling the next wrapper down.
void Translator::translateCausalLaw(ParseElement* head, ParseElement* ifBody, ParseElement* afterBody, ParseElement* unlessBody, ParseElement* whereBody)
{
    // Create "not unlessBody" if unlessBody exists.
    bool unlessCreationFailed = false; // Set to true if something goes wrong during the preparation of the unless clause.
    SimpleUnaryOperator* tempUOP = NULL;
    SimpleBinaryOperator* tempPE = NULL;
    ConstantLikeElement* unlessConstLike = NULL;
    if(unlessBody != NULL)
    {
        // The unlessBody needs to be a constant (or a constant miscategorized as an object) or this whole thing doesn't make sense.
        if(unlessBody->elemType == ParseElement::PELEM_CONSTLIKE || unlessBody->elemType == ParseElement::PELEM_OBJLIKE)
        {
            unlessConstLike = new ConstantLikeElement();
            if(unlessBody->elemType == ParseElement::PELEM_CONSTLIKE)
            {
                unlessConstLike->baseName = ((ConstantLikeElement*)unlessBody)->baseName;
                unlessConstLike->params = ((ConstantLikeElement*)unlessBody)->params;
                unlessConstLike->constRef = ((ConstantLikeElement*)unlessBody)->constRef;
            }
            else
            {
                unlessConstLike->baseName = ((ObjectLikeElement*)unlessBody)->baseName;
                unlessConstLike->params = ((ObjectLikeElement*)unlessBody)->params;
                unlessConstLike->constRef = NULL;
            }
            // If the constant in unlessBody doesn't even exist yet, make that first.
            if(unlessBody->elemType == ParseElement::PELEM_OBJLIKE || unlessConstLike->constRef == NULL)
            {
                // Take a best guess at what the parameters, if any, of the constant should be.
                std::string tempStr = "";
                Constant* unlessConst = new Constant();
                unlessConst->name = unlessConstLike->baseName;
                unlessConst->transName = Translator::sanitizeConstantName(unlessConstLike->baseName);
                tempStr = "boolean";
                unlessConst->domain = this->getSort(tempStr);
                // For each parameter, try to figure out what sort it came from.
                std::vector<Sort*> tempSortParams;
                for(std::vector<ParseElement*>::iterator vIter = unlessConstLike->params.begin(); vIter != unlessConstLike->params.end(); ++vIter)
                {
                    if((*vIter)->elemType == ParseElement::PELEM_VARLIKE)
                    {
                        if(((VariableLikeElement*)(*vIter))->varRef != NULL && ((VariableLikeElement*)(*vIter))->varRef->sortRef != NULL)
                        {
                            tempSortParams.push_back(((VariableLikeElement*)(*vIter))->varRef->sortRef);
                        }
                        else
                        {   // varRef didn't pan out, try finding the Variable that goes with this VariableLikeElement.
                            tempStr = ((VariableLikeElement*)(*vIter))->baseName;
                            Variable* varResult = this->getVariableLike(tempStr);
                            if(varResult != NULL && varResult->sortRef != NULL)
                            {
                                tempSortParams.push_back(varResult->sortRef);
                            }
                            else
                            {   // Couldn't find the sort for the variable, give up.
                                std::ostringstream ossUnlessErr;
                                ossUnlessErr << "% Translation Error: Could not dynamically declare abnormality constant \"" << unlessConstLike->fullName() << "\", could not figure out the sort(s) of its parameter(s). Declaring the constant yourself will fix this problem.";
                                this->error(ossUnlessErr, true);
                                this->translatorNumErrors++;
                                unlessCreationFailed = true;
                            }
                        }
                    }
                    else
                    {   // Anything but a variable and we probably can't guess the sort.
                        std::ostringstream ossUnlessErr;
                        ossUnlessErr << "% Translation Error: Could not dynamically declare abnormality constant \"" << unlessConstLike->fullName() << "\", could not figure out the sort(s) of its parameter(s). Declaring the constant yourself will fix this problem.";
                        this->error(ossUnlessErr, true);
                        this->translatorNumErrors++;
                        unlessCreationFailed = true;
                    }
                }
                if(!unlessCreationFailed)
                {   // We found sorts for all the parameters, assign the vector to our new Constant.
                    unlessConst->params = tempSortParams;
                    // What kind of constant unlessBody should be is based on what kind of law it's seen in.
                    // It's an abAction unless it's first seen in a static law, then it's an sdFluent.
                    unlessConst->constType = Constant::CONST_ABACTION;
                    if(!head->hasActions() && head->hasFluents())
                    {
                        if(ifBody == NULL && afterBody == NULL)
                        {   // Static law, this is an sdFluent.
                            unlessConst->constType = Constant::CONST_SDFLUENT;
                        }
                        else if(ifBody != NULL && afterBody == NULL && (!ifBody->hasActions() && ifBody->hasFluents()))
                        {   // Another form of static law, this is an sdFluent.
                            unlessConst->constType = Constant::CONST_SDFLUENT;
                        }
                    }
                    int addResult = this->addConstant(unlessConst);
                    if(addResult != SymbolTable::ADDSYM_OK)
                    {   // Throw an error about the ab constant being a bad symbol.
                        if(addResult == SymbolTable::ADDSYM_BAD)
                        {
                            std::ostringstream ossUnlessErr;
                            ossUnlessErr << "% Translation Error: Could not dynamically declare abnormality constant \"" << unlessConstLike->fullName() << "\", it appears to be a bad constant.";
                            this->error(ossUnlessErr, true);
                            this->translatorNumErrors++;
                            unlessCreationFailed = true;
                        }
                    }
                    else
                    {   // Successful add, translate the new constant.
                        this->translateConstantDecl(unlessConst);
                        unlessConstLike->constRef = unlessConst;
                        // Also, if it was an sdFluent, add "default -ab" as a law.
                        if(unlessConst->constType == Constant::CONST_SDFLUENT)
                        {
                            SimpleUnaryOperator* tempNotUnless = new SimpleUnaryOperator();
                            tempNotUnless->opType = SimpleUnaryOperator::UOP_NOT;
                            tempNotUnless->postOp = unlessConstLike;
                            this->translateCausalLaw(tempNotUnless, tempNotUnless, NULL, NULL, NULL);
                            // Carefully deallocate tempNotUnless.
                            tempNotUnless->postOp = NULL;
                            delete tempNotUnless;
                        }
                    }
                }
            }
            // Create the "-unlessBody" part to merge with
            tempUOP = new SimpleUnaryOperator();
            tempUOP->opType = SimpleUnaryOperator::UOP_NOT;
            tempUOP->postOp = unlessConstLike;
        }
    }

    // Finish translating this causal law even if something went wrong above.
    // If something went wrong, the law might translate funny, but at least they'll have something to look at.
    if(ifBody == NULL && unlessBody == NULL)
    {   // They're both NULL, pass NULL through.
        this->translateCausalLaw(head, NULL, afterBody, whereBody);
    }
    else if(afterBody == NULL)
    {   // Only unlessBody exists, just pass it along.
        this->translateCausalLaw(head, ifBody, tempUOP, whereBody);
    }
    else if(unlessBody == NULL)
    {   // unlessBody was NULL, just pass the rest along.
        this->translateCausalLaw(head, ifBody, afterBody, whereBody);
    }
    else
    {   // They both exist, merge them and pass that along.
        tempPE = (SimpleBinaryOperator*)Translator::mergeSubFormulas(afterBody, tempUOP);
        this->translateCausalLaw(head, ifBody, tempPE, whereBody);
    }

    if(unlessBody != NULL)
    {
        // Carefully deallocate the temporary "not unlessBody" construct,
        // avoiding deallocating the original unlessBody.
        // Do this first to avoid cascading deallocation from possible tempPE.
        tempUOP->postOp = NULL;
        delete tempUOP;
    }
    if(tempPE != NULL)
    {
        // Now (carefully) deallocate the temporary ParseElement.
        // Don't deallocate preOp or postOp, they get deallocated elsewhere.
        tempPE->preOp = NULL;
        tempPE->postOp = NULL;
        delete tempPE;
    }
    if(unlessConstLike != NULL)
    {   // Carefully deallocate unlessConstLike.
        unlessConstLike->params.clear();
        delete unlessConstLike;
    }
}

// Translate the macroaction defition law
void Translator::translateMacroActionDefLaw(ParseElement *mname, std::list<std::pair<ParseElement*, ParseElement* >* >* mcont)
{
    std::ostringstream ossOutputBuffer;
    ossOutputBuffer.str("");
    int i = 0;
    for (std::list<std::pair<ParseElement*, ParseElement*>*>::iterator it = mcont->begin();
         it != mcont->end(); ++it, ++i)
    {
        ParseElement* action = (*it)->first;
        ParseElement* condition = (*it)->second;
        std::string actionname = action->fullName();
		std::string normalprefix("V_astep");
		std::string indexprefix("V_astep,V_index");
		std::string seqnumprefix("V_astep,V_seqno");
		std::string seqidxprefix("V_astep,V_seqno+V_index");
		std::string zeroprefix("V_astep,0");

		mname->propogateTimeStamp(normalprefix);
        action->propogateTimeStamp(indexprefix);

        ossOutputBuffer << action->translate() << " <- " << mname->translate();

        if (condition != NULL)
		{
			condition->propogateTimeStamp(indexprefix);
			ossOutputBuffer << " & " << condition->translate();
		}
		ossOutputBuffer << " & index(" << mname->fullName() << "," << action->fullName()
						<< ",V_index" << ").\n";

		action->propogateTimeStamp(seqidxprefix);
		mname->propogateTimeStamp(seqnumprefix);

		ossOutputBuffer << action->translate() << " <- " << mname->translate();
		if (condition != NULL) {
			condition->propogateTimeStamp(seqidxprefix);
			ossOutputBuffer <<" & " << condition->translate();
		}
		ossOutputBuffer << " & index(" << mname->fullName() << "," << action->fullName()
						<< ",V_index" << ").\n";


		mname->propogateTimeStamp(normalprefix);
        action->propogateTimeStamp(zeroprefix);

        ossOutputBuffer << action->translate() << " <- " << mname->translate();

        if (condition != NULL)
		{
			condition->propogateTimeStamp(normalprefix);
			ossOutputBuffer << " & " << condition->translate();
		}
		ossOutputBuffer << " & index(" << mname->fullName() << "," << action->fullName()
						<< ",0" << ").\n";

		mname->propogateTimeStamp(zeroprefix);

        ossOutputBuffer << action->translate() << " <- " << mname->translate();

        if (condition != NULL)
		{
			condition->propogateTimeStamp(normalprefix);
			ossOutputBuffer << " & " << condition->translate();
		}
		ossOutputBuffer << " & index(" << mname->fullName() << "," << action->fullName()
						<< ",0" << ").\n";

        action->propogateTimeStamp(normalprefix);
		mname->propogateTimeStamp(normalprefix);
        ossOutputBuffer << "false <- " << mname->translate() << " & "
                        << action->translate() << ".\n";

        ossOutputBuffer << "inmacroAction(" << action->fullName() << ").\n";
        if (i == 0) ossOutputBuffer << "firstactionof(" << action->fullName() << ","
                                    << mname->fullName() << ").\n";
    }

    (*ostOutPtr) << ossOutputBuffer.str();
    ossOutputBuffer.str("");

	// Calculate the ``index'' of each action pair..
	for (std::list<AssoList*>::iterator it = assolists.begin();
		 it != assolists.end(); ++it)
	{
		std::string listName = (*it)->getListName();
		std::string fullName = mname->fullName();
		// (*ostErrPtr) << listName << "{}" << fullName << std::endl;
		if (mactionIsInstance(listName, fullName))
		{
			std::list<std::pair<ParseElement*, ParseElement*>*>::iterator
				listIt = mcont->begin();

			for (;listIt != mcont->end(); ++listIt)
			{
				(*it)->assoListA.push_back((*listIt)->first->fullName());
				(*it)->assoListB.push_back("NULL");
			}
			(*it)->realActionName = mname->fullName();
//			(*ostErrPtr) << ">>><<<" << mname->fullName() << ":";
			// (*it)->printAssoList(*ostErrPtr);
			break;
		}
	}

	if (testIndexofAction()) updateAssoLists();

}

void Translator::updateAssoLists()
{
	std::list<AssoList*> ::iterator listIt = assolists.begin();
	for (;listIt != assolists.end(); ++listIt)
	{
		std::string &actName = (*listIt)->macroActionName;
		for (std::list<AssoList*>::iterator iter = assolists.begin();
			 iter != assolists.end(); ++iter)
		{
			for (size_t i = 0; i < (*iter)->assoListA.size(); ++i)
			{
				std::string &subActName = (*iter)->assoListA[i];
				Constant* tempConst = getConstantLike(subActName);
				if (tempConst && tempConst->constType == Constant::CONST_MACROACTION)
				{
					// (*ostErrPtr) << tempConst->fullName() << "}{" << actName << std::endl;
					if (tempConst->fullName() == actName)
					{
						std::vector<std::string>::iterator posA = (*iter)->assoListA.begin();
						std::vector<std::string>::iterator posB = (*iter)->assoListB.begin();
						*(posA+i) = (*listIt)->assoListA[0];
						*(posB+i) = (*listIt)->realActionName;

						for (int j = 1; j < (*listIt)->assoListA.size(); ++j)
						{
							// (*ostErrPtr) << "WHERE j=" << j << std::endl;
							posA = (*iter)->assoListA.begin();
							posB = (*iter)->assoListB.begin();
							(*iter)->assoListA.insert(posA+i+j, (*listIt)->assoListA[j]);
							(*iter)->assoListB.insert(posB+i+j, "Nop");
						}
					}
					break;
				}
			}
		}
	}

	size_t maxk = 0;
	for (listIt = assolists.begin(); listIt != assolists.end(); ++listIt)
	{
		if ((*listIt)->assoListA.size() > maxk) maxk = (*listIt)->assoListA.size();
		// (*listIt)->printAssoList(*ostErrPtr);
		for (int i = 0; i < (*listIt)->assoListA.size(); ++i)
		{
			if ((*listIt)->assoListB[i] == "NULL")
			{
				std::string &subActName=(*listIt)->assoListA[i];
				(*ostOutPtr) << "index(" << (*listIt)->realActionName <<","
							 << subActName <<  "," << i << ").\nindexnumber("
							 << i << ")." << std::endl ;
			}
			else if ((*listIt)->assoListB[i] != "Nop")
			{
				(*ostOutPtr) << "index(" << (*listIt)->realActionName <<","
							 << (*listIt)->assoListB[i] << "," << i << ").\nindexnumber("
							 << i << ")." << std::endl;
			}
		}
	}

	(*ostOutPtr) << "seqnumber(0.." << maxk-1 << ").\nmaxseqnumber("
				 << maxk-1  << ").\ninseqnumber(1.." << maxk-1 <<").\n";

}

bool Translator::mactionIsInstance(std::string &mactProtoType, std::string &mactInst)
{
	size_t sztParenofP = mactProtoType.find_first_of("(");
	size_t sztParenofI = mactInst.find_first_of("(");
	if (sztParenofP != sztParenofI)
		return false;
	if (sztParenofI == std::string::npos)
		return (mactProtoType == mactInst);

	std::string basenameP = mactProtoType.substr(0, sztParenofP);
	std::string basenameI = mactInst.substr(0, sztParenofI);

	if (basenameP != basenameI)
		return false;

	std::vector<std::string> paralistP;
	std::vector<std::string> paralistI;

	size_t sztEndParenofP = mactProtoType.find_last_of(")");
	size_t sztEndParanofI = mactInst.find_last_of(")");

	size_t sztCommaofP = mactProtoType.find_first_of(",", sztParenofP);
	size_t sztCommaofI = mactInst.find_first_of(",", sztParenofI);

	while (sztCommaofP != std::string::npos || sztCommaofI != std::string::npos)
	{
		if (sztCommaofP == std::string::npos || sztCommaofI == std::string::npos)
			return false;
		sztParenofP = mactProtoType.find_first_not_of(" \t\n", sztParenofP+1);
		sztParenofI = mactInst.find_first_not_of(" \t\n", sztParenofI+1);

		paralistP.push_back(mactProtoType.substr(sztParenofP, sztCommaofP-sztParenofP-1));
		paralistI.push_back(mactInst.substr(sztParenofI, sztCommaofI-sztParenofI-1));

		sztParenofP = sztCommaofP;
		sztParenofI = sztCommaofI;

		sztCommaofP = mactProtoType.find_first_of(",", sztParenofP+1);
		sztCommaofI = mactInst.find_first_of(",", sztParenofI+1);
	}
	sztParenofP = mactProtoType.find_first_not_of(" \t\n", sztParenofP+1);
	sztParenofI = mactInst.find_first_not_of(" \t\n", sztParenofI+1);
	paralistP.push_back(mactProtoType.substr(sztParenofP, sztEndParenofP-sztParenofP-1));
	paralistI.push_back(mactInst.substr(sztParenofI, sztEndParanofI-sztParenofI-1));

	for (int i = 0; i < paralistP.size(); ++i)
	{
		Variable *tempVar = getVariable(paralistI[i]);
		if (tempVar != NULL)
		{
			std::string sortNameI = tempVar->sortRef->fullName();
			// (*ostErrPtr) << "SSS sortNameI (" << sortNameI << ")"<< " ParalistP[i] (" << paralistP[i]  <<")" << std::endl;
			if (paralistP[i] != sortNameI)
				return false;
		//Objects *tempObj = getObjects(paralistI[i]);

			//		(*ostErrPtr) << "..." << paralistI[i] << ":" << tempVar->fullName() << "..." << sortNameI;
		}
	}

	//(*ostErrPtr) << std::endl;
	return true;
}


bool Translator::testIndexofAction()
{
	std::list<AssoList*>::iterator listIt = assolists.begin();
	for (; listIt != assolists.end(); ++listIt)
	{
		if ((*listIt)->assoListA.empty())
			return false;
	}


	return true;
}

/* Class instance methods for general setup, etc. */

// Creates and adds a new sort to the translator's data structures without translating or outputting it.
Sort* Translator::createInternalSort(const char *newSortName, std::list<Sort*> subsorts)
{
    Sort* retVal = NULL;
    if(newSortName != NULL)
    {
        bool alreadyDeclared = true;
        std::string newSortStr = newSortName;
        // Add the sort if it isn't already in the symbol table.
        retVal = this->getSort(newSortStr);
        if(retVal == NULL)
        {
            alreadyDeclared = false;
            retVal = new Sort(newSortStr, Translator::sanitizeSortName(newSortStr));
            int addSymResult = this->addSort(retVal);
            if(addSymResult != SymbolTable::ADDSYM_OK)
            {
                if(addSymResult == SymbolTable::ADDSYM_DUP)
                {   // Just grab the already-declared sort.
                    delete retVal;
                    retVal = NULL;
                    retVal = this->getSort(newSortStr);
                    alreadyDeclared = true;
                }
                else
                {   // An error happened, null out the return value.
                    delete retVal;
                    retVal = NULL;
                }
            }
            else
            {
                // Try to create (or get) a default variable for the sort, connect the two if nothing goes wrong.
                std::string tempName = retVal->fullName();
                std::string tempTransName = retVal->fullTransName();
                std::string tempVarName = Translator::sortNameToVariable(tempName);
                Variable* tempVar = mainTrans.getVariable(tempVarName);
                if(tempVar == NULL)
                {
                    std::string tempTransVarName = Translator::sortNameToVariable(tempTransName);
                    tempVar = new Variable(tempVarName, tempTransVarName);
                    if(mainTrans.addVariable(tempVar) != SymbolTable::ADDSYM_OK)
                    {
                        delete tempVar;
                        tempVar = NULL;
                        retVal = NULL; // Won't affect the translator's storage of the (incomplete) sort.
                    }
                    else
                    {
                        tempVar->sortRef = retVal;
                    }
                }
                if(tempVar != NULL)
                {
                    retVal->sortVar = tempVar;
                }
            }
        }
        // Add subsorts to the sort's list.
        if(retVal != NULL && !subsorts.empty())
        {
            for(std::list<Sort*>::iterator lIter = subsorts.begin(); lIter != subsorts.end(); ++lIter)
            {
                if((*lIter) != NULL)
                {
                    retVal->subsorts.push_back(*lIter);
                }
            }
        }
        // If the sort is new and is a "something*" sort, make sure its child ("something")
        // is declared too, and link them together.
        if(!alreadyDeclared && newSortStr.length() > 0 && newSortStr[newSortStr.length()-1] == '*')
        {
            // Now find/create the child "something" sort.
            std::string nonStarIdent;
            nonStarIdent = newSortStr.substr(0, newSortStr.length()-1);

            // Check if the child already exists before proceeding with declaration etc.
            Sort *nonStarSort = mainTrans.getSort(nonStarIdent);
            if(nonStarSort == NULL)
            {   // Declare "something" so it can be added as the child of "something*".
                std::list<Sort*> nonStarSubsorts; // Empty on purpose.
                nonStarSort = this->createInternalSort(nonStarIdent.c_str(), nonStarSubsorts);
            }
            if(nonStarSort != NULL)
            {
                // Add "something" to subsorts.
                retVal->subsorts.push_back(nonStarSort);
            }

            // Create an object "none" and associate it with the "something*" sort.
            std::string noneName = "none";
            Object* noneObj = new Object(noneName, Translator::sanitizeObjectName(noneName));
            int noneAddResult = mainTrans.addObject(noneObj);
            if(noneAddResult == SymbolTable::ADDSYM_OK)
            {
                retVal->domainObjs.push_back(noneObj);
            }
        }
    }
    return retVal;
}

// Creates and adds a new object to the translator's data structures without translating or outputting it.
Object* Translator::createInternalObject(const char *newObjName, std::list<Sort*> params, Sort* ofSort)
{
    Object* retVal = NULL;
    if(newObjName != NULL && ofSort != NULL)
    {
        std::string newObjStr = newObjName;
        retVal = new Object(newObjStr, Translator::sanitizeObjectName(newObjStr));
        for(std::list<Sort*>::iterator lIter = params.begin(); lIter != params.end(); ++lIter)
        {
            if((*lIter) != NULL)
            {
                retVal->params.push_back(*lIter);
            }
        }
        int addSymResult = this->addObject(retVal);
        if(addSymResult != SymbolTable::ADDSYM_OK)
        {   // Something went wrong adding the object, skip connecting & translating it.
            if(addSymResult == SymbolTable::ADDSYM_DUP)
            {   // Duplicate object. don't bother adding it.
                delete retVal;
                retVal = NULL;
            }
            else
            {   // A real object error. Skip adding it.
                delete retVal;
                retVal = NULL;
            }
        }
        else
        {   // Object add went okay, connect the sort to the object.
            ofSort->domainObjs.push_back(retVal);
        }
    }
    return retVal;
}

// Creates and adds a new number range (child of Object) to the translator's data structures without translating or outputting it.
NumberRange* Translator::createInternalNumRange(const char *newObjName, const char *newMin, const char *newMax, Sort* ofSort)
{
    NumberRange* retVal = NULL;
    if(newObjName != NULL && newMin != NULL && newMax != NULL && ofSort != NULL)
    {
        std::string newObjStr = newObjName;
        retVal = new NumberRange();
        retVal->name = newObjStr;
        retVal->transName = Translator::sanitizeObjectName(newObjStr);
        retVal->min = newMin;
        retVal->max = newMax;
        int addSymResult = this->addObject(retVal);
        if(addSymResult != SymbolTable::ADDSYM_OK)
        {   // Something went wrong adding the object, skip connecting & translating it.
            if(addSymResult == SymbolTable::ADDSYM_DUP)
            {   // Duplicate object. don't bother adding it.
                delete retVal;
                retVal = NULL;
            }
            else
            {   // A real object error. Skip adding it.
                delete retVal;
                retVal = NULL;
            }
        }
        else
        {   // Object add went okay, connect the sort to the object.
            ofSort->domainObjs.push_back(retVal);
        }
    }
    return retVal;
}


// Allocates a new Query instance and assigns it to tempQuery.
void Translator::allocateNewTempQuery(bool deallocateFirst)
{
    if(deallocateFirst && tempQuery != NULL)
    {
        delete tempQuery;
        tempQuery = NULL;
    }
    tempQuery = new Query();
}

// Sets a translator instance's output stream to the passed stream.
void Translator::setOutput(std::ostream &newOst)
{
    if(ostOutPtr != NULL)
    {
        ostOutPtr->rdbuf(newOst.rdbuf());
    }
}

// Sets a translator instance's error output stream to the passed stream.
void Translator::setErrorOutput(std::ostream &newOst)
{
    if(ostErrPtr != NULL)
    {
        ostErrPtr->rdbuf(newOst.rdbuf());
    }
}

// Outputs the contents of str to wherever the translator's output stream is aimed.
void Translator::output(std::string &str, bool endWithNewline)
{
    (*ostOutPtr) << str;
    if(endWithNewline)
    {
        (*ostOutPtr) << std::endl;
    }
    ostOutPtr->flush();
}

// Outputs the contents of c_str to wherever the translator's output stream is aimed.
void Translator::output(const char *c_str, bool endWithNewline)
{
    if(c_str != NULL)
    {
        (*ostOutPtr) << c_str;
        if(endWithNewline)
        {
            (*ostOutPtr) << std::endl;
        }
        ostOutPtr->flush();
    }
}

// Outputs the contents of oss to wherever the translator's output stream is aimed.
void Translator::output(std::ostringstream &oss, bool endWithNewline)
{
    (*ostOutPtr) << oss.str();
    if(endWithNewline)
    {
        (*ostOutPtr) << std::endl;
    }
    ostOutPtr->flush();
}

// Outputs the contents of str to wherever the translator's error output stream is aimed.
void Translator::error(std::string &str, bool endWithNewline)
{
    (*ostErrPtr) << str;
    if(endWithNewline)
    {
        (*ostErrPtr) << std::endl;
    }
//  output(str,endWithNewline);
}

// Outputs the contents of c_str to wherever the translator's error output stream is aimed.
void Translator::error(const char *c_str, bool endWithNewline)
{
    if(c_str != NULL)
    {
        (*ostErrPtr) << c_str;
        if(endWithNewline)
        {
            (*ostErrPtr) << std::endl;
        }
//      output(c_str,endWithNewline);
    }
}

// Outputs the contents of oss to wherever the translator's error output stream is aimed.
void Translator::error(std::ostringstream &oss, bool endWithNewline)
{
    (*ostErrPtr) << oss.str();
    if(endWithNewline)
    {
        (*ostErrPtr) << std::endl;
    }
//  output(oss,endWithNewline);
}

// Destructor. Deallocates all memory associated with the list attributes.
Translator::~Translator()
{
    if(this->tempQuery != NULL)
    {
        delete tempQuery;
        tempQuery = NULL;
    }
    std::list<Constant*>::iterator cIter = constants.begin();
    while(cIter != constants.end())
    {
        delete *cIter;
        ++cIter;
    }
    constants.clear();
    std::list<Object*>::iterator oIter = objects.begin();
    while(oIter != objects.end())
    {
        delete *oIter;
        ++oIter;
    }
    objects.clear();
    std::list<Sort*>::iterator sIter = sorts.begin();
    while(sIter != sorts.end())
    {
        delete *sIter;
        ++sIter;
    }
    sorts.clear();
    std::list<Variable*>::iterator vIter = variables.begin();
    while(vIter != variables.end())
    {
        delete *vIter;
        ++vIter;
    }
    variables.clear();
    std::list<Query*>::iterator qIter = queries.begin();
    while(qIter != queries.end())
    {
        delete *qIter;
        ++qIter;
    }
    queries.clear();

	std::list<AssoList*>::iterator aIter = assolists.begin();
	while(aIter != assolists.end())
	{
		delete *aIter;
		++aIter;
	}
	assolists.clear();
    // Reset and deallocate the internal ostream pointers.
    if(ostNullPtr != NULL)
    {
        if(ostOutPtr != NULL)
        {
            ostOutPtr->rdbuf(ostNullPtr->rdbuf());
        }
        if(ostErrPtr != NULL)
        {
            ostErrPtr->rdbuf(ostNullPtr->rdbuf());
        }
    }
    delete ostOutPtr;
    delete ostErrPtr;
    delete ostNullPtr;
    // Close fNull so we don't leave an open file handle.
    fNull.close();
}
