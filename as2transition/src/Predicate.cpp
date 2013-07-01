#include "Predicate.h"

// Default constructor.
Predicate::Predicate()
{
	name = "";
	mainTimeStamp = INT_MIN;
	subTimeStamp = INT_MIN;
	blnIsHPredicate = false;
	blnIsNegated = false;
	constType = NULL;
}

// Partial constructor.
Predicate::Predicate(std::string &newName)
{
	name = newName;
	mainTimeStamp = INT_MIN;
	subTimeStamp = INT_MIN;
	blnIsHPredicate = false;
	blnIsNegated = false;
	constType = NULL;
}

// Partial constructor for h-style predicates.
Predicate::Predicate(std::string &newName, int newTimeStamp1, int newTimeStamp2)
{
	name = newName;
	mainTimeStamp = newTimeStamp1;
	subTimeStamp = newTimeStamp2;
	blnIsHPredicate = true;
	blnIsNegated = false;
	constType = NULL;
}

// Destructor.
Predicate::~Predicate()
{
	// Intentionally empty.
}

// Accessor for name.
std::string Predicate::getName()
{
	return name;
}

// Mutator for name.
void Predicate::setName(std::string &newName)
{
	name = newName;
}

// Accessor for timeStamp.
int Predicate::getMainTimeStamp()
{
	return mainTimeStamp;
}

int Predicate::getSubTimeStamp()
{
	return subTimeStamp;
}

// Mutator for timeStamp.
void Predicate::setTimeStamp(int newTimeStamp1, int newTimeStamp2)
{
	mainTimeStamp = newTimeStamp1;
	subTimeStamp = newTimeStamp2;
}

// Accessor for blnIsHPredicate.
bool Predicate::getBlnIsHPredicate()
{
	return blnIsHPredicate;
}

// Mutator for blnIsHPredicate.
void Predicate::setBlnIsHPredicate(bool newblnIsHPredicate)
{
	blnIsHPredicate = newblnIsHPredicate;
}

// Accessor for blnIsNegated.
bool Predicate::getBlnIsNegated()
{
	return blnIsNegated;
}

// Mutator for blnIsNegated.
void Predicate::setBlnIsNegated(bool newBlnIsNegated)
{
	blnIsNegated = newBlnIsNegated;
}

// Accessor for constType.
Constant* Predicate::getConstType()
{
	return constType;
}

// Mutator for constType.
void Predicate::setConstType(Constant* newConstType)
{
	constType = newConstType;
}

// Pseudo-accessor for blnIsAction.
bool Predicate::getBlnIsAction()
{
	bool retVal = false;
	if(constType != NULL)
	{
		retVal = constType->getBlnIsAction();
	}
	return retVal;
}

// Pseudo-accessor for blnIsBoolean.
bool Predicate::getBlnIsBoolean()
{
	bool retVal = false;
	if(constType != NULL)
	{
		retVal = constType->getBlnIsBoolean();
	}
	return retVal;
}

// Re-creates an appropriate string representation of the predicate and returns it.
std::string Predicate::toPredicateString(bool stripHPredicate, bool transformEqPredicate)
{
	std::string retVal = "";
	// Add negation first if needed.
	if(blnIsNegated)
	{
		retVal += "-";
	}
	// Most of the special formatting only happens to h-style predicates, so check that first.
	if(blnIsHPredicate)
	{
		// Transforming an eq-style predicate overrides the other options, so check that next.
		if(transformEqPredicate && (name.find("eq(") == 0 || name.find("eql(") == 0))
		{	// It's an eq-style inner predicate, transform it!
			size_t nameStart = name.find("(") + 1;
			size_t nameEnd = std::string::npos;
			size_t valueEnd = name.find_last_of(")") - 1;
			size_t valueStart = valueEnd;
			int numParens = 0;
			// Go backwards through the string until we find the comma that separates the constant name from its value.
			while(valueStart > 0 && numParens >= 0)
			{
				if(name[valueStart] == ')')
				{
					numParens++;
				}
				else if(name[valueStart] == '(')
				{
					numParens--;
				}
				else if(name[valueStart] == ',' && numParens == 0)
				{ 	// We aren't embedded in a complex value and found a comma, there's our delimiter!
					nameEnd = valueStart - 1; // While we're here, note where the name stops.
					valueStart++;
					break;
				}
				valueStart--;
			}
			std::string tempConst = name.substr(nameStart, nameEnd - nameStart + 1);
			std::string tempValue = name.substr(valueStart, valueEnd - valueStart + 1);
			// Now that we have the name and value, check if it's a boolean domain (shortcuts if so!).
			if(constType != NULL && constType->getBlnIsBoolean())
			{
				if(tempValue.find("false") == 0)
				{	// It's false, so don't even list it (i.e., return an empty string).
					retVal = "";
				}
				else if(tempValue.find("true") == 0)
				{ 	// It's true, so don't bother with the =true nonsense.
					retVal += tempConst;
				}
				else
				{ 	// What?! Oh well, just do normal constant=value form and hope for the best.
					retVal += tempConst;
					retVal += "=";
					retVal += tempValue;
				}
			}
			else
			{	// It's not a boolean domain, so return the normal constant=value style.
				retVal += tempConst;
				retVal += "=";
				retVal += tempValue;
			}
		} // Next, see if the h() part needs to be added back on or not.
		else if(stripHPredicate)
		{	// We're stripping the outer h() mess, so just return name.
			retVal += name;
		}
		else
		{ 	// Just re-create the standard h-style predicate, no fireworks.
			retVal += "h(";
			retVal += name;
			// Check if the time step is valid (i.e., isn't a "special" step), add it if it's normal.
			if(mainTimeStamp != TIMELESS_STEP)
			{
				retVal += ",";
				retVal += StringUtils::to_string(mainTimeStamp);
			}
			if (subTimeStamp != TIMELESS_STEP)
			{
				retVal += ",";
				retVal += StringUtils::to_string(subTimeStamp);
			}
			retVal += ")";
		}
	}
	else
	{	// This predicate isn't special, just append the name and pop out.
		retVal += name;
	}
	return retVal;
}
