#ifndef PREDICATE_DOT_H
#define PREDICATE_DOT_H

#include <climits> // For INT_MIN
#include <string>

#include "Constant.h"
#include "StringUtils.h"

const int TIMELESS_STEP = INT_MIN;

/**
 * The Predicate class represents an atom of a solution at a given time step.
 * It has member variables that store information about the atom's name and state,
 * and exposes static methods to evaluate strings for various signs of predicate-ness.
 */
class Predicate
{
  public:
	/**
	 * Default constructor. Initializes all member variables to 0, empty, or equivalent.
	 */
	Predicate();

	/**
	 * Partial constructor. Takes the predicate's name and sets everything else to 0, empty, or equivalent.
	 * @param newName - The full name of the predicate.
	 */
	Predicate(std::string &newName);

	/**
	 * Partial constructor for h-style predicates.
	 * Takes the predicate's inner contents as name, an appropriate time stamp, and auto-sets blnIsHPredicate to true.
	 * @param newName - The full name of the predicate.
	 * @param newTimeStamp - The time stamp that should be applied to this predicate.
	 */
	Predicate(std::string &newName, int newTimeStamp1, int newTimeStamp2);

	/**
	 * Destructor. Here for completeness purposes, but does nothing.
	 */
	virtual ~Predicate();

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
	 * Accessor for timeStamp.
	 * @return The current value of timeStamp.
	 */
	int getMainTimeStamp();
	int getSubTimeStamp();

	/**
	 * Mutator for timeStamp.
	 * @param newTimeStamp - The new value for timeStamp.
	 */
	void setTimeStamp(int newTimeStamp1, int newTimeStamp2);

	/**
	 * Accessor for blnIsHPredicate.
	 * @return The current value of blnIsHPredicate.
	 */
	bool getBlnIsHPredicate();

	/**
	 * Mutator for blnIsHPredicate.
	 * @param newBlnIsHPredicate - The new value for blnIsHPredicate.
	 */
	void setBlnIsHPredicate(bool newBlnIsHPredicate);

	/**
	 * Accessor for blnIsNegated.
	 * @return The current value of blnIsNegated.
	 */
	bool getBlnIsNegated();

	/**
	 * Mutator for blnIsNegated.
	 * @param newBlnIsNegated - The new value for blnIsNegated.
	 */
	void setBlnIsNegated(bool newBlnIsNegated);

	/**
	 * Accessor for constType.
	 * @return The current value of constType.
	 */
	Constant* getConstType();

	/**
	 * Mutator for constType.
	 * @param newConstType - The new value for constType.
	 */
	void setConstType(Constant* newConstType);

	/**
	 * Pseudo-accessor for blnIsAction.
	 * @return True if the Constant pointed to by the predicate is an action, false otherwise (or if constType hasn't been assigned yet).
	 */
	bool getBlnIsAction();

	/**
	 * Pseudo-accessor for blnIsBoolean.
	 * @return True if the Constant pointed to by the predicate has a boolean domain, false otherwise (or if constType hasn't been assigned yet).
	 */
	bool getBlnIsBoolean();

	/**
	 * Re-creates an appropriate string representation of the predicate and returns it.
	 * @param stripHPredicate - If true, will only use the inner predicate (i.e., name) if it is an h-style predicate. If false, will re-create the original h(inner(args),time) style. No effect if the predicate isn't an h-style predicate.
	 * @param transformEqPredicate - If true, will display an h-style predicate whose inner predicate is of the form eq(something,value) as something=value (overrides stripHPredicate). If false, will leave an inner eq(something,value) predicate alone. No effect if the predicate isn't an h-style predicate.
	 * @return The appropriate string representation of the predicate.
	 */
	std::string toPredicateString(bool stripHPredicate, bool transformEqPredicate);

	/**
	 * Evaluates text to determine if it's an h-style predicate or not.
	 * Assumes text is one complete predicate.
	 * @param text - The predicate to examine.
	 * @return True if text is a predicate of the form h(anything[,int]), false otherwise.
	 */
	static bool isHPredicate(std::string& text)
	{
		bool retVal = false;
		size_t sztFirstPos = 0;
		std::string strTemp = StringUtils::trimWhitespace(text);
		// To be an h predicate, it needs to be at least 4 characters long (for "h(X)", the shortest h-style predicate possible),
		// start with "h(", have stuff where X is (we don't really check that), and end with ")".
		if(strTemp.length() > 3 && strTemp.find("h(") == 0)
		{
			// Okay, it starts with h, sanity check that it ends with a closing parenthesis?
			sztFirstPos = strTemp.find_last_of(")");
			if(sztFirstPos != std::string::npos && sztFirstPos == strTemp.length() - 1)
			{
				// Yes sir, this counts as an h-style predicate!
				retVal = true;
			}
		}
		return retVal;
	}

	/**
	 * Evaluates text to determine if it's a negated h-style predicate or not.
	 * Assumes text is one complete predicate.
	 * @param text - The predicate to examine.
	 * @return True if text is a predicate of the form -h(anything[,int]), false otherwise.
	 */
	static bool isNegHPredicate(std::string& text)
	{
		bool retVal = false;
		std::string strTemp = StringUtils::trimWhitespace(text);
		if(strTemp.length() > 1 && strTemp[0] == '-')
		{
			// If a minus sign precedes the predicate, strip it and then see if it's a normal h predicate. If so, we have a match!
			strTemp = strTemp.substr(1);
			retVal = Predicate::isHPredicate(strTemp);
		}
		return retVal;
	}

	/**
	 * Evaluates text and determines if it's any kind of h-style predicate (negated or otherwise).
	 * Assumes text is one complete predicate.
	 * @param text - The predicate to examine.
	 * @return True if text is any predicate (true or false) of the form h(anything[,int]) or -h(anything[,int]), false otherwise.
	 */
	static bool isAnyHPredicate(std::string& text)
	{
		return Predicate::isHPredicate(text) || Predicate::isNegHPredicate(text);
	}

	/**
	 * Evaluates text to determine if it's an eq-style predicate or not (an h-predicate whose inner predicate starts with "eq(" or "eql(").
	 * Assumes text is one complete predicate.
	 * @param text - The predicate to examine.
	 * @return True if text is a predicate of the form h(eq(anything,value)[,int]) or h(eql(anything,value)[,int]), false otherwise.
	 */
	static bool isEqHPredicate(std::string& text)
	{
		bool retVal = false;
		size_t sztTempStart, sztTempPos;
		std::string strTemp = StringUtils::trimWhitespace(text);
		// First, check if it's an h-style predicate.
		if(Predicate::isHPredicate(strTemp))
		{
			sztTempStart = strTemp.find("h("); // Start at the "h(".
			sztTempPos = strTemp.find("eq(", sztTempStart);
			if(sztTempPos == sztTempStart + 2) // If "eq(" comes just after "h(", it's a match.
			{
				retVal = true;
			}
			else
			{   // Not an "eq(", try for "eql(".
				sztTempPos = strTemp.find("eql(", sztTempStart);
				if(sztTempPos == sztTempStart + 2)
				{
					retVal = true;
				}
			}
		}
		return retVal;
	}

	/**
	 * Evaluates text to determine if it's a negated eq-style predicate or not.
	 * Assumes text is one complete predicate.
	 * @param text - The predicate to examine.
	 * @return True if text is a predicate of the form -h(eq(anything,value)[,int]) or -h(eql(anything,value)[,int]), false otherwise.
	 */
	static bool isNegEqHPredicate(std::string& text)
	{
		bool retVal = false;
		std::string strTemp = StringUtils::trimWhitespace(text);
		if(strTemp.length() > 1 && strTemp[0] == '-')
		{
			// If a minus sign precedes the predicate, strip it and then see if it's a normal eq-style h predicate. If so, we have a match!
			strTemp = strTemp.substr(1);
			retVal = Predicate::isEqHPredicate(strTemp);
		}
		return retVal;
	}

	/**
	 * Evaluates text and determines if it's any kind of eq-style, h-style predicate (negated or otherwise).
	 * Assumes text is one complete predicate.
	 * @param text - The predicate to examine.
	 * @return True if text is any predicate (true or false) of the form h(eq(anything,value)[,int]), -h(eq(anything,value)[,int]), h(eql(anything,value)[,int]), or -h(eql(anything,value)[,int]), false otherwise.
	 */
	static bool isAnyEqHPredicate(std::string& text)
	{
		return Predicate::isEqHPredicate(text) || Predicate::isNegEqHPredicate(text);
	}

	/**
	 * Evaluates text and determines if it's an h-style predicate whose inner predicate is "contribution" or "x_contrib".
	 * Assumes text is a single, complete predicate.
	 * @param text - The predicate to examine.
	 * @return True if text is a predicate of the form h([eq[l](]contribution(optional_stuff)[,value)][,int]), false otherwise.
	 */
	static bool isContribHPredicate(std::string& text)
	{
		bool retVal = false;
		size_t sztTempFirstPos, sztTempSecondPos;
		std::string strTemp = StringUtils::trimWhitespace(text);
		// First, check if it's an h-style predicate.
		if(Predicate::isHPredicate(strTemp))
		{
			// If it is an h-style predicate, see if the inner predicate contains "contribution" or "x_contrib".
			sztTempFirstPos = strTemp.find("x_contrib(");
			if(sztTempFirstPos == std::string::npos)
			{
				sztTempFirstPos = strTemp.find("contribution(");
			}
			// Ensure one of the key strings is present before bothering to search more.
			if(sztTempFirstPos != std::string::npos)
			{
				// Figure out if this is an eq-style predicate before checking where we found "contribution".
				if(Predicate::isEqHPredicate(strTemp))
				{   // It's an eq-style predicate, make sure we check after the "eq(" or "eql(" for the "contribution".
					sztTempSecondPos = strTemp.find("eq(");
					if(sztTempSecondPos != std::string::npos)
					{
						sztTempSecondPos += 3;
					}
					else
					{
						sztTempSecondPos = strTemp.find("eql(");
						if(sztTempSecondPos != std::string::npos)
						{
							sztTempSecondPos += 4;
						}
					}
					// Check if what comes immediately after "eql(" is the key word.
					if(sztTempSecondPos != std::string::npos && sztTempSecondPos == sztTempFirstPos)
					{
						retVal = true;
					}
				}
				else
				{   // Not an eq-style predicate, the "contribution" should be just after the "h(".
					sztTempSecondPos = strTemp.find("h(") + 2;
					if(sztTempFirstPos == sztTempSecondPos)
					{
						retVal = true;
					}
				}
			}
		}
		return retVal;
	}

	/**
	 * Evaluates text and determines if it's a negated h-style predicate whose inner predicate is "contribution" or "x_contrib".
	 * Assumes text is a single, complete predicate.
	 * @param text - The predicate to examine.
	 * @return True if text is a predicate of the form -h([eq[l](]contribution(optional_stuff)[,value)][,int]), false otherwise.
	 */
	static bool isNegContribHPredicate(std::string& text)
	{
		bool retVal = false;
		std::string strTemp = StringUtils::trimWhitespace(text);
		if(strTemp.length() > 1 && strTemp[0] == '-')
		{
			// If a minus sign precedes the predicate, strip it and then see if it's a normal "contribution" h-style predicate.
			strTemp = strTemp.substr(1);
			retVal = Predicate::isContribHPredicate(strTemp);
		}
		return retVal;
	}

	/**
	 * Evaluates text and determines if it's any kind of h-style predicate whose inner predicate is "contribution" or "x_contrib" (negated or otherwise).
	 * Assumes text is a single, complete predicate.
	 * @param text - The predicate to examine.
	 * @return True if text is any predicate (true or false) of the form h([eq[l](]contribution(optional_stuff)[,value)][,int]) or -h([eq[l](]contribution(optional_stuff)[,value)][,int]), false otherwise.
	 */
	static bool isAnyContribHPredicate(std::string& text)
	{
		return Predicate::isContribHPredicate(text) || Predicate::isNegContribHPredicate(text);
	}

	/**
	 * Evaluates text and determines if it's an h-style predicate whose inner predicate starts with x_.
	 * Assumes text is a single, complete predicate.
	 * @param text - The predicate to examine.
	 * @return True if text is a predicate of the form h(x_anything(optional_stuff)[,int]), false otherwise.
	 */
	static bool isXHPredicate(std::string& text)
	{
		bool retVal = false;
		size_t sztTempFirstPos, sztTempSecondPos;
		std::string strTemp = StringUtils::trimWhitespace(text);
		// First, check if it's an h-style predicate.
		if(Predicate::isHPredicate(strTemp))
		{
			// If it is an h-style predicate, see if the inner predicate starts with "x_".
			sztTempFirstPos = strTemp.find("x_");
			if(sztTempFirstPos != std::string::npos)
			{
				// Figure out if this is an eq-style predicate before checking where we found "x_".
				if(Predicate::isEqHPredicate(strTemp))
				{   // It's an eq-style predicate, make sure we check after the "eq(" or "eql(" for the "x_".
					sztTempSecondPos = strTemp.find("eq(");
					if(sztTempSecondPos != std::string::npos)
					{
						sztTempSecondPos += 3;
					}
					else
					{
						sztTempSecondPos = strTemp.find("eql(");
						if(sztTempSecondPos != std::string::npos)
						{
							sztTempSecondPos += 4;
						}
					}
					// The "x_" should come just after the "eql(".
					if(sztTempFirstPos == sztTempSecondPos)
					{
						retVal = true;
					}
				}
				else
				{   // Not an eq-style predicate, the "x_" should be just after the "h(".
					sztTempSecondPos = strTemp.find("h(") + 2;
					if(sztTempFirstPos == sztTempSecondPos)
					{
						retVal = true;
					}
				}
			}
		}
		return retVal;
	}

	/**
	 * Evaluates text and determines if it's a negated h-style predicate whose inner predicate starts with x_.
	 * Assumes text is a single, complete predicate.
	 * @param text - The predicate to examine.
	 * @return True if text is a predicate of the form -h(x_anything(optional_stuff)[,int]), false otherwise.
	 */
	static bool isNegXHPredicate(std::string& text)
	{
		bool retVal = false;
		std::string strTemp = StringUtils::trimWhitespace(text);
		if(strTemp.length() > 1 && strTemp[0] == '-')
		{
			// If a minus sign precedes the predicate, strip it and then see if it's a normal "x_" h-style predicate.
			strTemp = strTemp.substr(1);
			retVal = Predicate::isXHPredicate(strTemp);
		}
		return retVal;
	}

	/**
	 * Evaluates text and determines if it's any kind of h-style predicate whose inner predicate starts with x_ (negated or otherwise).
	 * Assumes text is a single, complete predicate.
	 * @param text - The predicate to examine.
	 * @return True if text is any predicate (true or false) of the form h(x_anything(optional_stuff)[,int]) or -h(x_anything(optional_stuff)[,int]), false otherwise.
	 */
	static bool isAnyXHPredicate(std::string& text)
	{
		return Predicate::isXHPredicate(text) || Predicate::isNegXHPredicate(text);
	}

	/**
	 * Attempts to extract relevant info from an h-style predicate in text, populating notH, innerPredicate, and timeStamp accordingly.
	 * Assumes text is one complete predicate.
	 * @param text - The predicate to examine.
	 * @param notH - Set to true if this is a negated predicate.
	 * @param innerPredicate - Set to the value of the inner predicate (i.e., in h(anything(args),int), the "anything(args)" part).
	 * @param timeStamp - Set to the time stamp of the predicate, or INT_MIN if there is no time stamp.
	 * @return True on success, false on failure (including if the predicate isn't actually an h-style predicate).
	 */
	static bool extractHPredicateInfo(std::string& text, bool& notH,
									  std::string& innerPredicate,
									  int& timeStamp1, int& timeStamp2)
	{
		bool retVal = false;
		std::string strTemp = text;
		size_t sztFirstPos = 0, sztSecondPos = 0;
		size_t sztStartPos = 0, sztEndPos = 0;
		size_t sztLastCommaPos = 0;
		size_t sztStampCommaPos = 0;
		int intNumParens = 0, intNumArgs = 0;
		strTemp = StringUtils::trimWhitespace(strTemp);
		if(Predicate::isAnyHPredicate(strTemp))
		{
			// First: is it a -h predicate?
			if(strTemp[0] == '-')
			{
				notH = true;
			}
			else
			{
				notH = false;
			}
			// Next, gather the inner predicate and try to find a time stamp.
			// Assume if there's more than one argument and the last one is an integer, then that's a time stamp.
			sztFirstPos = strTemp.find("(");
			sztSecondPos = strTemp.find_last_of(")");
			if(sztFirstPos != std::string::npos && sztFirstPos != std::string::npos && sztFirstPos < sztSecondPos)
			{   // Start the substring position trackers just past the first opening parenthesis.
				sztStartPos = sztEndPos = sztFirstPos + 1;
				sztLastCommaPos = std::string::npos;
				sztStampCommaPos = std::string::npos;
				intNumParens = 0;
				intNumArgs = 1;
				// Walk through what's inside the "h(...)", tracking parenthesis in search of a second argument to the "h(...)" predicate.
				// If there are more than two arguments to the main h-predicate or the second argument isn't an integer, assume there's no time stamp.
				while(sztEndPos < sztSecondPos)
				{
					if(strTemp[sztEndPos] == '(')
					{
						intNumParens++;
					}
					else if(strTemp[sztEndPos] == ')')
					{
						intNumParens--;
						if(intNumParens < 0)
						{   // Malformed inner predicate, bork out.
							sztEndPos = std::string::npos;
							break;
						}
					}
					else if(strTemp[sztEndPos] == ',' && intNumParens == 0)
					{   // We're at the top level of the h-predicate and a comma was found, another argument.
						sztStampCommaPos = sztLastCommaPos;
						sztLastCommaPos = sztEndPos;
						intNumArgs++;
					}
					sztEndPos++; // Next character.
				}
				// If the inner predicate wasn't totally malformed, try figuring out the time stamp (if any) and capture it and the inner predicate.
				if(intNumParens == 0 && sztEndPos != std::string::npos)
				{
					sztEndPos--;
					timeStamp1 = INT_MIN; // Start assuming we didn't get a time stamp.
					timeStamp2 = INT_MIN;
					// If there were two real arguments and the last one is an integer, that's a time stamp.
					if(intNumArgs == 2 && sztLastCommaPos != std::string::npos && sztLastCommaPos < sztSecondPos)
					{
						// If we get a time stamp, set up to capture what came before as an inner predicate. Otherwise, grab the whole thing.
						if(StringUtils::from_string<int>(timeStamp1, strTemp.substr(sztLastCommaPos+1, sztEndPos-sztLastCommaPos)))
						{
							sztEndPos = sztLastCommaPos - 1;
						}
					}

					if (intNumArgs == 3 && sztStampCommaPos != std::string::npos
						&& sztStampCommaPos < sztSecondPos)
					{
						if (StringUtils::from_string<int>(
								timeStamp1,
								strTemp.substr(sztStampCommaPos+1,sztLastCommaPos-sztStampCommaPos))
							&& StringUtils::from_string<int>(
								timeStamp2,
								strTemp.substr(sztLastCommaPos+1, sztEndPos-sztLastCommaPos)))

						{
							sztEndPos = sztStampCommaPos - 1;
						}
					}

					// Regardless of whether or not there was a time stamp, now grab the inner predicate.
					innerPredicate = strTemp.substr(sztStartPos, sztEndPos-sztStartPos+1);
					retVal = true;
				}
			}
		}
		return retVal;
	}

  protected:
	std::string name; ///< The full contents of the predicate (just the inner predicate if it was an h-style predicate).
	int mainTimeStamp; ///< The time stamp the predicate occurs in (if applicable). INT_MIN signifies a given predicate has no time stamp. Only useful if blnIsHPredicate is true.
	int subTimeStamp; ///... see above
	bool blnIsHPredicate; ///< Tracks if the predicate was encased in an h-style predicate.
	bool blnIsNegated; ///< Tracks if the predicate was negated or not.
	Constant *constType; ///< A pointer to the base constant that the predicate represents.
};

#endif // PREDICATE_DOT_H
