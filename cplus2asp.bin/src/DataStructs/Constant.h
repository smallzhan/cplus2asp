#ifndef CONSTANT_H
#define CONSTANT_H

#include <string>
#include <vector>

#include "Element.h"
#include "Sort.h"
#include "Variable.h"
#include "utilities.h"

/**
 * Representation of a C+ constant (i.e., fluent/action).
 */
class Constant : public Element
{
private:
public:
    std::vector<Sort*> params; ///< Vector of parameters for a constant, if any, expressed as references to sorts.
    Sort* domain; ///< Reference to the sort that represents the domain of a constant.

    /// An enum of the possible kinds of constants the system recognizes.
    enum ConstantType { CONST_UNKNOWN, CONST_ACTION, CONST_ABACTION, CONST_MACROACTION, CONST_ATTRIBUTE, CONST_EXOGENOUSACTION, CONST_INERTIALFLUENT, CONST_RIGID, CONST_SDFLUENT, CONST_SIMPLEFLUENT, CONST_ADDITIVEACTION, CONST_ADDITIVEFLUENT };
    enum ConstantType constType; ///< The type of a constant.

    /**
     * Default constructor. Calls Element constructor and sets attributes to zero/blank/empty.
     */
    Constant();

    /**
     * Full constructor. Calls full Element constructor, still sets other attributes to zero/blank/empty.
     * @param _name - The C+ name of this object.
     * @param _transName - The ASP-compatible name of this object.
     */
    Constant(std::string _name, std::string _transName);

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
     * Function that generates a string representation of a Constant's type.
     * @param _constType - The constant type instance to transform.
     * @return A string representation of the constant type.
     */
    static std::string constTypeToString(enum ConstantType _constType);

    /**
     * Destructor. Clears params and sets domain to NULL, but does not deallocate associated memory.
     */
    virtual ~Constant();
};

#endif // CONSTANT_H
