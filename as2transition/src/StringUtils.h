#ifndef STRINGUTILS_DOT_H
#define STRINGUTILS_DOT_H

#include <sstream>
#include <string>

/**
 * A class of static string utilities that help with processing raw text into various forms.
 */
class StringUtils
{
  public:
	/**
	 * Attempts to transform a string into a numeric representation of itself.
	 * For numbers, fmt should be dec, hex, or oct.
	 * @param val - A reference to the recipient of the generated number.
	 * @param s - The string to convert.
	 * @param fmt - An optional parameter that specifies what kind of numeric conversion to attempt. If not given, will default to std::dec.
	 * @return True if s could be converted into a number using fmt, false if there was a problem performing the conversion.
	 */
	template <class T>
	static bool from_string(T& val, const std::string& s, std::ios_base& (*fmt)(std::ios_base&)=std::dec) 
	{
			std::istringstream iss(s);
			return !(iss >> fmt >> val).fail();
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
	static std::string to_string(T val, std::ios_base& (*fmt)(std::ios_base&)=std::dec, int precision=-1)
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
	 * Trims whitespace from both ends of a text string.
	 * @param text - The text to trim.
	 * @return The string stripped of whitespace on both sides.
	 */
	static std::string trimWhitespace(std::string& text)
	{
		std::string retVal = "";
		std::string whitespace = " \n\f\r\t\v";
		size_t sztFirstPos = 0, sztSecondPos = 0;
		if(text.length() > 0)
		{
			sztFirstPos = text.find_first_not_of(whitespace);
			sztSecondPos = text.find_last_not_of(whitespace);
			if(sztFirstPos != std::string::npos)
			{	// We got two valid positions, trim accordingly.
				retVal = text.substr(sztFirstPos, sztSecondPos - sztFirstPos + 1);
			}
			else
			{	// The whole dang string is whitespace, return blank.
				retVal = "";
			}
		}
		return retVal;
	}

	/**
	 * Starting from position index, finds the first character in text that isn't whitespace, returns its position.
	 * @param text - The string to search.
	 * @param index - Optional parameter specifying starting index of the search. Defaults to 0.
	 * @return The index of the first character in text that isn't whitespace, or string::npos if it's all whitespace.
	 */
	static size_t findFirstNotWhitespace(std::string& text, size_t index=0)
	{
		return text.find_first_not_of(" \n\f\r\t\v", index);
	}

	/**
	 * Starting from position index, finds the first character in text that is whitespace, returns its position.
	 * @param text - The string to search through.
	 * @param index - Optional parameter specifying starting index of the search. Defaults to 0.
	 * @return The index of the first character in text that is whitespace, or string::npos if none of it is whitespace.
	 */
	static size_t findFirstWhitespace(std::string& text, size_t index=0)
	{
		return text.find_first_of(" \n\f\r\t\v", index);
	}
  private:
	  /**
	   * Private default constructor. Does nothing, but prevents instantiation.
	   */
	  StringUtils()
	  {
		  // Intentionally empty.
	  }
};

#endif // STRINGUTILS_DOT_H
