
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* "%code requires" blocks.  */

/* Line 1676 of yacc.c  */
#line 8 "parser.y"

#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "Attribute.h"
#include "ASPCode.h"
#include "Comment.h"
#include "Constant.h"
#include "Object.h"
#include "NumberRange.h"
#include "Sort.h"
#include "Variable.h"
#include "Query.h"

#include "ElementCounter.h"
#include "SymbolTable.h"
#include "Translator.h"
#include "utilities.h"

#include "parser_types.h"



/* Line 1676 of yacc.c  */
#line 68 "parser.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END = 0,
     T_INTEGER = 258,
     T_IDENTIFIER = 259,
     T_STRING = 260,
     T_ASP = 261,
     T_COMMENT = 262,
     T_CONSTANTS = 263,
     T_INCLUDE = 264,
     T_MACROS = 265,
     T_OBJECTS = 266,
     T_QUERY = 267,
     T_SHOW = 268,
     T_SORTS = 269,
     T_VARIABLES = 270,
     T_ABACTION = 271,
     T_ACTION = 272,
     T_MACROACTION = 273,
     T_ADDITIVEACTION = 274,
     T_ADDITIVEFLUENT = 275,
     T_AFTER = 276,
     T_ALWAYS = 277,
     T_ATTRIBUTE = 278,
     T_BY = 279,
     T_CAUSED = 280,
     T_CAUSES = 281,
     T_CONSTRAINT = 282,
     T_DECREMENTS = 283,
     T_DEFAULT = 284,
     T_EXOGENOUS = 285,
     T_EXOGENOUSACTION = 286,
     T_IF = 287,
     T_INCREMENTS = 288,
     T_INERTIAL = 289,
     T_INERTIALFLUENT = 290,
     T_LABEL = 291,
     T_MAY_CAUSE = 292,
     T_MAXADDITIVE = 293,
     T_MAXSTEP = 294,
     T_NEVER = 295,
     T_NOCONCURRENCY = 296,
     T_NONEXECUTABLE = 297,
     T_OF = 298,
     T_POSSIBLY_CAUSED = 299,
     T_RIGID = 300,
     T_SDFLUENT = 301,
     T_SIMPLEFLUENT = 302,
     T_UNLESS = 303,
     T_WHERE = 304,
     T_IS = 305,
     T_FALSE = 306,
     T_NONE = 307,
     T_TRUE = 308,
     T_ABS = 309,
     T_AT = 310,
     T_BRACKET_L = 311,
     T_BRACKET_R = 312,
     T_COLON_DASH = 313,
     T_PAREN_L = 314,
     T_PAREN_R = 315,
     T_PERIOD = 316,
     T_PIPE = 317,
     T_SEMICOLON = 318,
     T_DBL_COLON = 319,
     T_ARROW_LDASH = 320,
     T_ARROW_REQ = 321,
     T_ARROW_LEQ = 322,
     T_ARROW_RDASH = 323,
     T_COLON = 324,
     T_COMMA = 325,
     T_EQUIV = 326,
     T_IMPL = 327,
     T_DBL_PLUS = 328,
     T_DBL_AMP = 329,
     T_AMP = 330,
     T_GTHAN_EQ = 331,
     T_EQ_LTHAN = 332,
     T_GTHAN = 333,
     T_LTHAN = 334,
     T_NOT_EQ = 335,
     T_DBL_EQ = 336,
     T_EQ = 337,
     T_NOT = 338,
     T_DBL_PERIOD = 339,
     T_PLUS = 340,
     T_DASH = 341,
     T_DBL_GTHAN = 342,
     T_MOD = 343,
     T_INT_DIV = 344,
     T_STAR = 345,
     T_BIG_CONJ = 346,
     T_BIG_DISJ = 347,
     T_POUND = 348,
     T_UMINUS = 349
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 34 "parser.y"

    /* Types returned by the lexer. */
    int integer; ///< Basic integer.
    std::string* str; ///< String pointer.
    ASPCode* asp; ///< Raw ASP code.
    Comment* com; ///< Raw commented text.
    /* Classes directly used by the parser. */
    Attribute* attribute; ///< Pointer to an Attribute element instance.
    Constant* constant; ///< Pointer to a Constant element instance.
    NumberRange* numRange; ///< Pointer to a NumRange element instance.
    Object* object; ///< Pointer to an Object element instance.
    Sort* sort; ///< Pointer to a Sort element instance.
    Variable* variable; ///< Pointer to a Variable element instance.
    Constant::ConstantType constType; ///< A ConstantType enum describing the type of a related constant.
    /* Containers used by the parser. */
    std::list<Constant*>* l_constant; ///< Pointer to a list of Constant element pointers.
    std::list<Object*>* l_object; ///< Pointer to a list of Object element pointers.
    std::list<Sort*>* l_sort; ///< Pointer to a list of Sort element pointers.
    std::list<Variable*>* l_variable; ///< Pointer to a list of Variable element pointers.
    std::vector<ParseElement*>* v_parseElement; ///< Pointer to a list of ParseElement pointers.
    std::list<std::pair<enum BigQuantifiers::QuantifierType, ParseElement*>* >* l_quantPair; ///< List of pairs of QuantifierType enums and a associated ParseElement pointers.
    std::pair<enum BigQuantifiers::QuantifierType, ParseElement*>* p_quantPair;
    ///< Pair of a QuantifierType enum and an associated ParseElement pointer.
    std::list<std::pair<ParseElement*, ParseElement*>* >* l_action; /// < List of actions in the macro Action definition
    std::pair<ParseElement*, ParseElement*>* p_action; ///< Pair of an action and the ``if formula part'' of the conditions.
    /* Types specific to the parser. */
    PT_constant_binder_t* constant_binder_t; ///< An internal type for carrying information in a particular constant declaration grammar rule up the chain.
    ParseElement* parseElement; ///< A pointer to a class like Element, but with translation features added and more loose ties to actual declared elements.
    /* Used to denote a rule whose $$ we don't care about and never (de)allocate or assign to. */
    void* not_used; ///< Used for rules whose lvalues are not used or referenced by other grammar rules.



/* Line 1676 of yacc.c  */
#line 214 "parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE ltsyylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE ltsyylloc;

/* "%code provides" blocks.  */

/* Line 1676 of yacc.c  */
#line 66 "parser.y"

/**
 * @file parser.h
 * @brief Contains parser for C+ programs, including definitions and helper functions.
 */

extern Translator mainTrans; ///< The main Translator instance, declared by the parser to create a close working relationship.
extern bool ltsyyendOfFile; ///< True if the parser has reached the end of the input stream.
extern int ltsyynerrs; ///< Output string stream used to store and output error messages from the parser and its helper modules.

/**
 * Invokes the parser, processing and translating input until either the end of input
 * or a fatal error are encountered.
 * @return 0 if parsing was successful (or if only non-fatal errors encountered), typically 1 if any fatal errors were encountered.
 */
int ltsyyparse();

/**
 * Wraps the given element in two new negation operators to create a "not not (...)." wrap.
 * @param elem - The element to wrap in a "not not (...)" wrapper.
 * @return A new SimpleUnaryOperator "not" object, wrapping another such object, wrapping the original element (or NULL if anything is invalid).
 */
SimpleUnaryOperator* createNotNot(ParseElement* elem);

/**
 * Creates an object-like element that mirrors the contents of elem.
 * Used when a constant needs to be treated directly as an object.
 * @param elem - The constant to mirror.
 * @return A new ObjectLikeElement object whose contents mirror those of elem.
 * @note The parameters of elem are shallow copied to the new element, be sure to safely clear the new element's parameters before deallocating it!
 */
ObjectLikeElement* createObjLikeFromConstLike(ConstantLikeElement* elem);

/**
 * Deallocates a "not not" wrapper such that the original ParseElement is not deallocated.
 * Removes any parentheses flags from the original ParseElement object.
 * @param uop - The outermost "not" operator of the two to destroy.
 * @return The ParseElement object that was formerly wrapped by the two "not" operators (or NULL if anything is invalid).
 */
ParseElement* deallocateNotNot(SimpleUnaryOperator* uop);

/**
 * NULLs elem's preOp and postOp before deallocating so the sub-ParseElement objects don't get caught in the deallocation.
 * @param elem - The temporary SimpleBinaryOperator element to destroy.
 */
void deallocateTempBinaryOp(SimpleBinaryOperator* &elem);

/**
 * NULLs elem's postOp before deallocating so the sub-ParseElement object doesn't get caught in the deallocation.
 * @param elem - The temporary SimpleUnaryOperator element to destroy.
 */
void deallocateTempUnaryOp(SimpleUnaryOperator* &elem);

/**
 * Adds a standard parsing caution header to ltsyyossErr to make caution
 * notifications easier to pinpoint.
 * @param cautionLoc - YYLTYPE struct where the caution was invoked.
 */
void ltsyystartCaution(YYLTYPE cautionLoc);
/**
 * Adds a standard (location-unaware) parsing caution header to ltsyyossErr
 * to try making caution notifications easier to locate.
 */
void ltsyystartCaution();
/**
 * Caution reporting function for the parser.
 * Never called by bison, called by parser actions when a non-fatal
 * situation is identified that might produce unexpected/undesired
 * translation results.
 * If ltsyyossErr is empty, outputs a generic caution notification,
 * otherwise uses the existing contents of ltsyyossErr. In either case,
 * outputs to the same place errors go, always appends a newline, and
 * resets the contents of ltsyyossErr after outputting the caution.
 */
void ltsyycaution();

/**
 * Adds a standard parsing warning header to ltsyyossErr to make warning
 * notifications easier to pinpoint.
 * @param warningLoc - YYLTYPE struct where the warning was invoked.
 */
void ltsyystartWarning(YYLTYPE warningLoc);
/**
 * Adds a standard (location-unaware) parsing warning header to ltsyyossErr
 * to try making warning notifications easier to locate.
 */
void ltsyystartWarning();
/**
 * Warning reporting function for the parser.
 * Never called by bison, called by parser actions when a non-fatal
 * situation is identified that will probably produce unexpected/undesired
 * translation results.
 * If ltsyyossErr is empty, outputs a generic warning notification,
 * otherwise uses the existing contents of ltsyyossErr. In either case,
 * outputs to the same place errors go, always appends a newline, and
 * resets the contents of ltsyyossErr after outputting the warning.
 */
void ltsyywarning();

/**
 * Adds a standard parse error header to ltsyyossErr to make it easier
 * to report errors in actions.
 * @param errLoc - YYLTYPE struct of the location of the error.
 */
void ltsyystartParseError(YYLTYPE errLoc);
/**
 * Adds a standard (location-unaware) parse error header to ltsyyossErr to
 * make it easier to report errors in actions.
 */
void ltsyystartParseError();
/**
 * Adds a standard syntax error header to ltsyyossErr to make it easier
 * to report errors in actions.
 * @param errLoc - YYLTYPE struct of the location of the error.
 */
void ltsyystartSyntaxError(YYLTYPE errLoc);
/**
 * Adds a standard (location-unaware) syntax error header to ltsyyossErr to
 * make it easier to report errors in actions.
 */
void ltsyystartSyntaxError();
/**
 * Error reporting function for the bison parser.
 * Since bison's default error message ("syntax error") is not useful,
 * ignores the passed message and looks at the contents of the ltsyyossErr
 * stream to decide what to output. If ltsyyossErr is empty, outputs
 * a general syntax error message, otherwise outputs the contents of
 * ltsyyossErr. In either case, automatically adds a newline to the end
 * of the message.
 * Automatically clears the contents and state of ltsyyossErr after printing
 * the applicable error message.
 * @param msg - The (ignored) error message provided by bison.
 */
void ltsyyerror(char const* msg);

/**
 * Wraps caution reporting for convenience and unification with convention for error reporting.
 */
void ltsyyreportCaution();
/**
 * Wraps warning reporting for convenience and unification with convention for error reporting.
 */
void ltsyyreportWarning();
/**
 * Wraps error reporting for ease and to ensure the number of errors gets incremented with each (action-generated) error report.
 */
void ltsyyreportError();




/* Line 1676 of yacc.c  */
#line 394 "parser.h"
