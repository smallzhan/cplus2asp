#include "parser_types.h"
#include "Translator.h"
#include "parser.h"

extern std::ostringstream ltsyyossErr;

// Default constructor. Initializes attributes to NULL.
PT_constant_binder_t::PT_constant_binder_t()
{
	constType = Constant::CONST_UNKNOWN;
	domain = NULL;
	attributeOf = NULL;
}

// Destructor. Resets all to NULL.
PT_constant_binder_t::~PT_constant_binder_t()
{
	constType = Constant::CONST_UNKNOWN;
	domain = NULL;
	attributeOf = NULL;
}

/* ParseElement methods. */

size_t ParseElement::extraClauseCount = 0;

// Constructor.
ParseElement::ParseElement()
{
	elemType = PELEM_PELEM;
	parenBefore = parenAfter = false;
	timeStamp = "";
}

// If the element's timeStamp isn't blank, propogates its value to any children of the element.
void ParseElement::propogateTimeStamp()
{
	// Intentionally empty, nothing to do.
}

// Sets the element's timeStamp to newTimeStamp and propogates the value to any children of the element.
void ParseElement::propogateTimeStamp(std::string newTimeStamp)
{
	// No children to propogate to, just set timeStamp.
	this->timeStamp = newTimeStamp;
}

// Translator method.
std::string ParseElement::translate()
{
	std::string retVal = "";
	retVal += translateBeforeParen();
	retVal += translateAfterParen();
	return retVal;
}

// Alternate Translator method.
std::string ParseElement::translateAsValue()
{
	return this->translate();
}

// Helper to translate method that intelligently handles the value of parenBefore.
std::string ParseElement::translateBeforeParen()
{
	std::string retVal = "";
	if(parenBefore)
	{
		retVal = "(";
	}
	return retVal;
}

// Helper to translate method that intelligently handles the value of parenAfter.
std::string ParseElement::translateAfterParen()
{
	std::string retVal = "";
	if(parenAfter)
	{
		retVal = ")";
	}
	return retVal;
}

// Adds all the items from toBeAdded onto the end of the element's preStatements list.
void ParseElement::addPreStatements(std::list<std::string>& toBeAdded)
{
	extraClauses.insert(preStatements.end(), toBeAdded.begin(), toBeAdded.end());
}

// Adds all the items from toBeAdded onto the end of the element's extraClauses list.
void ParseElement::addExtraClauses(std::list<std::string>& toBeAdded)
{
	//---Somehow, only add extraClauses that aren't already there---
	extraClauses.insert(extraClauses.end(), toBeAdded.begin(), toBeAdded.end());
}

// Returns true if this or any pre/postOp elements are action constants.
bool ParseElement::hasActions()
{	// Base ParseElement can never be an action.
	return false;
}

// Returns true if this or any pre/postOp elements are fluent constants.
bool ParseElement::hasFluents()
{	// The base ParseElement is never a fluent.
	return false;
}

// Stub method that returns a blank string (for pointer-wise compatibility with BaseLikeElement's real version of this method).
std::string ParseElement::fullName()
{
	return std::string("");
}

// Destructor.
ParseElement::~ParseElement()
{
	// Intentionally empty.
}

/* SimpleUnaryOperator methods. */

// Constructor.
SimpleUnaryOperator::SimpleUnaryOperator() : ParseElement()
{
	elemType = PELEM_UOP;
	opType = UOP_UNKNOWN;
	postOp = NULL;
}

// If the element's timeStamp isn't blank, propogates its value to any children of the element.
void SimpleUnaryOperator::propogateTimeStamp()
{
	if(this->timeStamp != "" && postOp != NULL)
	{
		postOp->propogateTimeStamp(this->timeStamp);
	}
}

// Sets the element's timeStamp to newTimeStamp and propogates the value to any children of the element.
void SimpleUnaryOperator::propogateTimeStamp(std::string newTimeStamp)
{
	this->timeStamp = newTimeStamp;
	if(postOp != NULL)
	{
		postOp->propogateTimeStamp(newTimeStamp);
	}
}

// Translator method.
std::string SimpleUnaryOperator::translate()
{
	std::string retVal = "";
	retVal += translateBeforeParen();
	// Sanity check: is the argument to the operator not NULL?
	if(postOp != NULL)
	{
		// First, create the appropriate string representation of the operator for use later.
		std::string opStr = "";
		switch(opType)
		{
		case UOP_NOT:
			opStr = "not ";
			break;
		case UOP_NEGATIVE:
			opStr = "-";
			break;
		case UOP_ABS:
			opStr = "#abs";
			break;
		case UOP_EXOGENOUS:
			opStr = "exogenous";
			break;
		case UOP_INERTIAL:
			opStr = "inertial";
			break;
		case UOP_RIGID:
			opStr = "rigid";
			break;
		default:
			// Unknown operator, just put a space in opStr.
			opStr = " ";
		}
		// Then, perform different translations based on what the operator is.
		std::ostringstream ossStrMaker;
		switch(opType)
		{
		case UOP_NOT: // Logical negation (including logical "-").
			// Negation works differently for bare booleans, check for them.
			if(postOp->elemType == PELEM_CONSTLIKE)
			{
				ConstantLikeElement* constPostOp = (ConstantLikeElement*)postOp;
				if(constPostOp->constRef != NULL)
				{
					if(constPostOp->constRef->domain->name == "boolean")
					{
						ossStrMaker << "-" << constPostOp->translate();
					}
					else
					{	// Not a boolean constant, but still used in bare "-c" style, this doesn't make sense.
						ltsyystartParseError();
						ltsyyossErr << "Can't use \"-\" or \"not\" to negate non-Boolean constant \"" << constPostOp->fullName() << "\" without specifying which value is being negated. Try something like \"" << constPostOp->fullName() << "=some_value\".";
						ltsyyreportError();
					}
				}
			}
			else if(postOp->elemType == PELEM_VARLIKE && ((VariableLikeElement*)postOp)->isConstantVariable())
			{	// This variable actually stands for a constant of some kind, treat this as "not constant".
				// Throw up a warning, as using "-V" with V being a constant is not guaranteed to work.
				VariableLikeElement* varPostOp = (VariableLikeElement*)postOp;
				ltsyystartWarning();
				ltsyyossErr << "Using negation on variable \"" << varPostOp->fullName() << "\" representing constant type \"" << varPostOp->varRef->sortRef->fullName() << "\" is not a good idea, and is almost guaranteed to not work as expected unless you know exactly what you're doing.";
				ltsyyreportWarning();
				ossStrMaker << opStr << "(" << varPostOp->translateAsConstant("true") << ")";
			}
			else
			{	// Just a normal negation.
				ossStrMaker << opStr << "(" << postOp->translate() << ")";
			}
			retVal += ossStrMaker.str();
			ossStrMaker.str("");
			break;
		case UOP_NEGATIVE: // Numeric negative.
			retVal += opStr;
			if(postOp->elemType == PELEM_CONSTLIKE)
			{	// Special case: constant used as intermediate value.
				retVal += ((ConstantLikeElement*)postOp)->translateAsValue();
			}
			else
			{	// Normal operand.
				retVal += postOp->translate();
			}
			break;
		case UOP_ABS: // Absolute value.
			retVal += opStr;
			if(!postOp->parenBefore)
			{	// Ensure the value is encased in parentheses if it wasn't already.
				retVal += "(";
			}
			if(postOp->elemType == PELEM_CONSTLIKE)
			{	// Special case: constant used as intermediate value.
				retVal += ((ConstantLikeElement*)postOp)->translateAsValue();
			}
			else
			{	// Normal operand.
				retVal += postOp->translate();
			}
			if(!postOp->parenAfter)
			{	// Ensure the value is encased in parentheses if it wasn't already.
				retVal += ")";
			}
			break;
		case UOP_EXOGENOUS: // Exogenous declaration.
		case UOP_INERTIAL: // Inertial declaration.
		case UOP_RIGID: // Rigid declaration.
			// All three "operators" do the same thing, it's just a matter of what name to use.
			if(postOp->elemType == PELEM_CONSTLIKE)
			{
				ConstantLikeElement *constOpRef = (ConstantLikeElement*)postOp;
				Constant* constRef = constOpRef->constRef;
				retVal += opStr;
				retVal += "(";
				if(constRef != NULL)
				{	// Use the canonical translated constant name if it's available.
					retVal += constRef->transName;
				}
				else
				{	// Otherwise, just wing it with this instance's base name.
					retVal += Translator::sanitizeConstantName(constOpRef->baseName);
				}
				retVal += constOpRef->translateParams();
				retVal += ")";
			}
			else
			{
				ltsyystartParseError();
				ltsyyossErr << "Declaring \"" << postOp->fullName() << "\" as " << opStr << " is not supported.";
				ltsyyreportError();
			}
			break;
		default:
			// Unknown operator, just do a blind translation.
			retVal += opStr;
			retVal += postOp->translate();
			break;
		}
		// Collect any preStatements and extra clauses created during translation.
		this->addPreStatements(postOp->preStatements);
		this->addExtraClauses(postOp->extraClauses);
	}
	retVal += translateAfterParen();
	return retVal;
}

// Returns true if this or any pre/postOp elements are action constants.
bool SimpleUnaryOperator::hasActions()
{	// True if postOp contains an action.
	bool retVal = false;
	if(postOp != NULL)
	{
		retVal = postOp->hasActions();
	}
	return retVal;
}

// Returns true if this or any pre/postOp elements are fluent constants.
bool SimpleUnaryOperator::hasFluents()
{	// True if postOp contains an fluent.
	bool retVal = false;
	if(postOp != NULL)
	{
		retVal = postOp->hasFluents();
	}
	return retVal;
}

// Returns an original string representation of this operator and its operand.
std::string SimpleUnaryOperator::fullName()
{
	std::string retVal = "";
	if(postOp != NULL)
	{
		// Create a CCalc-compatible representation of the operator first.
		std::string opStr = "";
		switch(opType)
		{
		case UOP_NOT:
			opStr = "not ";
			break;
		case UOP_NEGATIVE:
			opStr = "-";
			break;
		case UOP_ABS:
			opStr = "abs ";
			break;
		case UOP_EXOGENOUS:
			opStr = "exogenous ";
			break;
		case UOP_INERTIAL:
			opStr = "inertial ";
			break;
		case UOP_RIGID:
			opStr = "rigid ";
			break;
		default:
			// Unknown operator, just put a space in opStr.
			opStr = " ";
		}
		retVal += opStr;
		retVal += postOp->fullName();
	}
	return retVal;
}

// Destructor.
SimpleUnaryOperator::~SimpleUnaryOperator()
{
	if(postOp != NULL)
	{
		delete postOp;
		postOp = NULL;
	}
}

/* SimpleBinaryOperator methods. */

// Constructor.
SimpleBinaryOperator::SimpleBinaryOperator() : ParseElement()
{
	elemType = PELEM_BOP;
	opType = BOP_UNKNOWN;
	preOp = NULL;
	postOp = NULL;
}

// If the element's timeStamp isn't blank, propogates its value to any children of the element.
void SimpleBinaryOperator::propogateTimeStamp()
{
	if(this->timeStamp != "")
	{
		if(preOp != NULL)
		{
			preOp->propogateTimeStamp(this->timeStamp);
		}
		if(postOp != NULL)
		{
			postOp->propogateTimeStamp(this->timeStamp);
		}
	}
}

// Sets the element's timeStamp to newTimeStamp and propogates the value to any children of the element.
void SimpleBinaryOperator::propogateTimeStamp(std::string newTimeStamp)
{
	this->timeStamp = newTimeStamp;
	if(this->timeStamp != "")
	{
		if(preOp != NULL)
		{
			preOp->propogateTimeStamp(newTimeStamp);
		}
		if(postOp != NULL)
		{
			postOp->propogateTimeStamp(newTimeStamp);
		}
	}
}

// Translator method.
std::string SimpleBinaryOperator::translate()
{
	std::string retVal = "";
	retVal += translateBeforeParen();
	// Sanity check: are both arguments to the operator not NULL?
	if(preOp != NULL && postOp != NULL)
	{
		// First, create the appropriate string representation of the operator for use later.
		std::string opStr = "";
		switch(opType)
		{
		case BOP_PLUS:
			opStr = " + ";
			break;
		case BOP_MINUS:
			opStr = " - ";
			break;
		case BOP_TIMES:
			opStr = " * ";
			break;
		case BOP_DIVIDE:
			opStr = " / ";
			break;
		case BOP_MOD:
			opStr = " \\ ";
			break;
		case BOP_AND:
			opStr = " & ";
			break;
		case BOP_OR:
			opStr = " | ";
			break;
		case BOP_EQUIV:
			opStr = " <-> ";
			break;
		case BOP_IMPL:
			opStr = " -> ";
			break;
		case BOP_EQ:
			opStr = "=";
			break;
		case BOP_NEQ:
			opStr = "!=";
			break;
		case BOP_DBL_EQ:
			opStr = " == ";
			break;
		case BOP_LTHAN:
			opStr = " < ";
			break;
		case BOP_GTHAN:
			opStr = " > ";
			break;
		case BOP_LTHAN_EQ:
			opStr = " <= ";
			break;
		case BOP_GTHAN_EQ:
			opStr = " >= ";
			break;
		default:
			// Unknown, just put a space in there.
			opStr = " ";
		}
		// Then, perform different translations based on what the operator is.
		// Lack of breaks is intentional.
		switch(opType)
		{
		// Math ops only get messy if constant-like objects get involved.
		case BOP_PLUS:
		case BOP_MINUS:
		case BOP_TIMES:
		case BOP_DIVIDE:
		case BOP_MOD:
			if(preOp->elemType == PELEM_CONSTLIKE)
			{	// Special case: constant used as intermediate value.
				retVal += ((ConstantLikeElement*)preOp)->translateAsValue();
			}
			else
			{	// Normal operand.
				retVal += preOp->translate();
			}
			retVal += opStr;
			if(postOp->elemType == PELEM_CONSTLIKE)
			{	// Special case: constant used as intermediate value.
				retVal += ((ConstantLikeElement*)postOp)->translateAsValue();
			}
			else
			{	// Normal operand.
				retVal += postOp->translate();
			}
			break;
		// Logic ops are just simple translate & concatentate operations.
		case BOP_AND:
		case BOP_OR:
		case BOP_EQUIV:
		case BOP_IMPL:
			if(preOp->elemType == PELEM_VARLIKE && ((VariableLikeElement*)preOp)->isConstantVariable())
			{	// Treat bare constant variables as though they were constants.
				retVal += ((VariableLikeElement*)preOp)->translateAsConstant("true");
			}
			else
			{
				retVal += preOp->translate();
			}
			retVal += opStr;
			if(postOp->elemType == PELEM_VARLIKE && ((VariableLikeElement*)postOp)->isConstantVariable())
			{	// Treat bare constant variables as though they were constants.
				retVal += ((VariableLikeElement*)postOp)->translateAsConstant("true");
			}
			else
			{
				retVal += postOp->translate();
			}
			break;
		// (In)Equality and comparisons are potentially different based on what's on either side of the operator.
		case BOP_EQ:
			retVal += this->translateEq(true, opStr);
			break;
		case BOP_NEQ:
			retVal += this->translateEq(false, opStr);
			break;
		case BOP_DBL_EQ:
			retVal += this->translateDblEq(opStr);
			break;
		case BOP_LTHAN:
		case BOP_GTHAN:
		case BOP_LTHAN_EQ:
		case BOP_GTHAN_EQ:
			retVal += this->translateIneq(opStr);
			break;
		default:
			// Unknown, just do a blind translation.
			retVal += preOp->translate();
			retVal += opStr;
			retVal += postOp->translate();
		}
		// Collect any preStatements and extra clauses created during translation.
		this->addPreStatements(preOp->preStatements);
		this->addExtraClauses(preOp->extraClauses);
		this->addPreStatements(postOp->preStatements);
		this->addExtraClauses(postOp->extraClauses);
	}
	else if(preOp == NULL)
	{	// If just preOp is NULL, pretend there's just postOp and translate it.
		if(postOp->elemType == PELEM_VARLIKE && ((VariableLikeElement*)postOp)->isConstantVariable())
		{	// Treat bare constant variables as though they were constants.
			retVal += ((VariableLikeElement*)postOp)->translateAsConstant("true");
		}
		else
		{
			retVal += postOp->translate();
		}
		this->addPreStatements(postOp->preStatements);
		this->addExtraClauses(postOp->extraClauses);
	}
	else if(postOp == NULL)
	{	// If just postOp is NULL, pretend there's just preOp and translate it.
		if(preOp->elemType == PELEM_VARLIKE && ((VariableLikeElement*)preOp)->isConstantVariable())
		{	// Treat bare constant variables as though they were constants.
			retVal += ((VariableLikeElement*)preOp)->translateAsConstant("true");
		}
		else
		{
			retVal += preOp->translate();
		}
		this->addPreStatements(preOp->preStatements);
		this->addExtraClauses(preOp->extraClauses);
	}
	retVal += translateAfterParen();
	return retVal;
}

// Internal helper to translate method, translates preOp (not) equals postOp.
std::string SimpleBinaryOperator::translateEq(bool isEq, std::string eqSym)
{
	std::string retVal = "";
	std::ostringstream ossStrMaker;
	if(preOp->elemType == PELEM_CONSTLIKE && postOp->elemType == PELEM_CONSTLIKE)
	{	// Special case: c=d indirect constant value assignment.
		ConstantLikeElement* constPreOp = (ConstantLikeElement*)preOp;
		ConstantLikeElement* constPostOp = (ConstantLikeElement*)postOp;
		if(constPreOp->constRef != NULL && constPostOp->constRef != NULL)
		{
			if(!isEq)
			{
				retVal += "not (";
			}
			// The assignment/comparison looks a little different if at least one term is a boolean.
			if(constPreOp->constRef->domain->name == "boolean" && constPostOp->constRef->domain->name == "boolean")
			{
				ossStrMaker << "(";
				ossStrMaker << "(";
				ossStrMaker << constPreOp->translate();
				ossStrMaker << " & ";
				ossStrMaker << constPostOp->translate();
				ossStrMaker << ")";
				
				ossStrMaker << " | ";
				
				ossStrMaker << "(";
				ossStrMaker << "-" << constPreOp->translate();
				ossStrMaker << " & ";
				ossStrMaker << "-" << constPostOp->translate();
				ossStrMaker << ")";
				ossStrMaker << ")";
			}
			else if(constPreOp->constRef->domain->name == "boolean")
			{
				ossStrMaker << "(";
				ossStrMaker << "(";
				ossStrMaker << constPreOp->translate();
				ossStrMaker << " & ";
				ossStrMaker << "h(eql(" << constPostOp->translate() << ",true)" << constPostOp->translateTimeStamp() << ")";
				ossStrMaker << ")";
				
				ossStrMaker << " | ";
				
				ossStrMaker << "(";
				ossStrMaker << "-" << constPreOp->translate();
				ossStrMaker << " & ";
				ossStrMaker << "h(eql(" << constPostOp->translate() << ",false)" << constPostOp->translateTimeStamp() << ")";
				ossStrMaker << ")";
				ossStrMaker << ")";
			}
			else if(constPostOp->constRef->domain->name == "boolean")
			{
				ossStrMaker << "(";
				ossStrMaker << "(";
				ossStrMaker << "h(eql(" << constPreOp->translate() << ",true)" << constPreOp->translateTimeStamp() << ")";
				ossStrMaker << " & ";
				ossStrMaker << constPostOp->translate();
				ossStrMaker << ")";
				
				ossStrMaker << " | ";
				
				ossStrMaker << "(";
				ossStrMaker << "h(eql(" << constPreOp->translate() << ",false)" << constPreOp->translateTimeStamp() << ")";
				ossStrMaker << " & ";
				ossStrMaker << "-" << constPostOp->translate();
				ossStrMaker << ")";
				ossStrMaker << ")";
			}
			else
			{	// Just a normal equality assertion/check.
				std::string tempVarName = constPreOp->constRef->domain->sortVar->fullTransName();
				ossStrMaker << "?[" << tempVarName << "]:(";
				ossStrMaker << "h(eql(" << constPreOp->translate() << "," << tempVarName << ")" << constPreOp->translateTimeStamp() << ")";
				ossStrMaker << " & ";
				ossStrMaker << "h(eql(" << constPostOp->translate() << "," << tempVarName << ")" << constPostOp->translateTimeStamp() << ")";
				ossStrMaker << ")";
			}
			retVal += ossStrMaker.str();
			ossStrMaker.str("");
			if(!isEq)
			{
				retVal += ")";
			}
		}
	}
	else if(preOp->elemType == PELEM_CONSTLIKE)
	{	// Special case: c=v direct constant value assignment.
		ConstantLikeElement* constPreOp = (ConstantLikeElement*)preOp;
		if(constPreOp->constRef != NULL && constPreOp->constRef->domain->name == "boolean" && (postOp->elemType == PELEM_BASELIKE || postOp->elemType == PELEM_CONSTLIKE || postOp->elemType == PELEM_OBJLIKE || postOp->elemType == PELEM_VARLIKE))
		{	// The assignment looks different if it's a boolean.
			if(((BaseLikeElement*)postOp)->baseName == "false" && ((BaseLikeElement*)postOp)->params.empty() && isEq)
			{
				retVal += "-";
			}
			else if(((BaseLikeElement*)postOp)->baseName == "true" && ((BaseLikeElement*)postOp)->params.empty() && !isEq)
			{
				retVal += "-";
			}
			retVal += constPreOp->translate();
		}
		else
		{	// Normal value assignment.
			if(!isEq)
			{
				retVal += "-";
			}
			retVal += "h(eql(";
			retVal += constPreOp->translate();
			retVal += ",";
			retVal += postOp->translate();
			retVal += ")";
			retVal += constPreOp->translateTimeStamp();
			retVal += ")";
		}
	}
	else if(preOp->elemType == PELEM_VARLIKE && ((VariableLikeElement*)preOp)->isConstantVariable() && postOp->elemType == PELEM_VARLIKE && ((VariableLikeElement*)postOp)->isConstantVariable())
	{	// Special case: V1=V2 direct constant (variable) assignment/comparison.
		// Leave as normal variables.
		retVal += preOp->translate();
		retVal += eqSym;
		retVal += postOp->translate();
	}
	else if(preOp->elemType == PELEM_VARLIKE && ((VariableLikeElement*)preOp)->isConstantVariable())
	{	// Special case; V=v constant variable value assignment.
		VariableLikeElement* varPreOp = (VariableLikeElement*)preOp;
		if(postOp->elemType == PELEM_BASELIKE || postOp->elemType == PELEM_CONSTLIKE || postOp->elemType == PELEM_OBJLIKE || postOp->elemType == PELEM_VARLIKE)
		{	// Try to catch boolean assignment, warn about ambiguous "false" case.
			std::string eqlVal;
			if(((BaseLikeElement*)postOp)->baseName == "false" && ((BaseLikeElement*)postOp)->params.empty())
			{
				ltsyystartWarning();
				ltsyyossErr << "Ambiguous assignment of value \"false\" to constant variable \"" << varPreOp->fullName() << "\". Assuming variable's constant(s) have boolean domains.";
				ltsyyreportWarning();
				if(isEq)
				{	// If it was a positive equals, "false" makes it negative.
					retVal += "-";
				}
				eqlVal = "true";
			}
			else if(((BaseLikeElement*)postOp)->baseName == "true" && ((BaseLikeElement*)postOp)->params.empty())
			{
				ltsyystartWarning();
				ltsyyossErr << "Ambiguous assignment of value \"true\" to constant variable \"" << varPreOp->fullName() << "\". Assuming variable's constant(s) have boolean domains.";
				ltsyyreportWarning();
				if(!isEq)
				{	// If it was a negative equals, "true" keeps it negative.
					retVal += "-";
				}
				eqlVal = "true";
			}
			else
			{
				eqlVal = postOp->translate();
			}
			retVal += varPreOp->translateAsConstant(eqlVal.c_str());
		}
		else
		{	// Normal value assignment.
			if(!isEq)
			{
				retVal += "-";
			}
			retVal += varPreOp->translateAsConstant(postOp->translate().c_str());
		}
	}
	else
	{	// Normal assignment / equality check.
		retVal += preOp->translate();
		retVal += eqSym;
		retVal += postOp->translate();
	}
	return retVal;
}

// Internal helper to translate method, translates preOp == postOp.
std::string SimpleBinaryOperator::translateDblEq(std::string eqSym)
{
	std::string retVal = "";
	std::ostringstream ossStrMaker;
	if(preOp->elemType == PELEM_CONSTLIKE && postOp->elemType == PELEM_CONSTLIKE)
	{	// Special case: c==d indirect constant value comparison.
		ConstantLikeElement* constPreOp = (ConstantLikeElement*)preOp;
		ConstantLikeElement* constPostOp = (ConstantLikeElement*)postOp;
		if(constPreOp->constRef != NULL && constPostOp->constRef != NULL)
		{
			// The assignment/comparison looks a little different if at least one term is a boolean.
			if(constPreOp->constRef->domain->name == "boolean" && constPostOp->constRef->domain->name == "boolean")
			{
				ossStrMaker << "(";
				ossStrMaker << "(";
				ossStrMaker << constPreOp->translate();
				ossStrMaker << " & ";
				ossStrMaker << constPostOp->translate();
				ossStrMaker << ")";
				
				ossStrMaker << " | ";
				
				ossStrMaker << "(";
				ossStrMaker << "-" << constPreOp->translate();
				ossStrMaker << " & ";
				ossStrMaker << "-" << constPostOp->translate();
				ossStrMaker << ")";
				ossStrMaker << ")";
			}
			else if(constPreOp->constRef->domain->name == "boolean")
			{
				ossStrMaker << "(";
				ossStrMaker << "(";
				ossStrMaker << constPreOp->translate();
				ossStrMaker << " & ";
				ossStrMaker << "h(eql(" << constPostOp->translate() << ",true)" << constPostOp->translateTimeStamp() << ")";
				ossStrMaker << ")";
				
				ossStrMaker << " | ";
				
				ossStrMaker << "(";
				ossStrMaker << "-" << constPreOp->translate();
				ossStrMaker << " & ";
				ossStrMaker << "h(eql(" << constPostOp->translate() << ",false)" << constPostOp->translateTimeStamp() << ")";
				ossStrMaker << ")";
				ossStrMaker << ")";
			}
			else if(constPostOp->constRef->domain->name == "boolean")
			{
				ossStrMaker << "(";
				ossStrMaker << "(";
				ossStrMaker << "h(eql(" << constPreOp->translate() << ",true)" << constPreOp->translateTimeStamp() << ")";
				ossStrMaker << " & ";
				ossStrMaker << constPostOp->translate();
				ossStrMaker << ")";
				
				ossStrMaker << " | ";
				
				ossStrMaker << "(";
				ossStrMaker << "h(eql(" << constPreOp->translate() << ",false)" << constPreOp->translateTimeStamp() << ")";
				ossStrMaker << " & ";
				ossStrMaker << "-" << constPostOp->translate();
				ossStrMaker << ")";
				ossStrMaker << ")";
			}
			else
			{	// Just a normal equality assertion/check.
				std::string tempVarName = constPreOp->constRef->domain->sortVar->fullTransName();
				ossStrMaker << "?[" << tempVarName << "]:(";
				ossStrMaker << "h(eql(" << constPreOp->translate() << "," << tempVarName << ")" << constPreOp->translateTimeStamp() << ")";
				ossStrMaker << " & ";
				ossStrMaker << "h(eql(" << constPostOp->translate() << "," << tempVarName << ")" << constPostOp->translateTimeStamp() << ")";
				ossStrMaker << ")";
			}
			retVal += ossStrMaker.str();
			ossStrMaker.str("");
		}
	}
	else if(preOp->elemType == PELEM_CONSTLIKE)
	{	// Special case: c==v direct constant value comparison.
		ConstantLikeElement* constPreOp = (ConstantLikeElement*)preOp;
		if(constPreOp->constRef != NULL && constPreOp->constRef->domain->name == "boolean" && (postOp->elemType == PELEM_BASELIKE || postOp->elemType == PELEM_CONSTLIKE || postOp->elemType == PELEM_OBJLIKE || postOp->elemType == PELEM_VARLIKE))
		{	// The assignment looks different if it's a boolean.
			if(((BaseLikeElement*)postOp)->baseName == "false" && ((BaseLikeElement*)postOp)->params.empty())
			{
				retVal += "-";
			}
			retVal += constPreOp->translate();
		}
		else
		{	// Normal value assignment.
			retVal += "h(eql(";
			retVal += constPreOp->translate();
			retVal += ",";
			retVal += postOp->translate();
			retVal += ")";
			retVal += constPreOp->translateTimeStamp();
			retVal += ")";
		}
	}
	else if(preOp->elemType == PELEM_VARLIKE && ((VariableLikeElement*)preOp)->isConstantVariable() && postOp->elemType == PELEM_VARLIKE && ((VariableLikeElement*)postOp)->isConstantVariable())
	{	// Special case: V1==V2 direct constant (variable) assignment/comparison.
		// Leave as normal variables.
		retVal += preOp->translate();
		retVal += eqSym;
		retVal += postOp->translate();
	}
	else if(preOp->elemType == PELEM_VARLIKE && ((VariableLikeElement*)preOp)->isConstantVariable())
	{	// Special case; V==v constant variable value comparison.
		// Leave as a normal variable unless the value is "true" or "false" (then assume boolean constant).
		VariableLikeElement* varPreOp = (VariableLikeElement*)preOp;
		bool booleanComparison = false;
		std::string eqlVal;
		if(postOp->elemType == PELEM_BASELIKE || postOp->elemType == PELEM_CONSTLIKE || postOp->elemType == PELEM_OBJLIKE || postOp->elemType == PELEM_VARLIKE)
		{	// Try to catch boolean comparison, warn about ambiguous "false" case.
			if(((BaseLikeElement*)postOp)->baseName == "false" && ((BaseLikeElement*)postOp)->params.empty())
			{
				ltsyystartWarning();
				ltsyyossErr << "Ambiguous comparison of value \"false\" to constant variable \"" << varPreOp->fullName() << "\". Assuming variable's constant(s) have boolean domains.";
				ltsyyreportWarning();
				// "false" makes it negative.
				retVal += "-";
				eqlVal = "true";
				booleanComparison = true;
			}
			else if(((BaseLikeElement*)postOp)->baseName == "true" && ((BaseLikeElement*)postOp)->params.empty())
			{
				ltsyystartWarning();
				ltsyyossErr << "Ambiguous comparison of value \"true\" to constant variable \"" << varPreOp->fullName() << "\". Assuming variable's constant(s) have boolean domains.";
				ltsyyreportWarning();
				eqlVal = "true";
				booleanComparison = true;
			}
		}
		if(booleanComparison)
		{	// It was a boolean comparison, translate as such.
			retVal += varPreOp->translateAsConstant(eqlVal.c_str());
		}
		else
		{	// Normal value comparison. Stop the right-hand side from becoming an "h(eql(..." thing if it's a constant.
			retVal += varPreOp->translate();
			retVal += eqSym;
			if(postOp->elemType == PELEM_CONSTLIKE)
			{
				if(((ConstantLikeElement*)postOp)->constRef != NULL)
				{	// Use the canonical tranlated constant name if it's available.
					retVal += ((ConstantLikeElement*)postOp)->constRef->transName;
				}
				else
				{	// Otherwise just wing it with the constant-like instance's information.
					retVal += Translator::sanitizeConstantName(((ConstantLikeElement*)postOp)->baseName);
				}
				retVal += ((ConstantLikeElement*)postOp)->translateParams();
			}
			else
			{	// It's not a constant, just pass it through the normal translation scheme.
				retVal += postOp->translate();
			}
		}
	}
	else
	{	// Normal equality check.
		retVal += preOp->translate();
		retVal += eqSym;
		retVal += postOp->translate();
	}
	return retVal;
}

// Internal helper to translate method, translates preOp [ineq] postOp.
std::string SimpleBinaryOperator::translateIneq(std::string opSym)
{
	std::string retVal = "";
	std::ostringstream ossStrMaker;
	if(preOp->elemType == PELEM_CONSTLIKE && postOp->elemType == PELEM_CONSTLIKE)
	{	// Special case: c<d (or similar) indirect constant value comparison against another constant.
		ConstantLikeElement* constPreOp = (ConstantLikeElement*)preOp;
		ConstantLikeElement* constPostOp = (ConstantLikeElement*)postOp;
		if(constPreOp->constRef->domain != NULL && constPostOp->constRef->domain != NULL)
		{
			if(constPreOp->constRef->domain->name != "boolean" && constPostOp->constRef->domain->name != "boolean")
			{
				std::string tempSortName;
				size_t starPos;
				Sort* tempSortPre = NULL;
				Sort* tempSortPost = NULL;
				std::string tempVarNamePre;
				std::string tempVarNamePost;
				// Turn any "something*" sorts into "something" sorts so the "none" value doesn't mess with the inequality.
				tempSortName = constPreOp->constRef->domain->fullName();
				starPos = tempSortName.find("*");
				if(starPos != std::string::npos)
				{	// Strip the "*" and find a sort variable with that name.
					tempSortName.replace(starPos, 1, "");
					tempSortPre = mainTrans.getSort(tempSortName);
					if(tempSortPre != NULL)
					{
						tempVarNamePre = tempSortPre->sortVar->fullTransName();
					}
					else
					{	// A bad situation, hopefully this flags the problem.
						tempVarNamePre = constPreOp->constRef->domain->fullTransName();
						ltsyystartWarning();
						ltsyyossErr << "Couldn't find a non-starred version of sort \"" << constPreOp->constRef->domain->fullName() << "\" to use in a \"" << opSym << "\" comparison. Using the starred version, but it will probably not work as expected.";
						ltsyyreportWarning();
					}
				}
				else
				{	// Not a "something*" sort, move along as usual.
					tempSortPre = constPreOp->constRef->domain;
					tempVarNamePre = tempSortPre->sortVar->fullTransName();
				}
				// Now with the other operand.
				tempSortName = constPostOp->constRef->domain->fullName();
				starPos = tempSortName.find("*");
				if(starPos != std::string::npos)
				{	// Strip the "*" and find a sort variable with that name.
					tempSortName.replace(starPos, 1, "");
					tempSortPost = mainTrans.getSort(tempSortName);
					if(tempSortPost != NULL)
					{
						tempVarNamePost = tempSortPost->sortVar->fullTransName();
					}
					else
					{	// A bad situation, hopefully this flags the problem.
						tempVarNamePost = constPostOp->constRef->domain->fullTransName();
						ltsyystartWarning();
						ltsyyossErr << "Couldn't find a non-starred version of sort \"" << constPostOp->constRef->domain->fullName() << "\" to use in a \"" << opSym << "\" comparison. Using the starred version, but it will probably not work as expected.";
						ltsyyreportWarning();
					}
				}
				else
				{	// Not a "something*" sort, move along as usual.
					tempSortPost = constPostOp->constRef->domain;
					tempVarNamePost = tempSortPost->sortVar->fullTransName();
				}
				
				if(tempVarNamePre == tempVarNamePost)
				{	// If the variables are the same, get a different variable for the postOp constant's domain (or create one if need be).
					tempVarNamePost = tempSortPost->sortVar->fullName() + "_1";
					Variable* postVar = mainTrans.getVariable(tempVarNamePost);
					if(postVar == NULL)
					{
						postVar = new Variable(tempVarNamePost, Translator::sanitizeVariableName(tempVarNamePost));
						postVar->sortRef = tempSortPost;
						mainTrans.addVariable(postVar);
						std::string preVarDecl = Translator::translateVariableDeclToString(postVar);
						preStatements.push_back(preVarDecl);
					}
					tempVarNamePost = postVar->fullTransName();
				}
				ossStrMaker << "?[" << tempVarNamePre << "," << tempVarNamePost << "]:(";
				ossStrMaker << "h(eql(" << constPreOp->translate() << "," << tempVarNamePre << ")" << constPreOp->translateTimeStamp() << ")";
				ossStrMaker << " & ";
				ossStrMaker << "h(eql(" << constPostOp->translate() << "," << tempVarNamePost << ")" << constPostOp->translateTimeStamp() << ")";
				ossStrMaker << " & ";
				ossStrMaker << tempVarNamePre << opSym << tempVarNamePost;
				ossStrMaker << ")";
			}
			else
			{	// "c<d" doesn't make sense with Boolean domain constants, throw an error.
				ltsyystartParseError();
				ltsyyossErr << "Cannot perform numeric comparison \"" << opSym << "\" on constants \"" << constPreOp->fullName() << "\" and \"" << constPostOp->fullName() << "\", at least one of their domains is Boolean.";
				ltsyyreportError();
			}
		}
		retVal += ossStrMaker.str();
		ossStrMaker.str("");
	}
	else if(preOp->elemType == PELEM_CONSTLIKE || postOp->elemType == PELEM_CONSTLIKE)
	{	// Special case: c<v (or similar) indirect constant value comparison against a value.
		ConstantLikeElement* constOp = NULL;
		ParseElement* otherOp = NULL;
		bool constFirst = false;
		if(preOp->elemType == PELEM_CONSTLIKE)
		{
			constOp = (ConstantLikeElement*)preOp;
			otherOp = postOp;
			constFirst = true;
		}
		else
		{
			constOp = (ConstantLikeElement*)postOp;
			otherOp = preOp;
			constFirst = false;
		}
		if(constOp->constRef->domain != NULL)
		{
			if(constOp->constRef->domain->name != "boolean")
			{
				std::string tempSortName;
				size_t starPos;
				Sort* tempSort = NULL;
				std::string tempVarName;
				// Turn any "something*" sorts into "something" sorts so the "none" value doesn't mess with the inequality.
				tempSortName = constOp->constRef->domain->fullName();
				starPos = tempSortName.find("*");
				if(starPos != std::string::npos)
				{	// Strip the "*" and find a sort variable with that name.
					tempSortName.replace(starPos, 1, "");
					tempSort = mainTrans.getSort(tempSortName);
					if(tempSort != NULL)
					{
						tempVarName = tempSort->sortVar->fullTransName();
					}
					else
					{	// A bad situation, hopefully this flags the problem.
						tempVarName = constOp->constRef->domain->fullTransName();
						ltsyystartWarning();
						ltsyyossErr << "Couldn't find a non-starred version of sort \"" << constOp->constRef->domain->fullName() << "\" to use in a \"" << opSym << "\" comparison. Using the starred version, but it will probably not work as expected.";
						ltsyyreportWarning();
					}
				}
				else
				{	// Not a "something*" sort, move along as usual.
					tempSort = constOp->constRef->domain;
					tempVarName = tempSort->sortVar->fullTransName();
				}
				ossStrMaker << "?[" << tempVarName << "]:(";
				ossStrMaker << "h(eql(" << constOp->translate() << "," << tempVarName << ")" << constOp->translateTimeStamp() << ")";
				ossStrMaker << " & ";
				if(constFirst)
				{
					ossStrMaker << tempVarName << opSym << otherOp->translate();
				}
				else
				{
					ossStrMaker << otherOp->translate() << opSym << tempVarName;
				}
				ossStrMaker << ")";
			}
			else
			{	// "c<v" doesn't make sense with Boolean domain constants, throw an error.
				ltsyystartParseError();
				ltsyyossErr << "Cannot perform numeric comparison \"" << opSym << "\" on Boolean constant \"" << constOp->fullName() << "\".";
				ltsyyreportError();
			}
		}
		retVal += ossStrMaker.str();
		ossStrMaker.str("");
	}
	else
	{	// Normal mathematical comparison.
		retVal += preOp->translate();
		retVal += opSym;
		retVal += postOp->translate();
	}
	return retVal;
}

// Returns true if this or any pre/postOp elements are action constants.
bool SimpleBinaryOperator::hasActions()
{	// True if preOp or postOp contains an action.
	bool retVal = false;
	if(preOp != NULL)
	{
		retVal |= preOp->hasActions();
	}
	if(postOp != NULL)
	{
		retVal |= postOp->hasActions();
	}
	return retVal;
}

// Returns true if this or any pre/postOp elements are fluent constants.
bool SimpleBinaryOperator::hasFluents()
{	// True if preOp or postOp contains a fluent.
	bool retVal = false;
	if(preOp != NULL)
	{
		retVal |= preOp->hasFluents();
	}
	if(postOp != NULL)
	{
		retVal |= postOp->hasFluents();
	}
	return retVal;
}

// Returns an original string representation of this operator and its operands.
std::string SimpleBinaryOperator::fullName()
{
	std::string retVal = "";
	if(preOp != NULL && postOp != NULL)
	{
		// Get a string representation of the CCalc operator first.
		std::string opStr = "";
		switch(opType)
		{
		case BOP_PLUS:
			opStr = " + ";
			break;
		case BOP_MINUS:
			opStr = " - ";
			break;
		case BOP_TIMES:
			opStr = " * ";
			break;
		case BOP_DIVIDE:
			opStr = " // ";
			break;
		case BOP_MOD:
			opStr = " mod ";
			break;
		case BOP_AND:
			opStr = " & ";
			break;
		case BOP_OR:
			opStr = " ++ ";
			break;
		case BOP_EQUIV:
			opStr = " <-> ";
			break;
		case BOP_IMPL:
			opStr = " ->> ";
			break;
		case BOP_EQ:
			opStr = "=";
			break;
		case BOP_DBL_EQ:
			opStr = " == ";
			break;
		case BOP_NEQ:
			opStr = "!=";
			break;
		case BOP_LTHAN:
			opStr = " < ";
			break;
		case BOP_GTHAN:
			opStr = " > ";
			break;
		case BOP_LTHAN_EQ:
			opStr = " =< ";
			break;
		case BOP_GTHAN_EQ:
			opStr = " >= ";
			break;
		default:
			// Unknown, just put a space in there.
			opStr = " ";
		}
		retVal += preOp->fullName();
		retVal += opStr;
		retVal += postOp->fullName();
	}
	else if(preOp == NULL)
	{
		retVal += postOp->fullName();
	}
	else if(postOp == NULL)
	{
		retVal += preOp->fullName();
	}
	return retVal;
}

// Destructor.
SimpleBinaryOperator::~SimpleBinaryOperator()
{
	if(preOp != NULL)
	{
		delete preOp;
		preOp = NULL;
	}
	if(postOp != NULL)
	{
		delete postOp;
		postOp = NULL;
	}
}

/* BigQuantifiers methods. */

// Constructor.
BigQuantifiers::BigQuantifiers() : ParseElement()
{
	elemType = PELEM_QUANT;
	postOp = NULL;
}

// If the element's timeStamp isn't blank, propogates its value to any children of the element.
void BigQuantifiers::propogateTimeStamp()
{
	if(this->timeStamp != "" && postOp != NULL)
	{
		postOp->propogateTimeStamp(this->timeStamp);
	}
}

// Sets the element's timeStamp to newTimeStamp and propogates the value to any children of the element.
void BigQuantifiers::propogateTimeStamp(std::string newTimeStamp)
{
	this->timeStamp = newTimeStamp;
	if(postOp != NULL)
	{
		postOp->propogateTimeStamp(newTimeStamp);
	}
}

// Translator method.
std::string BigQuantifiers::translate()
{
	std::string retVal = "";
	retVal += translateBeforeParen();
	// First, create a wrapping quantifier statement for each quantifier.
	std::list<std::pair<enum QuantifierType, ParseElement*>* >::iterator lIter;
	for(lIter = quants.begin(); lIter != quants.end(); ++lIter)
	{
		switch((*lIter)->first)
		{
		case QUANT_CONJ:
			retVal += "![";
			if((*lIter)->second != NULL)
			{
				retVal += (*lIter)->second->translate();
				// Collect any preStatements and extra clauses created during translation.
				this->addPreStatements((*lIter)->second->preStatements);
				this->addExtraClauses((*lIter)->second->extraClauses);
			}
			retVal += "]:(";
			break;
		case QUANT_DISJ:
			retVal += "?[";
			if((*lIter)->second != NULL)
			{
				retVal += (*lIter)->second->translate();
				// Collect any preStatements and extra clauses created during translation.
				this->addPreStatements((*lIter)->second->preStatements);
				this->addExtraClauses((*lIter)->second->extraClauses);
			}
			retVal += "]:(";
			break;
		default:
			// Unknown, just open a parenthesis.
			retVal += "(";
		}
	}
	// Next, translate whatever subformula was in the big quantifiers.
	if(postOp != NULL)
	{
		if(postOp->elemType == PELEM_VARLIKE && ((VariableLikeElement*)postOp)->isConstantVariable())
		{	// Treat bare constant variables as though they were constants.
			retVal += ((VariableLikeElement*)postOp)->translateAsConstant("true");
		}
		else
		{
			retVal += postOp->translate();
		}
		// Collect any preStatements and extra clauses created during translation.
		this->addPreStatements(postOp->preStatements);
		this->addExtraClauses(postOp->extraClauses);
	}
	// Finally, close the quantifier statements' open parentheses.
	for(size_t i = 0; i < quants.size(); i++)
	{
		retVal += ")";
	}
	retVal += translateAfterParen();
	return retVal;
}

// Returns true if this or any pre/postOp elements are action constants.
bool BigQuantifiers::hasActions()
{	// True if postOp contains an action.
	bool retVal = false;
	if(postOp != NULL)
	{
		retVal = postOp->hasActions();
	}
	return retVal;
}

// Returns true if this or any pre/postOp elements are fluent constants.
bool BigQuantifiers::hasFluents()
{	// True if postOp contains an fluent.
	bool retVal = false;
	if(postOp != NULL)
	{
		retVal = postOp->hasFluents();
	}
	return retVal;
}

// Returns an original string representation of the quantifiers and what's getting quantified.
std::string BigQuantifiers::fullName()
{
	std::string retVal = "";
	if(postOp != NULL && !quants.empty())
	{
		retVal += "[ ";
		std::list<std::pair<enum QuantifierType, ParseElement*>* >::iterator lIter;
		for(lIter = quants.begin(); lIter != quants.end(); ++lIter)
		{
			if((*lIter) != NULL && (*lIter)->second != NULL)
			{
				switch((*lIter)->first)
				{
				case QUANT_CONJ:
					retVal += "/\\ ";
					break;
				case QUANT_DISJ:
					retVal += "\\/ ";
					break;
				default:
					break;
				}
				retVal += (*lIter)->second->fullName();
			}
		}
		retVal += " | ";
		retVal += postOp->fullName();
		retVal += " ]";
	}
	return retVal;
}

// Destructor.
BigQuantifiers::~BigQuantifiers()
{
	for(std::list<std::pair<enum QuantifierType, ParseElement*>* >::iterator lIter = quants.begin(); lIter != quants.end(); ++lIter)
	{
		if((*lIter)->second != NULL)
		{
			delete (*lIter)->second;
		}
		delete (*lIter);
	}
	quants.clear();
	if(postOp != NULL)
	{
		delete postOp;
		postOp = NULL;
	}
}

/* BaseLikeElement methods. */

// Constructor.
BaseLikeElement::BaseLikeElement() : ParseElement()
{
	elemType = PELEM_BASELIKE;
	baseName = "";
}

// Translator method.
std::string BaseLikeElement::translate()
{
	std::string retVal = "";
	retVal += translateBeforeParen();
	retVal += Translator::sanitizeObjectName(baseName);
	retVal += this->translateParams();
	retVal += translateAfterParen();
	return retVal;
}

// Translator helper method for params.
std::string BaseLikeElement::translateParams()
{
	std::string retVal = "";
	if(!params.empty())
	{
		retVal += "(";
		for(std::vector<ParseElement*>::iterator vIter = params.begin(); vIter != params.end(); ++vIter)
		{	
			if(vIter != params.begin())
			{
				retVal += ",";
			}
			if(*vIter != NULL)
			{
				retVal += (*vIter)->translateAsValue();
				this->addExtraClauses((*vIter)->extraClauses);
			}
		}
		retVal += ")";
	}
	return retVal;
}

// If the element's timeStamp isn't blank, propogates its value to any children of the element.
void BaseLikeElement::propogateTimeStamp()
{
	if(this->timeStamp != "")
	{
		for(std::vector<ParseElement*>::iterator vIter = params.begin(); vIter != params.end(); ++vIter)
		{	
			if(*vIter != NULL)
			{
				(*vIter)->propogateTimeStamp(this->timeStamp);
			}
		}
	}
}

// Sets the element's timeStamp to newTimeStamp and propogates the value to any children of the element.
void BaseLikeElement::propogateTimeStamp(std::string newTimeStamp)
{
	this->timeStamp = newTimeStamp;
	for(std::vector<ParseElement*>::iterator vIter = params.begin(); vIter != params.end(); ++vIter)
	{	
		if(*vIter != NULL)
		{
			(*vIter)->propogateTimeStamp(this->timeStamp);
		}
	}
}

// Returns true if this or any pre/postOp elements are action constants.
bool BaseLikeElement::hasActions()
{	// The base "x-like" element is never an action.
	return false;
}

// Returns true if this or any pre/postOp elements are fluent constants.
bool BaseLikeElement::hasFluents()
{	// The base "x-like" element is never a fluent.
	return false;
}

// Outputs the original full name of the element, including parameters.
std::string BaseLikeElement::fullName()
{
	std::string retVal = this->baseName;
	if(!params.empty())
	{
		retVal += "(";
	}
	for(std::vector<ParseElement*>::iterator vIter = params.begin(); vIter != params.end(); ++vIter)
	{
		if(*vIter != NULL)
		{
			if(vIter != params.begin())
			{
				retVal += ",";
			}
			retVal += (*vIter)->fullName();
		}
	}
	if(!params.empty())
	{
		retVal += ")";
	}
	return retVal;
}

// Destructor.
BaseLikeElement::~BaseLikeElement()
{
	for(std::vector<ParseElement*>::iterator vIter = params.begin(); vIter != params.end(); ++vIter)
	{
		if(*vIter != NULL)
		{
			delete *vIter;
		}
	}
	params.clear();
}

/* ConstantLikeElement methods. */

// Constructor.
ConstantLikeElement::ConstantLikeElement() : BaseLikeElement()
{
	elemType = PELEM_CONSTLIKE;
	constRef = NULL;
}

// Translator method.
std::string ConstantLikeElement::translate()
{
	std::string retVal = "";
	retVal += translateBeforeParen();
	if(this->constRef != NULL)
	{
		// A bare constant-like element with Boolean domain is actually a shortcut for "c=true", translate accordingly.
		if(this->constRef->domain->name == "boolean")
		{
			retVal += "h(eql(";
		}
		// Regardless of Boolean or not, use the canonical translated constant name if it's available.
		retVal += constRef->transName;
	}
	else
	{	// Otherwise, just wing it with this instance's information.
		retVal += Translator::sanitizeConstantName(baseName);
	}
	retVal += this->translateParams();
	// Finish the bare Boolean constant translation (if applicable).
	if(this->constRef != NULL && this->constRef->domain->name == "boolean")
	{
		retVal += ",true)";
		retVal += this->translateTimeStamp();
		retVal += ")";
	}
	retVal += translateAfterParen();
	return retVal;
}

// Alternate intermediate value translator method.
std::string ConstantLikeElement::translateAsValue()
{
	std::string retVal = "";
	std::string extraClause = "";
	ParseElement::extraClauseCount++;
	retVal += translateBeforeParen();
	retVal += "X_Value_";
	retVal += utils::to_string(ParseElement::extraClauseCount);
	retVal += translateAfterParen();
	extraClause += "h(eql(";
	if(constRef != NULL)
	{	// Use the canonical translated constant name if it's available.
		extraClause += constRef->transName;
	}
	else
	{	// Otherwise, just wing it with this instance's base name.
		extraClause += Translator::sanitizeConstantName(baseName);
	}
	extraClause += this->translateParams();
	extraClause += ",X_Value_";
	extraClause += utils::to_string(ParseElement::extraClauseCount);
	extraClause += ")";
	extraClause += this->translateTimeStamp();
	extraClause += ")";
	extraClauses.push_back(extraClause);
	return retVal;
}

// Conditionally outputs the current time stamp if the constant is of a type that uses time stamps.
std::string ConstantLikeElement::translateTimeStamp()
{
	std::string retVal = "";
	if(this->constRef != NULL)
	{
		if(this->constRef->constType != Constant::CONST_RIGID)
		{	// If it's not a rigid, give it a time stamp.
			retVal += ",";
			retVal += this->timeStamp;
		}
	}
	else
	{	// If the constRef is NULL, we can't check if the constant needs a time step or not.
		// Assume it does, warn the user, and hope for the best.
		ltsyystartWarning();
		ltsyyossErr << "Can't figure out if \"" << this->fullName() << "\" needs a time step or not, assuming it does.";
		ltsyyreportWarning();
		
	}
	return retVal;
}

// Returns true if this or any pre/postOp elements are action constants.
bool ConstantLikeElement::hasActions()
{	// A Constant-like has an action if it is linked with an actual
	// constant and that constant is any action type.
	bool retVal = false;
	if(this->constRef != NULL)
	{
		switch(this->constRef->constType)
		{
		case Constant::CONST_ACTION:
		case Constant::CONST_ABACTION:
		case Constant::CONST_ATTRIBUTE:
		case Constant::CONST_EXOGENOUSACTION:
		case Constant::CONST_ADDITIVEACTION:
			retVal = true;
			break;
		default:
			// Nothing to do, retVal is already false.
			break;
		}
	}
	// Special check: even if constRef is NULL, if this element looks
	// like the reserved "contribution" element, then assume it's an action.
	else if(this->baseName == "contribution" && this->params.size() == 2)
	{
		retVal = true;
	}
	return retVal;
}

// Returns true if this or any pre/postOp elements are fluent constants.
bool ConstantLikeElement::hasFluents()
{	// A Constant-like has a fluent if it is linked with an actual
	// constant and that constant is any fluent type.
	bool retVal = false;
	if(this->constRef != NULL)
	{
		switch(this->constRef->constType)
		{
		case Constant::CONST_INERTIALFLUENT:
		case Constant::CONST_SDFLUENT:
		case Constant::CONST_SIMPLEFLUENT:
		case Constant::CONST_RIGID:
		case Constant::CONST_ADDITIVEFLUENT:
			retVal = true;
			break;
		default:
			// Nothing to do, retVal is already false.
			break;
		}
	}
	return retVal;
}

// Destructor.
ConstantLikeElement::~ConstantLikeElement()
{
	constRef = NULL;
}

/* ObjectLikeElement methods. */

// Constructor.
ObjectLikeElement::ObjectLikeElement() : BaseLikeElement()
{
	elemType = PELEM_OBJLIKE;
	objRef = NULL;
}

// Translator method.
std::string ObjectLikeElement::translate()
{
	std::string retVal = "";
	retVal += translateBeforeParen();
	if(objRef != NULL)
	{	// Use the canonical translated object name if it's available.
		retVal += objRef->transName;
	}
	else
	{	// Otherwise, just wing it with this instance's base name.
		retVal += Translator::sanitizeObjectName(baseName);
	}
	retVal += this->translateParams();
	retVal += translateAfterParen();
	return retVal;
}

// Returns true if this or any pre/postOp elements are action constants.
bool ObjectLikeElement::hasActions()
{	// An Object-like element is never an action.
	return false;
}

// Returns true if this is one of the few reserved fluent constants.
bool ObjectLikeElement::hasFluents()
{	// A Object-like element counts as a fluent if it's "true" or "false".
	bool retVal = false;
	if(this->fullName() == "true" || this->fullName() == "false")
	{
		retVal = true;
	}
	return retVal;
}

// Destructor.
ObjectLikeElement::~ObjectLikeElement()
{
	objRef = NULL;
}

/* VariableLikeElement methods. */

// Constructor.
VariableLikeElement::VariableLikeElement() : BaseLikeElement()
{
	elemType = PELEM_VARLIKE;
	varRef = NULL;
}

// Checks if the variable-like element is a constant variable.
bool VariableLikeElement::isConstantVariable()
{
	bool retVal = false;
	if(this->varRef != NULL && this->varRef->sortRef != NULL)
	{
		if(this->varRef->sortRef->isActionSort() || this->varRef->sortRef->isFluentSort())
		{
			retVal = true;
		}
	}
	return retVal;
}

// Translator method. Ignores parameters, as variables shouldn't have any.
std::string VariableLikeElement::translate()
{
	std::string retVal = "";
	retVal += translateBeforeParen();
	if(varRef != NULL)
	{	// Use the canonical translated variable name if it's available.
		retVal += varRef->transName;
	}
	else
	{	// Otherwise, just wing it with this instance's base name.
		retVal += Translator::sanitizeVariableName(baseName);
	}
	retVal += translateAfterParen();
	return retVal;
}

// Translates the variable as though it were a constant.
std::string VariableLikeElement::translateAsConstant(const char* eqlValue)
{
	std::string retVal = "";
	retVal += translateBeforeParen();
	retVal += "h(eql(";
	if(this->varRef != NULL && this->varRef->sortRef != NULL)
	{
		// Use the canonical translated variable name if it's available.
		retVal += this->varRef->transName;
	}
	else
	{	// Otherwise, just wing it with this instance's information.
		retVal += Translator::sanitizeVariableName(this->baseName);
	}
	// Add on the value to finish the "eql" part.
	retVal += ",";
	if(eqlValue != NULL)
	{
		retVal += eqlValue;
	}
	else
	{
		ltsyystartWarning();
		ltsyyossErr << "In trying to treat variable \"" << this->fullName() << "\" like a constant, no value given to assign to it. Using \"NULL\".";
		ltsyyreportWarning();
		retVal += "NULL";
	}
	retVal += ")";
	if(this->varRef != NULL && this->varRef->sortRef != NULL)
	{	// Check if it's a rigid variable or not (determines if timeStamp is used).
		if(this->varRef->sortRef->name == "rigid")
		{	// It's a rigid, no time stamp needed.
			// Intentionally empty.
		}
		else
		{	// Not a rigid, include time stamp.
			retVal += ",";
			retVal += this->timeStamp;
		}
	}
	else
	{	// Assume it's not rigid, and stick a time stamp on.
		ltsyystartWarning();
		ltsyyossErr << "In trying to treat variable \"" << this->fullName() << "\" like a constant, can't figure out if it is representing a rigid constant or not. Assuming it isn't.";
		ltsyyreportWarning();
		retVal += ",";
		retVal += this->timeStamp;
	}
	// Finish up the "h(eql(..." predicate.
	retVal += ")";
	retVal += translateAfterParen();
	return retVal;
}

// Returns true if this or any pre/postOp elements are action constants.
bool VariableLikeElement::hasActions()
{	// A Variable-like is an action if it is linked with an actual variable
	// whose sort is any of the "internal" action sorts.
	bool retVal = false;
	if(this->varRef != NULL && this->varRef->sortRef != NULL)
	{
		retVal = this->varRef->sortRef->isActionSort();
	}
	return retVal;
}

// Returns true if this or any pre/postOp elements are fluent constants.
bool VariableLikeElement::hasFluents()
{	// A Variable-like element counts as a fluent if it is linked to
	// a real Variable that isn't an "action" variable.
	// A broad definition, but necessary for certain laws.
	bool retVal = false;
	if(this->varRef != NULL && this->varRef->sortRef != NULL)
	{
//		retVal = !this->hasActions();
		retVal = this->varRef->sortRef->isFluentSort();
	}
	return retVal;
}

// Destructor.
VariableLikeElement::~VariableLikeElement()
{
	varRef = NULL;
}

