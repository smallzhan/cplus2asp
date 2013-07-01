#include "Sort.h"

// Default constructor.
Sort::Sort() : Element()
{
	elemType = ELEM_SORT;
	domainObjs.clear();
	subsorts.clear();
	sortVar = NULL;
}

// Full constructor.
Sort::Sort(std::string _name, std::string _transName) : Element(_name, _transName)
{
	elemType = ELEM_SORT;
	domainObjs.clear();
	subsorts.clear();
	sortVar = NULL;
}

// Checks if this sort is any of the "internal" fluent sorts.
bool Sort::isActionSort()
{
	bool retVal = false; // Start pessimistic.
	std::string tempName = this->fullName();
	if(tempName == "abAction" || tempName == "action" || tempName == "additiveAction" || tempName == "attribute" || tempName == "exogenousAction")
	{
		retVal = true;
	}
	return retVal;
}

// Checks if this sort is any of the "internal" fluent sorts.
bool Sort::isFluentSort()
{
	bool retVal = false; // Start pessimistic.
	std::string tempName = this->fullName();
	if(tempName == "additiveFluent" || tempName == "fluent" || tempName == "inertialFluent" || tempName == "rigid" || tempName == "sdFluent" || tempName == "simpleFluent")
	{
		retVal = true;
	}
	return retVal;
}

// Generates the original full name of this element.
std::string Sort::fullName()
{
	std::string tempStr = name;
	return tempStr;
}

// Generates the translated full name of this element.
std::string Sort::fullTransName()
{
	std::string tempStr = transName;
	return tempStr;
}

// Standard toString function.
std::string Sort::toString()
{
	// Start with the basic Element info, then add on Sort-specific stuff.
	std::string tempStr = Element::toString();
	tempStr += "\n  [Sort]";
	tempStr += "\n  domainObjs = ";
	tempStr += utils::elementVectorToFullNameString<Object*>(domainObjs, ", ", true);
	tempStr += "\n  subsorts = ";
	tempStr += utils::elementVectorToFullNameString<Sort*>(subsorts, ", ", true);
	tempStr += "\n  sortvar = \"";
	tempStr += sortVar->name;
	tempStr += "\"";
	return tempStr;
}

// Destructor.
Sort::~Sort()
{
	domainObjs.clear();
	subsorts.clear();
}
