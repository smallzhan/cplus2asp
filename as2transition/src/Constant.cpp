#include "Constant.h"

// Default constructor.
Constant::Constant()
{
	name = "";
	blnIsAction = false;
	blnIsBoolean = false;
	blnIsRigid = false;
}

// Full constructor.
Constant::Constant(std::string &newName, bool newBlnIsAction, bool newBlnIsBoolean, bool newBlnIsRigid)
{
	name = newName;
	blnIsAction = newBlnIsAction;
	blnIsBoolean = newBlnIsBoolean;
	blnIsRigid = newBlnIsRigid;
}

// Destructor.
Constant::~Constant()
{
	// Intentionally empty.
}

// Accessor for name.
std::string Constant::getName()
{
	return name;
}

// Mutator for name.
void Constant::setName(std::string &newName)
{
	name = newName;
}

// Accessor for blnIsAction.
bool Constant::getBlnIsAction()
{
	return blnIsAction;
}

// Mutator for blnIsAction.
void Constant::setBlnIsAction(bool newBlnIsAction)
{
	blnIsAction = newBlnIsAction;
}

// Accessor for blnIsBoolean.
bool Constant::getBlnIsBoolean()
{
	return blnIsBoolean;
}

// Mutator for blnIsBoolean.
void Constant::setBlnIsBoolean(bool newBlnIsBoolean)
{
	blnIsBoolean = newBlnIsBoolean;
}

// Accessor for blnIsRigid.
bool Constant::getBlnIsRigid()
{
	return blnIsRigid;
}

// Mutator for blnIsRigid.
void Constant::setBlnIsRigid(bool newBlnIsRigid)
{
	blnIsRigid = newBlnIsRigid;
}
