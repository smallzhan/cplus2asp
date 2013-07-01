#ifndef PARSER_TYPES_H
#define PARSER_TYPES_H

/**
 * @file parser_types.h
 * @brief Data structures used to hold intermediate data for the parser.
 * @details Declarations of data structures used by the parser to contain
 * intermediate data while it processes grammar rules.
 */

#include <sstream>
#include <string>
#include <list>
#include <utility>

#include "Constant.h"
#include "Sort.h"
#include "Variable.h"

#include "utilities.h"

class Translator;

extern Translator mainTrans; ///< The main translator module.

/**
 * Container class to hold information from the constant_binder grammar rule.
 */
class PT_constant_binder_t
{
public:
	Constant::ConstantType constType; ///< The binding constant type (e.g., CONST_EXOGENOUSACTION).
	Sort* domain; ///< The domain of the constant.
	Constant* attributeOf; ///< If the constant binder is an attribute, this is a reference to the connecting action constant.
	
	/**
	 * Default constructor. Sets all dynamic attributes to NULL.
	 */
	PT_constant_binder_t();
	
	/**
	 * Destructor. Just resets everything to NULL.
	 */
	~PT_constant_binder_t();
};

/**
 * General parent of all self-contained, self-translating parse tree elements.
 * Empty except for the virtual translate function.
 */
class ParseElement
{
public:
	/// The possible types of a ParseElement instance.
	enum ParseElementType { PELEM_PELEM, PELEM_UOP, PELEM_BOP, PELEM_QUANT, PELEM_BASELIKE, PELEM_CONSTLIKE, PELEM_OBJLIKE, PELEM_VARLIKE };
	enum ParseElementType elemType; ///< The type of the parse element instance.
	bool parenBefore; ///< If true, a parenthesis came before the element.
	bool parenAfter; ///< If true, a parenthesis went after the element.
	
	/// The time stamp a ParseElement should use when it needs to represent
	/// a time step in a translated subformula. Expected to be set/updated by
	/// some external function (possibly another ParseElement's propogateTimeStamp
	/// method) before calling an element's translate method.
	std::string timeStamp;
	
	/// A list of any extra assignments, bindings, conditions, etc.
	/// created during translation and in need of insertion before the
	/// translated causal law the element is part of.
	/// All subclasses of ParseElement have logic in their translate methods
	/// to accumulate preStatements from subformulas during translation.
	std::list<std::string> preStatements;
	
	/// A list of any extra assignments, bindings, conditions, etc.
	/// created during translation and in need of insertion at the end of the
	/// body of the translated causal law the element is part of.
	/// All subclasses of ParseElement have logic in their translate methods
	/// to accumulate extra clauses from subformulas during translation.
	std::list<std::string> extraClauses;
	
	/// A global count of how many extra clauses have been created for any element.
	/// Used to help create dynamic variable names that won't clash with each other.
	/// Incremented when an extra clause is created, but not when it is added to anything.
	static size_t extraClauseCount;
	
	/**
	 * Default constructor. Sets elemType.
	 */
	ParseElement();
	
	/**
	 * If the element's timeStamp isn't blank, propogates its value to
	 * any children of the element.
	 * Base version that doesn't do anything (no children to propogate to).
	 */
	virtual void propogateTimeStamp();
	
	/**
	 * Sets the element's timeStamp to newTimeStamp and propogates the value to
	 * any children of the element.
	 * Base version that just assigns to self (no children to propogate to).
	 * @param newTimeStamp - The time stamp to use for this element and its children.
	 */
	virtual void propogateTimeStamp(std::string newTimeStamp);
	
	/**
	 * Method that generates a translated string representation of the element.
	 * @return A string containing the translated form of the element.
	 */
	virtual std::string translate();
	
	/**
	 * Alternate to translate method, represents the element such that it would
	 * be appropriate to use it as an indermediate value.
	 * @return A string containing the alterate translated form of the element.
	 */
	virtual std::string translateAsValue();
	
	/**
	 * Helper to translate that intelligently handles the value of parenBefore.
	 * @return A blank string if parenBefore is false, "(" if it's true.
	 */
	virtual std::string translateBeforeParen();
	
	/**
	 * Helper to translate that intelligently handles the value of parenAfter.
	 * @return A blank string if parenAfter is false, ")" if it's true.
	 */
	virtual std::string translateAfterParen();
	
	/**
	 * Adds all the items from toBeAdded onto the end of the element's preStatements list.
	 * @param toBeAdded - List of extra clauses to be added.
	 */
	virtual void addPreStatements(std::list<std::string>& toBeAdded);
	
	/**
	 * Adds all the items from toBeAdded onto the end of the element's extraClauses list.
	 * @param toBeAdded - List of extra clauses to be added.
	 */
	virtual void addExtraClauses(std::list<std::string>& toBeAdded);
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as action constant(s).
	 * @return True if the element or any elements "beneath" it are identified action constants, false otherwise.
	 */
	virtual bool hasActions();
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as fluent constant(s).
	 * @return True if the element or any elements "beneath" it are identified fluent constants, false otherwise.
	 */
	virtual bool hasFluents();
	
	/**
	 * Stub method that returns a blank string (for pointer-wise compatibility 
	 * with BaseLikeElement's real version of this method).
	 * @return A blank string ("").
	 */
	virtual std::string fullName();
	
	/**
	 * Destructor. Empty.
	 */
	virtual ~ParseElement();
};

/**
 * Child of ParseElement that represents a unary operator and the associated elements it operates on.
 */
class SimpleUnaryOperator : public ParseElement
{
public:
	/// Enum of the kinds of unary operators this class can be.
	enum UnaryOperatorType { UOP_UNKNOWN, UOP_NOT, UOP_NEGATIVE, UOP_ABS, UOP_EXOGENOUS, UOP_INERTIAL, UOP_RIGID };
	enum UnaryOperatorType opType; ///< Which kind of operator an instance represents.
	
	ParseElement* postOp; ///< What comes after (and is affected by) the operator.
	
	/**
	 * Default constructor. Performs basic initialization.
	 */
	SimpleUnaryOperator();
	
	/**
	 * If the element's timeStamp isn't blank, propogates its value to
	 * any children of the element.
	 * Propogates to postOp, if it exists.
	 */
	virtual void propogateTimeStamp();
	
	/**
	 * Sets the element's timeStamp to newTimeStamp and propogates the value to
	 * any children of the element.
	 * Propogates to postOp, if it exists.
	 * @param newTimeStamp - The time stamp to use for this element and its children.
	 */
	virtual void propogateTimeStamp(std::string newTimeStamp);
	
	/**
	 * Method that returns a translated string representation of the element.
	 * @return A string containing the translated form of the element.
	 */
	virtual std::string translate();
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as action constant(s).
	 * @return True if the element or any elements "beneath" it are identified action constants, false otherwise.
	 */
	virtual bool hasActions();
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as fluent constant(s).
	 * @return True if the element or any elements "beneath" it are identified fluent constants, false otherwise.
	 */
	virtual bool hasFluents();
	
	/**
	 * Returns an original string representation of this operator and its operand.
	 * @return The string representation of the operator and the full name of postOp, or a blank string ("") if postOp is NULL.
	 */
	virtual std::string fullName();
	
	/**
	 * Destructor. Deallocates postOp.
	 */
	virtual ~SimpleUnaryOperator();
};

/**
 * Child of ParseElement that represents a binary operator and the associated elements it operates on.
 */
class SimpleBinaryOperator : public ParseElement
{
public:
	/// Enum of the kinds of unary operators this class can be.
	enum BinaryOperatorType { BOP_UNKNOWN, BOP_PLUS, BOP_MINUS, BOP_TIMES, BOP_DIVIDE, BOP_MOD, BOP_AND, BOP_OR, BOP_EQUIV, BOP_IMPL, BOP_EQ, BOP_NEQ, BOP_DBL_EQ, BOP_LTHAN, BOP_GTHAN, BOP_LTHAN_EQ, BOP_GTHAN_EQ };
	enum BinaryOperatorType opType; ///< Which kind of operator an instance represents.
	
	ParseElement* preOp; ///< The bit(s) bound to the operator that come before it.
	ParseElement* postOp; ///< The bit(s) bound to the operator that come after it.
	
	/**
	 * Default constructor. Performs basic initialization.
	 */
	SimpleBinaryOperator();
	
	/**
	 * If the element's timeStamp isn't blank, propogates its value to
	 * any children of the element.
	 * Propogates to preOp and postOp, if they exist.
	 */
	virtual void propogateTimeStamp();
	
	/**
	 * Sets the element's timeStamp to newTimeStamp and propogates the value to
	 * any children of the element.
	 * Propogates to preOp and postOp, if they exist.
	 * @param newTimeStamp - The time stamp to use for this element and its children.
	 */
	virtual void propogateTimeStamp(std::string newTimeStamp);
	
	/**
	 * Method that returns a translated string representation of the element.
	 * @return A string containing the translated form of the element.
	 */
	virtual std::string translate();
	
	/**
	 * Internal helper to translate method, translates preOp (not) equals postOp.
	 * @param isEq - If true, translates as the "equals" operator (vs. "not equals").
	 * @param eqSym - A translated string representing the (not) equality symbol (used for normal equality cases).
	 * @return A string representation of the translated (not) equality between preOp and postOp.
	 */
	virtual std::string translateEq(bool isEq, std::string eqSym);
	
	/**
	 * Internal helper to translate method, translates preOp == postOp.
	 * @param eqSym - A translated string representing the equality symbol.
	 * @return A string representation of the translated equality between preOp and postOp.
	 */
	virtual std::string translateDblEq(std::string eqSym);
	
	/**
	 * Internal helper to translate method, translates preOp [ineq] postOp,
	 * where [ineq] is one of <, >, <=, >=, etc.
	 * @param opSym - A translated string representing the inequality symbol.
	 * @return A string representation of the translated inequality between preOp and postOp.
	 */
	virtual std::string translateIneq(std::string opSym);
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as action constant(s).
	 * @return True if the element or any elements "beneath" it are identified action constants, false otherwise.
	 */
	virtual bool hasActions();
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as fluent constant(s).
	 * @return True if the element or any elements "beneath" it are identified fluent constants, false otherwise.
	 */
	virtual bool hasFluents();
	
	/**
	 * Returns an original string representation of this operator and its operands.
	 * @return The string representation of preOp's full name, the operator, and postOp's full name, just one operand if the other is NULL, or a blank string ("") if both are NULL.
	 */
	virtual std::string fullName();
	
	/**
	 * Destructor. Deallocates preOp and postOp.
	 */
	virtual ~SimpleBinaryOperator();
};

/**
 * Child of ParseElement that represents a big quantifier group and its associated subformula.
 */
class BigQuantifiers : public ParseElement
{
public:
	/// Which kinds of "quantifiers" can be present.
	enum QuantifierType { QUANT_UNKNOWN, QUANT_CONJ, QUANT_DISJ };
	/// A list of the quantifiers present in this grouping, both the kinds
	/// of quantifiers and references to the quantifying variables.
	std::list<std::pair<enum QuantifierType, ParseElement*>* > quants;
	
	ParseElement* postOp; ///< The bit(s) affected by the quantifier(s).
	
	/**
	 * Default constructor. Performs basic initialization.
	 */
	BigQuantifiers();
	
	/**
	 * If the element's timeStamp isn't blank, propogates its value to
	 * any children of the element.
	 * Propogates to postOp, if it exists.
	 */
	virtual void propogateTimeStamp();
	
	/**
	 * Sets the element's timeStamp to newTimeStamp and propogates the value to
	 * any children of the element.
	 * Propogates to postOp, if it exists.
	 * @param newTimeStamp - The time stamp to use for this element and its children.
	 */
	virtual void propogateTimeStamp(std::string newTimeStamp);
	
	/**
	 * Method that returns a translated string representation of the element.
	 * @return A string containing the translated form of the element.
	 */
	virtual std::string translate();
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as action constant(s).
	 * @return True if the element or any elements "beneath" it are identified action constants, false otherwise.
	 */
	virtual bool hasActions();
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as fluent constant(s).
	 * @return True if the element or any elements "beneath" it are identified fluent constants, false otherwise.
	 */
	virtual bool hasFluents();
	
	/**
	 * Returns an original string representation of the quantifiers and what's getting quantified.
	 * @return The string representation of the quantifiers enclosing the full name of postOp, or a blank string ("") if postOp is NULL (or the quantifier list is empty).
	 */
	virtual std::string fullName();
	
	/**
	 * Destructor. Deallocates postOp and the contents of quants.
	 */
	virtual ~BigQuantifiers();
};

/**
 * Child of ParseElement that acts as a base class for parsed elements like constants and objects.
 */
class BaseLikeElement : public ParseElement
{
public:
	std::string baseName; ///< The original name of the element, sans parameters.
	std::vector<ParseElement*> params; ///< References to representations of the element's parameters, if any.
	
	/**
	 * Default constructor. Performs basic initialization.
	 */
	BaseLikeElement();
	
	/**
	 * Method that returns a translated string representation of the element.
	 * Here for completeness, but not meant to be called. Uses object
	 * translating rules on baseName.
	 * @return A string containing the translated form of the element.
	 */
	virtual std::string translate();
	
	/**
	 * Internal helper to translate, creates a list of translated params.
	 * @return A parentheses-surrounded, comma-separated list of translated
	 * params, or a blank string if params is empty.
	 */
	virtual std::string translateParams();
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as action constant(s).
	 * @return True if the element or any elements "beneath" it are identified action constants, false otherwise.
	 */
	virtual bool hasActions();
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as fluent constant(s).
	 * @return True if the element or any elements "beneath" it are identified fluent constants, false otherwise.
	 */
	virtual bool hasFluents();

	/**
	 * If the element's timeStamp isn't blank, propogates its value to
	 * any children of the element.
	 * Propogates to parameters, if any exist.
	 */
	virtual void propogateTimeStamp();

	/**
	 * Sets the element's timeStamp to newTimeStamp and propogates the value to
	 * any children of the element.
	 * Propogates to parameters, if any exist.
	 * @param newTimeStamp - The time stamp to use for this element and its children.
	 */
	virtual void propogateTimeStamp(std::string newTimeStamp);

	/**
	 * Outputs the original full name of the element, including parameters.
	 * @return The name & parameters of the element, as found in the original program.
	 */
	virtual std::string fullName();
	
	/**
	 * Destructor. Deallocates contents of params.
	 */
	virtual ~BaseLikeElement();
};

/**
 * Child of BaseLikeElement that represents a base element with the behavior of a constant.
 */
class ConstantLikeElement : public BaseLikeElement
{
public:
	/// Reference to the Constant object it's believed this element is an instance of.
	Constant* constRef;
	
	/**
	 * Default constructor. Performs basic initialization.
	 */
	ConstantLikeElement();
	
	/**
	 * Method that returns a translated string representation of the element.
	 * Uses constant translating conventions for the base name.
	 * @return A string containing the translated form of the element.
	 */
	virtual std::string translate();
	
	/**
	 * Alternate to translate method, represents the element such that it would
	 * be appropriate to use it as an indermediate value.
	 * @return A string containing the alterate translated form of the element.
	 */
	virtual std::string translateAsValue();
	
	/**
	 * Conditionally outputs the current time stamp if the constant is
	 * of a type that uses time stamps.
	 * @return ",[timestamp]", where [timestamp] is the current value of
	 * timeStamp, or "" if the constant is rigid (i.e., doesn't use time stamps).
	 */
	virtual std::string translateTimeStamp();
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as action constant(s).
	 * @return True if the element or any elements "beneath" it are identified action constants, false otherwise.
	 */
	virtual bool hasActions();
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as fluent constant(s).
	 * @return True if the element or any elements "beneath" it are identified fluent constants, false otherwise.
	 */
	virtual bool hasFluents();
	
	/**
	 * Destructor. Does not deallocate anything.
	 */
	virtual ~ConstantLikeElement();
};

/**
 * Child of BaseLikeElement that represents a base element with the behavior of an object.
 */
class ObjectLikeElement : public BaseLikeElement
{
public:
	/// Reference to the Object instance it's believed this element is an instance of.
	Object* objRef;
	
	/**
	 * Default constructor. Performs basic initialization.
	 */
	ObjectLikeElement();
	
	/**
	 * Method that returns a translated string representation of the element.
	 * Uses object translating conventions for the base name.
	 * @return A string containing the translated form of the element.
	 */
	virtual std::string translate();
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as action constant(s).
	 * @return True if the element or any elements "beneath" it are identified action constants, false otherwise.
	 */
	virtual bool hasActions();
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as fluent constant(s).
	 * @return True if the element or any elements "beneath" it are identified fluent constants, false otherwise.
	 */
	virtual bool hasFluents();
	
	/**
	 * Destructor. Does not deallocate anything.
	 */
	virtual ~ObjectLikeElement();
};

/**
 * Child of BaseLikeElement that represents a base element with the behavior of a variable.
 */
class VariableLikeElement : public BaseLikeElement
{
public:
	/// Reference to the Variable object it's believed this element is an instance of.
	Variable* varRef;
	
	/**
	 * Default constructor. Performs basic initialization.
	 */
	VariableLikeElement();
	
	/**
	 * Checks if a variable-like element represents a constant of some kind.
	 * @return True if the element is a constant variable, false otherwise.
	 */
	bool isConstantVariable();
	
	/**
	 * Method that returns a translated string representation of the element.
	 * Uses variable translating conventions for the base name.
	 * @return A string containing the translated form of the element.
	 */
	virtual std::string translate();
	
	/**
	 * Performs a translation on the variable-like element that treats it
	 * as though it were a constant (surrounding it in an "h(eql(..." wrapper).
	 * @param eqlValue - The value to set the variable equal to in the "eql(...)" part of the wrapper.
	 * @return A translated string representation of the variable expressed as a constant.
	 */
	std::string translateAsConstant(const char* eqlValue);
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as action constant(s).
	 * @return True if the element or any elements "beneath" it are identified action constants, false otherwise.
	 */
	virtual bool hasActions();
	
	/**
	 * This is true if the element (or any of its pre/postOp nodes) were
	 * identified as fluent constant(s).
	 * @return True if the element or any elements "beneath" it are identified fluent constants, false otherwise.
	 */
	virtual bool hasFluents();
	
	/**
	 * Destructor. Does not deallocate anything.
	 */
	virtual ~VariableLikeElement();
};

#endif // PARSER_TYPES_H
