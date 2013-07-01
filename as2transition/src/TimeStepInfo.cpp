#include "TimeStepInfo.h"

// Constructor.
TimeStepInfo::TimeStepInfo()
{
	mainTimeStep = INT_MIN;
	subTimeStep = INT_MIN;
	predicates = NULL;
}

// Destructor.
TimeStepInfo::~TimeStepInfo()
{
	if(predicates != NULL)
	{
		std::list<Predicate*>::iterator lIter = predicates->begin();
		for(; lIter != predicates->end(); lIter++)
		{
			delete (*lIter);
		}
		delete predicates;
	}
}

// Accessor for timeStep.
int TimeStepInfo::getMainTimeStep()
{
	return mainTimeStep;
}

int TimeStepInfo::getSubTimeStep()
{
	return subTimeStep;
}

// Mutator for timeStep.
void TimeStepInfo::setTimeStep(int newTimeStep1, int newTimeStep2)
{
	mainTimeStep = newTimeStep1;
	subTimeStep = newTimeStep2;
}

// Adds a predicate to our list of predicates.
void TimeStepInfo::addPredicate(std::string& newPredicate, Constant *newConstType)
{
	if(predicates == NULL)
	{
		allocatePredicates();
	}
	int compareResult = 0;
	bool tmpNegated = false;
	std::string tmpInnerPredicate = "";
	int tmpMTimeStamp;
	int tmpSTimeStamp;
	// Try to extract h-style predicate info from the string. If it works, save the h-style predicate info. If not, just save the normal predicate.
	bool tmpHPredicate = Predicate::extractHPredicateInfo(
		newPredicate, tmpNegated, tmpInnerPredicate, tmpMTimeStamp, tmpSTimeStamp);
	Predicate *newPred = new Predicate();
	if(tmpHPredicate)
	{
		newPred->setName(tmpInnerPredicate);
		newPred->setTimeStamp(tmpMTimeStamp, tmpSTimeStamp);
		newPred->setBlnIsHPredicate(true);
		newPred->setBlnIsNegated(tmpNegated);
	}
	else
	{
		newPred->setName(newPredicate);
		newPred->setBlnIsNegated(tmpNegated);
	}
	// Regardless, save whatever Constant object pointer (if any) we were given.
	newPred->setConstType(newConstType);

	if(predicates->empty())
	{	// If we don't have predicates yet, make this the first.
		predicates->push_back(newPred);
	}
	else
	{	// If we already have predicates, find this new one's proper place and stick it there.
		std::list<Predicate*>::iterator lIter = predicates->begin();
		while(lIter != predicates->end())
		{
			compareResult = (*lIter)->toPredicateString(false, false).compare(newPredicate);
			if(compareResult < 0 || compareResult == 0)
			{
				// If the current element comes before the newcomer (or is the same as the newcomer), move on.
				++lIter;
			}
			else
			{
				// The current element should go after the newcomer, break and insert here.
				break;
			}
		}
		predicates->insert(lIter, newPred);
	}
}

// Adds a predicate to our list of predicates, deep copying newPredicate into a freshly allocated Predicate object.
void TimeStepInfo::addPredicate(Predicate& newPredicate)
{
	if(predicates == NULL)
	{
		allocatePredicates();
	}
	std::string tempStrName = "";
	// Create a new predicate and copy the information.
	Predicate *newPred = new Predicate();
	tempStrName = newPredicate.getName();
	newPred->setName(tempStrName);
	newPred->setTimeStamp(newPredicate.getMainTimeStamp(), newPredicate.getSubTimeStamp());
	newPred->setBlnIsHPredicate(newPredicate.getBlnIsHPredicate());
	newPred->setBlnIsNegated(newPredicate.getBlnIsNegated());
	newPred->setConstType(newPredicate.getConstType());
	// Insert the new predicate in the appropriate place.
	if(predicates->empty())
	{	// If we don't have predicates yet, make this the first.
		predicates->push_back(newPred);
	}
	else
	{	// If we already have predicates, find this new one's proper place and stick it there.
		std::list<Predicate*>::iterator lIter = predicates->begin();
		int compareResult = 0;
		while(lIter != predicates->end())
		{
			tempStrName = (*lIter)->toPredicateString(false, false);
			compareResult = tempStrName.compare(newPredicate.getName());
			if(compareResult < 0 || compareResult == 0)
			{
				// If the current element comes before the newcomer (or is the same as the newcomer), move on.
				++lIter;
			}
			else
			{
				// The current element should go after the newcomer, break and insert here.
				break;
			}
		}
		predicates->insert(lIter, newPred);
	}
}

// Returns a constant iterator to the beginning of the predicates list.
std::list<Predicate*>::const_iterator TimeStepInfo::getPredicatesBegin()
{
	if(predicates == NULL)
	{
		allocatePredicates();
	}
	return predicates->begin();
}

// Returns a constant iterator to the end of the predicates list.
std::list<Predicate*>::const_iterator TimeStepInfo::getPredicatesEnd()
{
	if(predicates == NULL)
	{
		allocatePredicates();
	}
	return predicates->end();
}

// Allocates memory for predicates if that hasn't already been done. Exits on allocation error.
void TimeStepInfo::allocatePredicates()
{
	if(predicates == NULL)
	{
		predicates = new std::list<Predicate*>();
		if(predicates == NULL)
		{
			std::cout << "Error: Out of memory." << std::endl;
			exit(1);
		}
	}
}
