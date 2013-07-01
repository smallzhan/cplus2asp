#include "Constant.h"

// Default constructor.
Constant::Constant() : Element()
{
    elemType = ELEM_CONST;
    constType = CONST_UNKNOWN;
    domain = NULL;
}

// Full constructor.
Constant::Constant(std::string _name, std::string _transName) : Element(_name, _transName)
{
    elemType = ELEM_CONST;
    constType = CONST_UNKNOWN;
    domain = NULL;
}

// Returns the full name (including parameters) of this object.
std::string Constant::fullName()
{
    std::string tempStr = name;
    if(!params.empty())
    {
        tempStr += "(";
        tempStr += utils::elementVectorToFullNameString<Sort*>(params);
        tempStr += ")";
    }
    return tempStr;
}

// Returns the full translated name (including parameters) of this object.
std::string Constant::fullTransName()
{
    std::string tempStr = transName;
    if(!params.empty())
    {
        tempStr += "(";
        tempStr += utils::elementVectorToFullTransNameString<Sort*>(params);
        tempStr += ")";
    }
    return tempStr;
}

// Standard toString function.
std::string Constant::toString()
{
    // Start with the basic Element info, then add on Constant-specific stuff.
    std::string tempStr = Element::toString();
    tempStr += "\n  [Constant]";
    tempStr += "\n  params = (";
    if(!params.empty())
    {
        tempStr += utils::elementVectorToFullNameString<Sort*>(params, ", ", true);
    }
    tempStr += ")";
    tempStr += "\n  domain = ";
    // If we don't have a domain yet, just say NULL.
    if(domain == NULL)
    {
        tempStr += "NULL";
    }
    else
    {
        tempStr += "\"";
        tempStr += domain->fullName();
        tempStr += "\"";
    }
    tempStr += "\n  constType = ";
    // Print out the English version of the possible enum values of constType.
    tempStr += Constant::constTypeToString(constType);
    return tempStr;
}

// Generates a string representation of a Constant's type.
std::string Constant::constTypeToString(enum ConstantType _constType)
{
    std::string tempStr = "";
    // Print out the English version of the possible enum values of constType.
    if(_constType == CONST_ACTION)
    {
        tempStr = "action";
    }
    else if(_constType == CONST_ABACTION)
    {
        tempStr = "abAction";
    }
    else if(_constType == CONST_MACROACTION)
    {
        tempStr = "macroAction";
    }
    else if(_constType == CONST_ATTRIBUTE)
    {
        tempStr = "attribute";
    }
    else if(_constType == CONST_EXOGENOUSACTION)
    {
        tempStr = "exogenousAction";
    }
    else if(_constType == CONST_INERTIALFLUENT)
    {
        tempStr = "inertialFluent";
    }
    else if(_constType == CONST_RIGID)
    {
        tempStr = "rigid";
    }
    else if(_constType == CONST_SDFLUENT)
    {
        tempStr = "sdFluent";
    }
    else if(_constType == CONST_SIMPLEFLUENT)
    {
        tempStr = "simpleFluent";
    }
    else if(_constType == CONST_ADDITIVEACTION)
    {
        tempStr = "additiveAction";
    }
    else if(_constType == CONST_ADDITIVEFLUENT)
    {
        tempStr = "additiveFluent";
    }
    else
    {   // Unknown or unrecognized constant type.
        tempStr = "UNKNOWN";
    }
    return tempStr;
}

// Destructor.
Constant::~Constant()
{
    params.clear();
    domain = NULL;
}

