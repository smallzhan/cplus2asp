#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

#include <list>
#include "Token.h"

/**
 * Acts as a linear container for a series of Token objects.
 */
class TokenStream
{
protected:
	std::list<Token*> tokenList; ///< The internal data structure to hold the token pointers.
public:
	/**
	 * Default constructor. Does nothing, just here for completeness's sake.
	 */
	TokenStream();
	
	// Methods to access & manipulate the internal token list.
	/**
	 * Wrapper for tokenList.empty().
	 * @return The value of tokenList.empty().
	 */
	bool empty() const;
	/**
	 * Wrapper for tokenList.size().
	 * @return The value of tokenList.size().
	 */
	bool size() const;
	/**
	 * Wrapper for tokenList.front().
	 * @return The iterator returned by tokenList.front().
	 */
	Token* front();
	/**
	 * Wrapper for tokenList.back().
	 * @return The iterator returned by tokenList.back().
	 */
	Token* back();
	/**
	 * Wrapper for tokenList.begin().
	 * @return The iterator returned by tokenList.begin().
	 */
	std::list<Token*>::iterator begin();
	/**
	 * Wrapper for tokenList.end().
	 * @return The iterator returned by tokenList.end().
	 */
	std::list<Token*>::iterator end();
	/**
	 * Wrapper for tokenList.insert(...).
	 * Inserts a token into the stream just before the passed iterator's position.
	 * @param iter - Iterator at the desired insert position.
	 * @param tok - The Token pointer to insert.
	 * @return An iterator to the newly inserted Token pointer.
	 */
	std::list<Token*>::iterator insert(std::list<Token*>::iterator iter, Token* tok);
	/**
	 * Wrapper for tokenList.insert(...).
	 * Inserts a series of tokens into the stream just before the position iterator.
	 * @param position - Iterator pointing to the desired insert position.
	 * @param first - An iterator to the first token to insert.
	 * @param last - An iterator just past the last token to insert.
	 */
	void insert(std::list<Token*>::iterator position, std::list<Token*>::iterator first, std::list<Token*>::iterator last);
	/**
	 * Enhanced wrapper for tokenList.erase(...).
	 * Removes a token from the stream at the passed iterator's position.
	 * Frees the memory associated with the removed Token pointer.
	 * @param iter - Iterator at the desired Token pointer to erase.
	 * @return An iterator to the Token pointer immediately following the removed element.
	 */
	std::list<Token*>::iterator erase(std::list<Token*>::iterator iter);
	/**
	 * Enhanced wrapper for tokenList.erase(...).
	 * Removes a token from the stream at the passed iterator's position.
	 * Does NOT free the memory associated with the removed Token pointer.
	 * @param iter - Iterator at the desired Token pointer to pop.
	 * @return An iterator to the Token pointer immediately following the removed element.
	 */
	std::list<Token*>::iterator pop(std::list<Token*>::iterator iter);
	/**
	 * Enhanced wrapper for tokenList.clear().
	 * Frees the memory for all Token objects in tokenList, then clears the list.
	 */
	void clear();
	/**
	 * Wrapper for tokenList.push_front().
	 * Inserts tok at the front of the list.
	 * @param tok - Pointer to the new token to insert.
	 */
	void push_front(Token* tok);
	/**
	 * Wrapper for tokenList.pop_front().
	 * Removes the token at the front of the list.
	 * Does NOT free the popped token's memory.
	 */
	void pop_front();
	/**
	 * Wrapper for tokenList.push_back().
	 * Inserts tok at the back of the list.
	 * @param tok - Pointer to the new token to insert.
	 */
	void push_back(Token* tok);
	/**
	 * Wrapper for tokenList.pop_back().
	 * Removes the token at the back of the list.
	 * Does NOT free the popped token's memory.
	 */
	void pop_back();
	
	/**
	 * Destructor. Frees the memory for all allocated tokens in tokenList.
	 */
	virtual ~TokenStream();
};

#endif /* TOKENSTREAM_H */
