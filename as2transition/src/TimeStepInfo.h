#ifndef TIMESTEPINFO_DOT_H
#define TIMESTEPINFO_DOT_H

#include <climits> // For INT_MIN
#include <cstdlib> // For exit()
#include <iostream>
#include <list>
#include <string>

#include "Constant.h"
#include "Predicate.h"

/**
 * Holds information about the predicates that are true at a given time step.
 */
class TimeStepInfo
{
public:
	/// Constructor.  Initializes timeStep to INT_MIN and predicates to NULL.
	TimeStepInfo();

	/// Destructor.  Frees predicates and everything in it if it was pointing to valid data.
	virtual ~TimeStepInfo();

	/**
	 * Accessor for timeStep.
	 * @return The value of timeStep.
	 */
	int getMainTimeStep();

	int getSubTimeStep();
	/**
	 * Mutator for timeStep.
	 * @param newTimeStep - The new value for timeStep.
	 */
	void setTimeStep(int newTimeStep1, int newTimeStamp2);

	/**
	 * Adds a predicate to our list of predicates, creating a new Predicate object to hold the appropriate data.
	 * Automatically keeps the predicates sorted.
	 * @param newPredicate - A reference to the string representation of the predicate to add.
	 * @param newConstType - An optional parameter of a pointer to a Constant object that represents the type of this predicate. Defaults to NULL.
	 */
	void addPredicate(std::string& newPredicate, Constant *newConstType=NULL);

	/**
	 * Adds a predicate to our list of predicates, deep copying newPredicate into a freshly allocated Predicate object.
	 * Automatically keeps the predicates sorted.
	 * @param newPredicate - A reference to the predicate to add.
	 */
	void addPredicate(Predicate& newPredicate);

	/**
	 * Retrieves a constant iterator to the beginning of the predicates list.
	 * Ensures predicates has been allocated.
	 * @return An iterator pointing at the beginning of the predicates list.
	 */
	std::list<Predicate*>::const_iterator getPredicatesBegin();

	/**
	 * Retrieves a constant iterator to the end of the predicates list.
	 * Ensures predicates has been allocated.
	 * @return An iterator pointing at the end of the predicates list.
	 */
	std::list<Predicate*>::const_iterator getPredicatesEnd();

protected:
	int mainTimeStep; ///< The time step this structure represents in the solution.
	int subTimeStep;
	std::list<Predicate*>* predicates; ///< The predicates that are true at this time step.

	/// Allocates memory for predicates if that hasn't already been done. Exits on allocation error.
	void allocatePredicates();
};

#endif // TIMESTEPINFO_DOT_H
