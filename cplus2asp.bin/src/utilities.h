#ifndef UTILITIES_H
#define UTILITIES_H

#include <list>
#include <sstream>
#include <string>
#include <vector>

#include "Element.h"
#include "ElementCounter.h"

/**
 * @namespace utils
 * @brief Contains miscellaneous utility functions for manipulating and ouputting data.
 */
namespace utils
{

/**
 * Given a list of pointers to Element objects (or subclasses of Element), will create a human-readable string representation of the list using the names of each element.
 * The template allows for lists of subclasses of Element to be passed in without any casting issues.
 * @param lst - A list of Element (or a subclass of Element) pointers to be stringified.
 * @param useFullName - If true, will use the elements' full names (including any parameters) instead of just their base names. (Default: false)
 * @param useTransName - If true, will use the elements' translated names instead of their original names. (Default: false)
 * @param separator - What string to insert between elements of the list. (Default: ", ")
 * @param prettyPrint - If true, will add extra formatting around the names assuming they're being displayed as part of a toString function or output to a log. (Default: false)
 * @return A string representation of the vector's contents.
 */
template <class T>
std::string elementListToNameString(const std::list<T> &lst, bool useFullName=false, bool useTransName=false, const char* separator=", ", bool prettyPrint=false)
{
	std::string tempStr = "";
	std::ostringstream sout; // Use a string stream to form the string, then copy it to tempStr.
	class std::list<T>::const_iterator lIter;
	
	std::string prettyPrintQuotes = "";
	if(prettyPrint)
	{
		prettyPrintQuotes = "\"";
	}
	
	// Output the name of each element of lst.
	for(lIter = lst.begin(); lIter != lst.end(); ++lIter)
	{
		if(lIter != lst.begin())
		{	// If this isn't the first element, stick a list separator before it.
			sout << separator;
		}
		// Protect from accessing a NULL pointer, inserting "NULL" in if the pointer is invalid.
		if(*lIter == NULL)
		{
			sout << "NULL";
		}
		else
		{
			if(useFullName)
			{
				if(useTransName)
				{
					sout << prettyPrintQuotes << (*lIter)->fullTransName() << prettyPrintQuotes;
				}
				else
				{
					sout << prettyPrintQuotes << (*lIter)->fullName() << prettyPrintQuotes;
				}
			}
			else
			{
				if(useTransName)
				{
					sout << prettyPrintQuotes << (*lIter)->transName << prettyPrintQuotes;
				}
				else
				{
					sout << prettyPrintQuotes << (*lIter)->name << prettyPrintQuotes;
				}
			}
		}
	}
	tempStr = sout.str();
	return tempStr;
}

/**
 * Convenience function that calls elementListToNameString with useFullName set to true.
 * Leaves useTransName set to false.
 * @param lst - A list of Element (or a subclass of Element) pointers to be stringified.
 * @param separator - What string to insert between elements of the list. (Default: ", ")
 * @param prettyPrint - If true, will add extra formatting around the names assuming they're being displayed as part of a toString function or output to a log. (Default: false)
 * @return A string representation of the vector's contents, using the full name of each element.
 */
template <class T>
std::string elementListToFullNameString(const std::list<T> &lst, const char* separator=", ", bool prettyPrint=false)
{
	return elementListToNameString<T>(lst, true, false, separator, prettyPrint);
}

/**
 * Convenience function that calls elementListToNameString with useTransName set to true.
 * Leaves useFullName set to false.
 * @param lst - A list of Element (or a subclass of Element) pointers to be stringified.
 * @param separator - What string to insert between elements of the list. (Default: ", ")
 * @param prettyPrint - If true, will add extra formatting around the names assuming they're being displayed as part of a toString function or output to a log. (Default: false)
 * @return A string representation of the vector's contents, using the translated name of each element.
 */
template <class T>
std::string elementListToTransNameString(const std::list<T> &lst, const char* separator=", ", bool prettyPrint=false)
{
	return elementListToNameString<T>(lst, false, true, separator, prettyPrint);
}

/**
 * Convenience function that calls elementListToNameString with useFullName and useTransName set to true.
 * @param lst - A list of Element (or a subclass of Element) pointers to be stringified.
 * @param separator - What string to insert between elements of the list. (Default: ", ")
 * @param prettyPrint - If true, will add extra formatting around the names assuming they're being displayed as part of a toString function or output to a log. (Default: false)
 * @return A string representation of the vector's contents, using the translated full name of each element.
 */
template <class T>
std::string elementListToFullTransNameString(const std::list<T> &lst, const char* separator=", ", bool prettyPrint=false)
{
	return elementListToNameString<T>(lst, true, true, separator, prettyPrint);
}

/**
 * Given a vector of pointers to Element objects (or subclasses of Element), will create a human-readable string representation of the vector using the names of each element.
 * The template allows for vectors of subclasses of Element to be passed in without any casting issues.
 * @param vec - A vector of Element (or a subclass of Element) pointers to be stringified.
 * @param useFullName - If true, will use the elements' full names (including any parameters) instead of just their base names. (Default: false)
 * @param useTransName - If true, will use the elements' translated names instead of their original names. (Default: false)
 * @param separator - What string to insert between elements of the list. (Default: ", ")
 * @param prettyPrint - If true, will add extra formatting around the names assuming they're being displayed as part of a toString function or output to a log. (Default: false)
 * @return A string representation of the vector's contents.
 */
template <class T>
std::string elementVectorToNameString(const std::vector<T> &vec, bool useFullName=false, bool useTransName=false, const char* separator=", ", bool prettyPrint=false)
{
	std::string tempStr = "";
	std::ostringstream sout; // Use a string stream to form the string, then copy it to tempStr.
	
	std::string prettyPrintQuotes = "";
	if(prettyPrint)
	{
		prettyPrintQuotes = "\"";
	}
	
	// Output the name of each element of vec.
	for(size_t i = 0; i < vec.size(); i++)
	{
		if(i > 0)
		{	// If this isn't the first element, stick a list separator before it.
			sout << separator;
		}
		if(prettyPrint)
		{
			sout << "[" << i << "]=";
		}
		// Protect from accessing a NULL pointer, inserting "NULL" in if the pointer is invalid.
		if(vec[i] == NULL)
		{
			sout << "NULL";
		}
		else
		{
			if(useFullName)
			{
				if(useTransName)
				{
					sout << prettyPrintQuotes << vec[i]->fullTransName() << prettyPrintQuotes;
				}
				else
				{
					sout << prettyPrintQuotes << vec[i]->fullName() << prettyPrintQuotes;
				}
			}
			else
			{
				if(useTransName)
				{
					sout << prettyPrintQuotes << vec[i]->transName << prettyPrintQuotes;
				}
				else
				{
					sout << prettyPrintQuotes << vec[i]->name << prettyPrintQuotes;
				}
			}
		}
	}
	tempStr = sout.str();
	return tempStr;
}

/**
 * Convenience function that calls elementVectorToNameString with useFullName set to true.
 * Passes false for useTransName.
 * @param vec - A vector of Element (or a subclass of Element) pointers to be stringified.
 * @param separator - What string to insert between elements of the list. (Default: ", ")
 * @param prettyPrint - If true, will add extra formatting around the names assuming they're being displayed as part of a toString function or output to a log. (Default: false)
 * @return A string representation of the vector's contents, using the full name of each element.
 */
template <class T>
std::string elementVectorToFullNameString(const std::vector<T> &vec, const char* separator=", ", bool prettyPrint=false)
{
	return elementVectorToNameString<T>(vec, true, false, separator, prettyPrint);
}

/**
 * Convenience function that calls elementVectorToNameString with useTransName set to true.
 * Passes false for useFullName.
 * @param vec - A vector of Element (or a subclass of Element) pointers to be stringified.
 * @param separator - What string to insert between elements of the list. (Default: ", ")
 * @param prettyPrint - If true, will add extra formatting around the names assuming they're being displayed as part of a toString function or output to a log. (Default: false)
 * @return A string representation of the vector's contents, using the translated name of each element.
 */
template <class T>
std::string elementVectorToTransNameString(const std::vector<T> &vec, const char* separator=", ", bool prettyPrint=false)
{
	return elementVectorToNameString<T>(vec, false, true, separator, prettyPrint);
}

/**
 * Convenience function that calls elementVectorToNameString with useFullName and useTransName set to true.
 * @param vec - A vector of Element (or a subclass of Element) pointers to be stringified.
 * @param separator - What string to insert between elements of the list. (Default: ", ")
 * @param prettyPrint - If true, will add extra formatting around the names assuming they're being displayed as part of a toString function or output to a log. (Default: false)
 * @return A string representation of the vector's contents, using the translated full name of each element.
 */
template <class T>
std::string elementVectorToFullTransNameString(const std::vector<T> &vec, const char* separator=", ", bool prettyPrint=false)
{
	return elementVectorToNameString<T>(vec, true, true, separator, prettyPrint);
}

/**
 * Grabs the names of Element objects in a vector and forms a vector of those names.
 * @param vec - The Element vector to extract names from.
 * @param useFullName - If true, will use the elements' full names (including any parameters) instead of just their base names. (Default: false)
 * @param useTransName - If true, will use the translated names of the elements instead of their original names. (Default: false)
 * @return A vector of strings representing the base names of each element.
 */
template <class T>
std::vector<std::string> elementVectorToNameVector(const std::vector<T> &vec, bool useFullName=false, bool useTransName=false)
{
	std::vector<std::string> tempVec;
	// Add the name of each element to tempVec.
	for(size_t i = 0; i < vec.size(); i++)
	{
		// Protect from accessing a NULL pointer, inserting "NULL" in if the pointer is invalid.
		if(vec[i] == NULL)
		{
			tempVec.push_back(std::string("NULL"));
		}
		else
		{
			if(useFullName)
			{
				if(useTransName)
				{
					tempVec.push_back(vec[i]->fullTransName());
				}
				else
				{
					tempVec.push_back(vec[i]->fullName());
				}
			}
			else
			{
				if(useTransName)
				{
					tempVec.push_back(vec[i]->transName);
				}
				else
				{
					tempVec.push_back(vec[i]->name);
				}
			}
		}
	}
	return tempVec;
}

/**
 * Convenience function that calls elementVectorToNameVector with useFullName set to true.
 * Passes false for useTransName.
 * @param vec - The Element vector to extract names from.
 * @return A vector of strings representing the full names of each element.
 */
template <class T>
std::vector<std::string> elementVectorToFullNameVector(const std::vector<T> &vec)
{
	return elementVectorToNameVector(vec, true, false);
}

/**
 * Convenience function that calls elementVectorToNameVector with useTransName set to true.
 * Passes false for useFullName.
 * @param vec - The Element vector to extract names from.
 * @return A vector of strings representing the translated base names of each element.
 */
template <class T>
std::vector<std::string> elementVectorToTransNameVector(const std::vector<T> &vec)
{
	return elementVectorToNameVector(vec, false, true);
}

/**
 * Convenience function that calls elementVectorToNameVector with useFullName and useTransName set to true.
 * @param vec - The Element vector to extract names from.
 * @return A vector of strings representing the translated full names of each element.
 */
template <class T>
std::vector<std::string> elementVectorToFullTransNameVector(const std::vector<T> &vec)
{
	return elementVectorToNameVector(vec, true, true);
}

/**
 * Takes a list of Element objects and makes a vector out of it.
 * @param lst - The list to transform.
 * @return A vector containing the same elements in the same order as lst.
 */
template <class T>
std::vector<T> elementListToElementVector(const std::list<T>& lst)
{
	class std::vector<T> retVec;
	class std::list<T>::const_iterator lIter;
	for(lIter = lst.begin(); lIter != lst.end(); ++lIter)
	{
		retVec.push_back(*lIter);
	}
	return retVec;
}

/**
 * Safely deallocates and clears the contents of a list whose elements are pointers.
 * @param lst - The list whose contents should be deallocated and cleared.
 */
template <class T>
void deallocateListContents(std::list<T*>& lst)
{
	class std::list<T*>::iterator lIter;
	for(lIter = lst.begin(); lIter != lst.end(); ++lIter)
	{
		if(*lIter != NULL)
		{
			delete *lIter;
		}
	}
	lst.clear();
}

/**
 * Attempts to transform a string into a numeric representation of itself.
 * For numbers, fmt should be dec, hex, or oct.
 * @param val - A reference to the recipient of the generated number.
 * @param s - The string to convert.
 * @param fmt - An optional parameter that specifies what kind of numeric conversion to attempt. If not given, will default to std::dec.
 * @return True if s could be converted into a number using fmt, false if there was a problem performing the conversion.
 */
template <class T>
bool from_string(T& val, const std::string& s, std::ios_base& (*fmt)(std::ios_base&)=std::dec) 
{
	std::istringstream iss(s);
	return !((iss >> fmt >> val).fail());
}

/**
 * Transforms something (usually a number) into a string representation of itself.
 * For integers, fmt should be dec, hex, or oct. For floating-point numbers, fmt should be fixed or scientific.
 * Precision will help control the precision of floating-point numbers.
 * @param val - The number to transform into a string.
 * @param fmt - An optional parameter controlling what kind of number val should be treated as. Defaults to std::dec.
 * @param precision - The decimal precision to use with floating-point numbers. Defaults to -1.
 * @return The string version of val on success, a blank string on failure.
 */
template <class T>
std::string to_string(T val, std::ios_base& (*fmt)(std::ios_base&)=std::dec, int precision=-1)
{
	std::stringstream ss;
	if(precision > -1)
	{
		ss.precision(precision);
	}
	ss << fmt << val;
	return ss.str();
}

/**
 * Checks if the contents of two vectors are equal.
 * To be true, the vectors must be the same size, and each element must match
 * in the vectors. Uses the != operator for comparison.
 * Two empty vectors are considered equal.
 * @param vec1 - The first vector to compare.
 * @param vec2 - The second vector to compare.
 * @return True if both vectors are the same size and all elements match, false otherwise.
 */
template <typename T>
bool areVectorsEqual(const std::vector<T&>& vec1, const std::vector<T&>& vec2)
{
	bool retVal = true; // Start optimistic.
	if(vec1.size() != vec2.size())
	{
		retVal = false;
	}
	else
	{
		for(size_t i = 0; i < vec1.size() && i < vec2.size(); i++)
		{
			if(vec1[i] != vec2[i])
			{
				retVal = false;
				break;
			}
		}
	}
	return retVal;
}

/**
 * Checks if a character represents a digit or not.
 * @param testChar - The character to test.
 * @return True if it's a digit, false otherwise.
 */
bool isDigit(char testChar);

/**
 * Checks if a character is an lower-case (English) letter or not.
 * @param testChar - The character to test.
 * @return True if it's a lower-case letter, false otherwise.
 */
bool isLowercase(char testChar);

/**
 * Checks if a character is an upper-case (English) letter or not.
 * @param testChar - The character to test.
 * @return True if it's an upper-case letter, false otherwise.
 */
bool isUppercase(char testChar);

/**
 * Checks if a character is an English letter or not, regardless of case.
 * @param testChar - The character to test.
 * @return True if it's an upper- or lower-case letter, false otherwise.
 */
bool isLetter(char testChar);

}

#endif /* UTILITIES_H */
