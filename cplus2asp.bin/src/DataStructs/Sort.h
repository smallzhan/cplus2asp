#ifndef SORT_H
#define SORT_H

#include <string>
#include <vector>

#include "Element.h"
#include "Object.h"
#include "Variable.h"
#include "utilities.h"

/**
 * The Sort class defines a C+ sort (i.e., domain of objects used as arguments and values).
 * Each Sort is set up to be aware of its objects and any subsorts it has.
 */
class Sort : public Element
{
public:
	std::vector<Object*> domainObjs; ///< Dynamic array to keep track of the objects specific to this sort.
	std::vector<Sort*> subsorts; ///< Dynamic array to track any subsorts of this sort.
	Variable* sortVar; ///< The default Variable associated with this sort.
	/**
	 * Default constructor. Calls Element's default constructor and initializes variables to blank (or equivalent).
	 */
	Sort();
	
	/**
	 * Full constructor. Calls Element's full constructor, saves the given varName, and initializes the domainObjs and subsorts vectors.
	 * @param _name - The C+ name of the sort.
	 * @param _transName - The ASP-compatible name of the sort.
	 */
	Sort(std::string _name, std::string _transName);
	
	/**
	 * Examines its own name and determines if it is any of the special
	 * "internal" sorts for tracking action constants.
	 * @return True if it is an action sort, false otherwise.
	 */
	bool isActionSort();
	
	/**
	 * Examines its own name and determines if it is any of the special
	 * "internal" sorts for tracking fluent constants.
	 * @return True if it is a fluent sort, false otherwise.
	 */
	bool isFluentSort();
	
	/**
	 * Generates the original full name of this element, including full parameter names (if any).
	 * @return A string representation of this element's base name plus a
	 * parenthesized, comma-separated list of the full names of any parameters
	 * (if it has any).
	 */
	virtual std::string fullName();
	
	/**
	 * Generates the translated full name of this element, including
	 * translated full parameter names (if any).
	 * @return A string representation of this element's translated base name
	 * plus a parenthesized, comma-separated list of the full names of any 
	 * parameters (if it has any).
	 */
	virtual std::string fullTransName(); 
	
	/**
	 * Generates a human-readable string representation of this object.
	 * @return A string suitable for printing to a console or log.
	 */
	virtual std::string toString();
	
	/**
	 * Destructor. Clears domainObjs and subsorts, but does not deallocate memory associated with the pointers in those lists.
	 */
	virtual ~Sort();
};

#endif // SORT_H
