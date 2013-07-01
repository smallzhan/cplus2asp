#ifndef CONSTANT_DOT_H
#define CONSTANT_DOT_H

#include <string>

/**
 * Represents a basic constant from an action description. Predicates point to an instance of this class and use it to determine if they count as boolean or action predicates.
 */
class Constant
{
  public:
	/**
	 * Default constructor. Sets member variables to 0 or equivalent.
	 */
	Constant();
	
	/**
	 * Full constructor.
	 * @param newName - The base name for the constant.
	 * @param newBlnIsAction - An optional parameter setting whether or not the constant is an action. Defaults to false.
	 * @param newBlnIsBoolean - An optional parameter setting whether or not the constant has a boolean domain. Defaults to false.
	 * @param newBlnIsRigid - An optional parameter setting whether or not the constant is rigid. Defaults to false.
	 */
	Constant(std::string &newName, bool newBlnIsAction=false, bool newBlnIsBoolean=false, bool newBlnIsRigid=false);
	
	/**
	 * Destructor. Present for completeness, but does nothing.
	 */
	virtual ~Constant();
	
	/**
	 * Accessor for name.
	 * @return The string name.
	 */
	std::string getName();
	
	/**
	 * Mutator for name.
	 * @param newName - The new value for name.
	 */
	void setName(std::string &newName);
	
	/**
	 * Accessor for blnIsAction.
	 * @return The current value of blnIsAction.
	 */
	bool getBlnIsAction();
	
	/**
	 * Mutator for blnIsAction.
	 * @param newBlnIsAction - The new value for blnIsAction.
	 */
	void setBlnIsAction(bool newBlnIsAction);
	
	/**
	 * Accessor for blnIsBoolean.
	 * @return The current value of blnIsBoolean.
	 */
	bool getBlnIsBoolean();
	
	/**
	 * Mutator for blnIsBoolean.
	 * @param newBlnIsBoolean - The new value for blnIsBoolean.
	 */
	void setBlnIsBoolean(bool newBlnIsBoolean);
	
	/**
	 * Accessor for blnIsRigid.
	 * @return The current value of blnIsRigid.
	 */
	bool getBlnIsRigid();
	
	/**
	 * Mutator for blnIsRigid.
	 * @param newBlnIsRigid - The new value for blnIsRigid.
	 */
	void setBlnIsRigid(bool newBlnIsRigid);
	
  private:
	std::string name; ///< The base name of the constant.
	bool blnIsAction; ///< Tracks if the constant counts as an action (affects where and how predicates of this type are displayed in solutions). Used with h-style predicates.
	bool blnIsBoolean; ///< Tracks if the constant's domain is boolean (true,false) or not. Used for h-style predicates with eq-style inner predicates.
	bool blnIsRigid; ///< Tracks if the constant is a rigid fluent (affects where and how predicates of this type are displayed). Used with rigid h-style predicates.
};

#endif // CONSTANT_DOT_H
