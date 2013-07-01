
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse         ltsyyparse
#define yylex           ltsyylex
#define yyerror         ltsyyerror
#define yylval          ltsyylval
#define yychar          ltsyychar
#define yydebug         ltsyydebug
#define yynerrs         ltsyynerrs
#define yylloc          ltsyylloc

/* Copy the first part of user declarations.  */


/* Line 189 of yacc.c  */
#line 81 "parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 1
#endif

/* "%code requires" blocks.  */

/* Line 209 of yacc.c  */
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



/* Line 209 of yacc.c  */
#line 133 "parser.cpp"

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

/* Line 214 of yacc.c  */
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



/* Line 214 of yacc.c  */
#line 279 "parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

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

/* "%code provides" blocks.  */

/* Line 261 of yacc.c  */
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




/* Line 261 of yacc.c  */
#line 455 "parser.cpp"

/* Copy the second part of user declarations.  */

/* Line 264 of yacc.c  */
#line 216 "parser.y"

#include "lexerTokenStream.h"

/* Line 264 of yacc.c  */
#line 220 "parser.y"

Translator mainTrans; // The main Translator instance, declared by the parser to create a close working relationship.
bool ltsyyendOfFile = false; // True if the parser has reached the end of the input stream.
std::ostringstream ltsyyossErr; // Output string stream used to store and output error messages from the parser and its helper modules.
/// Clears the contents and error flags of the output string stream used for error reporting.
#define LTSYYRESETOSS \
ltsyyossErr.str(""); \
ltsyyossErr.clear();
/// Placeholder value for parse rules whose lvals ($$) we don't end up needing.
#define PARSERULE_NOT_USED NULL
/// Clears out, deallocates, and nullifies a list/vector/etc. pointer.
#define deallocateList(lst) \
lst->clear(); \
delete lst; \
lst = NULL;
/// Deallocates and nullifies a non-container pointer.
#define deallocateItem(item) \
delete item; \
item = NULL;

// Helper functions for actions.
/**
 * Takes a sort identifier and a (possibly empty) list of subsorts and tries to
 * create, add, and translate a sort from the information.
 * @param sortIdent - A string of the new sort's original name.
 * @param subsorts - A (possibly empty) list of subsorts of the desired sort.
 * @return A pointer to the new sort object, or NULL on an error.
 */
Sort* processSort(std::string* sortIdent, std::list<Sort*>* subsorts);

/**
 * Tries to find an existing normal sort or declare a starred ("something*") sort.
 * Will not instantiate a normal sort (even as a child of a "something*" sort, will
 * report an error instead.
 * @param sortIdent - The name of the sort to check and find.
 * @return A pointer to the associated instantiated sort obect, or NULL if the sort wasn't found.
 */
Sort* checkDynamicSortDecl(std::string* sortIdent);

/**
 * Transforms declarative laws ("inertial p", "exogenous a(X)", "rigid q", etc.) to basic form and calls the translator for them.
 * @param head - The head of the law, in this case a bare constant-like expression.
 * @param ifBody - Optional conditional formula to govern when the law applies.
 * @param afterBody - Optional conditional formula specifying conditions from the prior time step.
 * @param whereBody - Another conditional formula to govern when the law applies.
 * @param opType - The kind of declaration this is (exogenous, inertial, etc.).
 * @return True if everything translates properly, false if anything goes wrong.
 */
bool handleDeclarativeLaw(ParseElement* head, ParseElement* ifBody, ParseElement* afterBody, ParseElement* whereBody, SimpleUnaryOperator::UnaryOperatorType opType);

/**
 * Transforms a causal law of the form "always F [where G]." to basic form, then calls the translator for it.
 * @param constraint - The condition that must be true.
 * @param whereBody - A conditional formula to govern when the law applies.
 * @return True if everything translates properly, false if anything goes wrong.
 */
bool handleAlwaysLaw(ParseElement* constraint, ParseElement* whereBody);

/**
 * Transforms a causal law of the form "constraint F [after H] [where J]." to basic form, then calls the translator for it.
 * @param constraint - The condition that must be true.
 * @param afterBody - Optional conditional formula specifying restrictions from the prior time step.
 * @param unlessBody - Optional formula that acts as an abnormality condition.
 * @param whereBody - Another conditional formula to govern when the law applies.
 * @return True if everything translates properly, false if anything goes wrong.
 */
bool handleConstraintLaw(ParseElement* constraint, ParseElement* afterBody, ParseElement* unlessBody, ParseElement* whereBody);

/**
 * Transforms a causal law of the form "default F [if G] [after H] [where J]." to basic form, then calls the translator on it.
 * @param head - The head of the law.
 * @param ifBody - Optional conditional formula to govern when the law applies.
 * @param afterBody - Optional conditional formula specifying conditions from the prior time step.
 * @param whereBody - Another conditional formula to govern when the law applies.
 * @return True if everything translates properly, false if anything goes wrong.
 */
bool handleDefaultLaw(ParseElement* head, ParseElement* ifBody, ParseElement* afterBody, ParseElement* whereBody);

/**
 * Transforms a causal law of the form "nonexecutable F [if G] [where H]." to basic form, then calls the translator for it.
 * @param nonEx - The formula that should not be executed.
 * @param ifBody - Optional conditional formula to govern when the law applies.
 * @param whereBody - Another conditional formula to govern when the law applies.
 * @return True if everything translates properly, false if anything goes wrong.
 */
bool handleNonexecutableLaw(ParseElement* nonEx, ParseElement* ifBody, ParseElement* whereBody);

/**
 * Transforms a causal law of the form "possibly caused F [if G] [after H] [where J]." to basic form, then calls the translator on it.
 * @param head - The head of the law.
 * @param ifBody - Optional conditional formula to govern when the law applies.
 * @param afterBody - Optional conditional formula specifying conditions from the prior time step.
 * @param whereBody - Another conditional formula to govern when the law applies.
 * @return True if everything translates properly, false if anything goes wrong.
 */
bool handlePossiblyCausedLaw(ParseElement* head, ParseElement* ifBody, ParseElement* afterBody, ParseElement* whereBody);

/**
 * Transforms a causal law of the form "G may cause F [if H] [where J]." to basic form, then calls the translator on it.
 * @param causer - The causing action formula.
 * @param causee - The formula being caused.
 * @param ifBody - Optional conditional formula to govern when the law applies.
 * @param whereBody - Another conditional formula to govern when the law applies.
 * @return True if everything translates properly, false if anything goes wrong.
 */
bool handleMayCauseLaw(ParseElement* causer, ParseElement* causee, ParseElement* ifBody, ParseElement* whereBody);

/**
 * Transforms a causal law of the form "G causes F [if H] [where J]." to basic form, then calls the translator on it.
 * @param causer - The causing action formula.
 * @param causee - The formula being caused.
 * @param ifBody - Optional conditional formula to govern when the law applies.
 * @param whereBody - Another conditional formula to govern when the law applies.
 * @return True if everything translates properly, false if anything goes wrong.
 */
bool handleCausesLaw(ParseElement* causer, ParseElement* causee, ParseElement* ifBody, ParseElement* whereBody);

/**
 * Transforms a causal law of the form "A increments B by N [if H] [where J]." to basic form, then calls the translator on it.
 * @param causer - The causing action.
 * @param causee - The additive constant being incremented.
 * @param increment - The increment expression
 * @param ifBody - Optional conditional formula to govern when the law applies.
 * @param whereBody - Another conditional formula to govern when the law applies.
 * @param isIncrement - True if the law is increment, false if it is decrement.
 * @return True if everything translates properly, false if anything goes wrong.
 */
bool handleIncrementLaw(ParseElement* causer, ParseElement* causee, ParseElement* increment, ParseElement* ifBody, ParseElement* whereBody, bool isIncrement);

bool handleMacroActionDefLaw( ParseElement* mname, std::list<std::pair<ParseElement*, ParseElement*> *> *mcont);


/* Line 264 of yacc.c  */
#line 599 "parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  104
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1149

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  104
/* YYNRULES -- Number of rules.  */
#define YYNRULES  310
/* YYNRULES -- Number of states.  */
#define YYNSTATES  561

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   349

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    30,    35,    37,    41,    43,
      47,    49,    53,    57,    59,    63,    65,    69,    71,    75,
      77,    82,    84,    89,    91,    95,    97,   102,   106,   113,
     115,   121,   126,   128,   132,   134,   138,   140,   144,   148,
     150,   154,   156,   160,   162,   166,   168,   173,   175,   177,
     182,   187,   189,   193,   195,   199,   201,   205,   207,   211,
     213,   216,   220,   222,   224,   226,   228,   230,   232,   234,
     236,   238,   240,   242,   244,   249,   251,   255,   257,   261,
     263,   267,   271,   273,   277,   279,   283,   285,   287,   290,
     293,   295,   297,   299,   301,   303,   305,   307,   309,   311,
     313,   315,   317,   319,   324,   327,   336,   343,   350,   355,
     362,   367,   372,   375,   384,   391,   398,   403,   410,   415,
     420,   423,   432,   439,   446,   451,   458,   463,   468,   471,
     478,   483,   488,   491,   498,   503,   508,   511,   516,   519,
     528,   535,   542,   547,   554,   559,   564,   567,   575,   581,
     587,   591,   599,   605,   611,   615,   617,   627,   635,   643,
     649,   659,   667,   675,   681,   692,   701,   710,   717,   726,
     733,   740,   745,   754,   761,   768,   773,   780,   785,   790,
     793,   797,   801,   803,   805,   809,   813,   819,   821,   823,
     825,   827,   831,   833,   836,   840,   844,   848,   852,   854,
     858,   860,   864,   868,   872,   874,   876,   878,   882,   884,
     888,   890,   893,   897,   903,   905,   907,   910,   913,   916,
     919,   924,   926,   930,   934,   938,   944,   946,   948,   952,
     956,   958,   961,   965,   969,   973,   977,   979,   983,   985,
     989,   993,   997,   999,  1005,  1007,  1012,  1014,  1018,  1020,
    1022,  1026,  1028,  1030,  1032,  1034,  1036,  1040,  1042,  1046,
    1050,  1054,  1058,  1062,  1065,  1070,  1072,  1074,  1078,  1080,
    1082,  1084,  1087,  1089,  1093,  1095,  1099,  1103,  1107,  1111,
    1115,  1117,  1119,  1121,  1123,  1125,  1127,  1129,  1131,  1134,
    1137,  1139,  1141,  1143,  1145,  1147,  1149,  1151,  1153,  1156,
    1158
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      96,     0,    -1,    -1,    97,    -1,    98,    -1,    97,    98,
      -1,    99,    -1,   111,    -1,   112,    -1,   169,    -1,   121,
      -1,   122,    -1,   130,    -1,   138,    -1,     1,    61,    -1,
      58,     8,   100,    61,    -1,   101,    -1,    59,   101,    60,
      -1,   102,    -1,   100,    63,   102,    -1,   103,    -1,    59,
     103,    60,    -1,   104,    64,   109,    -1,   105,    -1,    59,
     105,    60,    -1,   106,    -1,   104,    70,   106,    -1,   107,
      -1,    59,   107,    60,    -1,     4,    -1,     4,    59,   180,
      60,    -1,     4,    -1,     4,    59,   180,    60,    -1,   110,
      -1,    59,   110,    60,    -1,   127,    -1,   129,    59,   127,
      60,    -1,    23,    43,   108,    -1,    23,    59,   127,    60,
      43,   108,    -1,   185,    -1,    58,    38,    64,   187,    61,
      -1,    58,    11,   113,    61,    -1,   114,    -1,    59,   114,
      60,    -1,   115,    -1,   113,    63,   113,    -1,   116,    -1,
      59,   116,    60,    -1,   117,    64,   126,    -1,   118,    -1,
      59,   118,    60,    -1,   119,    -1,   117,    70,   119,    -1,
     120,    -1,    59,   120,    60,    -1,     4,    -1,     4,    59,
     180,    60,    -1,   187,    -1,   185,    -1,    58,    13,     1,
      61,    -1,    58,    14,   123,    61,    -1,   124,    -1,    59,
     124,    60,    -1,   125,    -1,   123,    63,   123,    -1,   127,
      -1,   127,    87,   123,    -1,   127,    -1,    59,   127,    60,
      -1,   128,    -1,   128,    90,    -1,   128,    85,    52,    -1,
       4,    -1,   129,    -1,    16,    -1,    17,    -1,    18,    -1,
      19,    -1,    20,    -1,    31,    -1,    35,    -1,    45,    -1,
      46,    -1,    47,    -1,    58,    15,   131,    61,    -1,   132,
      -1,    59,   132,    60,    -1,   133,    -1,   133,    63,   131,
      -1,   134,    -1,    59,   134,    60,    -1,   135,    64,   137,
      -1,   136,    -1,    59,   136,    60,    -1,     4,    -1,   136,
      70,     4,    -1,   126,    -1,   185,    -1,   139,    61,    -1,
     152,    61,    -1,   140,    -1,   141,    -1,   142,    -1,   143,
      -1,   144,    -1,   145,    -1,   146,    -1,   147,    -1,   148,
      -1,   149,    -1,   150,    -1,   151,    -1,   153,    -1,    22,
     157,    49,   161,    -1,    22,   157,    -1,    27,   157,    21,
     157,    48,   177,    49,   161,    -1,    27,   157,    21,   157,
      49,   161,    -1,    27,   157,    21,   157,    48,   177,    -1,
      27,   157,    21,   157,    -1,    27,   157,    48,   177,    49,
     161,    -1,    27,   157,    49,   161,    -1,    27,   157,    48,
     177,    -1,    27,   157,    -1,    29,   156,    32,   157,    21,
     157,    49,   161,    -1,    29,   156,    32,   157,    21,   157,
      -1,    29,   156,    32,   157,    49,   161,    -1,    29,   156,
      32,   157,    -1,    29,   156,    21,   157,    49,   161,    -1,
      29,   156,    21,   157,    -1,    29,   156,    49,   161,    -1,
      29,   156,    -1,    30,   177,    32,   157,    21,   157,    49,
     161,    -1,    30,   177,    32,   157,    21,   157,    -1,    30,
     177,    21,   157,    49,   161,    -1,    30,   177,    21,   157,
      -1,    30,   177,    32,   157,    49,   161,    -1,    30,   177,
      32,   157,    -1,    30,   177,    49,   161,    -1,    30,   177,
      -1,    34,   177,    32,   157,    49,   161,    -1,    34,   177,
      32,   157,    -1,    34,   177,    49,   161,    -1,    34,   177,
      -1,    42,   157,    32,   157,    49,   161,    -1,    42,   157,
      32,   157,    -1,    42,   157,    49,   161,    -1,    42,   157,
      -1,    45,   177,    49,   161,    -1,    45,   177,    -1,    44,
     156,    32,   157,    21,   157,    49,   161,    -1,    44,   156,
      32,   157,    21,   157,    -1,    44,   156,    32,   157,    49,
     161,    -1,    44,   156,    32,   157,    -1,    44,   156,    21,
     157,    49,   161,    -1,    44,   156,    21,   157,    -1,    44,
     156,    49,   161,    -1,    44,   156,    -1,   157,    37,   156,
      32,   157,    49,   161,    -1,   157,    37,   156,    32,   157,
      -1,   157,    37,   156,    49,   161,    -1,   157,    37,   156,
      -1,   157,    26,   156,    32,   157,    49,   161,    -1,   157,
      26,   156,    32,   157,    -1,   157,    26,   156,    49,   161,
      -1,   157,    26,   156,    -1,    41,    -1,   157,    33,   156,
      24,   182,    32,   157,    49,   161,    -1,   157,    33,   156,
      24,   182,    32,   157,    -1,   157,    33,   156,    24,   182,
      49,   161,    -1,   157,    33,   156,    24,   182,    -1,   157,
      28,   156,    24,   182,    32,   157,    49,   161,    -1,   157,
      28,   156,    24,   182,    32,   157,    -1,   157,    28,   156,
      24,   182,    49,   161,    -1,   157,    28,   156,    24,   182,
      -1,    25,   156,    32,   157,    21,   157,    48,   177,    49,
     161,    -1,    25,   156,    32,   157,    21,   157,    48,   177,
      -1,    25,   156,    32,   157,    21,   157,    49,   161,    -1,
      25,   156,    32,   157,    21,   157,    -1,    25,   156,    32,
     157,    48,   177,    49,   161,    -1,    25,   156,    32,   157,
      48,   177,    -1,    25,   156,    32,   157,    49,   161,    -1,
      25,   156,    32,   157,    -1,    25,   156,    21,   157,    48,
     177,    49,   161,    -1,    25,   156,    21,   157,    48,   177,
      -1,    25,   156,    21,   157,    49,   161,    -1,    25,   156,
      21,   157,    -1,    25,   156,    48,   177,    49,   161,    -1,
      25,   156,    48,   177,    -1,    25,   156,    49,   161,    -1,
      25,   156,    -1,   177,    50,   154,    -1,   154,    63,   155,
      -1,   155,    -1,   177,    -1,    59,   177,    60,    -1,   177,
      32,   157,    -1,    59,   177,    32,   157,    60,    -1,   162,
      -1,    53,    -1,    51,    -1,   158,    -1,    59,   158,    60,
      -1,   159,    -1,   191,   157,    -1,   157,   189,   157,    -1,
     157,   190,   157,    -1,   157,    71,   157,    -1,   157,    72,
     157,    -1,   160,    -1,    59,   160,    60,    -1,   181,    -1,
     181,   192,   181,    -1,   181,   193,   181,    -1,   181,   194,
     181,    -1,   165,    -1,   157,    -1,   163,    -1,    59,   163,
      60,    -1,   164,    -1,   162,   189,   162,    -1,   177,    -1,
     191,   177,    -1,   177,    82,   181,    -1,    56,   166,    62,
     157,    57,    -1,   167,    -1,   168,    -1,   166,   167,    -1,
     166,   168,    -1,    91,     4,    -1,    92,     4,    -1,    58,
      12,   170,    61,    -1,   171,    -1,   170,    63,   170,    -1,
      36,    64,     3,    -1,    39,    64,     3,    -1,    39,    64,
       3,    84,     3,    -1,   172,    -1,   173,    -1,    59,   172,
      60,    -1,   183,    69,   172,    -1,   174,    -1,   191,   172,
      -1,   172,   189,   172,    -1,   172,   190,   172,    -1,   172,
      71,   172,    -1,   172,    72,   172,    -1,   175,    -1,    59,
     175,    60,    -1,   181,    -1,   181,   192,   181,    -1,   181,
     193,   181,    -1,   181,   194,   181,    -1,   176,    -1,    56,
     166,    62,   172,    57,    -1,     4,    -1,     4,    59,   178,
      60,    -1,   179,    -1,   178,    70,   179,    -1,   182,    -1,
     127,    -1,   180,    70,   127,    -1,    53,    -1,    51,    -1,
      52,    -1,   182,    -1,   183,    -1,    59,   183,    60,    -1,
     184,    -1,   182,    85,   182,    -1,   182,    86,   182,    -1,
     182,    90,   182,    -1,   182,    89,   182,    -1,   182,    88,
     182,    -1,    54,   182,    -1,    54,    59,   182,    60,    -1,
     186,    -1,   177,    -1,   187,    84,   187,    -1,     3,    -1,
      38,    -1,    39,    -1,    86,   186,    -1,   188,    -1,    59,
     188,    60,    -1,   186,    -1,   187,    85,   187,    -1,   187,
      86,   187,    -1,   187,    90,   187,    -1,   187,    89,   187,
      -1,   187,    88,   187,    -1,    75,    -1,    74,    -1,    70,
      -1,    73,    -1,    86,    -1,    83,    -1,    82,    -1,    80,
      -1,    55,    79,    -1,    55,    78,    -1,    81,    -1,   195,
      -1,   196,    -1,   197,    -1,   198,    -1,    79,    -1,    78,
      -1,    77,    -1,    55,    77,    -1,    76,    -1,    55,    76,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   517,   517,   518,   521,   522,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   547,   550,   551,   554,   555,
     558,   559,   562,   653,   657,   663,   672,   696,   700,   706,
     712,   733,   739,   753,   757,   763,   837,   898,   916,   945,
     989,  1006,  1009,  1010,  1013,  1014,  1017,  1018,  1021,  1082,
    1086,  1092,  1102,  1126,  1130,  1136,  1142,  1159,  1165,  1174,
    1184,  1195,  1199,  1205,  1210,  1243,  1255,  1268,  1272,  1278,
    1282,  1288,  1297,  1301,  1307,  1313,  1319,  1324,  1330,  1336,
    1342,  1348,  1354,  1360,  1370,  1373,  1374,  1377,  1378,  1381,
    1382,  1385,  1405,  1409,  1415,  1451,  1491,  1505,  1539,  1540,
    1543,  1544,  1545,  1546,  1547,  1548,  1549,  1550,  1551,  1552,
    1553,  1554,  1555,  1559,  1570,  1582,  1595,  1607,  1619,  1630,
    1642,  1653,  1664,  1676,  1689,  1701,  1713,  1724,  1736,  1747,
    1758,  1770,  1783,  1795,  1807,  1818,  1830,  1841,  1852,  1864,
    1876,  1887,  1898,  1910,  1922,  1933,  1944,  1956,  1967,  1979,
    1992,  2004,  2016,  2027,  2039,  2050,  2061,  2073,  2086,  2098,
    2110,  2123,  2136,  2148,  2160,  2173,  2181,  2196,  2210,  2224,
    2237,  2252,  2266,  2280,  2295,  2305,  2314,  2323,  2331,  2340,
    2348,  2356,  2363,  2372,  2380,  2388,  2395,  2403,  2410,  2417,
    2425,  2438,  2443,  2450,  2457,  2465,  2472,  2482,  2486,  2493,
    2502,  2506,  2517,  2521,  2528,  2536,  2544,  2552,  2562,  2566,
    2577,  2596,  2604,  2612,  2640,  2646,  2652,  2656,  2667,  2671,
    2681,  2685,  2692,  2733,  2747,  2756,  2765,  2797,  2831,  2856,
    2883,  2912,  2916,  2922,  2937,  2952,  2970,  2988,  2992,  3001,
    3024,  3028,  3035,  3043,  3051,  3059,  3069,  3073,  3084,  3103,
    3111,  3119,  3147,  3153,  3169,  3202,  3235,  3244,  3255,  3261,
    3282,  3309,  3316,  3323,  3330,  3336,  3340,  3352,  3356,  3364,
    3372,  3380,  3388,  3396,  3403,  3414,  3422,  3428,  3443,  3448,
    3453,  3458,  3467,  3471,  3481,  3485,  3494,  3503,  3512,  3521,
    3533,  3537,  3541,  3547,  3553,  3557,  3563,  3569,  3573,  3578,
    3585,  3589,  3593,  3597,  3601,  3607,  3613,  3619,  3623,  3630,
    3634
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "T_INTEGER", "T_IDENTIFIER",
  "T_STRING", "T_ASP", "T_COMMENT", "T_CONSTANTS", "T_INCLUDE", "T_MACROS",
  "T_OBJECTS", "T_QUERY", "T_SHOW", "T_SORTS", "T_VARIABLES", "T_ABACTION",
  "T_ACTION", "T_MACROACTION", "T_ADDITIVEACTION", "T_ADDITIVEFLUENT",
  "T_AFTER", "T_ALWAYS", "T_ATTRIBUTE", "T_BY", "T_CAUSED", "T_CAUSES",
  "T_CONSTRAINT", "T_DECREMENTS", "T_DEFAULT", "T_EXOGENOUS",
  "T_EXOGENOUSACTION", "T_IF", "T_INCREMENTS", "T_INERTIAL",
  "T_INERTIALFLUENT", "T_LABEL", "T_MAY_CAUSE", "T_MAXADDITIVE",
  "T_MAXSTEP", "T_NEVER", "T_NOCONCURRENCY", "T_NONEXECUTABLE", "T_OF",
  "T_POSSIBLY_CAUSED", "T_RIGID", "T_SDFLUENT", "T_SIMPLEFLUENT",
  "T_UNLESS", "T_WHERE", "T_IS", "T_FALSE", "T_NONE", "T_TRUE", "T_ABS",
  "T_AT", "T_BRACKET_L", "T_BRACKET_R", "T_COLON_DASH", "T_PAREN_L",
  "T_PAREN_R", "T_PERIOD", "T_PIPE", "T_SEMICOLON", "T_DBL_COLON",
  "T_ARROW_LDASH", "T_ARROW_REQ", "T_ARROW_LEQ", "T_ARROW_RDASH",
  "T_COLON", "T_COMMA", "T_EQUIV", "T_IMPL", "T_DBL_PLUS", "T_DBL_AMP",
  "T_AMP", "T_GTHAN_EQ", "T_EQ_LTHAN", "T_GTHAN", "T_LTHAN", "T_NOT_EQ",
  "T_DBL_EQ", "T_EQ", "T_NOT", "T_DBL_PERIOD", "T_PLUS", "T_DASH",
  "T_DBL_GTHAN", "T_MOD", "T_INT_DIV", "T_STAR", "T_BIG_CONJ",
  "T_BIG_DISJ", "T_POUND", "T_UMINUS", "$accept", "program",
  "statement_sequence", "statement", "constant_statement",
  "constant_spec_outer_tuple", "constant_spec_tuple",
  "constant_outer_spec", "constant_spec", "constant_schema_outer_list",
  "constant_schema_list", "constant_outer_schema", "constant_schema",
  "constant_schema_nodecl", "constant_outer_binder", "constant_binder",
  "maxadditive_statement", "object_statement", "object_spec_outer_tuple",
  "object_spec_tuple", "object_outer_spec", "object_spec",
  "object_outer_schema_list", "object_schema_list", "object_outer_schema",
  "object_schema", "show_statement", "sort_statement",
  "sort_spec_outer_tuple", "sort_spec_tuple", "sort_spec",
  "sort_outer_identifier", "sort_identifier", "sort_identifier_name",
  "sort_constant_name", "variable_statement", "variable_spec_outer_tuple",
  "variable_spec_tuple", "variable_outer_spec", "variable_spec",
  "variable_outer_list", "variable_list", "variable_binding", "causal_law",
  "causal_law_shortcut_forms", "cl_always_forms", "cl_constraint_forms",
  "cl_default_forms", "cl_exogenous_forms", "cl_inertial_forms",
  "cl_nonexecutable_forms", "cl_rigid_forms", "cl_possibly_caused_forms",
  "cl_may_cause_forms", "cl_causes_forms", "cl_noconcurrency_forms",
  "cl_increment_forms", "causal_law_basic_forms", "cl_macroaction_forms",
  "cl_action_list", "cl_action", "cl_head_formula", "cl_body_formula",
  "cl_body_formula_inner", "cl_body_term", "cl_body_term_inner",
  "cl_where_expr", "literal_assign_conj", "literal_assign_conj_inner",
  "literal_assign_expr", "expr_big_expression", "expr_big_quantifiers",
  "expr_big_conj", "expr_big_disj", "query_statement",
  "query_expression_tuple", "query_expression", "query_body_formula",
  "query_body_formula_inner", "query_body_term", "query_body_term_inner",
  "expr_big_query_expression", "constant_expr", "parameter_list",
  "parameter_general", "sort_identifier_list", "extended_value_expression",
  "extended_math_expression", "extended_math_expr_inner",
  "extended_math_term", "num_range", "extended_integer",
  "extended_integer_outer_expression", "extended_integer_expression",
  "AND", "OR", "NOT", "EQUALS", "NOT_EQUALS", "COMPARISON", "LESS_THAN",
  "GREATER_THAN", "LESS_THAN_EQ", "GREATER_THAN_EQ", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    96,    97,    97,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    99,   100,   100,   101,   101,
     102,   102,   103,   104,   104,   105,   105,   106,   106,   107,
     107,   108,   108,   109,   109,   110,   110,   110,   110,   110,
     111,   112,   113,   113,   114,   114,   115,   115,   116,   117,
     117,   118,   118,   119,   119,   120,   120,   120,   120,   121,
     122,   123,   123,   124,   124,   125,   125,   126,   126,   127,
     127,   127,   128,   128,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   130,   131,   131,   132,   132,   133,
     133,   134,   135,   135,   136,   136,   137,   137,   138,   138,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   140,   140,   141,   141,   141,   141,   141,
     141,   141,   141,   142,   142,   142,   142,   142,   142,   142,
     142,   143,   143,   143,   143,   143,   143,   143,   143,   144,
     144,   144,   144,   145,   145,   145,   145,   146,   146,   147,
     147,   147,   147,   147,   147,   147,   147,   148,   148,   148,
     148,   149,   149,   149,   149,   150,   151,   151,   151,   151,
     151,   151,   151,   151,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     153,   154,   154,   155,   155,   155,   155,   156,   156,   156,
     157,   157,   158,   158,   158,   158,   158,   158,   159,   159,
     160,   160,   160,   160,   160,   161,   162,   162,   163,   163,
     164,   164,   164,   165,   166,   166,   166,   166,   167,   168,
     169,   170,   170,   171,   171,   171,   171,   172,   172,   172,
     173,   173,   173,   173,   173,   173,   174,   174,   175,   175,
     175,   175,   175,   176,   177,   177,   178,   178,   179,   180,
     180,   181,   181,   181,   181,   182,   182,   183,   183,   183,
     183,   183,   183,   183,   183,   184,   184,   185,   186,   186,
     186,   186,   187,   187,   188,   188,   188,   188,   188,   188,
     189,   189,   189,   190,   191,   191,   192,   193,   193,   193,
     194,   194,   194,   194,   194,   195,   196,   197,   197,   198,
     198
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     4,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       4,     1,     4,     1,     3,     1,     4,     3,     6,     1,
       5,     4,     1,     3,     1,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     4,     1,     1,     4,
       4,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       2,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     2,     8,     6,     6,     4,     6,
       4,     4,     2,     8,     6,     6,     4,     6,     4,     4,
       2,     8,     6,     6,     4,     6,     4,     4,     2,     6,
       4,     4,     2,     6,     4,     4,     2,     4,     2,     8,
       6,     6,     4,     6,     4,     4,     2,     7,     5,     5,
       3,     7,     5,     5,     3,     1,     9,     7,     7,     5,
       9,     7,     7,     5,    10,     8,     8,     6,     8,     6,
       6,     4,     8,     6,     6,     4,     6,     4,     4,     2,
       3,     3,     1,     1,     3,     3,     5,     1,     1,     1,
       1,     3,     1,     2,     3,     3,     3,     3,     1,     3,
       1,     3,     3,     3,     1,     1,     1,     3,     1,     3,
       1,     2,     3,     5,     1,     1,     2,     2,     2,     2,
       4,     1,     3,     3,     3,     5,     1,     1,     3,     3,
       1,     2,     3,     3,     3,     3,     1,     3,     1,     3,
       3,     3,     1,     5,     1,     4,     1,     3,     1,     1,
       3,     1,     1,     1,     1,     1,     3,     1,     3,     3,
       3,     3,     3,     2,     4,     1,     1,     3,     1,     1,
       1,     2,     1,     3,     1,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,   278,   254,     0,     0,     0,     0,     0,     0,
     279,   280,   165,     0,     0,     0,   262,   263,   261,     0,
       0,     0,     0,   295,   294,     0,     0,     4,     6,     7,
       8,    10,    11,    12,    13,     0,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,     0,   112,
       0,   200,   202,   208,   214,     9,   276,   210,   264,   265,
     267,   275,     0,    14,     0,   114,   276,   199,   198,     0,
     294,   189,   197,   216,   218,   220,     0,   122,   130,   138,
     142,   146,   156,   148,     0,     0,   273,     0,     0,     0,
     224,   225,     0,     0,     0,     0,     0,     0,     0,     0,
     200,   208,   265,   281,     1,     5,    98,    99,     0,     0,
       0,     0,   292,     0,     0,   293,   291,   290,     0,     0,
       0,     0,   309,   307,   306,   305,   297,   300,   296,     0,
       0,     0,   301,   302,   303,   304,     0,     0,     0,     0,
       0,   203,     0,     0,   256,   258,     0,     0,   216,     0,
       0,     0,     0,     0,     0,   221,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   228,   229,     0,   226,   227,    29,
       0,     0,    16,    18,    20,     0,    23,    25,    27,    55,
       0,     0,    42,    44,    46,     0,    49,    51,    53,    58,
     284,    57,   282,     0,   280,     0,     0,     0,   231,   236,
     237,   240,   246,   252,   248,   265,     0,     0,    72,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,     0,
       0,    61,    63,    65,    69,    73,    94,     0,     0,    85,
      87,    89,     0,    92,     0,   201,   209,   266,   164,     0,
       0,   160,   206,   207,   204,   205,     0,   190,   192,   193,
     310,   308,   299,   298,   211,   212,   213,   268,   269,   272,
     271,   270,     0,   255,     0,   215,   113,   217,   185,   181,
     187,   188,   219,   222,   118,   121,   120,   128,   126,   129,
     134,   136,   137,   140,   141,   144,   145,   154,   152,   155,
     147,   274,     0,     0,     0,    16,    20,    23,    27,    15,
       0,     0,     0,     0,     0,    42,    46,    49,    53,   282,
      41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   246,   265,   230,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   241,    59,     0,    61,
      60,     0,     0,     0,    70,     0,     0,    89,    92,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   257,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   223,   259,     0,    17,    21,
      24,    28,     0,    19,     0,     0,    22,    33,    35,    73,
      39,     0,     0,    26,     0,    43,    47,    50,    54,   283,
      45,     0,    48,    67,     0,    52,   277,   285,   286,   289,
     288,   287,   233,   234,     0,   238,   247,   232,   244,   245,
     242,   243,   249,   250,   251,   239,    62,    64,    66,    71,
       0,     0,    86,    90,    93,    88,     0,    96,    91,    97,
      95,     0,    40,   162,   163,   173,   169,   158,   159,     0,
     194,   191,   195,   183,   184,   177,   179,   180,   186,   117,
     116,   119,   127,   124,   125,   133,   132,   135,   139,   143,
     153,   150,   151,    30,     0,     0,     0,     0,     0,     0,
       0,     0,    56,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   260,     0,    31,    37,     0,    34,     0,
      68,   235,   253,   161,   171,   172,   167,   168,   157,   196,
     182,   175,   176,   178,   115,   123,   131,   149,     0,     0,
      36,     0,     0,     0,     0,     0,   170,   166,   174,    32,
      38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,   181,   182,   183,   184,   185,
     307,   187,   188,   526,   406,   407,    29,    30,   191,   192,
     193,   194,   195,   196,   197,   198,    31,    32,   230,   231,
     232,   422,   233,   234,   235,    33,   238,   239,   240,   241,
     242,   243,   458,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,   257,
     258,    71,   275,    51,    52,    53,   276,    72,    73,    74,
      54,    89,    90,    91,    55,   207,   208,   209,   210,   211,
     212,   213,    66,   143,   144,   397,    57,    58,    59,    60,
     199,    61,   201,   202,   118,   119,    62,   129,   130,   131,
     132,   133,   134,   135
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -312
static const yytype_int16 yypact[] =
{
     502,    13,  -312,    18,   730,   462,   730,   462,    43,    43,
    -312,  -312,  -312,   730,   462,    43,  -312,  -312,  -312,   771,
      68,   289,   730,  -312,   167,    78,   589,  -312,  -312,  -312,
    -312,  -312,  -312,  -312,  -312,    28,  -312,  -312,  -312,  -312,
    -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,    79,  -312,
     871,  -312,  -312,  -312,  -312,  -312,    54,   418,   399,  -312,
    -312,  -312,   730,  -312,   790,   913,  -312,  -312,  -312,   135,
    -312,   227,   156,  -312,  -312,    74,    43,   531,    23,   208,
       3,   728,   230,   123,   790,   109,   399,   179,   192,   -30,
    -312,  -312,    29,    60,   424,   214,   842,    33,   175,   627,
     195,   203,   204,  -312,  -312,  -312,  -312,  -312,   462,   462,
     462,   462,  -312,   730,   730,  -312,  -312,  -312,   730,   730,
      36,   205,  -312,  -312,  -312,  -312,  -312,  -312,  -312,   291,
     291,   291,  -312,  -312,  -312,  -312,   790,   790,   790,   790,
     790,  -312,   790,    45,  -312,   399,   730,   156,   217,   730,
     730,    43,   730,   135,   291,  -312,   730,    43,   730,   730,
     730,   730,   730,   730,   730,   730,   730,   730,   730,   730,
     730,   730,   730,   278,  -312,  -312,   730,  -312,  -312,   193,
      29,    55,  -312,  -312,  -312,   -14,  -312,  -312,  -312,   239,
      60,   197,  -312,  -312,  -312,    88,  -312,  -312,  -312,  -312,
    -312,   536,  -312,   268,   275,    68,   768,   308,  -312,   886,
    -312,  -312,  -312,  -312,   418,   271,   768,   286,  -312,  -312,
    -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,   842,
     340,  -312,  -312,   265,   -36,  -312,  -312,    37,   292,  -312,
     293,  -312,   296,   295,    83,  -312,  -312,  -312,     4,   333,
     337,   122,   760,   247,   627,   627,    43,   307,  -312,   344,
    -312,  -312,  -312,  -312,  -312,  -312,  -312,   199,   199,  -312,
    -312,  -312,   399,  -312,   790,   627,  -312,  -312,   613,   766,
     331,  -312,   156,  -312,   843,   334,  -312,   919,   849,  -312,
     928,   857,  -312,   946,  -312,   955,  -312,   961,   863,  -312,
    -312,  -312,  1026,   935,   328,   332,   335,   336,   347,  -312,
      38,   635,    41,   935,   345,   349,   351,   353,   355,   356,
    -312,    60,   848,   287,    83,    83,    83,    83,    83,    83,
     420,   421,   119,  1058,   369,   147,  -312,   424,   768,   768,
     768,   768,   291,   291,   291,   768,  -312,  -312,   370,   374,
    -312,   842,   842,   385,  -312,    42,   389,   391,    47,  -312,
      33,   706,   448,    83,   509,   730,   730,   790,   790,   730,
     730,     6,    36,   730,  -312,    43,   730,   730,    43,   730,
     730,    43,   730,   730,   730,   730,   730,   730,   730,   730,
     730,   730,   730,   730,   730,  -312,  -312,   105,  -312,  -312,
    -312,  -312,    44,  -312,    25,   673,  -312,  -312,  -312,   394,
    -312,   536,   457,  -312,   143,  -312,  -312,  -312,  -312,  -312,
     345,   935,  -312,  -312,   320,  -312,   579,   218,   218,  -312,
    -312,  -312,  -312,   380,   768,  -312,  -312,   406,   934,   445,
     886,   886,  -312,  -312,  -312,   886,  -312,   370,  -312,  -312,
     470,   391,  -312,  -312,  -312,  -312,   711,  -312,  -312,  -312,
    -312,   579,  -312,   973,  -312,   299,   382,   988,  -312,   730,
    -312,  -312,   627,   430,  -312,   901,   432,  -312,  -312,   433,
    -312,  -312,  -312,  1000,  -312,  -312,  1006,  -312,  -312,  -312,
    -312,  1015,  -312,  -312,   935,    44,   335,   486,   935,   441,
     935,   347,  -312,   444,   355,   489,  1052,    47,   730,   730,
     730,   730,   730,   730,  1074,   730,    43,   730,   730,   730,
     730,   730,   730,  -312,   438,   450,  -312,   451,  -312,   452,
    -312,  -312,  -312,  -312,  1033,  -312,  1042,  -312,  -312,  -312,
    -312,   473,  -312,  -312,  -312,  -312,  -312,  -312,   935,   480,
    -312,   730,   730,   730,   149,   486,  -312,  -312,  -312,  -312,
    -312
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -312,  -312,  -312,   499,  -312,   350,   354,   223,  -179,    62,
     -64,   225,  -177,   -17,  -312,   134,  -312,  -312,  -166,   352,
    -312,   359,  -312,   360,   228,  -174,  -312,  -312,  -219,   330,
    -312,   201,  -220,  -312,  -277,  -312,   207,   326,  -312,  -210,
    -312,  -212,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,
    -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,  -312,
     200,    53,    17,   543,  -312,   559,    56,   -40,   513,  -312,
    -312,   378,   -85,   -78,  -312,   250,  -312,  -141,  -312,  -312,
     390,  -312,     0,  -312,   310,  -311,   -72,   -13,    -4,  -312,
    -291,   -12,   130,  -171,   -41,  -196,    80,   377,   386,   396,
    -312,  -312,  -312,  -312
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -4
static const yytype_int16 yytable[] =
{
      56,   306,   414,   308,   177,    75,    86,    75,    79,    80,
     348,   178,   103,   341,    75,    83,   318,    50,   102,   319,
     410,    65,   214,    77,   314,   358,    56,   357,   186,   147,
      81,   153,   176,   179,   409,   165,   365,   236,   469,    99,
       3,   236,   179,    50,   159,   179,   236,     3,   179,   353,
     311,   145,   166,   366,   354,   160,   312,   264,   265,   266,
      78,    87,    88,     2,   189,   333,   470,    82,   497,    75,
     459,   173,   161,   103,    63,   346,   155,    64,   104,   141,
     102,   200,   283,   396,   498,    76,     2,    76,   180,   106,
     215,   408,   237,   396,    76,   256,   355,   402,    10,    11,
     412,   450,   423,   495,   120,   273,   153,   454,    75,    75,
      75,    75,     2,   282,   410,   274,   309,   362,   310,   190,
     259,    10,    11,   267,   268,   269,   270,   271,   409,   272,
     252,   253,   447,   448,   214,   254,   255,   341,   102,     3,
     107,   423,   363,   358,   214,   451,    85,    10,    11,    76,
     341,   280,   322,    75,   369,   420,   154,   285,   323,    87,
      88,   248,   249,   250,   251,   493,   278,   279,   340,    85,
       2,   370,   172,   284,   216,   494,   287,   288,   200,   290,
     291,   434,   293,   174,   295,   408,   297,   298,    76,    76,
      76,    76,   319,   302,    69,    85,   175,   438,   439,   440,
     441,   503,   335,   502,   445,    10,    11,   247,   281,   559,
      87,    88,   215,   494,   286,   217,   345,   289,    23,   494,
     292,    70,   294,   496,   296,   308,   112,   299,   300,   162,
     116,   117,   200,    76,   319,   501,   503,   554,   507,   244,
     163,   153,   341,   341,   341,   341,   186,   177,   149,   341,
     504,   169,   303,   319,   178,   245,   371,   164,   320,   150,
     321,   145,   170,   246,   247,   214,   214,   214,   214,   214,
     442,   443,   444,   214,   523,   151,   152,   277,   527,   171,
     529,   260,   261,   262,   263,   319,   216,   138,   139,   140,
       2,   189,   340,   506,     2,     3,   216,    92,   313,   200,
      93,    94,    95,    96,    97,   340,   327,   328,   329,   200,
     341,   200,   200,   200,   200,   200,   200,   200,   308,   114,
     115,   116,   117,     2,   189,    10,    11,    98,   396,    10,
      11,   509,   330,   215,   215,   215,   215,   215,   301,   331,
     345,   215,    16,    17,    18,    19,   424,   347,   510,   200,
     142,   200,   352,   359,   465,   466,   360,   367,    10,    11,
     361,   368,   214,   136,   137,   362,   138,   139,   140,   336,
     372,   337,   259,    85,   364,   473,   373,    85,   476,   363,
     380,   479,   463,   383,   136,   137,   467,   138,   139,   140,
     472,   310,   398,   200,   475,   399,   400,   340,   340,   340,
     340,   350,   483,   351,   340,   486,    85,   401,   321,   415,
     491,   416,   200,   417,   511,   418,   419,   216,   216,   216,
     216,   216,   464,   432,   433,   216,   468,     2,     3,   436,
     215,   512,   474,   351,   446,   477,   478,   449,   480,   481,
     482,   411,   484,   485,   200,   487,   488,   489,   490,   452,
     492,   453,   460,   500,   426,   427,   428,   429,   430,   431,
     203,   179,    10,   204,   505,   340,     3,   136,   137,   337,
     138,   139,   140,   121,   236,    16,    17,    18,    19,   515,
     205,   518,   519,   206,   136,   137,   514,   138,   139,   140,
     525,   411,   531,   461,   122,   123,   124,   125,   126,   127,
     128,   528,    -2,     1,   530,     2,     3,    23,   312,   548,
      24,   549,   550,    67,   216,    68,   541,   339,   115,   116,
     117,    69,   553,   555,     4,   105,   534,     5,   536,     6,
     304,     7,     8,   403,   305,   411,     9,   413,   560,   499,
      10,    11,   315,    12,    13,    23,    14,    15,    70,   316,
     317,   425,   156,    16,    17,    18,    19,   524,    20,   349,
      21,    22,   457,   356,   533,   100,   535,   455,   537,   538,
     462,   540,   471,   542,   543,   544,   545,   546,   547,   157,
     158,   101,   148,   332,   374,    23,   461,   437,    24,    -3,
       1,   342,     2,     3,   325,   326,   334,   327,   328,   329,
     343,   112,   113,   114,   115,   116,   117,   556,   557,   558,
     344,     4,     0,     0,     5,     0,     6,     0,     7,     8,
     324,   325,   326,     9,   327,   328,   329,    10,    11,     0,
      12,    13,     0,    14,    15,     0,     0,     0,     2,   218,
      16,    17,    18,    19,     0,    20,     0,    21,    22,     0,
       0,   219,   220,   221,   222,   223,     0,     0,   404,     0,
       0,   375,   376,     0,   325,   326,   224,   327,   328,   329,
     225,     0,    23,    10,    11,    24,     2,   218,     0,     0,
     226,   227,   228,   112,   113,   114,   115,   116,   117,   219,
     220,   221,   222,   223,   405,     0,   404,   112,   113,   114,
     115,   116,   117,     0,   224,     0,     0,     0,   225,     2,
     218,    10,    11,     0,     2,   218,     0,     0,   226,   227,
     228,    85,   219,   220,   221,   222,   223,   219,   220,   221,
     222,   223,   363,     2,     3,     0,     0,   224,     0,     0,
       0,   225,   224,     0,    10,    11,   225,     0,     0,    10,
      11,   226,   227,   228,     0,     0,   226,   227,   228,    85,
     167,     0,     0,     0,     0,   456,     0,     0,    10,    11,
     363,     2,     3,     0,     2,     3,     0,   168,     0,     0,
       0,    16,    17,    18,    19,     0,    20,   377,     0,    22,
       0,     0,    85,     2,     3,     0,     0,    85,   112,   113,
     114,   115,   116,   117,     0,     0,    10,    11,     0,    10,
      11,     0,     0,    23,   378,   379,    24,     0,     0,    16,
      17,    18,    19,     0,   205,    19,     0,   206,    10,    11,
      84,   113,   114,   115,   116,   117,   112,   113,   114,   115,
     116,   117,     0,     0,    19,     0,   218,     0,     0,   142,
       0,    23,   218,     0,    24,     0,     0,    85,   219,   220,
     221,   222,   223,     0,   219,   220,   221,   222,   223,     0,
     385,     0,     0,   224,     0,     0,    85,   225,   388,   224,
       0,     0,     0,   225,   393,     0,     0,   226,   227,   228,
       0,   381,   382,   226,   227,   228,     0,   108,   386,   109,
       0,   229,     0,     0,   110,     0,   389,   421,   111,     0,
       0,     0,   394,   112,   113,   114,   115,   116,   117,   112,
     113,   114,   115,   116,   117,     0,     0,   112,   113,   114,
     115,   116,   117,   112,   113,   114,   115,   116,   117,   218,
       0,   112,   113,   114,   115,   116,   117,     0,     0,   516,
     517,   219,   220,   221,   222,   223,   112,   338,   339,   115,
     116,   117,   146,     0,     0,     0,   224,     0,   384,     0,
     225,   112,   113,   114,   115,   116,   117,   387,     0,     0,
     226,   227,   228,   112,   113,   114,   115,   116,   117,   112,
     113,   114,   115,   116,   117,   390,     0,     0,   112,   113,
     114,   115,   116,   117,   391,   338,   339,   115,   116,   117,
     392,     0,     0,     0,     0,     0,   112,   113,   114,   115,
     116,   117,   508,     0,     0,   112,   113,   114,   115,   116,
     117,   112,   113,   114,   115,   116,   117,   513,     0,     0,
       0,     0,     0,   112,   113,   114,   115,   116,   117,   520,
       0,     0,     0,     0,     0,   521,     0,     0,   112,   113,
     114,   115,   116,   117,   522,     0,     0,     0,     0,     0,
     112,   113,   114,   115,   116,   117,   112,   113,   114,   115,
     116,   117,   551,   395,     0,   112,   113,   114,   115,   116,
     117,   552,     0,     0,     0,     0,   112,   113,   114,   115,
     116,   117,     0,   112,   113,   114,   115,   116,   117,   532,
       0,     0,   112,   113,   114,   115,   116,   117,   435,     0,
       0,     0,   112,   338,   339,   115,   116,   117,   112,   338,
     339,   115,   116,   117,   539,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   113,   114,   115,   116,   117
};

static const yytype_int16 yycheck[] =
{
       0,   180,   313,   180,    89,     5,    19,     7,     8,     9,
     229,    89,    24,   209,    14,    15,   190,     0,    22,   190,
     311,     4,    94,     6,   190,   237,    26,   237,    92,    69,
      13,    72,    62,     4,   311,    32,    32,     4,    32,    22,
       4,     4,     4,    26,    21,     4,     4,     4,     4,    85,
      64,    64,    49,    49,    90,    32,    70,   129,   130,   131,
       7,    91,    92,     3,     4,   206,    60,    14,    43,    69,
     361,    84,    49,    85,    61,   216,    76,    59,     0,    62,
      84,    93,   154,   303,    59,     5,     3,     7,    59,    61,
      94,   311,    59,   313,    14,    59,    59,    59,    38,    39,
      59,    59,   322,    59,    50,    60,   147,    60,   108,   109,
     110,   111,     3,   153,   405,    70,    61,    70,    63,    59,
     120,    38,    39,   136,   137,   138,   139,   140,   405,   142,
     113,   114,   351,   352,   206,   118,   119,   333,   142,     4,
      61,   361,    59,   355,   216,   355,    86,    38,    39,    69,
     346,   151,    64,   153,    32,   321,    82,   157,    70,    91,
      92,   108,   109,   110,   111,    60,   149,   150,   209,    86,
       3,    49,    49,   156,    94,    70,   159,   160,   190,   162,
     163,    62,   165,     4,   167,   405,   169,   170,   108,   109,
     110,   111,   363,   176,    59,    86,     4,   338,   339,   340,
     341,   421,   206,    60,   345,    38,    39,    60,   152,    60,
      91,    92,   216,    70,   158,     1,    69,   161,    83,    70,
     164,    86,   166,   402,   168,   402,    70,   171,   172,    21,
      74,    75,   244,   153,   405,   412,   456,   548,   450,    64,
      32,   282,   438,   439,   440,   441,   310,   332,    21,   445,
     424,    21,    59,   424,   332,    60,   256,    49,    61,    32,
      63,   274,    32,    60,    60,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   494,    48,    49,    60,   498,    49,
     500,    76,    77,    78,    79,   456,   206,    88,    89,    90,
       3,     4,   333,   434,     3,     4,   216,     8,    59,   311,
      11,    12,    13,    14,    15,   346,    88,    89,    90,   321,
     506,   323,   324,   325,   326,   327,   328,   329,   495,    72,
      73,    74,    75,     3,     4,    38,    39,    38,   548,    38,
      39,    32,    64,   337,   338,   339,   340,   341,    60,    64,
      69,   345,    51,    52,    53,    54,    59,    61,    49,   361,
      59,   363,    87,    61,   367,   368,    63,    24,    38,    39,
      64,    24,   434,    85,    86,    70,    88,    89,    90,    61,
      63,    63,   372,    86,   244,   375,    32,    86,   378,    59,
      49,   381,   365,    49,    85,    86,   369,    88,    89,    90,
     373,    63,    60,   405,   377,    60,    60,   438,   439,   440,
     441,    61,   385,    63,   445,   388,    86,    60,    63,    60,
     393,    60,   424,    60,    32,    60,    60,   337,   338,   339,
     340,   341,   366,     3,     3,   345,   370,     3,     4,    60,
     434,    49,   376,    63,    60,   379,   380,    52,   382,   383,
     384,   311,   386,   387,   456,   389,   390,   391,   392,    60,
     394,    60,     4,    59,   324,   325,   326,   327,   328,   329,
      36,     4,    38,    39,    84,   506,     4,    85,    86,    63,
      88,    89,    90,    55,     4,    51,    52,    53,    54,    49,
      56,    49,    49,    59,    85,    86,   469,    88,    89,    90,
       4,   361,     3,   363,    76,    77,    78,    79,    80,    81,
      82,    60,     0,     1,    60,     3,     4,    83,    70,    59,
      86,    60,    60,    51,   434,    53,   516,    72,    73,    74,
      75,    59,    49,    43,    22,    26,   509,    25,   511,    27,
     180,    29,    30,   310,   180,   405,    34,   312,   555,   405,
      38,    39,   190,    41,    42,    83,    44,    45,    86,   190,
     190,   323,    21,    51,    52,    53,    54,   495,    56,   229,
      58,    59,   361,   237,   508,    22,   510,   360,   512,   513,
      61,   515,   372,   517,   518,   519,   520,   521,   522,    48,
      49,    22,    69,   205,   274,    83,   456,   337,    86,     0,
       1,   214,     3,     4,    85,    86,   206,    88,    89,    90,
     214,    70,    71,    72,    73,    74,    75,   551,   552,   553,
     214,    22,    -1,    -1,    25,    -1,    27,    -1,    29,    30,
      84,    85,    86,    34,    88,    89,    90,    38,    39,    -1,
      41,    42,    -1,    44,    45,    -1,    -1,    -1,     3,     4,
      51,    52,    53,    54,    -1,    56,    -1,    58,    59,    -1,
      -1,    16,    17,    18,    19,    20,    -1,    -1,    23,    -1,
      -1,    48,    49,    -1,    85,    86,    31,    88,    89,    90,
      35,    -1,    83,    38,    39,    86,     3,     4,    -1,    -1,
      45,    46,    47,    70,    71,    72,    73,    74,    75,    16,
      17,    18,    19,    20,    59,    -1,    23,    70,    71,    72,
      73,    74,    75,    -1,    31,    -1,    -1,    -1,    35,     3,
       4,    38,    39,    -1,     3,     4,    -1,    -1,    45,    46,
      47,    86,    16,    17,    18,    19,    20,    16,    17,    18,
      19,    20,    59,     3,     4,    -1,    -1,    31,    -1,    -1,
      -1,    35,    31,    -1,    38,    39,    35,    -1,    -1,    38,
      39,    45,    46,    47,    -1,    -1,    45,    46,    47,    86,
      32,    -1,    -1,    -1,    -1,    59,    -1,    -1,    38,    39,
      59,     3,     4,    -1,     3,     4,    -1,    49,    -1,    -1,
      -1,    51,    52,    53,    54,    -1,    56,    21,    -1,    59,
      -1,    -1,    86,     3,     4,    -1,    -1,    86,    70,    71,
      72,    73,    74,    75,    -1,    -1,    38,    39,    -1,    38,
      39,    -1,    -1,    83,    48,    49,    86,    -1,    -1,    51,
      52,    53,    54,    -1,    56,    54,    -1,    59,    38,    39,
      59,    71,    72,    73,    74,    75,    70,    71,    72,    73,
      74,    75,    -1,    -1,    54,    -1,     4,    -1,    -1,    59,
      -1,    83,     4,    -1,    86,    -1,    -1,    86,    16,    17,
      18,    19,    20,    -1,    16,    17,    18,    19,    20,    -1,
      21,    -1,    -1,    31,    -1,    -1,    86,    35,    21,    31,
      -1,    -1,    -1,    35,    21,    -1,    -1,    45,    46,    47,
      -1,    48,    49,    45,    46,    47,    -1,    26,    49,    28,
      -1,    59,    -1,    -1,    33,    -1,    49,    59,    37,    -1,
      -1,    -1,    49,    70,    71,    72,    73,    74,    75,    70,
      71,    72,    73,    74,    75,    -1,    -1,    70,    71,    72,
      73,    74,    75,    70,    71,    72,    73,    74,    75,     4,
      -1,    70,    71,    72,    73,    74,    75,    -1,    -1,    48,
      49,    16,    17,    18,    19,    20,    70,    71,    72,    73,
      74,    75,    49,    -1,    -1,    -1,    31,    -1,    49,    -1,
      35,    70,    71,    72,    73,    74,    75,    49,    -1,    -1,
      45,    46,    47,    70,    71,    72,    73,    74,    75,    70,
      71,    72,    73,    74,    75,    49,    -1,    -1,    70,    71,
      72,    73,    74,    75,    49,    71,    72,    73,    74,    75,
      49,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    75,    49,    -1,    -1,    70,    71,    72,    73,    74,
      75,    70,    71,    72,    73,    74,    75,    49,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    49,
      -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    70,    71,
      72,    73,    74,    75,    49,    -1,    -1,    -1,    -1,    -1,
      70,    71,    72,    73,    74,    75,    70,    71,    72,    73,
      74,    75,    49,    57,    -1,    70,    71,    72,    73,    74,
      75,    49,    -1,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    75,    -1,    70,    71,    72,    73,    74,    75,    57,
      -1,    -1,    70,    71,    72,    73,    74,    75,    60,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    70,    71,
      72,    73,    74,    75,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,    22,    25,    27,    29,    30,    34,
      38,    39,    41,    42,    44,    45,    51,    52,    53,    54,
      56,    58,    59,    83,    86,    96,    97,    98,    99,   111,
     112,   121,   122,   130,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     157,   158,   159,   160,   165,   169,   177,   181,   182,   183,
     184,   186,   191,    61,    59,   157,   177,    51,    53,    59,
      86,   156,   162,   163,   164,   177,   191,   157,   156,   177,
     177,   157,   156,   177,    59,    86,   182,    91,    92,   166,
     167,   168,     8,    11,    12,    13,    14,    15,    38,   157,
     158,   160,   183,   186,     0,    98,    61,    61,    26,    28,
      33,    37,    70,    71,    72,    73,    74,    75,   189,   190,
      50,    55,    76,    77,    78,    79,    80,    81,    82,   192,
     193,   194,   195,   196,   197,   198,    85,    86,    88,    89,
      90,   157,    59,   178,   179,   182,    49,   162,   163,    21,
      32,    48,    49,   189,    82,   177,    21,    48,    49,    21,
      32,    49,    21,    32,    49,    32,    49,    32,    49,    21,
      32,    49,    49,   182,     4,     4,    62,   167,   168,     4,
      59,   100,   101,   102,   103,   104,   105,   106,   107,     4,
      59,   113,   114,   115,   116,   117,   118,   119,   120,   185,
     186,   187,   188,    36,    39,    56,    59,   170,   171,   172,
     173,   174,   175,   176,   181,   183,   191,     1,     4,    16,
      17,    18,    19,    20,    31,    35,    45,    46,    47,    59,
     123,   124,   125,   127,   128,   129,     4,    59,   131,   132,
     133,   134,   135,   136,    64,    60,    60,    60,   156,   156,
     156,   156,   157,   157,   157,   157,    59,   154,   155,   177,
      76,    77,    78,    79,   181,   181,   181,   182,   182,   182,
     182,   182,   182,    60,    70,   157,   161,    60,   157,   157,
     177,   161,   162,   181,   157,   177,   161,   157,   157,   161,
     157,   157,   161,   157,   161,   157,   161,   157,   157,   161,
     161,    60,   157,    59,   100,   101,   103,   105,   107,    61,
      63,    64,    70,    59,   113,   114,   116,   118,   120,   188,
      61,    63,    64,    70,    84,    85,    86,    88,    89,    90,
      64,    64,   166,   172,   175,   183,    61,    63,    71,    72,
     189,   190,   192,   193,   194,    69,   172,    61,   123,   124,
      61,    63,    87,    85,    90,    59,   132,   134,   136,    61,
      63,    64,    70,    59,   187,    32,    49,    24,    24,    32,
      49,   177,    63,    32,   179,    48,    49,    21,    48,    49,
      49,    48,    49,    49,    49,    21,    49,    49,    21,    49,
      49,    49,    49,    21,    49,    57,   127,   180,    60,    60,
      60,    60,    59,   102,    23,    59,   109,   110,   127,   129,
     185,   187,    59,   106,   180,    60,    60,    60,    60,    60,
     113,    59,   126,   127,    59,   119,   187,   187,   187,   187,
     187,   187,     3,     3,    62,    60,    60,   170,   172,   172,
     172,   172,   181,   181,   181,   172,    60,   123,   123,    52,
      59,   134,    60,    60,    60,   131,    59,   126,   137,   185,
       4,   187,    61,   157,   161,   182,   182,   157,   161,    32,
      60,   155,   157,   177,   161,   157,   177,   161,   161,   177,
     161,   161,   161,   157,   161,   161,   157,   161,   161,   161,
     161,   157,   161,    60,    70,    59,   103,    43,    59,   110,
      59,   107,    60,   127,   120,    84,   172,   136,    49,    32,
      49,    32,    49,    49,   157,    49,    48,    49,    49,    49,
      49,    49,    49,   127,   104,     4,   108,   127,    60,   127,
      60,     3,    57,   161,   157,   161,   157,   161,   161,    60,
     161,   177,   161,   161,   161,   161,   161,   161,    59,    60,
      60,    49,    49,    49,   180,    43,   161,   161,   161,    60,
     108
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 4: /* "T_IDENTIFIER" */

/* Line 1000 of yacc.c  */
#line 501 "parser.y"
	{ delete (yyvaluep->str); };

/* Line 1000 of yacc.c  */
#line 2214 "parser.cpp"
	break;
      case 5: /* "T_STRING" */

/* Line 1000 of yacc.c  */
#line 501 "parser.y"
	{ delete (yyvaluep->str); };

/* Line 1000 of yacc.c  */
#line 2223 "parser.cpp"
	break;
      case 104: /* "constant_schema_outer_list" */

/* Line 1000 of yacc.c  */
#line 509 "parser.y"
	{ if((yyvaluep->l_constant) != NULL) { deallocateList((yyvaluep->l_constant)); } };

/* Line 1000 of yacc.c  */
#line 2232 "parser.cpp"
	break;
      case 105: /* "constant_schema_list" */

/* Line 1000 of yacc.c  */
#line 509 "parser.y"
	{ if((yyvaluep->l_constant) != NULL) { deallocateList((yyvaluep->l_constant)); } };

/* Line 1000 of yacc.c  */
#line 2241 "parser.cpp"
	break;
      case 106: /* "constant_outer_schema" */

/* Line 1000 of yacc.c  */
#line 503 "parser.y"
	{ delete (yyvaluep->constant); };

/* Line 1000 of yacc.c  */
#line 2250 "parser.cpp"
	break;
      case 107: /* "constant_schema" */

/* Line 1000 of yacc.c  */
#line 503 "parser.y"
	{ delete (yyvaluep->constant); };

/* Line 1000 of yacc.c  */
#line 2259 "parser.cpp"
	break;
      case 108: /* "constant_schema_nodecl" */

/* Line 1000 of yacc.c  */
#line 503 "parser.y"
	{ delete (yyvaluep->constant); };

/* Line 1000 of yacc.c  */
#line 2268 "parser.cpp"
	break;
      case 109: /* "constant_outer_binder" */

/* Line 1000 of yacc.c  */
#line 513 "parser.y"
	{ if((yyvaluep->constant_binder_t) != NULL) { deallocateItem((yyvaluep->constant_binder_t)); } };

/* Line 1000 of yacc.c  */
#line 2277 "parser.cpp"
	break;
      case 110: /* "constant_binder" */

/* Line 1000 of yacc.c  */
#line 513 "parser.y"
	{ if((yyvaluep->constant_binder_t) != NULL) { deallocateItem((yyvaluep->constant_binder_t)); } };

/* Line 1000 of yacc.c  */
#line 2286 "parser.cpp"
	break;
      case 117: /* "object_outer_schema_list" */

/* Line 1000 of yacc.c  */
#line 510 "parser.y"
	{ if((yyvaluep->l_object) != NULL) { deallocateList((yyvaluep->l_object)); } };

/* Line 1000 of yacc.c  */
#line 2295 "parser.cpp"
	break;
      case 118: /* "object_schema_list" */

/* Line 1000 of yacc.c  */
#line 510 "parser.y"
	{ if((yyvaluep->l_object) != NULL) { deallocateList((yyvaluep->l_object)); } };

/* Line 1000 of yacc.c  */
#line 2304 "parser.cpp"
	break;
      case 119: /* "object_outer_schema" */

/* Line 1000 of yacc.c  */
#line 505 "parser.y"
	{ delete (yyvaluep->object); };

/* Line 1000 of yacc.c  */
#line 2313 "parser.cpp"
	break;
      case 120: /* "object_schema" */

/* Line 1000 of yacc.c  */
#line 505 "parser.y"
	{ delete (yyvaluep->object); };

/* Line 1000 of yacc.c  */
#line 2322 "parser.cpp"
	break;
      case 123: /* "sort_spec_outer_tuple" */

/* Line 1000 of yacc.c  */
#line 511 "parser.y"
	{ if((yyvaluep->l_sort) != NULL) { deallocateList((yyvaluep->l_sort)); } };

/* Line 1000 of yacc.c  */
#line 2331 "parser.cpp"
	break;
      case 124: /* "sort_spec_tuple" */

/* Line 1000 of yacc.c  */
#line 511 "parser.y"
	{ if((yyvaluep->l_sort) != NULL) { deallocateList((yyvaluep->l_sort)); } };

/* Line 1000 of yacc.c  */
#line 2340 "parser.cpp"
	break;
      case 125: /* "sort_spec" */

/* Line 1000 of yacc.c  */
#line 507 "parser.y"
	{ delete (yyvaluep->sort); };

/* Line 1000 of yacc.c  */
#line 2349 "parser.cpp"
	break;
      case 126: /* "sort_outer_identifier" */

/* Line 1000 of yacc.c  */
#line 501 "parser.y"
	{ delete (yyvaluep->str); };

/* Line 1000 of yacc.c  */
#line 2358 "parser.cpp"
	break;
      case 127: /* "sort_identifier" */

/* Line 1000 of yacc.c  */
#line 501 "parser.y"
	{ delete (yyvaluep->str); };

/* Line 1000 of yacc.c  */
#line 2367 "parser.cpp"
	break;
      case 128: /* "sort_identifier_name" */

/* Line 1000 of yacc.c  */
#line 501 "parser.y"
	{ delete (yyvaluep->str); };

/* Line 1000 of yacc.c  */
#line 2376 "parser.cpp"
	break;
      case 129: /* "sort_constant_name" */

/* Line 1000 of yacc.c  */
#line 501 "parser.y"
	{ delete (yyvaluep->str); };

/* Line 1000 of yacc.c  */
#line 2385 "parser.cpp"
	break;
      case 135: /* "variable_outer_list" */

/* Line 1000 of yacc.c  */
#line 512 "parser.y"
	{ if((yyvaluep->l_variable) != NULL) { deallocateList((yyvaluep->l_variable)); } };

/* Line 1000 of yacc.c  */
#line 2394 "parser.cpp"
	break;
      case 136: /* "variable_list" */

/* Line 1000 of yacc.c  */
#line 512 "parser.y"
	{ if((yyvaluep->l_variable) != NULL) { deallocateList((yyvaluep->l_variable)); } };

/* Line 1000 of yacc.c  */
#line 2403 "parser.cpp"
	break;
      case 137: /* "variable_binding" */

/* Line 1000 of yacc.c  */
#line 507 "parser.y"
	{ delete (yyvaluep->sort); };

/* Line 1000 of yacc.c  */
#line 2412 "parser.cpp"
	break;
      case 180: /* "sort_identifier_list" */

/* Line 1000 of yacc.c  */
#line 511 "parser.y"
	{ if((yyvaluep->l_sort) != NULL) { deallocateList((yyvaluep->l_sort)); } };

/* Line 1000 of yacc.c  */
#line 2421 "parser.cpp"
	break;
      case 185: /* "num_range" */

/* Line 1000 of yacc.c  */
#line 504 "parser.y"
	{ delete (yyvaluep->numRange); };

/* Line 1000 of yacc.c  */
#line 2430 "parser.cpp"
	break;
      case 186: /* "extended_integer" */

/* Line 1000 of yacc.c  */
#line 501 "parser.y"
	{ delete (yyvaluep->str); };

/* Line 1000 of yacc.c  */
#line 2439 "parser.cpp"
	break;
      case 187: /* "extended_integer_outer_expression" */

/* Line 1000 of yacc.c  */
#line 501 "parser.y"
	{ delete (yyvaluep->str); };

/* Line 1000 of yacc.c  */
#line 2448 "parser.cpp"
	break;
      case 188: /* "extended_integer_expression" */

/* Line 1000 of yacc.c  */
#line 501 "parser.y"
	{ delete (yyvaluep->str); };

/* Line 1000 of yacc.c  */
#line 2457 "parser.cpp"
	break;

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 517 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 518 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 521 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 522 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 525 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 526 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 527 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 528 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 529 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 530 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 531 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 532 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 534 "parser.y"
    {
    (yyval.not_used) = PARSERULE_NOT_USED;
    /* On an error, go to the end of the bad statement and try to continue.
       Set the error handler to not wait to report syntax errors if more show up. */
    yyerrok;
;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 547 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 550 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 551 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 554 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 555 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 558 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 559 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 563 "parser.y"
    {
    // Fill in each Constant's type and domain and translate each of them.
    bool constantError = false; // Set to true if any of the constants have trouble getting added to the symbol table.
    Sort* tempSort = NULL;
    if((yyvsp[(1) - (3)].l_constant) != NULL && (yyvsp[(3) - (3)].constant_binder_t) != NULL)
    {
        tempSort = (yyvsp[(3) - (3)].constant_binder_t)->domain;
        if(tempSort != NULL)
        {
            std::list<Constant*>::iterator lIter;
            // If the binding type is "attribute", turn the Constant objects into Attribute objects before adding them.
            if((yyvsp[(3) - (3)].constant_binder_t)->constType == Constant::CONST_ATTRIBUTE)
            {
                Attribute* tempAttribute = NULL;
                for(lIter = (yyvsp[(1) - (3)].l_constant)->begin(); lIter != (yyvsp[(1) - (3)].l_constant)->end(); ++lIter)
                {
                    tempAttribute = new Attribute((*lIter)->name, (*lIter)->transName);
                    tempAttribute->domain = (*lIter)->domain; // Should be NULL = NULL, but just in case.
                    for(std::vector<Sort*>::iterator vIter = (*lIter)->params.begin(); vIter != (*lIter)->params.end(); ++vIter)
                    {
                        if((*vIter) != NULL)
                        {
                            tempAttribute->params.push_back(*vIter);
                        }
                    }
                    deallocateItem(*lIter);
                    (*lIter) = tempAttribute;
                }
            }

            for(lIter = (yyvsp[(1) - (3)].l_constant)->begin(); lIter != (yyvsp[(1) - (3)].l_constant)->end(); ++lIter)
            {   // Try to add each constant to the symbol table before hooking it up and translating it.
                int addSymResult = mainTrans.addConstant(*lIter);
                if(addSymResult != SymbolTable::ADDSYM_OK)
                {   // Something went wrong adding this constant, skip connecting & translating it.
                    if(addSymResult == SymbolTable::ADDSYM_DUP)
                    {   // Duplicate constant declarations are errors, but give a separate error message for clarity.
                        ltsyystartParseError(ltsyylloc);
                        ltsyyossErr << "Duplicate constant declaration: \"" << (*lIter)->fullName() << "\".";
                        ltsyyreportError();
                        deallocateItem(*lIter);
                        constantError = true;
                    }
                    else
                    {   // Other constant adding errors can get grouped together.
                        ltsyystartParseError(ltsyylloc);
                        ltsyyossErr << "Bad constant declaration: \"" << (*lIter)->fullName() << "\".";
                        ltsyyreportError();
                        deallocateItem(*lIter);
                        constantError = true;
                    }
                }
                else
                {   // Successfully added constant, hook it up and translate it.
                    (*lIter)->constType = (yyvsp[(3) - (3)].constant_binder_t)->constType;
                    (*lIter)->domain = tempSort;
                    if((*lIter)->constType == Constant::CONST_ATTRIBUTE && (yyvsp[(3) - (3)].constant_binder_t)->attributeOf != NULL)
                    {
                        ((Attribute*)(*lIter))->attributeOf = (yyvsp[(3) - (3)].constant_binder_t)->attributeOf;
                    }
                    // Translate each constant once its information is complete.
                    mainTrans.translateConstantDecl(*lIter);
                }
            }
        }
        else
        {
            // Deallocate all of the constants in the errant list, they're never going to get used by anything.
            for(std::list<Constant*>::iterator lIter = (yyvsp[(1) - (3)].l_constant)->begin(); lIter != (yyvsp[(1) - (3)].l_constant)->end(); ++lIter)
            {
                deallocateItem(*lIter);
            }
        }
    }
    if((yyvsp[(3) - (3)].constant_binder_t) != NULL)
    {
        deallocateItem((yyvsp[(3) - (3)].constant_binder_t));
    }
    if((yyvsp[(1) - (3)].l_constant) != NULL)
    {
        deallocateList((yyvsp[(1) - (3)].l_constant));
    }
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(tempSort == NULL || constantError == true)
    {
        YYERROR;
    }
;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 654 "parser.y"
    {
    (yyval.l_constant) = (yyvsp[(1) - (1)].l_constant);
;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 658 "parser.y"
    {
    (yyval.l_constant) = (yyvsp[(2) - (3)].l_constant);
;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 664 "parser.y"
    {
    // Create a new constant list, add the schema as the first element.
    (yyval.l_constant) = new std::list<Constant*>;
    if((yyvsp[(1) - (1)].constant) != NULL)
    {
        (yyval.l_constant)->push_back((yyvsp[(1) - (1)].constant));
    }
;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 673 "parser.y"
    {
    // Merge a schema into an existing list.
    (yyval.l_constant) = NULL;
    if((yyvsp[(1) - (3)].l_constant) != NULL && (yyvsp[(3) - (3)].constant) != NULL)
    {
        (yyval.l_constant) = (yyvsp[(1) - (3)].l_constant);
        (yyval.l_constant)->push_back((yyvsp[(3) - (3)].constant));
    }
    if((yyvsp[(1) - (3)].l_constant) == NULL)
    {
        deallocateItem((yyvsp[(3) - (3)].constant));
    }
    if((yyvsp[(3) - (3)].constant) == NULL)
    {
        for(std::list<Constant*>::iterator lIter = (yyvsp[(1) - (3)].l_constant)->begin(); lIter != (yyvsp[(1) - (3)].l_constant)->end(); ++lIter)
        {
            deallocateItem(*lIter);
        }
        deallocateItem((yyvsp[(3) - (3)].constant));
    }
;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 697 "parser.y"
    {
    (yyval.constant) = (yyvsp[(1) - (1)].constant);
;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 701 "parser.y"
    {
    (yyval.constant) = (yyvsp[(2) - (3)].constant);
;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 707 "parser.y"
    {
    // Create a new Constant from a bare identifier.
    (yyval.constant) = new Constant(*(yyvsp[(1) - (1)].str), Translator::sanitizeConstantName(*(yyvsp[(1) - (1)].str)));
    deallocateItem((yyvsp[(1) - (1)].str));
;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 713 "parser.y"
    {
    // Create a new Constant from a parameterized identifier.
    (yyval.constant) = NULL;
    if((yyvsp[(3) - (4)].l_sort) != NULL)
    {
        (yyval.constant) = new Constant(*(yyvsp[(1) - (4)].str), Translator::sanitizeConstantName(*(yyvsp[(1) - (4)].str)));
        for(std::list<Sort*>::iterator lIter = (yyvsp[(3) - (4)].l_sort)->begin(); lIter != (yyvsp[(3) - (4)].l_sort)->end(); ++lIter)
        {
            if((*lIter) != NULL)
            {
                (yyval.constant)->params.push_back(*lIter);
            }
        }
        deallocateList((yyvsp[(3) - (4)].l_sort));
    }
    deallocateItem((yyvsp[(1) - (4)].str));
;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 734 "parser.y"
    {
    std::vector<std::string> dummyParams;
    (yyval.constant) = mainTrans.getConstant(*(yyvsp[(1) - (1)].str), dummyParams);
    deallocateItem((yyvsp[(1) - (1)].str));
;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 740 "parser.y"
    {
    (yyval.constant) = NULL;
    if((yyvsp[(3) - (4)].l_sort) != NULL)
    {
        std::vector<Sort*> constVecParams = utils::elementListToElementVector(*(yyvsp[(3) - (4)].l_sort));
        std::vector<std::string> constParamNames = utils::elementVectorToFullNameVector(constVecParams);
        (yyval.constant) = mainTrans.getConstant(*(yyvsp[(1) - (4)].str), constParamNames);
        deallocateList((yyvsp[(3) - (4)].l_sort));
    }
    deallocateItem((yyvsp[(1) - (4)].str));
;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 754 "parser.y"
    {
    (yyval.constant_binder_t) = (yyvsp[(1) - (1)].constant_binder_t);
;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 758 "parser.y"
    {
    (yyval.constant_binder_t) = (yyvsp[(2) - (3)].constant_binder_t);
;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 764 "parser.y"
    {
    // Two possibilities, check for each:
    // 1) The identifier is a plain constant type (e.g. "exogenousAction").
    // 2) The identifier is something else, which is a shortcut for "rigid(identifier)".
    Constant::ConstantType constType = Constant::CONST_UNKNOWN;
    std::string tempIdent = (*(yyvsp[(1) - (1)].str));
    deallocateItem((yyvsp[(1) - (1)].str));
    // Check for a real constant type.
    if(tempIdent == "abAction")
    {
        constType = Constant::CONST_ABACTION;
    }
    else if(tempIdent == "action")
    {
        constType = Constant::CONST_ACTION;
    }
    else if (tempIdent == "macroAction")
    {
        constType = Constant::CONST_MACROACTION;
    }
    else if(tempIdent == "additiveAction")
    {
        constType = Constant::CONST_ADDITIVEACTION;
    }
    else if(tempIdent == "additiveFluent")
    {
        constType = Constant::CONST_ADDITIVEFLUENT;
    }
    else if(tempIdent == "exogenousAction")
    {
        constType = Constant::CONST_EXOGENOUSACTION;
    }
    else if(tempIdent == "inertialFluent")
    {
        constType = Constant::CONST_INERTIALFLUENT;
    }
    else if(tempIdent == "rigid")
    {
        constType = Constant::CONST_RIGID;
    }
    else if(tempIdent == "sdFluent")
    {
        constType = Constant::CONST_SDFLUENT;
    }
    else if(tempIdent == "simpleFluent")
    {
        constType = Constant::CONST_SIMPLEFLUENT;
    }

    (yyval.constant_binder_t) = new PT_constant_binder_t;
    if(constType != Constant::CONST_UNKNOWN)
    {   // Basic constant binder with Boolean domain.
        (yyval.constant_binder_t)->constType = constType;
        std::string domainName = std::string("boolean");
        (yyval.constant_binder_t)->domain = checkDynamicSortDecl(&domainName);
    }
    else
    {   // If it wasn't a real constant type, it's just a shortcut for "rigid(identifier)".
        (yyval.constant_binder_t)->constType = Constant::CONST_RIGID;
        (yyval.constant_binder_t)->domain = checkDynamicSortDecl(&tempIdent);
        if((yyval.constant_binder_t)->domain == NULL)
        {
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "Sort \"" << tempIdent << "\" not declared, can't use as the domain of a constant declaration.";
            ltsyyreportError();
        }
        if((yyval.constant_binder_t)->domain == NULL)
        {   // If $$'s domain attribute is NULL, an error happened.
            deallocateItem((yyval.constant_binder_t));
            YYERROR;
        }
    }
;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 838 "parser.y"
    {
    // Basic constant binder with given domain.
    Constant::ConstantType constType = Constant::CONST_UNKNOWN;
    std::string tempIdent = (*(yyvsp[(1) - (4)].str));
    deallocateItem((yyvsp[(1) - (4)].str));
    // Figure out which constant type was given.
    if(tempIdent == "abAction")
    {
        constType = Constant::CONST_ABACTION;
    }
    else if(tempIdent == "action")
    {
        constType = Constant::CONST_ACTION;
    }
    else if (tempIdent == "macroAction")
    {
       constType = Constant::CONST_MACROACTION;
    }
    else if(tempIdent == "additiveAction")
    {
        constType = Constant::CONST_ADDITIVEACTION;
    }
    else if(tempIdent == "additiveFluent")
    {
        constType = Constant::CONST_ADDITIVEFLUENT;
    }
    else if(tempIdent == "exogenousAction")
    {
        constType = Constant::CONST_EXOGENOUSACTION;
    }
    else if(tempIdent == "inertialFluent")
    {
        constType = Constant::CONST_INERTIALFLUENT;
    }
    else if(tempIdent == "rigid")
    {
        constType = Constant::CONST_RIGID;
    }
    else if(tempIdent == "sdFluent")
    {
        constType = Constant::CONST_SDFLUENT;
    }
    else if(tempIdent == "simpleFluent")
    {
        constType = Constant::CONST_SIMPLEFLUENT;
    }

    (yyval.constant_binder_t) = new PT_constant_binder_t;
    (yyval.constant_binder_t)->constType = constType;
    if((yyvsp[(3) - (4)].str) != NULL)
    {
        (yyval.constant_binder_t)->domain = checkDynamicSortDecl((yyvsp[(3) - (4)].str));
        deallocateItem((yyvsp[(3) - (4)].str));
    }
    if((yyval.constant_binder_t)->domain == NULL)
    {   // Start error mode if anything went wrong.
        deallocateItem((yyval.constant_binder_t));
        YYERROR;
    }
;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 899 "parser.y"
    {
    // Attribute binder with Boolean(*) domain.
    (yyval.constant_binder_t) = new PT_constant_binder_t;
    (yyval.constant_binder_t)->constType = Constant::CONST_ATTRIBUTE;
    std::string* domainName = new std::string("boolean*");
    (yyval.constant_binder_t)->domain = checkDynamicSortDecl(domainName);
    deallocateItem(domainName);
    if((yyvsp[(3) - (3)].constant) != NULL)
    {
        (yyval.constant_binder_t)->attributeOf = (yyvsp[(3) - (3)].constant);
    }
    else
    {   // Something's wrong, start error mode.
        deallocateItem((yyval.constant_binder_t));
        YYERROR;
    }
;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 917 "parser.y"
    {
    // Attribute binder with given(*) domain.
    (yyval.constant_binder_t) = new PT_constant_binder_t;
    (yyval.constant_binder_t)->constType = Constant::CONST_ATTRIBUTE;
    if((yyvsp[(3) - (6)].str) != NULL)
    {
        std::string* domainName = new std::string(*(yyvsp[(3) - (6)].str));
        (*domainName) += "*";
        (yyval.constant_binder_t)->domain = checkDynamicSortDecl(domainName);
        deallocateItem(domainName);
        if((yyval.constant_binder_t)->domain == NULL)
        {
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "Sort \"" << *(yyvsp[(3) - (6)].str) << "\" not declared, can't use as the domain of a constant declaration.";
            ltsyyreportError();
        }
        deallocateItem((yyvsp[(3) - (6)].str));
    }
    if((yyvsp[(6) - (6)].constant) != NULL)
    {
        (yyval.constant_binder_t)->attributeOf = (yyvsp[(6) - (6)].constant);
    }
    if((yyval.constant_binder_t)->domain == NULL || (yyval.constant_binder_t)->attributeOf == NULL)
    {   // If $$'s attributes are NULL, an error happened.
        deallocateItem((yyval.constant_binder_t));
        YYERROR;
    }
;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 946 "parser.y"
    {
    // A (dirty) shortcut for rigid(num_range), dynamically instantiating a sort for the num range.
    (yyval.constant_binder_t) = new PT_constant_binder_t;
    (yyval.constant_binder_t)->constType = Constant::CONST_RIGID;
    // Turn the number range into a sort (if that hasn't happened already).
    if((yyvsp[(1) - (1)].numRange) != NULL)
    {
        std::string numRangeSortName = Translator::numRangeToSortName((yyvsp[(1) - (1)].numRange)->min, (yyvsp[(1) - (1)].numRange)->max);
        Sort* tempSort = mainTrans.getSort(numRangeSortName);
        if(tempSort == NULL)
        {
            // Have a helper function handle making and translating the sort.
            std::list<Sort*>* dummyList = new std::list<Sort*>; // No subsorts.
            tempSort = processSort(&numRangeSortName, dummyList);
            deallocateList(dummyList);
            // Also add the number range as an object for this new sort.
            int addResult = mainTrans.addObject((yyvsp[(1) - (1)].numRange));
            if(addResult == SymbolTable::ADDSYM_OK)
            {
                tempSort->domainObjs.push_back((yyvsp[(1) - (1)].numRange));
                // Output the translation of the object declaration.
                mainTrans.translateObjectDecl((yyvsp[(1) - (1)].numRange), tempSort);
            }
        }
        if((yyval.constant_binder_t) != NULL && tempSort != NULL)
        {
            (yyval.constant_binder_t)->domain = tempSort;
        }
        if(tempSort == NULL)
        {
            deallocateItem((yyvsp[(1) - (1)].numRange));
        }
    }
    if((yyval.constant_binder_t)->domain == NULL)
    {   // If $$'s domain is NULL, an error happened.
        deallocateItem((yyval.constant_binder_t));
        YYERROR;
    }
;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 990 "parser.y"
    {
    // The new style of maxAdditive declaration. Insert a hint comment with the given maxAdditive value.
    if((yyvsp[(4) - (5)].str) != NULL)
    {
        std::string maxAdditiveHint = "% [MaxAdditive:";
        maxAdditiveHint += *((yyvsp[(4) - (5)].str));
        maxAdditiveHint += "]";
        mainTrans.output(maxAdditiveHint, true);
        (yyval.not_used) = PARSERULE_NOT_USED;
        deallocateItem((yyvsp[(4) - (5)].str));
    }
;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 1006 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 1009 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 1010 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 1013 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 1014 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 1017 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 1018 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 1022 "parser.y"
    {
    // Connect each Object in the list to its sort, (try to) add them to the symbol table, and translate each object.
    Sort* tempSort = NULL;
    bool objectError = false; // Set to true if a serious error happens during object adding.
    if((yyvsp[(1) - (3)].l_object) != NULL && (yyvsp[(3) - (3)].str) != NULL)
    {
        tempSort = mainTrans.getSort(*(yyvsp[(3) - (3)].str));
        if(tempSort != NULL)
        {
            for(std::list<Object*>::iterator lIter = (yyvsp[(1) - (3)].l_object)->begin(); lIter != (yyvsp[(1) - (3)].l_object)->end(); ++lIter)
            {   // Try to add the object to the symbol table (mostly to check for dupes).
                int addSymResult = mainTrans.addObject(*lIter);
                if(addSymResult != SymbolTable::ADDSYM_OK)
                {   // Something went wrong adding the object, skip connecting & translating it.
                    if(addSymResult == SymbolTable::ADDSYM_DUP)
                    {   // Warn about duplicate object declarations (not an error), then move on.
                        ltsyystartCaution(ltsyylloc);
                        ltsyyossErr << "Duplicate object declaration: \"" << (*lIter)->fullName() << "\".";
                        ltsyyreportCaution();
                        deallocateItem(*lIter);
                    }
                    else
                    {   // A real object error.
                        ltsyystartParseError(ltsyylloc);
                        ltsyyossErr << "Bad object declaration: \"" << (*lIter)->fullName() << "\".";
                        ltsyyreportError();
                        deallocateItem(*lIter);
                        objectError = true;
                    }
                }
                else
                {   // Object add went okay, connect the sort to the object and translate them.
                    tempSort->domainObjs.push_back(*lIter);
                    // Translate each object as we add it to the sort's domain.
                    mainTrans.translateObjectDecl(*lIter, tempSort);
                }
            }
        }
        else
        {
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "Sort \"" << *(yyvsp[(3) - (3)].str) << "\" not declared, can't use as the target of an object declaration.";
            ltsyyreportError();
            // Deallocate all of the objects in the errant list, they're never going to get used by anything.
            for(std::list<Object*>::iterator lIter = (yyvsp[(1) - (3)].l_object)->begin(); lIter != (yyvsp[(1) - (3)].l_object)->end(); ++lIter)
            {
                deallocateItem(*lIter);
            }
        }
        deallocateList((yyvsp[(1) - (3)].l_object));
        deallocateItem((yyvsp[(3) - (3)].str));
    }
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(tempSort == NULL || objectError == true)
    {   // If the binding sort never got a match or an object had a problem getting added, an error occurred.
        YYERROR;
    }
;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 1083 "parser.y"
    {
    (yyval.l_object) = (yyvsp[(1) - (1)].l_object);
;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 1087 "parser.y"
    {
    (yyval.l_object) = (yyvsp[(2) - (3)].l_object);
;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 1093 "parser.y"
    {
    // Create a new list and make the new object the first element.
    (yyval.l_object) = NULL;
    if((yyvsp[(1) - (1)].object) != NULL)
    {
        (yyval.l_object) = new std::list<Object*>;
        (yyval.l_object)->push_back((yyvsp[(1) - (1)].object));
    }
;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 1103 "parser.y"
    {
    // Merge a new object with an exisiting list.
    (yyval.l_object) = NULL;
    if((yyvsp[(1) - (3)].l_object) != NULL && (yyvsp[(3) - (3)].object) != NULL)
    {
        (yyval.l_object) = (yyvsp[(1) - (3)].l_object);
        (yyval.l_object)->push_back((yyvsp[(3) - (3)].object));
    }
    if((yyvsp[(1) - (3)].l_object) == NULL)
    {
        deallocateItem((yyvsp[(3) - (3)].object));
    }
    if((yyvsp[(3) - (3)].object) == NULL)
    {
        for(std::list<Object*>::iterator lIter = (yyvsp[(1) - (3)].l_object)->begin(); lIter != (yyvsp[(1) - (3)].l_object)->end(); ++lIter)
        {
            deallocateItem(*lIter);
        }
        deallocateList((yyvsp[(1) - (3)].l_object));
    }
;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 1127 "parser.y"
    {
    (yyval.object) = (yyvsp[(1) - (1)].object);
;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 1131 "parser.y"
    {
    (yyval.object) = (yyvsp[(2) - (3)].object);
;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 1137 "parser.y"
    {
    // Create a new Object from a bare identifier.
    (yyval.object) = new Object(*(yyvsp[(1) - (1)].str), Translator::sanitizeObjectName(*(yyvsp[(1) - (1)].str)));
    deallocateItem((yyvsp[(1) - (1)].str));
;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 1143 "parser.y"
    {
    // Create a new Object from a parameterized identifier.
    (yyval.object) = new Object(*(yyvsp[(1) - (4)].str), Translator::sanitizeObjectName(*(yyvsp[(1) - (4)].str)));
    if((yyvsp[(3) - (4)].l_sort) != NULL)
    {
        for(std::list<Sort*>::iterator lIter = (yyvsp[(3) - (4)].l_sort)->begin(); lIter != (yyvsp[(3) - (4)].l_sort)->end(); ++lIter)
        {
            if((*lIter) != NULL)
            {
                (yyval.object)->params.push_back(*lIter);
            }
        }
        deallocateList((yyvsp[(3) - (4)].l_sort));
    }
    deallocateItem((yyvsp[(1) - (4)].str));
;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 1160 "parser.y"
    {
    // Create a new object from arbitrary math.
    (yyval.object) = new Object(*(yyvsp[(1) - (1)].str), Translator::sanitizeObjectName(*(yyvsp[(1) - (1)].str)));
    deallocateItem((yyvsp[(1) - (1)].str)); // Free dynamic memory that's not needed anymore.
;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 1166 "parser.y"
    {
    // Upcast a NumberRange into an Object.
    (yyval.object) = (Object*)(yyvsp[(1) - (1)].numRange);
;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 1175 "parser.y"
    {
    (yyval.not_used) = PARSERULE_NOT_USED;
    /* Not supported yet. */
    yyerrok;
;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 1185 "parser.y"
    {
    // Deallocate the main sort list of the statement.
    if((yyvsp[(3) - (4)].l_sort) != NULL)
    {
        deallocateList((yyvsp[(3) - (4)].l_sort));
    }
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 1196 "parser.y"
    {
    (yyval.l_sort) = (yyvsp[(1) - (1)].l_sort);
;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 1200 "parser.y"
    {
    (yyval.l_sort) = (yyvsp[(2) - (3)].l_sort);
;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 1206 "parser.y"
    {
    (yyval.l_sort) = new std::list<Sort*>;
    (yyval.l_sort)->push_back((yyvsp[(1) - (1)].sort));
;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 1211 "parser.y"
    {
    (yyval.l_sort) = NULL;
    if((yyvsp[(1) - (3)].l_sort) != NULL || (yyvsp[(3) - (3)].l_sort) != NULL)
    {
        (yyval.l_sort) = new std::list<Sort*>;
    }
    // Merge the two sort lists, if they exist.
    if((yyvsp[(1) - (3)].l_sort) != NULL)
    {
        for(std::list<Sort*>::iterator lIter = (yyvsp[(1) - (3)].l_sort)->begin(); lIter != (yyvsp[(1) - (3)].l_sort)->end(); ++lIter)
        {
            if((*lIter) != NULL)
            {
                (yyval.l_sort)->push_back((*lIter));
            }
        }
        deallocateList((yyvsp[(1) - (3)].l_sort));
    }
    if((yyvsp[(3) - (3)].l_sort) != NULL)
    {
        for(std::list<Sort*>::iterator lIter = (yyvsp[(3) - (3)].l_sort)->begin(); lIter != (yyvsp[(3) - (3)].l_sort)->end(); ++lIter)
        {
            if((*lIter) != NULL)
            {
                (yyval.l_sort)->push_back((*lIter));
            }
        }
        deallocateList((yyvsp[(3) - (3)].l_sort));
    }
;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1244 "parser.y"
    {
    // Have a helper function handle making and translating the sort.
    std::list<Sort*>* dummyList = new std::list<Sort*>;
    (yyval.sort) = processSort((yyvsp[(1) - (1)].str), dummyList);
    deallocateList(dummyList);
    deallocateItem((yyvsp[(1) - (1)].str));
    if((yyval.sort) == NULL)
    {
        YYERROR;
    }
;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 1256 "parser.y"
    {
    // Have a helper function handle making and translating the sort.
    (yyval.sort) = processSort((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].l_sort));
    deallocateItem((yyvsp[(1) - (3)].str));
    deallocateList((yyvsp[(3) - (3)].l_sort));
    if((yyval.sort) == NULL)
    {
        YYERROR;
    }
;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 1269 "parser.y"
    {
    (yyval.str) = (yyvsp[(1) - (1)].str);
;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1273 "parser.y"
    {
    (yyval.str) = (yyvsp[(2) - (3)].str);
;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1279 "parser.y"
    {
    (yyval.str) = (yyvsp[(1) - (1)].str);
;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 1283 "parser.y"
    {
    (yyval.str) = new std::string;
    (*(yyval.str)) = (*(yyvsp[(1) - (2)].str)) + "*";
    deallocateItem((yyvsp[(1) - (2)].str));
;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 1289 "parser.y"
    {
    // Alternate way to express the idea of a starred sort.
    (yyval.str) = new std::string;
    (*(yyval.str)) = (*(yyvsp[(1) - (3)].str)) + "*";
    deallocateItem((yyvsp[(1) - (3)].str));
;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1298 "parser.y"
    {
    (yyval.str) = (yyvsp[(1) - (1)].str);
;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 1302 "parser.y"
    {
    (yyval.str) = (yyvsp[(1) - (1)].str)
;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1308 "parser.y"
    {
    // Directly referencing an internal sort, return the name of the desired sort.
    (yyval.str) = new std::string;
    (*(yyval.str)) = "abAction";
;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1314 "parser.y"
    {
    // Directly referencing an internal sort, return the name of the desired sort.
    (yyval.str) = new std::string;
    (*(yyval.str)) = "action";
;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1320 "parser.y"
    {
    (yyval.str) = new std::string;
    (*(yyval.str)) = "macroAction";
;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1325 "parser.y"
    {
    // Directly referencing an internal sort, return the name of the desired sort.
    (yyval.str) = new std::string;
    (*(yyval.str)) = "additiveAction";
;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1331 "parser.y"
    {
    // Directly referencing an internal sort, return the name of the desired sort.
    (yyval.str) = new std::string;
    (*(yyval.str)) = "additiveFluent";
;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 1337 "parser.y"
    {
    // Directly referencing an internal sort, return the name of the desired sort.
    (yyval.str) = new std::string;
    (*(yyval.str)) = "exogenousAction";
;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 1343 "parser.y"
    {
    // Directly referencing an internal sort, return the name of the desired sort.
    (yyval.str) = new std::string;
    (*(yyval.str)) = "inertialFluent";
;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 1349 "parser.y"
    {
    // Directly referencing an internal sort, return the name of the desired sort.
    (yyval.str) = new std::string;
    (*(yyval.str)) = "rigid";
;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1355 "parser.y"
    {
    // Directly referencing an internal sort, return the name of the desired sort.
    (yyval.str) = new std::string;
    (*(yyval.str)) = "sdFluent";
;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 1361 "parser.y"
    {
    // Directly referencing an internal sort, return the name of the desired sort.
    (yyval.str) = new std::string;
    (*(yyval.str)) = "simpleFluent";
;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1370 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 1373 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 1374 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 1377 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 1378 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 1381 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 1382 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1386 "parser.y"
    {
    // Connect the variables in the list to the binding sort, then translate them.
    if((yyvsp[(1) - (3)].l_variable) != NULL && (yyvsp[(3) - (3)].sort) != NULL)
    {
        std::list<Variable*>::iterator vIter;
        for(vIter = (yyvsp[(1) - (3)].l_variable)->begin(); vIter != (yyvsp[(1) - (3)].l_variable)->end(); ++vIter)
        {
            (*vIter)->sortRef = (yyvsp[(3) - (3)].sort);
            mainTrans.translateVariableDecl(*vIter);
        }
    }
    if((yyvsp[(1) - (3)].l_variable) != NULL)
    {   // Clear out the list, we don't need it anymore.
        deallocateList((yyvsp[(1) - (3)].l_variable));
    }
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1406 "parser.y"
    {
    (yyval.l_variable) = (yyvsp[(1) - (1)].l_variable);
;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1410 "parser.y"
    {
    (yyval.l_variable) = (yyvsp[(2) - (3)].l_variable);
;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1416 "parser.y"
    {
    // Create a new list of Variables, add this one as the first item.
    (yyval.l_variable) = new std::list<Variable*>;
    Variable* tempVar = new Variable(*(yyvsp[(1) - (1)].str), Translator::sanitizeVariableName(*(yyvsp[(1) - (1)].str)));
    int addSymResult = mainTrans.addVariable(tempVar);
    if(addSymResult != SymbolTable::ADDSYM_OK)
    {
        if(addSymResult == SymbolTable::ADDSYM_DUP)
        {   // Warn about duplicate variable declarations (not an error), then grab the already-declared variable.
            ltsyystartCaution(ltsyylloc);
            ltsyyossErr << "Duplicate variable declaration: \"" << *(yyvsp[(1) - (1)].str) << "\".";
            ltsyyreportCaution();
            deallocateItem(tempVar);
            tempVar = mainTrans.getVariable(*(yyvsp[(1) - (1)].str));
            (yyval.l_variable)->push_back(tempVar);
        }
        else
        {   // A real variable error.
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "Bad variable declaration: \"" << *(yyvsp[(1) - (1)].str) << "\".";
            ltsyyreportError();
            deallocateList((yyval.l_variable));
            deallocateItem(tempVar);
        }
    }
    else
    {
        (yyval.l_variable)->push_back(tempVar);
    }
    deallocateItem((yyvsp[(1) - (1)].str));
    if(tempVar == NULL || (yyval.l_variable) == NULL)
    {   // If $$ or tempVar are NULL, something went wrong.
        YYERROR;
    }
;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1452 "parser.y"
    {
    // Merge a new variable declaration into an existing list of variables.
    if((yyvsp[(1) - (3)].l_variable) == NULL)
    {
        (yyval.l_variable) = new std::list<Variable*>;
    }
    Variable* tempVar = new Variable(*(yyvsp[(3) - (3)].str), Translator::sanitizeVariableName(*(yyvsp[(3) - (3)].str)));
    int addSymResult = mainTrans.addVariable(tempVar);
    if(addSymResult != SymbolTable::ADDSYM_OK)
    {
        if(addSymResult == SymbolTable::ADDSYM_DUP)
        {   // Warn about duplicate variable declarations (not an error), then grab the already-declared variable.
            ltsyystartCaution(ltsyylloc);
            ltsyyossErr << "Duplicate variable declaration: \"" << *(yyvsp[(3) - (3)].str) << "\".";
            ltsyyreportCaution();
            deallocateItem(tempVar);
            tempVar = mainTrans.getVariable(*(yyvsp[(3) - (3)].str));
            (yyval.l_variable)->push_back(tempVar);
        }
        else
        {   // A real variable error.
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "Bad variable declaration: \"" << *(yyvsp[(3) - (3)].str) << "\".";
            ltsyyreportError();
            deallocateItem(tempVar);
        }
    }
    else
    {
        (yyval.l_variable)->push_back(tempVar);
    }
    deallocateItem((yyvsp[(3) - (3)].str));
    if(tempVar == NULL)
    {   // If tempVar is NULL, something went wrong.
        YYERROR;
    }
;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1492 "parser.y"
    {
    // Find the sort in question, create it if it doesn't exist and is a "something*" sort (whose "something" exists already), or report an error.
    (yyval.sort) = mainTrans.getSort(*(yyvsp[(1) - (1)].str));
    if((yyval.sort) == NULL)
    {
        (yyval.sort) = checkDynamicSortDecl((yyvsp[(1) - (1)].str)); // Reports appropriate errors, we just need to YYERROR if that happens.
    }
    deallocateItem((yyvsp[(1) - (1)].str));
    if((yyval.sort) == NULL)
    {   // If $$ is NULL, something went wrong.
        YYERROR;
    }
;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1506 "parser.y"
    {
    // Turn the number range into a sort (if that hasn't happened already).
    (yyval.sort) = NULL;
    if((yyvsp[(1) - (1)].numRange) != NULL)
    {
        std::string numRangeSortName = Translator::numRangeToSortName((yyvsp[(1) - (1)].numRange)->min, (yyvsp[(1) - (1)].numRange)->max);
        (yyval.sort) = mainTrans.getSort(numRangeSortName);
        if((yyval.sort) == NULL)
        {
            // Have a helper function handle making and translating the sort.
            std::list<Sort*>* dummyList = new std::list<Sort*>; // No subsorts.
            (yyval.sort) = processSort(&numRangeSortName, dummyList);
            deallocateList(dummyList);
            // Also add the number range as an object for this new sort.
            int addResult = mainTrans.addObject((yyvsp[(1) - (1)].numRange));
            if(addResult == SymbolTable::ADDSYM_OK)
            {
                (yyval.sort)->domainObjs.push_back((yyvsp[(1) - (1)].numRange));
                // Output the translation of the object declaration.
                mainTrans.translateObjectDecl((yyvsp[(1) - (1)].numRange), (yyval.sort));
            }
        }
    }
    if((yyval.sort) == NULL)
    {   // If $$ is NULL, something went wrong.
        deallocateItem((yyvsp[(1) - (1)].numRange));
        YYERROR;
    }
;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 1539 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1540 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1543 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1544 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 1545 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 1546 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 1547 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1548 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1549 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1550 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1551 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1552 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1553 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1554 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1555 "parser.y"
    { (yyval.not_used) = PARSERULE_NOT_USED; ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1560 "parser.y"
    {
    bool transResult = handleAlwaysLaw((yyvsp[(2) - (4)].parseElement), (yyvsp[(4) - (4)].parseElement));
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1571 "parser.y"
    {
    bool transResult = handleAlwaysLaw((yyvsp[(2) - (2)].parseElement), NULL);
    deallocateItem((yyvsp[(2) - (2)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1583 "parser.y"
    {
    bool transResult = handleConstraintLaw((yyvsp[(2) - (8)].parseElement), (yyvsp[(4) - (8)].parseElement), (yyvsp[(6) - (8)].parseElement), (yyvsp[(8) - (8)].parseElement));
    deallocateItem((yyvsp[(2) - (8)].parseElement));
    deallocateItem((yyvsp[(4) - (8)].parseElement));
    deallocateItem((yyvsp[(6) - (8)].parseElement));
    deallocateItem((yyvsp[(8) - (8)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1596 "parser.y"
    {
    bool transResult = handleConstraintLaw((yyvsp[(2) - (6)].parseElement), (yyvsp[(4) - (6)].parseElement), NULL, (yyvsp[(6) - (6)].parseElement));
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1608 "parser.y"
    {
    bool transResult = handleConstraintLaw((yyvsp[(2) - (6)].parseElement), (yyvsp[(4) - (6)].parseElement), (yyvsp[(6) - (6)].parseElement), NULL);
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1620 "parser.y"
    {
    bool transResult = handleConstraintLaw((yyvsp[(2) - (4)].parseElement), (yyvsp[(4) - (4)].parseElement), NULL, NULL);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1631 "parser.y"
    {
    bool transResult = handleConstraintLaw((yyvsp[(2) - (6)].parseElement), NULL, (yyvsp[(4) - (6)].parseElement), (yyvsp[(6) - (6)].parseElement));
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1643 "parser.y"
    {
    bool transResult = handleConstraintLaw((yyvsp[(2) - (4)].parseElement), NULL, NULL, (yyvsp[(4) - (4)].parseElement));
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1654 "parser.y"
    {
    bool transResult = handleConstraintLaw((yyvsp[(2) - (4)].parseElement), NULL, (yyvsp[(4) - (4)].parseElement), NULL);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1665 "parser.y"
    {
    bool transResult = handleConstraintLaw((yyvsp[(2) - (2)].parseElement), NULL, NULL, NULL);
    deallocateItem((yyvsp[(2) - (2)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1677 "parser.y"
    {
    bool transResult = handleDefaultLaw((yyvsp[(2) - (8)].parseElement), (yyvsp[(4) - (8)].parseElement), (yyvsp[(6) - (8)].parseElement), (yyvsp[(8) - (8)].parseElement));
    deallocateItem((yyvsp[(2) - (8)].parseElement));
    deallocateItem((yyvsp[(4) - (8)].parseElement));
    deallocateItem((yyvsp[(6) - (8)].parseElement));
    deallocateItem((yyvsp[(8) - (8)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1690 "parser.y"
    {
    bool transResult = handleDefaultLaw((yyvsp[(2) - (6)].parseElement), (yyvsp[(4) - (6)].parseElement), (yyvsp[(6) - (6)].parseElement), NULL);
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1702 "parser.y"
    {
    bool transResult = handleDefaultLaw((yyvsp[(2) - (6)].parseElement), (yyvsp[(4) - (6)].parseElement), NULL, (yyvsp[(6) - (6)].parseElement));
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1714 "parser.y"
    {
    bool transResult = handleDefaultLaw((yyvsp[(2) - (4)].parseElement), (yyvsp[(4) - (4)].parseElement), NULL, NULL);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1725 "parser.y"
    {
    bool transResult = handleDefaultLaw((yyvsp[(2) - (6)].parseElement), NULL, (yyvsp[(4) - (6)].parseElement), (yyvsp[(6) - (6)].parseElement));
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1737 "parser.y"
    {
    bool transResult = handleDefaultLaw((yyvsp[(2) - (4)].parseElement), NULL, (yyvsp[(4) - (4)].parseElement), NULL);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1748 "parser.y"
    {
    bool transResult = handleDefaultLaw((yyvsp[(2) - (4)].parseElement), NULL, NULL, (yyvsp[(4) - (4)].parseElement));
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1759 "parser.y"
    {
    bool transResult = handleDefaultLaw((yyvsp[(2) - (2)].parseElement), NULL, NULL, NULL);
    deallocateItem((yyvsp[(2) - (2)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1771 "parser.y"
    {
    bool transResult = handleDeclarativeLaw((yyvsp[(2) - (8)].parseElement), (yyvsp[(4) - (8)].parseElement), (yyvsp[(6) - (8)].parseElement), (yyvsp[(8) - (8)].parseElement), SimpleUnaryOperator::UOP_EXOGENOUS);
    deallocateItem((yyvsp[(2) - (8)].parseElement));
    deallocateItem((yyvsp[(4) - (8)].parseElement));
    deallocateItem((yyvsp[(6) - (8)].parseElement));
    deallocateItem((yyvsp[(8) - (8)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1784 "parser.y"
    {
    bool transResult = handleDeclarativeLaw((yyvsp[(2) - (6)].parseElement), (yyvsp[(4) - (6)].parseElement), (yyvsp[(6) - (6)].parseElement), NULL, SimpleUnaryOperator::UOP_EXOGENOUS);
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1796 "parser.y"
    {
    bool transResult = handleDeclarativeLaw((yyvsp[(2) - (6)].parseElement), NULL, (yyvsp[(4) - (6)].parseElement), (yyvsp[(6) - (6)].parseElement), SimpleUnaryOperator::UOP_EXOGENOUS);
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1808 "parser.y"
    {
    bool transResult = handleDeclarativeLaw((yyvsp[(2) - (4)].parseElement), NULL, (yyvsp[(4) - (4)].parseElement), NULL, SimpleUnaryOperator::UOP_EXOGENOUS);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1819 "parser.y"
    {
    bool transResult = handleDeclarativeLaw((yyvsp[(2) - (6)].parseElement), (yyvsp[(4) - (6)].parseElement), NULL, (yyvsp[(6) - (6)].parseElement), SimpleUnaryOperator::UOP_EXOGENOUS);
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1831 "parser.y"
    {
    bool transResult = handleDeclarativeLaw((yyvsp[(2) - (4)].parseElement), (yyvsp[(4) - (4)].parseElement), NULL, NULL, SimpleUnaryOperator::UOP_EXOGENOUS);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1842 "parser.y"
    {
    bool transResult = handleDeclarativeLaw((yyvsp[(2) - (4)].parseElement), NULL, NULL, (yyvsp[(4) - (4)].parseElement), SimpleUnaryOperator::UOP_EXOGENOUS);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1853 "parser.y"
    {
    bool transResult = handleDeclarativeLaw((yyvsp[(2) - (2)].parseElement), NULL, NULL, NULL, SimpleUnaryOperator::UOP_EXOGENOUS);
    deallocateItem((yyvsp[(2) - (2)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1865 "parser.y"
    {
    bool transResult = handleDeclarativeLaw((yyvsp[(2) - (6)].parseElement), (yyvsp[(4) - (6)].parseElement), NULL, (yyvsp[(6) - (6)].parseElement), SimpleUnaryOperator::UOP_INERTIAL);
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1877 "parser.y"
    {
    bool transResult = handleDeclarativeLaw((yyvsp[(2) - (4)].parseElement), (yyvsp[(4) - (4)].parseElement), NULL, NULL, SimpleUnaryOperator::UOP_INERTIAL);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1888 "parser.y"
    {
    bool transResult = handleDeclarativeLaw((yyvsp[(2) - (4)].parseElement), NULL, NULL, (yyvsp[(4) - (4)].parseElement), SimpleUnaryOperator::UOP_INERTIAL);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1899 "parser.y"
    {
    bool transResult = handleDeclarativeLaw((yyvsp[(2) - (2)].parseElement), NULL, NULL, NULL, SimpleUnaryOperator::UOP_INERTIAL);
    deallocateItem((yyvsp[(2) - (2)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1911 "parser.y"
    {
    bool transResult = handleNonexecutableLaw((yyvsp[(2) - (6)].parseElement), (yyvsp[(4) - (6)].parseElement), (yyvsp[(6) - (6)].parseElement));
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1923 "parser.y"
    {
    bool transResult = handleNonexecutableLaw((yyvsp[(2) - (4)].parseElement), (yyvsp[(4) - (4)].parseElement), NULL);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1934 "parser.y"
    {
    bool transResult = handleNonexecutableLaw((yyvsp[(2) - (4)].parseElement), NULL, (yyvsp[(4) - (4)].parseElement));
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1945 "parser.y"
    {
    bool transResult = handleNonexecutableLaw((yyvsp[(2) - (2)].parseElement), NULL, NULL);
    deallocateItem((yyvsp[(2) - (2)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1957 "parser.y"
    {
    bool transResult = handleDeclarativeLaw((yyvsp[(2) - (4)].parseElement), NULL, NULL, (yyvsp[(4) - (4)].parseElement), SimpleUnaryOperator::UOP_RIGID);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1968 "parser.y"
    {
    bool transResult = handleDeclarativeLaw((yyvsp[(2) - (2)].parseElement), NULL, NULL, NULL, SimpleUnaryOperator::UOP_RIGID);
    deallocateItem((yyvsp[(2) - (2)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1980 "parser.y"
    {
    bool transResult = handlePossiblyCausedLaw((yyvsp[(2) - (8)].parseElement), (yyvsp[(4) - (8)].parseElement), (yyvsp[(6) - (8)].parseElement), (yyvsp[(8) - (8)].parseElement));
    deallocateItem((yyvsp[(2) - (8)].parseElement));
    deallocateItem((yyvsp[(4) - (8)].parseElement));
    deallocateItem((yyvsp[(6) - (8)].parseElement));
    deallocateItem((yyvsp[(8) - (8)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1993 "parser.y"
    {
    bool transResult = handlePossiblyCausedLaw((yyvsp[(2) - (6)].parseElement), (yyvsp[(4) - (6)].parseElement), (yyvsp[(6) - (6)].parseElement), NULL);
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 2005 "parser.y"
    {
    bool transResult = handlePossiblyCausedLaw((yyvsp[(2) - (6)].parseElement), (yyvsp[(4) - (6)].parseElement), NULL, (yyvsp[(6) - (6)].parseElement));
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 2017 "parser.y"
    {
    bool transResult = handlePossiblyCausedLaw((yyvsp[(2) - (4)].parseElement), (yyvsp[(4) - (4)].parseElement), NULL, NULL);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 2028 "parser.y"
    {
    bool transResult = handlePossiblyCausedLaw((yyvsp[(2) - (6)].parseElement), NULL, (yyvsp[(4) - (6)].parseElement), (yyvsp[(6) - (6)].parseElement));
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 2040 "parser.y"
    {
    bool transResult = handlePossiblyCausedLaw((yyvsp[(2) - (4)].parseElement), NULL, (yyvsp[(4) - (4)].parseElement), NULL);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 2051 "parser.y"
    {
    bool transResult = handlePossiblyCausedLaw((yyvsp[(2) - (4)].parseElement), NULL, NULL, (yyvsp[(4) - (4)].parseElement));
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 2062 "parser.y"
    {
    bool transResult = handlePossiblyCausedLaw((yyvsp[(2) - (2)].parseElement), NULL, NULL, NULL);
    deallocateItem((yyvsp[(2) - (2)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 2074 "parser.y"
    {
    bool transResult = handleMayCauseLaw((yyvsp[(1) - (7)].parseElement), (yyvsp[(3) - (7)].parseElement), (yyvsp[(5) - (7)].parseElement), (yyvsp[(7) - (7)].parseElement));
    deallocateItem((yyvsp[(1) - (7)].parseElement));
    deallocateItem((yyvsp[(3) - (7)].parseElement));
    deallocateItem((yyvsp[(5) - (7)].parseElement));
    deallocateItem((yyvsp[(7) - (7)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 2087 "parser.y"
    {
    bool transResult = handleMayCauseLaw((yyvsp[(1) - (5)].parseElement), (yyvsp[(3) - (5)].parseElement), (yyvsp[(5) - (5)].parseElement), NULL);
    deallocateItem((yyvsp[(1) - (5)].parseElement));
    deallocateItem((yyvsp[(3) - (5)].parseElement));
    deallocateItem((yyvsp[(5) - (5)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 2099 "parser.y"
    {
    bool transResult = handleMayCauseLaw((yyvsp[(1) - (5)].parseElement), (yyvsp[(3) - (5)].parseElement), NULL, (yyvsp[(5) - (5)].parseElement));
    deallocateItem((yyvsp[(1) - (5)].parseElement));
    deallocateItem((yyvsp[(3) - (5)].parseElement));
    deallocateItem((yyvsp[(5) - (5)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 2111 "parser.y"
    {
    bool transResult = handleMayCauseLaw((yyvsp[(1) - (3)].parseElement), (yyvsp[(3) - (3)].parseElement), NULL, NULL);
    deallocateItem((yyvsp[(1) - (3)].parseElement));
    deallocateItem((yyvsp[(3) - (3)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 2124 "parser.y"
    {
    bool transResult = handleCausesLaw((yyvsp[(1) - (7)].parseElement), (yyvsp[(3) - (7)].parseElement), (yyvsp[(5) - (7)].parseElement), (yyvsp[(7) - (7)].parseElement));
    deallocateItem((yyvsp[(1) - (7)].parseElement));
    deallocateItem((yyvsp[(3) - (7)].parseElement));
    deallocateItem((yyvsp[(5) - (7)].parseElement));
    deallocateItem((yyvsp[(7) - (7)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 2137 "parser.y"
    {
    bool transResult = handleCausesLaw((yyvsp[(1) - (5)].parseElement), (yyvsp[(3) - (5)].parseElement), (yyvsp[(5) - (5)].parseElement), NULL);
    deallocateItem((yyvsp[(1) - (5)].parseElement));
    deallocateItem((yyvsp[(3) - (5)].parseElement));
    deallocateItem((yyvsp[(5) - (5)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 2149 "parser.y"
    {
    bool transResult = handleCausesLaw((yyvsp[(1) - (5)].parseElement), (yyvsp[(3) - (5)].parseElement), NULL, (yyvsp[(5) - (5)].parseElement));
    deallocateItem((yyvsp[(1) - (5)].parseElement));
    deallocateItem((yyvsp[(3) - (5)].parseElement));
    deallocateItem((yyvsp[(5) - (5)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 2161 "parser.y"
    {
    bool transResult = handleCausesLaw((yyvsp[(1) - (3)].parseElement), (yyvsp[(3) - (3)].parseElement), NULL, NULL);
    deallocateItem((yyvsp[(1) - (3)].parseElement));
    deallocateItem((yyvsp[(3) - (3)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 2174 "parser.y"
    {
    // This one's easy, it's just a pass-through.
    mainTrans.output("noconcurrency.", true);
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 2182 "parser.y"
    {
    bool transResult = handleIncrementLaw((yyvsp[(1) - (9)].parseElement), (yyvsp[(3) - (9)].parseElement), (yyvsp[(5) - (9)].parseElement), (yyvsp[(7) - (9)].parseElement), (yyvsp[(9) - (9)].parseElement), true);
    deallocateItem((yyvsp[(1) - (9)].parseElement));
    deallocateItem((yyvsp[(3) - (9)].parseElement));
    deallocateItem((yyvsp[(5) - (9)].parseElement));
    deallocateItem((yyvsp[(7) - (9)].parseElement));
    deallocateItem((yyvsp[(9) - (9)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;

    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 2197 "parser.y"
    {
    bool transResult = handleIncrementLaw((yyvsp[(1) - (7)].parseElement), (yyvsp[(3) - (7)].parseElement), (yyvsp[(5) - (7)].parseElement), (yyvsp[(7) - (7)].parseElement), NULL, true);
    deallocateItem((yyvsp[(1) - (7)].parseElement));
    deallocateItem((yyvsp[(3) - (7)].parseElement));
    deallocateItem((yyvsp[(5) - (7)].parseElement));
    deallocateItem((yyvsp[(7) - (7)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;

    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 2211 "parser.y"
    {
    bool transResult = handleIncrementLaw((yyvsp[(1) - (7)].parseElement), (yyvsp[(3) - (7)].parseElement), (yyvsp[(5) - (7)].parseElement), NULL, (yyvsp[(7) - (7)].parseElement), true);
    deallocateItem((yyvsp[(1) - (7)].parseElement));
    deallocateItem((yyvsp[(3) - (7)].parseElement));
    deallocateItem((yyvsp[(5) - (7)].parseElement));
    deallocateItem((yyvsp[(7) - (7)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;

    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 2225 "parser.y"
    {
    bool transResult = handleIncrementLaw((yyvsp[(1) - (5)].parseElement), (yyvsp[(3) - (5)].parseElement), (yyvsp[(5) - (5)].parseElement), NULL, NULL, true);
    deallocateItem((yyvsp[(1) - (5)].parseElement));
    deallocateItem((yyvsp[(3) - (5)].parseElement));
    deallocateItem((yyvsp[(5) - (5)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;

    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 2238 "parser.y"
    {
    bool transResult = handleIncrementLaw((yyvsp[(1) - (9)].parseElement), (yyvsp[(3) - (9)].parseElement), (yyvsp[(5) - (9)].parseElement), (yyvsp[(7) - (9)].parseElement), (yyvsp[(9) - (9)].parseElement), false);
    deallocateItem((yyvsp[(1) - (9)].parseElement));
    deallocateItem((yyvsp[(3) - (9)].parseElement));
    deallocateItem((yyvsp[(5) - (9)].parseElement));
    deallocateItem((yyvsp[(7) - (9)].parseElement));
    deallocateItem((yyvsp[(9) - (9)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;

    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 2253 "parser.y"
    {
    bool transResult = handleIncrementLaw((yyvsp[(1) - (7)].parseElement), (yyvsp[(3) - (7)].parseElement), (yyvsp[(5) - (7)].parseElement), (yyvsp[(7) - (7)].parseElement),NULL, false);
    deallocateItem((yyvsp[(1) - (7)].parseElement));
    deallocateItem((yyvsp[(3) - (7)].parseElement));
    deallocateItem((yyvsp[(5) - (7)].parseElement));
    deallocateItem((yyvsp[(7) - (7)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;

    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 2267 "parser.y"
    {
    bool transResult = handleIncrementLaw((yyvsp[(1) - (7)].parseElement), (yyvsp[(3) - (7)].parseElement), (yyvsp[(5) - (7)].parseElement), NULL, (yyvsp[(7) - (7)].parseElement), false);
    deallocateItem((yyvsp[(1) - (7)].parseElement));
    deallocateItem((yyvsp[(3) - (7)].parseElement));
    deallocateItem((yyvsp[(5) - (7)].parseElement));
    deallocateItem((yyvsp[(7) - (7)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;

    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 2281 "parser.y"
    {
    bool transResult = handleIncrementLaw((yyvsp[(1) - (5)].parseElement), (yyvsp[(3) - (5)].parseElement), (yyvsp[(5) - (5)].parseElement), NULL, NULL, false);
    deallocateItem((yyvsp[(1) - (5)].parseElement));
    deallocateItem((yyvsp[(3) - (5)].parseElement));
    deallocateItem((yyvsp[(5) - (5)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;

    if(!transResult)
    {
        YYERROR;
    }
;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 2296 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (10)].parseElement), (yyvsp[(4) - (10)].parseElement), (yyvsp[(6) - (10)].parseElement), (yyvsp[(8) - (10)].parseElement), (yyvsp[(10) - (10)].parseElement));
    deallocateItem((yyvsp[(2) - (10)].parseElement));
    deallocateItem((yyvsp[(4) - (10)].parseElement));
    deallocateItem((yyvsp[(6) - (10)].parseElement));
    deallocateItem((yyvsp[(8) - (10)].parseElement));
    deallocateItem((yyvsp[(10) - (10)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 2306 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (8)].parseElement), (yyvsp[(4) - (8)].parseElement), (yyvsp[(6) - (8)].parseElement), (yyvsp[(8) - (8)].parseElement), NULL);
    deallocateItem((yyvsp[(2) - (8)].parseElement));
    deallocateItem((yyvsp[(4) - (8)].parseElement));
    deallocateItem((yyvsp[(6) - (8)].parseElement));
    deallocateItem((yyvsp[(8) - (8)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 2315 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (8)].parseElement), (yyvsp[(4) - (8)].parseElement), (yyvsp[(6) - (8)].parseElement), NULL, (yyvsp[(8) - (8)].parseElement));
    deallocateItem((yyvsp[(2) - (8)].parseElement));
    deallocateItem((yyvsp[(4) - (8)].parseElement));
    deallocateItem((yyvsp[(6) - (8)].parseElement));
    deallocateItem((yyvsp[(8) - (8)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 2324 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (6)].parseElement), (yyvsp[(4) - (6)].parseElement), (yyvsp[(6) - (6)].parseElement), NULL, NULL);
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 2332 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (8)].parseElement), (yyvsp[(4) - (8)].parseElement), NULL, (yyvsp[(6) - (8)].parseElement), (yyvsp[(8) - (8)].parseElement));
    deallocateItem((yyvsp[(2) - (8)].parseElement));
    deallocateItem((yyvsp[(4) - (8)].parseElement));
    deallocateItem((yyvsp[(6) - (8)].parseElement));
    deallocateItem((yyvsp[(8) - (8)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 2341 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (6)].parseElement), (yyvsp[(4) - (6)].parseElement), NULL, (yyvsp[(6) - (6)].parseElement), NULL);
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 2349 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (6)].parseElement), (yyvsp[(4) - (6)].parseElement), NULL, NULL, (yyvsp[(6) - (6)].parseElement));
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 2357 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (4)].parseElement), (yyvsp[(4) - (4)].parseElement), NULL, NULL, NULL);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 2364 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (8)].parseElement), NULL, (yyvsp[(4) - (8)].parseElement), (yyvsp[(6) - (8)].parseElement), (yyvsp[(8) - (8)].parseElement));
    deallocateItem((yyvsp[(2) - (8)].parseElement));
    deallocateItem((yyvsp[(4) - (8)].parseElement));
    deallocateItem((yyvsp[(6) - (8)].parseElement));
    deallocateItem((yyvsp[(8) - (8)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 2373 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (6)].parseElement), NULL, (yyvsp[(4) - (6)].parseElement), (yyvsp[(6) - (6)].parseElement), NULL);
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 2381 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (6)].parseElement), NULL, (yyvsp[(4) - (6)].parseElement), NULL, (yyvsp[(6) - (6)].parseElement));
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 2389 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (4)].parseElement), NULL, (yyvsp[(4) - (4)].parseElement), NULL, NULL);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 2396 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (6)].parseElement), NULL, NULL, (yyvsp[(4) - (6)].parseElement), (yyvsp[(6) - (6)].parseElement));
    deallocateItem((yyvsp[(2) - (6)].parseElement));
    deallocateItem((yyvsp[(4) - (6)].parseElement));
    deallocateItem((yyvsp[(6) - (6)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 2404 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (4)].parseElement), NULL, NULL, (yyvsp[(4) - (4)].parseElement), NULL);
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 2411 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (4)].parseElement), NULL, NULL, NULL, (yyvsp[(4) - (4)].parseElement));
    deallocateItem((yyvsp[(2) - (4)].parseElement));
    deallocateItem((yyvsp[(4) - (4)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 2418 "parser.y"
    {
    mainTrans.translateCausalLaw((yyvsp[(2) - (2)].parseElement), NULL, NULL, NULL, NULL);
    deallocateItem((yyvsp[(2) - (2)].parseElement));
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 2426 "parser.y"
    {
                bool transResult = handleMacroActionDefLaw((yyvsp[(1) - (3)].parseElement), (yyvsp[(3) - (3)].l_action));
                deallocateItem((yyvsp[(1) - (3)].parseElement));
                deallocateList((yyvsp[(3) - (3)].l_action))

                (yyval.not_used) = PARSERULE_NOT_USED;
                if (!transResult) {
                YYERROR;
                }
               ;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 2439 "parser.y"
    {
                (yyval.l_action) = (yyvsp[(1) - (3)].l_action);
                (yyval.l_action)->push_back((yyvsp[(3) - (3)].p_action));
                ;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 2444 "parser.y"
    {
                (yyval.l_action)    = new (std::list<std::pair<ParseElement*, ParseElement*>*>);
                (yyval.l_action)->clear();
                (yyval.l_action)->push_back((yyvsp[(1) - (1)].p_action));
                ;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 2451 "parser.y"
    {
                   std::pair<ParseElement*, ParseElement*>* tempAct = new (std::pair<ParseElement*, ParseElement*>);
                tempAct->first = (yyvsp[(1) - (1)].parseElement);
                tempAct->second = NULL;
                (yyval.p_action) = tempAct;
               ;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 2458 "parser.y"
    {
                    std::pair<ParseElement*, ParseElement*>* tempAct = new (std::pair<ParseElement*, ParseElement*>);
                tempAct->first = (yyvsp[(2) - (3)].parseElement);
                tempAct->second = NULL;
                (yyval.p_action) = tempAct;

               ;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 2466 "parser.y"
    {
                    std::pair<ParseElement*, ParseElement*>* tempAct = new (std::pair<ParseElement*, ParseElement*>);
                tempAct->first = (yyvsp[(1) - (3)].parseElement);
                tempAct->second = (yyvsp[(3) - (3)].parseElement);
                (yyval.p_action) = tempAct;
                ;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 2473 "parser.y"
    {
                    std::pair<ParseElement*, ParseElement*>* tempAct = new (std::pair<ParseElement*, ParseElement*>);
                tempAct->first = (yyvsp[(2) - (5)].parseElement);
                tempAct->second = (yyvsp[(4) - (5)].parseElement);
                (yyval.p_action) = tempAct;
                ;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 2483 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 2487 "parser.y"
    {
    ObjectLikeElement* tempPE = new ObjectLikeElement();
    tempPE->baseName = "true";
    tempPE->objRef = mainTrans.getObjectLike(tempPE->baseName, 0);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 2494 "parser.y"
    {
    ObjectLikeElement* tempPE = new ObjectLikeElement();
    tempPE->baseName = "false";
    tempPE->objRef = mainTrans.getObjectLike(tempPE->baseName, 0);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 2503 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 2507 "parser.y"
    {
    if((yyvsp[(2) - (3)].parseElement) != NULL)
    {
        (yyvsp[(2) - (3)].parseElement)->parenBefore = true;
        (yyvsp[(2) - (3)].parseElement)->parenAfter = true;
    }
    (yyval.parseElement) = (yyvsp[(2) - (3)].parseElement);
;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 2518 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 2522 "parser.y"
    {
    SimpleUnaryOperator* tempPE = new SimpleUnaryOperator();
    tempPE->opType = SimpleUnaryOperator::UOP_NOT;
    tempPE->postOp = (yyvsp[(2) - (2)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 2529 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_AND;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 2537 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_OR;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 2545 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_EQUIV;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 2553 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_IMPL;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 2563 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 2567 "parser.y"
    {
    if((yyvsp[(2) - (3)].parseElement) != NULL)
    {
        (yyvsp[(2) - (3)].parseElement)->parenBefore = true;
        (yyvsp[(2) - (3)].parseElement)->parenAfter = true;
    }
    (yyval.parseElement) = (yyvsp[(2) - (3)].parseElement);
;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 2578 "parser.y"
    {
    // This is really only allowed to be a constant/variable/object expression, verify that.
    if((yyvsp[(1) - (1)].parseElement) != NULL)
    {
        if((yyvsp[(1) - (1)].parseElement)->elemType != ParseElement::PELEM_BASELIKE && (yyvsp[(1) - (1)].parseElement)->elemType != ParseElement::PELEM_CONSTLIKE && (yyvsp[(1) - (1)].parseElement)->elemType != ParseElement::PELEM_OBJLIKE && (yyvsp[(1) - (1)].parseElement)->elemType != ParseElement::PELEM_VARLIKE)
        {
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "Bare expression \"" << (yyvsp[(1) - (1)].parseElement)->fullName() << "\" not allowed there, did you forget an equality or comparison sign?";
            ltsyyreportError();
            deallocateItem((yyvsp[(1) - (1)].parseElement));
        }
    }
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
    if((yyval.parseElement) == NULL)
    {
        YYERROR;
    }
;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 2597 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_EQ;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 2605 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_NEQ;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 2613 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    // A bunch of possible operators bundle into COMPARISON. Find out which one.
    switch((yyvsp[(2) - (3)].integer))
    {
    case T_DBL_EQ:
        tempPE->opType = SimpleBinaryOperator::BOP_DBL_EQ;
        break;
    case T_LTHAN:
        tempPE->opType = SimpleBinaryOperator::BOP_LTHAN;
        break;
    case T_GTHAN:
        tempPE->opType = SimpleBinaryOperator::BOP_GTHAN;
        break;
    case T_EQ_LTHAN:
        tempPE->opType = SimpleBinaryOperator::BOP_LTHAN_EQ;
        break;
    case T_GTHAN_EQ:
        tempPE->opType = SimpleBinaryOperator::BOP_GTHAN_EQ;
        break;
    default:
        tempPE->opType = SimpleBinaryOperator::BOP_UNKNOWN;
    }
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 2641 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 2647 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 2653 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 2657 "parser.y"
    {
    if((yyvsp[(2) - (3)].parseElement) != NULL)
    {
        (yyvsp[(2) - (3)].parseElement)->parenBefore = true;
        (yyvsp[(2) - (3)].parseElement)->parenAfter = true;
    }
    (yyval.parseElement) = (yyvsp[(2) - (3)].parseElement);
;}
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 2668 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 2672 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_AND;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 2682 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 2686 "parser.y"
    {
    SimpleUnaryOperator* tempPE = new SimpleUnaryOperator();
    tempPE->opType = SimpleUnaryOperator::UOP_NOT;
    tempPE->postOp = (yyvsp[(2) - (2)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 2693 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_EQ;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 2734 "parser.y"
    {
    (yyval.parseElement) = NULL;
    if((yyvsp[(2) - (5)].l_quantPair) != NULL && (yyvsp[(4) - (5)].parseElement) != NULL)
    {
        BigQuantifiers* tempPE = new BigQuantifiers();
        tempPE->quants = *(yyvsp[(2) - (5)].l_quantPair);
        tempPE->postOp = (yyvsp[(4) - (5)].parseElement);
        deallocateList((yyvsp[(2) - (5)].l_quantPair));
        (yyval.parseElement) = tempPE;
    }
;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 2748 "parser.y"
    {
    (yyval.l_quantPair) = NULL;
    if((yyvsp[(1) - (1)].p_quantPair) != NULL)
    {
        (yyval.l_quantPair) = new std::list<std::pair<enum BigQuantifiers::QuantifierType, ParseElement*>* >();
        (yyval.l_quantPair)->push_back((yyvsp[(1) - (1)].p_quantPair));
    }
;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 2757 "parser.y"
    {
    (yyval.l_quantPair) = NULL;
    if((yyvsp[(1) - (1)].p_quantPair) != NULL)
    {
        (yyval.l_quantPair) = new std::list<std::pair<enum BigQuantifiers::QuantifierType, ParseElement*>* >();
        (yyval.l_quantPair)->push_back((yyvsp[(1) - (1)].p_quantPair));
    }
;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 2766 "parser.y"
    {
    if((yyvsp[(1) - (2)].l_quantPair) != NULL && (yyvsp[(2) - (2)].p_quantPair) != NULL)
    {
        (yyval.l_quantPair) = (yyvsp[(1) - (2)].l_quantPair);
        (yyval.l_quantPair)->push_back((yyvsp[(2) - (2)].p_quantPair));
    }
    else
    {
        if((yyvsp[(1) - (2)].l_quantPair) != NULL)
        {
            for(std::list<std::pair<enum BigQuantifiers::QuantifierType, ParseElement*>* >::iterator lIter = (yyvsp[(1) - (2)].l_quantPair)->begin(); lIter != (yyvsp[(1) - (2)].l_quantPair)->end(); ++lIter)
            {
                if((*lIter)->second != NULL)
                {
                    deallocateItem((*lIter)->second);
                }
                deallocateItem(*lIter);
            }
            deallocateList((yyvsp[(1) - (2)].l_quantPair));
        }
        if((yyvsp[(2) - (2)].p_quantPair) != NULL)
        {
            if((yyvsp[(2) - (2)].p_quantPair)->second != NULL)
            {
                deallocateItem((yyvsp[(2) - (2)].p_quantPair)->second);
            }
            deallocateItem((yyvsp[(2) - (2)].p_quantPair));
        }
        (yyval.l_quantPair) = NULL;
    }
;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 2798 "parser.y"
    {
    if((yyvsp[(1) - (2)].l_quantPair) != NULL && (yyvsp[(2) - (2)].p_quantPair) != NULL)
    {
        (yyval.l_quantPair) = (yyvsp[(1) - (2)].l_quantPair);
        (yyval.l_quantPair)->push_back((yyvsp[(2) - (2)].p_quantPair));
    }
    else
    {
        if((yyvsp[(1) - (2)].l_quantPair) != NULL)
        {
            for(std::list<std::pair<enum BigQuantifiers::QuantifierType, ParseElement*>* >::iterator lIter = (yyvsp[(1) - (2)].l_quantPair)->begin(); lIter != (yyvsp[(1) - (2)].l_quantPair)->end(); ++lIter)
            {
                if((*lIter)->second != NULL)
                {
                    deallocateItem((*lIter)->second);
                }
                deallocateItem(*lIter);
            }
            deallocateList((yyvsp[(1) - (2)].l_quantPair));
        }
        if((yyvsp[(2) - (2)].p_quantPair) != NULL)
        {
            if((yyvsp[(2) - (2)].p_quantPair)->second != NULL)
            {
                deallocateItem((yyvsp[(2) - (2)].p_quantPair)->second);
            }
            deallocateItem((yyvsp[(2) - (2)].p_quantPair));
        }
        (yyval.l_quantPair) = NULL;
    }
;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 2832 "parser.y"
    {
    (yyval.p_quantPair) = new std::pair<enum BigQuantifiers::QuantifierType, ParseElement*>();
    (yyval.p_quantPair)->first = BigQuantifiers::QUANT_CONJ;
    // Guess that the identifier is a variable, otherwise just default to object.
    Variable* varRef = mainTrans.getVariableLike(*(yyvsp[(2) - (2)].str));
    if(varRef == NULL)
    {
        Object* objRef = mainTrans.getObjectLike(*(yyvsp[(2) - (2)].str),0);;
        ObjectLikeElement* tempPE = new ObjectLikeElement();
        tempPE->baseName = *(yyvsp[(2) - (2)].str);
        tempPE->objRef = objRef;
        (yyval.p_quantPair)->second = tempPE;
    }
    else
    {
        VariableLikeElement* tempPE = new VariableLikeElement();
        tempPE->baseName = *(yyvsp[(2) - (2)].str);
        tempPE->varRef = varRef;
        (yyval.p_quantPair)->second = tempPE;
    }
    deallocateItem((yyvsp[(2) - (2)].str));
;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 2857 "parser.y"
    {
    (yyval.p_quantPair) = new std::pair<enum BigQuantifiers::QuantifierType, ParseElement*>();
    (yyval.p_quantPair)->first = BigQuantifiers::QUANT_DISJ;
    // Guess that the identifier is a variable, otherwise just default to object.
    Variable* varRef = mainTrans.getVariableLike(*(yyvsp[(2) - (2)].str));
    if(varRef == NULL)
    {
        Object* objRef = mainTrans.getObjectLike(*(yyvsp[(2) - (2)].str),0);;
        ObjectLikeElement* tempPE = new ObjectLikeElement();
        tempPE->baseName = *(yyvsp[(2) - (2)].str);
        tempPE->objRef = objRef;
        (yyval.p_quantPair)->second = tempPE;
    }
    else
    {
        VariableLikeElement* tempPE = new VariableLikeElement();
        tempPE->baseName = *(yyvsp[(2) - (2)].str);
        tempPE->varRef = varRef;
        (yyval.p_quantPair)->second = tempPE;
    }
    deallocateItem((yyvsp[(2) - (2)].str));
;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 2884 "parser.y"
    {
    (yyval.not_used) = PARSERULE_NOT_USED;
    int addQueryResult = mainTrans.addQuery(mainTrans.tempQuery);
    if(addQueryResult != SymbolTable::ADDSYM_OK)
    {
        if(addQueryResult == SymbolTable::ADDSYM_DUP)
        {   // Query with same label already exists.
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "A query with label \"" << mainTrans.tempQuery->label << "\" already exists, query labels must be unique.";
            ltsyyreportError();
        }
        else
        {   // General error.
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "Query malformed or missing critical information (e.g., maxstep).";
            ltsyyreportError();
        }
        // We can just error here, the error reporting functions already handle creating a new tempQuery.
        YYERROR;
    }
    else
    {   // It added okay, translate it and make a new tempQuery without destroying the one that just got added.
        mainTrans.translateQuery(mainTrans.tempQuery);
        mainTrans.allocateNewTempQuery();
    }
;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 2913 "parser.y"
    {
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 2917 "parser.y"
    {
    (yyval.not_used) = PARSERULE_NOT_USED;
;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 2923 "parser.y"
    {
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(mainTrans.tempQuery->label == "")
    {
        mainTrans.tempQuery->label = utils::to_string((yyvsp[(3) - (3)].integer));
    }
    else
    {
        ltsyystartParseError(ltsyylloc);
        ltsyyossErr << "label already defined as \"" << mainTrans.tempQuery->maxstep << "\" in this query, can only define it once per query.";
        ltsyyreportError();
        YYERROR;
    }
;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 2938 "parser.y"
    {
    (yyval.not_used) = PARSERULE_NOT_USED;
    if(mainTrans.tempQuery->maxstep == "")
    {
        mainTrans.tempQuery->maxstep = utils::to_string((yyvsp[(3) - (3)].integer));
    }
    else
    {
        ltsyystartParseError(ltsyylloc);
        ltsyyossErr << "maxstep already defined as \"" << mainTrans.tempQuery->maxstep << "\" in this query, can only define it once per query.";
        ltsyyreportError();
        YYERROR;
    }
;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 2953 "parser.y"
    {
    (yyval.not_used) = PARSERULE_NOT_USED;
    // Explicit declaration of a limited form of a number range that only supports (positive) integers as its bounds.
    if(mainTrans.tempQuery->maxstep == "")
    {
        mainTrans.tempQuery->maxstep = utils::to_string((yyvsp[(3) - (5)].integer));
        mainTrans.tempQuery->maxstep += "..";
        mainTrans.tempQuery->maxstep += utils::to_string((yyvsp[(5) - (5)].integer));
    }
    else
    {
        ltsyystartParseError(ltsyylloc);
        ltsyyossErr << "maxstep already defined as \"" << mainTrans.tempQuery->maxstep << "\" in this query, can only define it once per query.";
        ltsyyreportError();
        YYERROR;
    }
;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 2971 "parser.y"
    {
    (yyval.not_used) = PARSERULE_NOT_USED;
    if((yyvsp[(1) - (1)].parseElement) != NULL)
    {
        // Add this new condition to the temp query.
        mainTrans.tempQuery->queryConditions.push_back((yyvsp[(1) - (1)].parseElement));
    }
    else
    {
        ltsyystartWarning(ltsyylloc);
        ltsyyossErr << "Query body formula is NULL!";
        ltsyyreportWarning();
    }
;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 2989 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 2993 "parser.y"
    {
    if((yyvsp[(2) - (3)].parseElement) != NULL)
    {
        (yyvsp[(2) - (3)].parseElement)->parenBefore = true;
        (yyvsp[(2) - (3)].parseElement)->parenAfter = true;
    }
    (yyval.parseElement) = (yyvsp[(2) - (3)].parseElement);
;}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 3002 "parser.y"
    {
    // Turn the time stamp into a plain, translated string representation, then propogate it through the body formula.
    std::string tempTimeStamp = "";
    if((yyvsp[(1) - (3)].parseElement) != NULL)
    {
        tempTimeStamp = (yyvsp[(1) - (3)].parseElement)->translate();
        deallocateItem((yyvsp[(1) - (3)].parseElement));
    }
    if((yyvsp[(3) - (3)].parseElement) != NULL)
    {
        (yyvsp[(3) - (3)].parseElement)->propogateTimeStamp(tempTimeStamp);
    }
    else
    {
        ltsyystartWarning(ltsyylloc);
        ltsyyossErr << "Query body formula with time stamp \"" << tempTimeStamp << "\" is NULL!";
        ltsyyreportWarning();
    }
    (yyval.parseElement) = (yyvsp[(3) - (3)].parseElement);
;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 3025 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 3029 "parser.y"
    {
    SimpleUnaryOperator* tempPE = new SimpleUnaryOperator();
    tempPE->opType = SimpleUnaryOperator::UOP_NOT;
    tempPE->postOp = (yyvsp[(2) - (2)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 3036 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_AND;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 3044 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_OR;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 3052 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_EQUIV;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 3060 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_IMPL;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 3070 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 3074 "parser.y"
    {
    if((yyvsp[(2) - (3)].parseElement) != NULL)
    {
        (yyvsp[(2) - (3)].parseElement)->parenBefore = true;
        (yyvsp[(2) - (3)].parseElement)->parenAfter = true;
    }
    (yyval.parseElement) = (yyvsp[(2) - (3)].parseElement);
;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 3085 "parser.y"
    {
    // This is really only allowed to be a constant/variable/object expression, verify that.
    if((yyvsp[(1) - (1)].parseElement) != NULL)
    {
        if((yyvsp[(1) - (1)].parseElement)->elemType != ParseElement::PELEM_BASELIKE && (yyvsp[(1) - (1)].parseElement)->elemType != ParseElement::PELEM_CONSTLIKE && (yyvsp[(1) - (1)].parseElement)->elemType != ParseElement::PELEM_OBJLIKE && (yyvsp[(1) - (1)].parseElement)->elemType != ParseElement::PELEM_VARLIKE)
        {
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "Bare expression \"" << (yyvsp[(1) - (1)].parseElement)->fullName() << "\" not allowed there, did you forget an equality or comparison sign?";
            ltsyyreportError();
            deallocateItem((yyvsp[(1) - (1)].parseElement));
        }
    }
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
    if((yyval.parseElement) == NULL)
    {
        YYERROR;
    }
;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 3104 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_EQ;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 3112 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_NEQ;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 3120 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    // A bunch of possible operators bundle into COMPARISON. Find out which one.
    switch((yyvsp[(2) - (3)].integer))
    {
    case T_DBL_EQ:
        tempPE->opType = SimpleBinaryOperator::BOP_DBL_EQ;
        break;
    case T_LTHAN:
        tempPE->opType = SimpleBinaryOperator::BOP_LTHAN;
        break;
    case T_GTHAN:
        tempPE->opType = SimpleBinaryOperator::BOP_GTHAN;
        break;
    case T_EQ_LTHAN:
        tempPE->opType = SimpleBinaryOperator::BOP_LTHAN_EQ;
        break;
    case T_GTHAN_EQ:
        tempPE->opType = SimpleBinaryOperator::BOP_GTHAN_EQ;
        break;
    default:
        tempPE->opType = SimpleBinaryOperator::BOP_UNKNOWN;
    }
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 3148 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 3154 "parser.y"
    {
    (yyval.parseElement) = NULL;
    if((yyvsp[(2) - (5)].l_quantPair) != NULL && (yyvsp[(4) - (5)].parseElement) != NULL)
    {
        BigQuantifiers* tempPE = new BigQuantifiers();
        tempPE->quants = *(yyvsp[(2) - (5)].l_quantPair);
        tempPE->postOp = (yyvsp[(4) - (5)].parseElement);
        deallocateList((yyvsp[(2) - (5)].l_quantPair));
        (yyval.parseElement) = tempPE;
    }
;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 3170 "parser.y"
    {
    // Guess what kind of instance this might be, go with the best match.
    // Guess variable, then constant, then just default to object.
    Variable* varRef = mainTrans.getVariableLike(*(yyvsp[(1) - (1)].str));
    if(varRef == NULL)
    {
        Constant* constRef = mainTrans.getConstantLike(*(yyvsp[(1) - (1)].str),0);
        if(constRef == NULL)
        {
            Object* objRef = mainTrans.getObjectLike(*(yyvsp[(1) - (1)].str),0);;
            ObjectLikeElement* tempPE = new ObjectLikeElement();
            tempPE->baseName = *(yyvsp[(1) - (1)].str);
            tempPE->objRef = objRef;
            (yyval.parseElement) = tempPE;
        }
        else
        {
            ConstantLikeElement* tempPE = new ConstantLikeElement();
            tempPE->baseName = *(yyvsp[(1) - (1)].str);
            tempPE->constRef = constRef;
            (yyval.parseElement) = tempPE;
        }
    }
    else
    {
        VariableLikeElement* tempPE = new VariableLikeElement();
        tempPE->baseName = *(yyvsp[(1) - (1)].str);
        tempPE->varRef = varRef;
        (yyval.parseElement) = tempPE;
    }
    deallocateItem((yyvsp[(1) - (1)].str));
;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 3203 "parser.y"
    {
    // Guess what kind of instance this might be, go with the best match.
    // Guess constant, then just default to object.
    Constant* constRef = mainTrans.getConstantLike(*(yyvsp[(1) - (4)].str),(yyvsp[(3) - (4)].v_parseElement)->size());
    if(constRef == NULL)
    {
        Object* objRef = mainTrans.getObjectLike(*(yyvsp[(1) - (4)].str),(yyvsp[(3) - (4)].v_parseElement)->size());
        ObjectLikeElement* tempPE = new ObjectLikeElement();
        tempPE->baseName = *(yyvsp[(1) - (4)].str);
        tempPE->objRef = objRef;
        (yyval.parseElement) = tempPE;
    }
    else
    {
        ConstantLikeElement* tempPE = new ConstantLikeElement();
        tempPE->baseName = *(yyvsp[(1) - (4)].str);
        tempPE->constRef = constRef;
        (yyval.parseElement) = tempPE;
    }
    // Add the parameters.
    if((yyvsp[(3) - (4)].v_parseElement) != NULL)
    {
        for(std::vector<ParseElement*>::iterator vIter = (yyvsp[(3) - (4)].v_parseElement)->begin(); vIter != (yyvsp[(3) - (4)].v_parseElement)->end(); ++vIter)
        {
            ((BaseLikeElement*)(yyval.parseElement))->params.push_back(*vIter);
        }
    }
    deallocateItem((yyvsp[(1) - (4)].str));
    deallocateList((yyvsp[(3) - (4)].v_parseElement));
;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 3236 "parser.y"
    {
    (yyval.v_parseElement) = NULL;
    if((yyvsp[(1) - (1)].parseElement) != NULL)
    {
        (yyval.v_parseElement) = new std::vector<ParseElement*>();
        (yyval.v_parseElement)->push_back((yyvsp[(1) - (1)].parseElement));
    }
;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 3245 "parser.y"
    {
    (yyval.v_parseElement) = NULL;
    if((yyvsp[(1) - (3)].v_parseElement) != NULL && (yyvsp[(3) - (3)].parseElement) != NULL)
    {
        (yyval.v_parseElement) = (yyvsp[(1) - (3)].v_parseElement);
        (yyval.v_parseElement)->push_back((yyvsp[(3) - (3)].parseElement));
    }
;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 3256 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 3262 "parser.y"
    {
    Sort* tempSort = mainTrans.getSort(*(yyvsp[(1) - (1)].str));
    (yyval.l_sort) = NULL;
    if(tempSort != NULL)
    {
        (yyval.l_sort) = new std::list<Sort*>;
        (yyval.l_sort)->push_back(tempSort);
    }
    else
    {
        ltsyystartParseError(ltsyylloc);
        ltsyyossErr << "Sort \"" << *(yyvsp[(1) - (1)].str) << "\" not declared, can't use as part of another declaration.";
        ltsyyreportError();
    }
    deallocateItem((yyvsp[(1) - (1)].str));
    if((yyval.l_sort) == NULL)
    {   // If $$ is NULL, something went wrong.
        YYERROR;
    }
;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 3283 "parser.y"
    {
    (yyval.l_sort) = NULL;
    if((yyvsp[(1) - (3)].l_sort) != NULL)
    {
        (yyval.l_sort) = (yyvsp[(1) - (3)].l_sort);
        Sort* tempSort = mainTrans.getSort(*(yyvsp[(3) - (3)].str));
        if(tempSort != NULL)
        {
            (yyval.l_sort)->push_back(tempSort);
        }
        else
        {
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "Sort \"" << *(yyvsp[(3) - (3)].str) << "\" not declared, can't use as part of another declaration.";
            ltsyyreportError();
            deallocateList((yyval.l_sort));
        }
    }
    deallocateItem((yyvsp[(3) - (3)].str));
    if((yyval.l_sort) == NULL)
    {   // If $$ is NULL, something went wrong.
        YYERROR;
    }
;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 3310 "parser.y"
    {
    ObjectLikeElement* tempPE = new ObjectLikeElement();
    tempPE->baseName = "true";
    tempPE->objRef = mainTrans.getObjectLike(tempPE->baseName, 0);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 3317 "parser.y"
    {
    ObjectLikeElement* tempPE = new ObjectLikeElement();
    tempPE->baseName = "false";
    tempPE->objRef = mainTrans.getObjectLike(tempPE->baseName, 0);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 3324 "parser.y"
    {
    ObjectLikeElement* tempPE = new ObjectLikeElement();
    tempPE->baseName = "none";
    tempPE->objRef = mainTrans.getObjectLike(tempPE->baseName, 0);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 3331 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 3337 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 3341 "parser.y"
    {
    (yyval.parseElement) = NULL;
    if((yyvsp[(2) - (3)].parseElement) != NULL)
    {
        (yyval.parseElement) = (yyvsp[(2) - (3)].parseElement);
        (yyval.parseElement)->parenBefore = true;
        (yyval.parseElement)->parenAfter = true;
    }
;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 3353 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 3357 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_PLUS;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 3365 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_MINUS;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 3373 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_TIMES;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 3381 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_DIVIDE;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 3389 "parser.y"
    {
    SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
    tempPE->opType = SimpleBinaryOperator::BOP_MOD;
    tempPE->preOp = (yyvsp[(1) - (3)].parseElement);
    tempPE->postOp = (yyvsp[(3) - (3)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 3397 "parser.y"
    {
    SimpleUnaryOperator* tempPE = new SimpleUnaryOperator();
    tempPE->opType = SimpleUnaryOperator::UOP_ABS;
    tempPE->postOp = (yyvsp[(2) - (2)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 3404 "parser.y"
    {
    // Not necessary to flag parenBefore and parenAfter, translation of abs
    // automatically adds parentheses around the expression.
    SimpleUnaryOperator* tempPE = new SimpleUnaryOperator();
    tempPE->opType = SimpleUnaryOperator::UOP_ABS;
    tempPE->postOp = (yyvsp[(3) - (4)].parseElement);
    (yyval.parseElement) = tempPE;
;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 3415 "parser.y"
    {
    ObjectLikeElement* tempPE = new ObjectLikeElement();
    tempPE->baseName = *(yyvsp[(1) - (1)].str);
    tempPE->objRef = mainTrans.getObjectLike(tempPE->baseName, 0);
    (yyval.parseElement) = tempPE;
    deallocateItem((yyvsp[(1) - (1)].str));
;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 3423 "parser.y"
    {
    (yyval.parseElement) = (yyvsp[(1) - (1)].parseElement);
;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 3429 "parser.y"
    {
    (yyval.numRange) = new NumberRange();
    std::string tempStr = (*(yyvsp[(1) - (3)].str));
    tempStr += "..";
    tempStr += (*(yyvsp[(3) - (3)].str));
    (yyval.numRange)->name = tempStr;
    (yyval.numRange)->transName = Translator::sanitizeObjectName(tempStr);
    (yyval.numRange)->min = (*(yyvsp[(1) - (3)].str));
    (yyval.numRange)->max = (*(yyvsp[(3) - (3)].str));
    deallocateItem((yyvsp[(1) - (3)].str));
    deallocateItem((yyvsp[(3) - (3)].str));
;}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 3444 "parser.y"
    {
    (yyval.str) = new std::string();
    (*(yyval.str)) = utils::to_string((yyvsp[(1) - (1)].integer));
;}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 3449 "parser.y"
    {
    (yyval.str) = new std::string;
    (*(yyval.str)) = "maxAdditive";
;}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 3454 "parser.y"
    {
    (yyval.str) = new std::string;
    (*(yyval.str)) = "maxstep";
;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 3459 "parser.y"
    {
    (yyval.str) = new std::string();
    (*(yyval.str)) = "-";
    (*(yyval.str)) += (*(yyvsp[(2) - (2)].str));
    deallocateItem((yyvsp[(2) - (2)].str));
;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 3468 "parser.y"
    {
    (yyval.str) = (yyvsp[(1) - (1)].str);
;}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 3472 "parser.y"
    {
    (yyval.str) = new std::string();
    (*(yyval.str)) += "(";
    (*(yyval.str)) += (*(yyvsp[(2) - (3)].str));
    (*(yyval.str)) += ")";
    deallocateItem((yyvsp[(2) - (3)].str));
;}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 3482 "parser.y"
    {
    (yyval.str) = (yyvsp[(1) - (1)].str);
;}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 3486 "parser.y"
    {
    (yyval.str) = new std::string();
    (*(yyval.str)) += (*(yyvsp[(1) - (3)].str));
    (*(yyval.str)) += " + ";
    (*(yyval.str)) += (*(yyvsp[(3) - (3)].str));
    deallocateItem((yyvsp[(1) - (3)].str));
    deallocateItem((yyvsp[(3) - (3)].str));
;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 3495 "parser.y"
    {
    (yyval.str) = new std::string();
    (*(yyval.str)) += (*(yyvsp[(1) - (3)].str));
    (*(yyval.str)) += " - ";
    (*(yyval.str)) += (*(yyvsp[(3) - (3)].str));
    deallocateItem((yyvsp[(1) - (3)].str));
    deallocateItem((yyvsp[(3) - (3)].str));
;}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 3504 "parser.y"
    {
    (yyval.str) = new std::string();
    (*(yyval.str)) += (*(yyvsp[(1) - (3)].str));
    (*(yyval.str)) += " * ";
    (*(yyval.str)) += (*(yyvsp[(3) - (3)].str));
    deallocateItem((yyvsp[(1) - (3)].str));
    deallocateItem((yyvsp[(3) - (3)].str));
;}
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 3513 "parser.y"
    {
    (yyval.str) = new std::string();
    (*(yyval.str)) += (*(yyvsp[(1) - (3)].str));
    (*(yyval.str)) += " // ";
    (*(yyval.str)) += (*(yyvsp[(3) - (3)].str));
    deallocateItem((yyvsp[(1) - (3)].str));
    deallocateItem((yyvsp[(3) - (3)].str));
;}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 3522 "parser.y"
    {
    (yyval.str) = new std::string();
    (*(yyval.str)) += (*(yyvsp[(1) - (3)].str));
    (*(yyval.str)) += " mod ";
    (*(yyval.str)) += (*(yyvsp[(3) - (3)].str));
    deallocateItem((yyvsp[(1) - (3)].str));
    deallocateItem((yyvsp[(3) - (3)].str));
;}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 3534 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 3538 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 3542 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 3548 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 3554 "parser.y"
    {
    (yyval.integer) = T_UMINUS;
;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 3558 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 3564 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 3570 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 3574 "parser.y"
    {
    // This means "less than in sorted order", which can be safely approximated with !=.
    (yyval.integer) = (yyvsp[(2) - (2)].integer);
;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 3579 "parser.y"
    {
    // This means "greater than in sorted order", which can be safely approximated with !=.
    (yyval.integer) = (yyvsp[(2) - (2)].integer);
;}
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 3586 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 3590 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 3594 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 3598 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 3602 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 3608 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 3614 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 3620 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 3624 "parser.y"
    {
    // This means "less than or equal to in sorted order", which has no good approximation except for <=.
    (yyval.integer) = (yyvsp[(2) - (2)].integer);
;}
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 3631 "parser.y"
    {
    (yyval.integer) = (yyvsp[(1) - (1)].integer);
;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 3635 "parser.y"
    {
    // This means "greater than or equal to in sorted order", which has no good approximation except for >=.
    (yyval.integer) = (yyvsp[(2) - (2)].integer);
;}
    break;



/* Line 1455 of yacc.c  */
#line 7244 "parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 3641 "parser.y"


// Tries to create a Sort out of an identifier and (possibly empty) subsort list.
Sort* processSort(std::string* sortIdent, std::list<Sort*>* subsorts)
{
    Sort* retVal = NULL;
    bool alreadyDeclared = true;
    // Add the sort if it isn't already in the symbol table.
    retVal = mainTrans.getSort(*sortIdent);
    if(retVal == NULL)
    {
        alreadyDeclared = false;
        retVal = new Sort(*sortIdent, Translator::sanitizeSortName(*sortIdent));
        int addSymResult = mainTrans.addSort(retVal);
        if(addSymResult != SymbolTable::ADDSYM_OK)
        {
            if(addSymResult == SymbolTable::ADDSYM_DUP)
            {   // Warn about duplicate sort declarations (not an error), then grab the already-declared sort.
                // Shouldn't encounter this bit of code, the getSort call earlier should take care of the "already exists" case.
                ltsyystartCaution(ltsyylloc);
                ltsyyossErr << "Duplicate sort declaration: \"" << *sortIdent << "\".";
                ltsyyreportCaution();
                deallocateItem(retVal);
                retVal = mainTrans.getSort(*sortIdent);
                alreadyDeclared = true;
            }
            else
            {   // Report a real sort error.
                ltsyystartParseError(ltsyylloc);
                ltsyyossErr << "Bad sort declaration: \"" << *sortIdent << "\".";
                ltsyyreportError();
                deallocateItem(retVal);
            }
        }
        else
        {
            // Try to create (or get) a default variable for the sort, connect the two if nothing goes wrong.
            std::string tempName = retVal->fullName();
            std::string tempTransName = retVal->fullTransName();
            std::string tempVarName = Translator::sortNameToVariable(tempName);
            Variable* tempVar = mainTrans.getVariable(tempVarName);
            if(tempVar == NULL)
            {
                std::string tempTransVarName = Translator::sortNameToVariable(tempTransName);
                tempVar = new Variable(tempVarName, tempTransVarName);
                if(mainTrans.addVariable(tempVar) != SymbolTable::ADDSYM_OK)
                {
                    deallocateItem(tempVar);
                    ltsyystartParseError(ltsyylloc);
                    ltsyyossErr << "Could not create default variable \"" << tempVarName << "\" ";
                    ltsyyossErr << "for sort \"" << tempName << "\".";
                    ltsyyreportError();
                    retVal = NULL; // Won't affect the translator's storage of the (incomplete) sort.
                }
                else
                {
                    tempVar->sortRef = retVal;
                }
            }
            if(tempVar != NULL)
            {
                retVal->sortVar = tempVar;
            }
        }
    }
    // Add subsorts to the sort's list.
    if(retVal != NULL && subsorts != NULL)
    {
        for(std::list<Sort*>::iterator lIter = subsorts->begin(); lIter != subsorts->end(); ++lIter)
        {
            if((*lIter) != NULL)
            {
                retVal->subsorts.push_back((*lIter));
                // If the sort was already declared and we're just adding subsorts,
                // perform the translation now.
                if(alreadyDeclared)
                {
                    mainTrans.translateSubsortDecl(retVal,*lIter);
                }
            }
        }
    }
    // If the sort is new and is a "something*" sort, make sure its child ("something")
    // is declared too, and link them together.
    if(!alreadyDeclared && sortIdent->length() > 0 && (*sortIdent)[sortIdent->length()-1] == '*')
    {
        // Now find/create the child "something" sort.
        std::string* nonStarIdent = new std::string;
        (*nonStarIdent) = sortIdent->substr(0, sortIdent->length()-1);

        // Check if the child already exists before proceeding with declaration etc.
        Sort *nonStarSort = mainTrans.getSort(*nonStarIdent);
        if(nonStarSort == NULL)
        {   // Declare "something" so it can be added as the child of "something*".
            std::list<Sort*>* nonStarSubsorts = new std::list<Sort*>; // Empty on purpose.
            nonStarSort = processSort(nonStarIdent, nonStarSubsorts);
            deallocateList(nonStarSubsorts);
        }
        if(nonStarSort != NULL)
        {
            // Add "something" to subsorts.
            retVal->subsorts.push_back(nonStarSort);
        }
        deallocateItem(nonStarIdent);

        // Create an object "none" and associate it with the "something*" sort.
        std::string noneName = "none";
        Object* noneObj = new Object(noneName, Translator::sanitizeObjectName(noneName));
        int noneAddResult = mainTrans.addObject(noneObj);
        if(noneAddResult == SymbolTable::ADDSYM_OK)
        {
            retVal->domainObjs.push_back(noneObj);
            // Output the translation of the object declaration.
            mainTrans.translateObjectDecl(noneObj, retVal);
        }
    }
    // If the sort is new, output its translated declaration.
    if(!alreadyDeclared)
    {
        mainTrans.translateSortDecl(retVal);
    }
    return retVal;
}

// Tries to find an existing normal sort or declare a starred ("something*") sort.
Sort* checkDynamicSortDecl(std::string* sortIdent)
{
    Sort* retVal = mainTrans.getSort(*sortIdent);
    // Allow dynamic instantiation of starred sorts.
    if(retVal == NULL && sortIdent->length() > 0 && (*sortIdent)[sortIdent->length()-1] == '*')
    {
        // Verify that the non-starred version exists before instantiating the starred version.
        std::string* nonStarIdent = new std::string;
        (*nonStarIdent) = sortIdent->substr(0, sortIdent->length()-1);
        Sort *nonStarSort = mainTrans.getSort(*nonStarIdent);
        if(nonStarSort == NULL)
        {
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "Sort \"" << *nonStarIdent << "\" not declared, can't dynamically use \"" << *sortIdent << "\" as the domain of another declaration.";
            ltsyyreportError();
        }
        else
        {
            // Instantiate the starred version, link to child.
            std::list<Sort*>* starSubsorts = new std::list<Sort*>;
            // No need to add unstarred version to subsorts, that's done automatically.
            retVal = processSort(sortIdent, starSubsorts);
            if(retVal == NULL)
            {
                ltsyystartParseError(ltsyylloc);
                ltsyyossErr << "Bad domain declaration \"" << *sortIdent << "\".";
                ltsyyreportError();
            }
            deallocateList(starSubsorts);
        }
        deallocateItem(nonStarIdent);
    }
    else if(retVal == NULL)
    {   // The domain isn't an undeclared starred case, it's just undeclared.
        ltsyystartParseError(ltsyylloc);
        ltsyyossErr << "Sort \"" << *sortIdent << "\" not declared, can't use as the domain of another declaration.";
        ltsyyreportError();
    }
    return retVal;
}

// Transforms declarative laws ("inertial p", "exogenous a(X)", "rigid q", etc.) to basic form and calls the translator for them.
bool handleDeclarativeLaw(ParseElement* head, ParseElement* ifBody, ParseElement* afterBody, ParseElement* whereBody, SimpleUnaryOperator::UnaryOperatorType opType)
{
    bool retVal = false; // Start pessimistic.
    if(head != NULL)
    {
        // head needs to be wrapped in the appropriate declarative operator.
        SimpleUnaryOperator* tempPE = new SimpleUnaryOperator();
        tempPE->opType = opType;
        tempPE->postOp = head;
        // This law becomes "delaration(F) [if G] [after H] [where J]."
        mainTrans.translateCausalLaw(tempPE, ifBody, afterBody, NULL, whereBody);
        retVal = true;
        deallocateTempUnaryOp(tempPE);
    }
    return retVal;
}

// Transforms a causal law of the form "always F [where G]." to basic form, then calls the translator for it.
bool handleAlwaysLaw(ParseElement* constraint, ParseElement* whereBody)
{
    bool retVal = false; // Start pessimistic.
    if(constraint != NULL)
    {
        // "not constraint" is the afterBody.
        SimpleUnaryOperator* tempPE = new SimpleUnaryOperator();
        tempPE->opType = SimpleUnaryOperator::UOP_NOT;
        tempPE->postOp = constraint;
        // The head is "false".
        ObjectLikeElement* tempObj = new ObjectLikeElement();
        tempObj->baseName = "false";
        tempObj->objRef = mainTrans.getObjectLike(tempObj->baseName, 0);
        // The law becomes "caused false after -F where H."
        mainTrans.translateCausalLaw(tempObj, NULL, tempPE, NULL, whereBody);
        delete tempObj;
        deallocateTempUnaryOp(tempPE);
        retVal = true;
    }
    return retVal;
}

// Transforms a causal law of the form "constraint F [after H] [where J]." to basic form, then calls the translator for it.
bool handleConstraintLaw(ParseElement* constraint, ParseElement* afterBody, ParseElement* unlessBody, ParseElement* whereBody)
{
    bool retVal = false; // Start pessimistic.
    if(constraint != NULL)
    {
        // constraint has to be a fluent formula or the law is malformed. Soft warn if we can't tell what it is (i.e., not a fluent or action formula).
        if(!constraint->hasActions())
        {
            if(!constraint->hasFluents())
            {
                ltsyystartWarning(ltsyylloc);
                ltsyyossErr << "Cannot determine if \"" << constraint->fullName() << "\" is a fluent formula or not, it might not work as F in a \"constraint F\" style law.";
                ltsyyreportWarning();
            }

            // "not constraint" is the ifBody.
            SimpleUnaryOperator* tempUOP = NULL;
            ParseElement* tempPE = NULL; // Points at whatever ends up becoming the head of the rule.
            // If the constraint is "not something", then we can just drop the not (we'd end up with "not not something", which is equivalent to "something" since "false" is the head).
            if(constraint->elemType == ParseElement::PELEM_UOP && ((SimpleUnaryOperator*)constraint)->opType == SimpleUnaryOperator::UOP_NOT)
            {
                tempPE = ((SimpleUnaryOperator*)constraint)->postOp;
            }
            else
            {   // It's not an optimizable case, just tack "not" onto the constraint.
                tempUOP = new SimpleUnaryOperator();
                tempUOP->opType = SimpleUnaryOperator::UOP_NOT;
                tempUOP->postOp = constraint;
                tempPE = (ParseElement*)tempUOP;
            }

            // The head is "false".
            ObjectLikeElement* tempObj = new ObjectLikeElement();
            tempObj->baseName = "false";
            tempObj->objRef = mainTrans.getObjectLike(tempObj->baseName, 0);
            // The law becomes "caused false if -F after G where H."
            mainTrans.translateCausalLaw(tempObj, tempPE, afterBody, unlessBody, whereBody);
            delete tempObj;
            deallocateTempUnaryOp(tempUOP);
            retVal = true;
        }
        else
        {
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "\"" << constraint->fullName() << "\" is not a fluent formula, can't use it as F in a \"constraint F\" style law.";
            ltsyyreportError();
        }
    }
    return retVal;
}

// Transforms a causal law of the form "default F [if G] [after H] [where J]." to basic form, then calls the translator on it.
bool handleDefaultLaw(ParseElement* head, ParseElement* ifBody, ParseElement* afterBody, ParseElement* whereBody)
{
    bool retVal = false; // Start pessimistic.
    if(head != NULL)
    {
        // head and ifBody are going to end up together no matter what.
        SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
        tempPE->opType = SimpleBinaryOperator::BOP_AND;
        tempPE->preOp = head;
        tempPE->postOp = ifBody;
        // This law becomes "caused F if F [& G] [after H] [where J]."
        mainTrans.translateCausalLaw(head, tempPE, afterBody, NULL, whereBody);
        retVal = true;
        deallocateTempBinaryOp(tempPE);
    }
    return retVal;
}

// Transforms a causal law of the form "nonexecutable F [if G] [where H]." to basic form, then calls the translator for it.
bool handleNonexecutableLaw(ParseElement* nonEx, ParseElement* ifBody, ParseElement* whereBody)
{
    bool retVal = false; // Start pessimistic.
    if(nonEx != NULL)
    {
        // nonEx has to be an action formula or the law is malformed. Soft warn if its neither kind of formula.
        if(!nonEx->hasFluents())
        {
            if(!nonEx->hasActions())
            {
                ltsyystartWarning(ltsyylloc);
                ltsyyossErr << "Cannot determine if \"" << nonEx->fullName() << "\" is an action formula or not, it might not work as F in a \"nonexecutable F\" style law.";
                ltsyyreportWarning();
            }
            // nonEx and ifBody are going to end up together no matter what.
            SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
            tempPE->opType = SimpleBinaryOperator::BOP_AND;
            tempPE->preOp = nonEx;
            tempPE->postOp = ifBody;
            // Create a head of "false".
            ObjectLikeElement* tempObj = new ObjectLikeElement();
            tempObj->baseName = "false";
            tempObj->objRef = mainTrans.getObjectLike(tempObj->baseName, 0);
            mainTrans.translateCausalLaw(tempObj, NULL, tempPE, NULL, whereBody);
            delete tempObj;
            deallocateTempBinaryOp(tempPE);
            retVal = true;
        }
        else
        {
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "\"" << nonEx->fullName() << "\" is not an action formula, can't use it as F in a \"nonexecutable F\" style law.";
            ltsyyreportError();
        }
    }
    return retVal;
}

// Transforms a causal law of the form "possibly caused F [if G] [after H] [where J]." to basic form, then calls the translator on it.
bool handlePossiblyCausedLaw(ParseElement* head, ParseElement* ifBody, ParseElement* afterBody, ParseElement* whereBody)
{
    bool retVal = false; // Start pessimistic.
    if(head != NULL)
    {
        // head and ifBody are going to end up together no matter what.
        SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
        tempPE->opType = SimpleBinaryOperator::BOP_AND;
        tempPE->preOp = head;
        tempPE->postOp = ifBody;
        // This law becomes "caused F if F [& G] [after H] [where J]."
        mainTrans.translateCausalLaw(head, tempPE, afterBody, NULL, whereBody);
        retVal = true;
        deallocateTempBinaryOp(tempPE);
    }
    return retVal;
}

// Transforms a causal law of the form "G may cause F [if H] [where J]." to basic form, then calls the translator on it.
bool handleMayCauseLaw(ParseElement* causer, ParseElement* causee, ParseElement* ifBody, ParseElement* whereBody)
{
    bool retVal = false; // Start pessimistic.
    if(causer != NULL && causee != NULL)
    {
        // Causer has to be an action formula, or the law is not properly written.
        if(causer->hasActions() && !causer->hasFluents())
        {
            // Causer and ifBody are going to end up together no matter what.
            SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
            tempPE->opType = SimpleBinaryOperator::BOP_AND;
            tempPE->preOp = causer;
            tempPE->postOp = ifBody;
            // Where causer and ifBody end up in the basic form depend on what's in causee.
            if(causee->hasActions() && !causee->hasFluents())
            {   // Causee is an action formula, this is "caused F if F & G & H".
                // Merge F into G & H.
                SimpleBinaryOperator* tempPE2 = new SimpleBinaryOperator();
                tempPE2->opType = SimpleBinaryOperator::BOP_AND;
                tempPE2->preOp = causee;
                tempPE2->postOp = tempPE;
                mainTrans.translateCausalLaw(causee, tempPE2, NULL, NULL, whereBody);
                retVal = true;
                deallocateTempBinaryOp(tempPE2);
            }
            else if(!causee->hasActions() && causee->hasFluents())
            {   // Causee is a fluent formula, this is "caused F if F after G & H".
                mainTrans.translateCausalLaw(causee, causee, tempPE, NULL, whereBody);
                retVal = true;
            }
            else
            {   // Causee is mixed, that isn't allowed.
                ltsyystartParseError(ltsyylloc);
                ltsyyossErr << "\"" << causee->fullName() << "\" must be a pure action formula or pure fluent formula in this law, it can't have both kinds of constants.";
                ltsyyreportError();
            }
            deallocateTempBinaryOp(tempPE);
        }
        else
        {
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "\"" << causer->fullName() << "\" is not an action formula, can't use it as G in a \"G may cause F\" style law.";
            ltsyyreportError();
        }
    }
    return retVal;
}

// Transforms a causal law of the form "G causes F [if H] [where J]." to basic form, then calls the translator on it.
bool handleCausesLaw(ParseElement* causer, ParseElement* causee, ParseElement* ifBody, ParseElement* whereBody)
{
    bool retVal = false; // Start pessimistic.
    if(causer != NULL && causee != NULL)
    {
        // Causer has to be an action formula, or the law is not properly written.
        if(causer->hasActions() && !causer->hasFluents())
        {
            // Causer and ifBody are going to end up together no matter what.
            SimpleBinaryOperator* tempPE = new SimpleBinaryOperator();
            tempPE->opType = SimpleBinaryOperator::BOP_AND;
            tempPE->preOp = causer;
            tempPE->postOp = ifBody;
            // Where causer and ifBody end up in the basic form depend on what's in causee.
            if((causee->hasActions() && !causee->hasFluents()) || causee->elemType == ParseElement::PELEM_OBJLIKE)
            {   // Causee is an action formula, this is "caused F if G".
                mainTrans.translateCausalLaw(causee, tempPE, NULL, NULL, whereBody);
                retVal = true;
            }
            else if(!causee->hasActions() && causee->hasFluents())
            {   // Causee is a fluent formula, this is "caused F after G".
                mainTrans.translateCausalLaw(causee, NULL, tempPE, NULL, whereBody);
                retVal = true;
            }
            else
            {   // Causee is mixed, that isn't allowed.
                ltsyystartParseError(ltsyylloc);
                ltsyyossErr << "\"" << causee->fullName() << "\" must be a pure action formula or pure fluent formula in this law, it can't have both kinds of constants.";
                ltsyyreportError();
            }
            deallocateTempBinaryOp(tempPE);
        }
        else
        {
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "\"" << causer->fullName() << "\" is not an action formula, can't use it as G in a \"G causes F\" style law.";
            ltsyyreportError();
        }
    }
    return retVal;
}

// Transforms an increment law of the form "A increments B by N [if H] [where J]." to basic form, then calls the translator on it.
bool handleIncrementLaw(ParseElement* causer, ParseElement* causee, ParseElement* increment, ParseElement* ifBody, ParseElement* whereBody, bool isIncrement)
{
    SimpleBinaryOperator* inc_expr = NULL;
    SimpleBinaryOperator* negative_expr = NULL;
    VariableLikeElement* x_val = NULL;
    ObjectLikeElement* tempNegOnePE = NULL;
    SimpleBinaryOperator* tempPE = NULL;
    SimpleBinaryOperator* newCausee = NULL;
    Constant* constRef;
    bool retVal = false; // Start pessimistic.
    if(causer != NULL && causee != NULL)
    {
        // Causer has to be a single action, or the law is not properly written.
        if(causer->hasActions() && causer->elemType == ParseElement::PELEM_CONSTLIKE && !causer->hasFluents())
        {
            // Causer and ifBody are going to end up together no matter what.

            //define the expression of the increment variable, X_VAL
            inc_expr = new SimpleBinaryOperator();
            inc_expr->opType = SimpleBinaryOperator::BOP_EQ;

            x_val = new VariableLikeElement();
            x_val->baseName = "X_Value";
            x_val->varRef = NULL;
            inc_expr->preOp = x_val;

            if(isIncrement)
            {
                increment->parenBefore = true;
                increment->parenAfter = true;
                inc_expr->postOp = increment;
            }
            else //multiply by -1
            {
                negative_expr = new SimpleBinaryOperator();
                negative_expr->opType = SimpleBinaryOperator::BOP_TIMES;

                tempNegOnePE = new ObjectLikeElement();
                tempNegOnePE->baseName = "-1";
                //tempNegOnePE->objRef = mainTrans.getObjectLike("-1", 0);
                tempNegOnePE->objRef = NULL;
                tempNegOnePE->parenBefore = true;
                tempNegOnePE->parenAfter = true;
                increment->parenBefore = true;
                increment->parenAfter = true;
                negative_expr->preOp = tempNegOnePE;
                negative_expr->postOp = increment;
                inc_expr->postOp = negative_expr;
            }

            //add the expression to the whereBody
            SimpleBinaryOperator* tempWherePE = NULL;
            if(whereBody != NULL)
            {
                tempWherePE = new SimpleBinaryOperator();
                tempWherePE->opType = SimpleBinaryOperator::BOP_AND;
                whereBody->parenBefore = true;
                whereBody->parenAfter = true;
                tempWherePE->preOp = whereBody;
                tempWherePE->postOp = inc_expr;
            }
            else
            {
                tempWherePE = inc_expr;
            }

            tempPE = new SimpleBinaryOperator();
            tempPE->opType = SimpleBinaryOperator::BOP_AND;
            tempPE->preOp = causer;
            tempPE->postOp = ifBody;
            // Causee must be a single constant-like additive fluent or additive action.
            if(causee->elemType == ParseElement::PELEM_CONSTLIKE)
            {
                if(((ConstantLikeElement*)causee)->constRef->constType == Constant::CONST_ADDITIVEACTION || ((ConstantLikeElement*)causee)->constRef->constType == Constant::CONST_ADDITIVEFLUENT)
                {
                    // Create contribution element.
                    newCausee = new SimpleBinaryOperator();
                    newCausee->opType = SimpleBinaryOperator::BOP_EQ;
                    ConstantLikeElement* contrib = new ConstantLikeElement();
                    std::string contrib_str("contribution");
                    contrib->baseName = contrib_str;
                    // To avoid a weird translation, temporarily create object-like versions of causer and causee and use those instead.
                    ObjectLikeElement *tempCauser = createObjLikeFromConstLike((ConstantLikeElement*)causer);
                    ObjectLikeElement *tempCausee = createObjLikeFromConstLike((ConstantLikeElement*)causee);
                    contrib->params.push_back(tempCauser);
                    contrib->params.push_back(tempCausee);
                    constRef = mainTrans.getConstantLike(contrib_str,2);
                    contrib->constRef = constRef;
                    newCausee->preOp = contrib;
                    newCausee->postOp = x_val;

                    mainTrans.translateCausalLaw(newCausee, tempPE, NULL, NULL, tempWherePE);
                    retVal = true;
                    deallocateTempBinaryOp(newCausee);
                    contrib->params.clear();
                    deallocateItem(contrib);
                    tempCauser->params.clear();
                    deallocateItem(tempCauser);
                    tempCausee->params.clear();
                    deallocateItem(tempCausee);
                }
                else
                {
                    ltsyystartParseError(ltsyylloc);
                    ltsyyossErr << "\"" << causee->fullName() << "\" is not an additive constant, can't use it as B in a \"A increments B by N\" style law.";
                    ltsyyreportError();
                }
            }
            else
            {
                ltsyystartParseError(ltsyylloc);
                ltsyyossErr << "\"" << causer->fullName() << "\" is not a single additive constant, can't use it as B in a \"A increments B by N\" style law.";
                ltsyyreportError();
            }
            deallocateTempBinaryOp(tempWherePE);
            deallocateTempBinaryOp(tempPE);
        }
        else
        {
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "\"" << causer->fullName() << "\" is not a single action, can't use it as A in a \"A increments B by N\" style law.";
            ltsyyreportError();
        }
    }
    return retVal;
}

bool handleMacroActionDefLaw( ParseElement* mname, std::list<std::pair<ParseElement*, ParseElement*> *> *mcont)
{
    bool retVal = false;
    if (mname != NULL)
    {
        ConstantLikeElement* cname = (ConstantLikeElement*) (mname);
        if (cname->constRef == NULL || cname->constRef->constType != Constant::CONST_MACROACTION)
        {

            // Causee is mixed, that isn't allowed.
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "\"" << mname->fullName() << "\" is not an macro action formula, can't use it in a \"M is M1;M2.\" style law.";
            ltsyyreportError();
        }
        else if (mcont->size() < 1)
        {
            ltsyystartParseError(ltsyylloc);
            ltsyyossErr << "\"" << mname->fullName() << "\"" << " has defined less than two actions, which is not allowed.";
            ltsyyreportError();
        }
        else
        {
            mainTrans.translateMacroActionDefLaw(mname, mcont);
            retVal = true;
        }

    }

    return retVal;
}
// Wraps the given element in two new negation operators to create a "not not (...)" wrap.
SimpleUnaryOperator* createNotNot(ParseElement* elem)
{
    SimpleUnaryOperator* retVal = NULL;
    if(elem != NULL)
    {
        elem->parenBefore = true;
        elem->parenAfter = true;
        SimpleUnaryOperator* tempNotNot1 = new SimpleUnaryOperator();
        SimpleUnaryOperator* tempNotNot2 = new SimpleUnaryOperator();
        tempNotNot1->opType = SimpleUnaryOperator::UOP_NOT;
        tempNotNot1->postOp = elem;
        tempNotNot2->opType = SimpleUnaryOperator::UOP_NOT;
        tempNotNot2->postOp = tempNotNot1;
        retVal = tempNotNot2;
    }
    return retVal;
}

// Creates an object-like element that mirrors the contents of elem.
ObjectLikeElement* createObjLikeFromConstLike(ConstantLikeElement* elem)
{
    ObjectLikeElement* retVal = NULL;

    if(elem != NULL)
    {
        retVal = new ObjectLikeElement();
        retVal->baseName = elem->baseName;
        retVal->params = elem->params;
        retVal->objRef = NULL;
    }

    return retVal;
}

// Deallocates a "not not" wrapper such that the original ParseElement is not touched, and returns the original ParseElement object.
ParseElement* deallocateNotNot(SimpleUnaryOperator* uop)
{
    ParseElement* retVal = NULL;
    if(uop != NULL)
    {
        if(uop->postOp != NULL)
        {
            retVal = ((SimpleUnaryOperator*)(uop->postOp))->postOp;
            ((SimpleUnaryOperator*)(uop->postOp))->postOp->parenBefore = false;
            ((SimpleUnaryOperator*)(uop->postOp))->postOp->parenAfter = false;
            ((SimpleUnaryOperator*)(uop->postOp))->postOp = NULL;
            delete uop->postOp;
            uop->postOp = NULL;
        }
        delete uop;
        uop = NULL;
    }
    return retVal;
}

// NULLs elem's preOp and postOp before deallocating so the sub-ParseElement objects don't get caught in the deallocation.
void deallocateTempBinaryOp(SimpleBinaryOperator* &elem)
{
    if(elem != NULL)
    {
        elem->preOp = NULL;
        elem->postOp = NULL;
        delete elem;
        elem = NULL;
    }
}

// NULLs elem's postOp before deallocating so the sub-ParseElement object doesn't get caught in the deallocation.
void deallocateTempUnaryOp(SimpleUnaryOperator* &elem)
{
    if(elem != NULL)
    {
        elem->postOp = NULL;
        delete elem;
        elem = NULL;
    }
}

// Adds a standard parsing caution header to ltsyyossErr.
void ltsyystartCaution(YYLTYPE cautionLoc)
{
    ltsyyossErr << "% Caution, ";
    if(ltsyyFileName != "")
    {
        ltsyyossErr << "File \"" << ltsyyFileName << "\", ";
    }
    ltsyyossErr << "Line #" << cautionLoc.first_line << "." << cautionLoc.first_column << ": ";
}

// Adds a standard (location-unaware) parsing caution header to ltsyyossErr.
void ltsyystartCaution()
{
    ltsyyossErr << "% Caution, ";
    if(ltsyyFileName != "")
    {
        ltsyyossErr << "File \"" << ltsyyFileName << "\"";
    }
    ltsyyossErr << ": ";
}

// Caution reporting function for the parser.
void ltsyycaution()
{
    if(ltsyyossErr.str() == "")
    {
        ltsyystartCaution(ltsyylloc);
        ltsyyossErr << "Using \"" << ltsyytext << "\" here may not be a good idea.";
    }
    mainTrans.error(ltsyyossErr, true);
    LTSYYRESETOSS;
}

// Adds a standard parsing warning header to ltsyyossErr.
void ltsyystartWarning(YYLTYPE warningLoc)
{
    ltsyyossErr << "% Warning, ";
    if(ltsyyFileName != "")
    {
        ltsyyossErr << "File \"" << ltsyyFileName << "\", ";
    }
    ltsyyossErr << "Line #" << warningLoc.first_line << "." << warningLoc.first_column << ": ";
}

// Adds a standard (location-unaware) parsing warning header to ltsyyossErr.
void ltsyystartWarning()
{
    ltsyyossErr << "% Warning, ";
    if(ltsyyFileName != "")
    {
        ltsyyossErr << "File \"" << ltsyyFileName << "\"";
    }
    ltsyyossErr << ": ";
}

// Warning reporting function for the parser.
void ltsyywarning()
{
    if(ltsyyossErr.str() == "")
    {
        ltsyystartWarning(ltsyylloc);
        ltsyyossErr << "Using \"" << ltsyytext << "\" here will probably break something.";
    }
    mainTrans.error(ltsyyossErr, true);
    LTSYYRESETOSS;
}

// Adds a standard parse error header to ltsyyossErr to make it easier to report errors in actions.
void ltsyystartParseError(YYLTYPE errLoc)
{
    ltsyyossErr << "% Parse Error, ";
    if(ltsyyFileName != "")
    {
        ltsyyossErr << "File \"" << ltsyyFileName << "\", ";
    }
    ltsyyossErr << "Line #" << errLoc.first_line << "." << errLoc.first_column << ": ";
}

// Adds a standard (location-unaware) parse error header to ltsyyossErr to make it easier to report errors in actions.
void ltsyystartParseError()
{
    ltsyyossErr << "% Parse Error, ";
    if(ltsyyFileName != "")
    {
        ltsyyossErr << "File \"" << ltsyyFileName << "\"";
    }
    ltsyyossErr << ": ";
}

// Adds a standard syntax error header to ltsyyossErr to make it easier to report errors in actions.
void ltsyystartSyntaxError(YYLTYPE errLoc)
{
    ltsyyossErr << "% Syntax Error, ";
    if(ltsyyFileName != "")
    {
        ltsyyossErr << "File \"" << ltsyyFileName << "\", ";
    }
    ltsyyossErr << "Line #" << errLoc.first_line << "." << errLoc.first_column << ": ";
}

// Adds a standard (location-unaware) syntax error header to ltsyyossErr to make it easier to report errors in actions.
void ltsyystartSyntaxError()
{
    ltsyyossErr << "% Syntax Error, ";
    if(ltsyyFileName != "")
    {
        ltsyyossErr << "File \"" << ltsyyFileName << "\"";
    }
    ltsyyossErr << ": ";
}

// Error reporting function for the bison parser.
void ltsyyerror(char const* msg)
{
    if(ltsyyossErr.str() == "")
    {
        ltsyystartSyntaxError(ltsyylloc);
        ltsyyossErr << "Unexpected token \"" << ltsyytext << "\".";
    }
    mainTrans.error(ltsyyossErr, true);
    LTSYYRESETOSS;
    // If the translator's temporary query appears to have been partially populated, destroy it and create another in its place.
    if(mainTrans.tempQuery != NULL && (mainTrans.tempQuery->label != "" || mainTrans.tempQuery->maxstep != "" || !(mainTrans.tempQuery->queryConditions.empty())))
    {
        mainTrans.allocateNewTempQuery(true);
    }
    if(mainTrans.tempQuery == NULL)
    {
        mainTrans.allocateNewTempQuery();
    }
}

// Wraps caution reporting for convenience and unification with convention for error reporting.
void ltsyyreportCaution()
{
    ltsyycaution();
}
// Wraps warning reporting for convenience and unification with convention for error reporting.
void ltsyyreportWarning()
{
    ltsyywarning();
}
// Wraps error reporting for ease and to ensure the number of errors gets incremented with each (action-generated) error report.
void ltsyyreportError()
{
    ltsyynerrs++;
    ltsyyerror("");
}

