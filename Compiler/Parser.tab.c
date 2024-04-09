/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "Parser.y"

 
#include "Data_File.h"
#include "Parser.tab.h"

static int label_address, temp_counter, flag_counter, case_counter, switch_counter, while_counter, if_counter;

/*
    Label address - keeps track of label declarations within middle file.
    Temp counter - assists in instantiating temp variables.
    Flag counter - ... boolean flags.  
    Case counter - assists in creating labels for cases within switch-case statements.
    Switch counter - ... labels for beginning and end of switch-case statements.
    While counter - ... labels for beginning and end of while loops.
    If counter - ... labels for the else statement and end-of-if.
    NOTE: 
    (I) We insert the labels into ltable before poping them, so as to save the labels and their declaration addresses (as in the middle file) for the backpatch phase.
    (II) Wherever there is a derivation rule with a singular non-terminal or terminal followed by an action ({...}), it represents a transition node within the parse tree,
    meaning it forwards information (mostly an id or a number and their type) upwards in the parse tree.
    (III) When deriving while loops and switch-case statements, we set their exit labels to the head of the label stack.
    This is in the event that a break statement will appear further in the derivation process.
    (IV) Any rules that contain the special error token in them, in the event that an error has occured, the parser will begin
    to search in the input for the delimiter that is right of the error token in the attempt to recover from the error. The parser may
    also pull symbols from its stack in its attempt to recover. Error recovery is difficult for any parser.
*/


#line 99 "Parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "Parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BREAK = 3,                      /* BREAK  */
  YYSYMBOL_CASE = 4,                       /* CASE  */
  YYSYMBOL_ELSE = 5,                       /* ELSE  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_INPUT = 7,                      /* INPUT  */
  YYSYMBOL_OUTPUT = 8,                     /* OUTPUT  */
  YYSYMBOL_SWITCH = 9,                     /* SWITCH  */
  YYSYMBOL_WHILE = 10,                     /* WHILE  */
  YYSYMBOL_RELOP = 11,                     /* RELOP  */
  YYSYMBOL_ADDOP = 12,                     /* ADDOP  */
  YYSYMBOL_MULOP = 13,                     /* MULOP  */
  YYSYMBOL_OR = 14,                        /* OR  */
  YYSYMBOL_AND = 15,                       /* AND  */
  YYSYMBOL_NOT = 16,                       /* NOT  */
  YYSYMBOL_FLOAT = 17,                     /* FLOAT  */
  YYSYMBOL_INT = 18,                       /* INT  */
  YYSYMBOL_CAST = 19,                      /* CAST  */
  YYSYMBOL_NUM = 20,                       /* NUM  */
  YYSYMBOL_ID = 21,                        /* ID  */
  YYSYMBOL_DEFAULT = 22,                   /* DEFAULT  */
  YYSYMBOL_23_ = 23,                       /* ':'  */
  YYSYMBOL_24_ = 24,                       /* ';'  */
  YYSYMBOL_25_ = 25,                       /* ','  */
  YYSYMBOL_26_ = 26,                       /* '='  */
  YYSYMBOL_27_ = 27,                       /* '('  */
  YYSYMBOL_28_ = 28,                       /* ')'  */
  YYSYMBOL_29_ = 29,                       /* '{'  */
  YYSYMBOL_30_ = 30,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_program = 32,                   /* program  */
  YYSYMBOL_declarations = 33,              /* declarations  */
  YYSYMBOL_declaration = 34,               /* declaration  */
  YYSYMBOL_type = 35,                      /* type  */
  YYSYMBOL_idlist = 36,                    /* idlist  */
  YYSYMBOL_stmt = 37,                      /* stmt  */
  YYSYMBOL_assignment_stmt = 38,           /* assignment_stmt  */
  YYSYMBOL_input_stmt = 39,                /* input_stmt  */
  YYSYMBOL_output_stmt = 40,               /* output_stmt  */
  YYSYMBOL_if_stmt = 41,                   /* if_stmt  */
  YYSYMBOL_42_1 = 42,                      /* $@1  */
  YYSYMBOL_43_2 = 43,                      /* $@2  */
  YYSYMBOL_while_stmt = 44,                /* while_stmt  */
  YYSYMBOL_45_3 = 45,                      /* $@3  */
  YYSYMBOL_var1 = 46,                      /* var1  */
  YYSYMBOL_switch_stmt = 47,               /* switch_stmt  */
  YYSYMBOL_48_4 = 48,                      /* $@4  */
  YYSYMBOL_49_5 = 49,                      /* $@5  */
  YYSYMBOL_var2 = 50,                      /* var2  */
  YYSYMBOL_caselist = 51,                  /* caselist  */
  YYSYMBOL_52_6 = 52,                      /* $@6  */
  YYSYMBOL_break_stmt = 53,                /* break_stmt  */
  YYSYMBOL_stmt_block = 54,                /* stmt_block  */
  YYSYMBOL_stmtlist = 55,                  /* stmtlist  */
  YYSYMBOL_boolexpr = 56,                  /* boolexpr  */
  YYSYMBOL_boolterm = 57,                  /* boolterm  */
  YYSYMBOL_boolfactor = 58,                /* boolfactor  */
  YYSYMBOL_expression = 59,                /* expression  */
  YYSYMBOL_term = 60,                      /* term  */
  YYSYMBOL_factor = 61                     /* factor  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   151

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  132

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   277


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      27,    28,     2,     2,    25,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    23,    24,
       2,    26,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    71,    71,    76,    78,    85,   107,   109,   114,   114,
     121,   138,   150,   150,   150,   150,   150,   150,   150,   150,
     152,   160,   199,   201,   208,   229,   234,   247,   263,   271,
     263,   292,   294,   296,   298,   309,   309,   326,   328,   330,
     332,   338,   413,   420,   413,   469,   471,   473,   475,   479,
     500,   500,   526,   545,   582,   586,   588,   594,   621,   630,
     657,   665,   677,   712,   719,   727,   735,   739,   746,   783,
     797
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "BREAK", "CASE",
  "ELSE", "IF", "INPUT", "OUTPUT", "SWITCH", "WHILE", "RELOP", "ADDOP",
  "MULOP", "OR", "AND", "NOT", "FLOAT", "INT", "CAST", "NUM", "ID",
  "DEFAULT", "':'", "';'", "','", "'='", "'('", "')'", "'{'", "'}'",
  "$accept", "program", "declarations", "declaration", "type", "idlist",
  "stmt", "assignment_stmt", "input_stmt", "output_stmt", "if_stmt", "$@1",
  "$@2", "while_stmt", "$@3", "var1", "switch_stmt", "$@4", "$@5", "var2",
  "caselist", "$@6", "break_stmt", "stmt_block", "stmtlist", "boolexpr",
  "boolterm", "boolfactor", "expression", "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-48)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-52)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -48,    14,     6,   -48,    74,   -48,   -48,   -48,    52,   -48,
     -48,   -48,     2,    94,     7,    54,    45,     3,    16,    28,
      56,    57,     0,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
     -48,   -48,   -48,   -48,   -48,    77,   -48,   -48,   -48,   -48,
      76,    72,    89,    15,    97,    75,    79,    75,    86,    95,
      99,    75,   -48,   -48,   -48,   -48,   -48,    98,   100,   -48,
     -48,    75,    10,   109,   -48,   106,   113,   -48,   -48,   101,
     -48,    58,   -48,   -48,   -48,   -48,   116,   -48,   -48,   -48,
     -48,    72,   -48,    55,    72,    75,    59,    72,   -48,    72,
      75,    75,    75,   107,   108,   102,    11,   -48,    62,    61,
     -48,   109,    53,   -48,   116,   113,   -48,   -48,   -48,   -48,
     -48,   -48,   -48,   128,   105,    53,   -48,   -48,   -48,    53,
      44,   -48,   115,   -48,   -48,   114,   117,   -48,   -48,    12,
      43,   -48
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,    11,    56,     3,     0,     2,
       6,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,    55,    12,    13,    14,    15,    16,
      17,    18,    19,     9,     8,     0,    10,    20,    22,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     5,    34,    31,    32,    33,     0,     0,    70,
      69,     0,     0,    58,    60,     0,    64,    66,    25,     0,
      27,     0,    48,    45,    46,    47,    42,    40,    37,    38,
      39,     0,    23,     0,     0,     0,     0,     0,    28,     0,
       0,     0,     0,     0,     0,     0,     0,    21,     0,     0,
      67,    57,     0,    59,    62,    63,    65,    24,    26,    49,
      35,    61,    68,     0,     0,     0,    29,    52,    36,     0,
       0,    30,     0,    43,    50,     0,     0,    56,    56,     0,
       0,    44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -48,   -48,   -48,   -48,   -48,   -48,   -34,   -48,   -48,   -48,
     -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
     -48,   -48,   -48,   134,    -8,   -47,    51,    50,   -45,    60,
      49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     7,    35,     8,    24,    25,    26,    27,
      28,   102,   119,    29,   115,    49,    30,    95,   125,   114,
     120,   126,    31,    32,    12,    62,    63,    64,    65,    66,
      67
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,    50,    76,    15,    40,    16,    83,     4,    17,    18,
      19,    20,    21,    15,     3,    16,    86,    42,    17,    18,
      19,    20,    21,    22,    87,    87,    51,     5,    36,    44,
      41,     6,    23,    22,    96,     6,    69,    98,    88,   110,
      99,     6,   131,    43,    15,   104,    16,   -51,   122,    17,
      18,    19,    20,    21,    15,    45,    16,    46,    48,    17,
      18,    19,    20,    21,    22,   -51,   123,    91,   113,    39,
      91,    91,     6,    91,    22,    13,    87,    14,    37,    97,
      38,   118,     6,    47,   -41,   121,    94,   100,    57,   112,
     111,    58,    59,    60,    58,    59,    60,    10,    11,    61,
      53,    52,    61,    72,    54,    55,    56,    73,    74,    75,
      77,    33,    34,    68,    78,    79,    80,    90,    91,   129,
     130,    70,    81,    82,    89,    84,    92,    85,    91,    93,
     109,   107,   108,   116,   117,   124,     9,   127,   101,   103,
     128,   106,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105
};

static const yytype_int16 yycheck[] =
{
      45,     1,    47,     1,     1,     3,    51,     1,     6,     7,
       8,     9,    10,     1,     0,     3,    61,     1,     6,     7,
       8,     9,    10,    21,    14,    14,    26,    21,    21,     1,
      27,    29,    30,    21,    81,    29,    21,    84,    28,    28,
      85,    29,    30,    27,     1,    90,     3,     4,     4,     6,
       7,     8,     9,    10,     1,    27,     3,     1,     1,     6,
       7,     8,     9,    10,    21,    22,    22,    12,   102,    24,
      12,    12,    29,    12,    21,    23,    14,    25,    24,    24,
      26,   115,    29,    27,    27,   119,    28,    28,    16,    28,
      28,    19,    20,    21,    19,    20,    21,    23,    24,    27,
      24,    24,    27,    24,    28,    29,    30,    28,    29,    30,
      24,    17,    18,    24,    28,    29,    30,    11,    12,   127,
     128,    24,    27,    24,    15,    27,    13,    27,    12,    28,
      28,    24,    24,     5,    29,    20,     2,    23,    87,    89,
      23,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    32,    33,     0,     1,    21,    29,    34,    36,    54,
      23,    24,    55,    23,    25,     1,     3,     6,     7,     8,
       9,    10,    21,    30,    37,    38,    39,    40,    41,    44,
      47,    53,    54,    17,    18,    35,    21,    24,    26,    24,
       1,    27,     1,    27,     1,    27,     1,    27,     1,    46,
       1,    26,    24,    24,    28,    29,    30,    16,    19,    20,
      21,    27,    56,    57,    58,    59,    60,    61,    24,    21,
      24,    59,    24,    28,    29,    30,    59,    24,    28,    29,
      30,    27,    24,    59,    27,    27,    59,    14,    28,    15,
      11,    12,    13,    28,    28,    48,    56,    24,    56,    59,
      28,    57,    42,    58,    59,    60,    61,    24,    24,    28,
      28,    28,    28,    37,    50,    45,     5,    29,    37,    43,
      51,    37,     4,    22,    20,    49,    52,    23,    23,    55,
      55,    30
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    35,    35,
      36,    36,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    38,    38,    38,    39,    39,    40,    40,    42,    43,
      41,    41,    41,    41,    41,    45,    44,    44,    44,    44,
      44,    46,    48,    49,    47,    47,    47,    47,    47,    50,
      52,    51,    51,    53,    54,    55,    55,    56,    56,    57,
      57,    58,    58,    59,    59,    60,    60,    61,    61,    61,
      61
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     4,     2,     2,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     4,     2,     3,     5,     3,     5,     3,     0,     0,
       9,     3,     3,     3,     3,     0,     7,     3,     3,     3,
       3,     0,     0,     0,    13,     3,     3,     3,     3,     0,
       0,     6,     0,     2,     3,     2,     0,     3,     1,     3,
       1,     4,     3,     3,     1,     3,     1,     3,     4,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_FLOAT: /* FLOAT  */
#line 58 "Parser.y"
            {strcpy(((*yyvaluep).en).id, "\0"); ((*yyvaluep).en).idtype = UNDEFINED;}
#line 1245 "Parser.tab.c"
        break;

    case YYSYMBOL_INT: /* INT  */
#line 58 "Parser.y"
            {strcpy(((*yyvaluep).en).id, "\0"); ((*yyvaluep).en).idtype = UNDEFINED;}
#line 1251 "Parser.tab.c"
        break;

    case YYSYMBOL_CAST: /* CAST  */
#line 58 "Parser.y"
            {strcpy(((*yyvaluep).en).id, "\0"); ((*yyvaluep).en).idtype = UNDEFINED;}
#line 1257 "Parser.tab.c"
        break;

    case YYSYMBOL_NUM: /* NUM  */
#line 58 "Parser.y"
            {strcpy(((*yyvaluep).en).id, "\0"); ((*yyvaluep).en).idtype = UNDEFINED;}
#line 1263 "Parser.tab.c"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 58 "Parser.y"
            {strcpy(((*yyvaluep).en).id, "\0"); ((*yyvaluep).en).idtype = UNDEFINED;}
#line 1269 "Parser.tab.c"
        break;

    case YYSYMBOL_DEFAULT: /* DEFAULT  */
#line 60 "Parser.y"
            {free (((*yyvaluep).caselist)); ((*yyvaluep).caselist) = NULL;}
#line 1275 "Parser.tab.c"
        break;

    case YYSYMBOL_type: /* type  */
#line 58 "Parser.y"
            {strcpy(((*yyvaluep).en).id, "\0"); ((*yyvaluep).en).idtype = UNDEFINED;}
#line 1281 "Parser.tab.c"
        break;

    case YYSYMBOL_idlist: /* idlist  */
#line 59 "Parser.y"
            {free (((*yyvaluep).idlist)); ((*yyvaluep).idlist) = NULL;}
#line 1287 "Parser.tab.c"
        break;

    case YYSYMBOL_caselist: /* caselist  */
#line 60 "Parser.y"
            {free (((*yyvaluep).caselist)); ((*yyvaluep).caselist) = NULL;}
#line 1293 "Parser.tab.c"
        break;

    case YYSYMBOL_boolexpr: /* boolexpr  */
#line 58 "Parser.y"
            {strcpy(((*yyvaluep).en).id, "\0"); ((*yyvaluep).en).idtype = UNDEFINED;}
#line 1299 "Parser.tab.c"
        break;

    case YYSYMBOL_boolterm: /* boolterm  */
#line 58 "Parser.y"
            {strcpy(((*yyvaluep).en).id, "\0"); ((*yyvaluep).en).idtype = UNDEFINED;}
#line 1305 "Parser.tab.c"
        break;

    case YYSYMBOL_boolfactor: /* boolfactor  */
#line 58 "Parser.y"
            {strcpy(((*yyvaluep).en).id, "\0"); ((*yyvaluep).en).idtype = UNDEFINED;}
#line 1311 "Parser.tab.c"
        break;

    case YYSYMBOL_expression: /* expression  */
#line 58 "Parser.y"
            {strcpy(((*yyvaluep).en).id, "\0"); ((*yyvaluep).en).idtype = UNDEFINED;}
#line 1317 "Parser.tab.c"
        break;

    case YYSYMBOL_term: /* term  */
#line 58 "Parser.y"
            {strcpy(((*yyvaluep).en).id, "\0"); ((*yyvaluep).en).idtype = UNDEFINED;}
#line 1323 "Parser.tab.c"
        break;

    case YYSYMBOL_factor: /* factor  */
#line 58 "Parser.y"
            {strcpy(((*yyvaluep).en).id, "\0"); ((*yyvaluep).en).idtype = UNDEFINED;}
#line 1329 "Parser.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: declarations stmt_block  */
#line 71 "Parser.y"
                                                            {fprintf(intermediary_file,"\t\t\tHALT\n\nDor Elbaz --- CPL-to-Quad Compiler Project\n");}
#line 1602 "Parser.tab.c"
    break;

  case 5: /* declaration: idlist ':' type ';'  */
#line 85 "Parser.y"
                                    { 
                                                     
    Id *idptr = (yyvsp[-3].idlist); 
    while (idptr) 
    { 
        insert(idptr->id, (yyvsp[-1].en).idtype);
        idptr = idptr->next;
    }

    idptr = (yyvsp[-3].idlist);
    Id **idptr2 = &idptr;
    while (*idptr2)
    {
        idptr = idptr->next;
        free(*idptr2);
        idptr2 = NULL;
        idptr2 = &idptr;
    }

    print_Symbol_Table();
}
#line 1628 "Parser.tab.c"
    break;

  case 9: /* type: FLOAT  */
#line 114 "Parser.y"
                            {(yyval.en).idtype = (yyvsp[0].en).idtype;}
#line 1634 "Parser.tab.c"
    break;

  case 10: /* idlist: idlist ',' ID  */
#line 121 "Parser.y"
                            {
    
    (yyval.idlist) = malloc(sizeof(Id));
    if (!(yyval.idlist)) 
    {
        output_Error_Msg(FAILED_TO_ALLOCATE_MEMORY); 
        return EXIT_FAILURE;
    } 
    strcpy((yyval.idlist)->id,(yyvsp[0].en).id); 
    (yyval.idlist)->next = (yyvsp[-2].idlist); 
}
#line 1650 "Parser.tab.c"
    break;

  case 11: /* idlist: ID  */
#line 138 "Parser.y"
                            { 
    
    (yyval.idlist) = malloc(sizeof(Id));
    if (!(yyval.idlist)) 
    {
        output_Error_Msg(FAILED_TO_ALLOCATE_MEMORY); 
        return EXIT_FAILURE;
    } 
    strcpy((yyval.idlist)->id,(yyvsp[0].en).id); 
    (yyval.idlist)->next = NULL; 
}
#line 1666 "Parser.tab.c"
    break;

  case 21: /* assignment_stmt: ID '=' expression ';'  */
#line 160 "Parser.y"
                                        { 

    char temp[LABEL_LENGTH];
    Entry *e = lookup((yyvsp[-3].en).id);
    if (e)
    {
        if ((yyvsp[-3].en).idtype != (yyvsp[-1].en).idtype)
        {
            strcpy(temp, Label_Generator("tvar",temp_counter));
            temp_counter++;
            if ((yyvsp[-3].en).idtype == DOUBLE)
            {
                fprintf(intermediary_file,"\t\b\t\tITOR %s %s\n\t\t\tRASN %s %s\n",temp,(yyvsp[-1].en).id,(yyvsp[-3].en).id,temp); 
                label_address += 2;
            }
            else
            {
                output_Error_Msg(ILLEGAL_ASSIGNMENT);
            }
        }
        else
        {
            if ((yyvsp[-3].en).idtype == INTEGER)
            {
                fprintf(intermediary_file,"\t\t\tIASN %s %s\n",(yyvsp[-3].en).id,(yyvsp[-1].en).id);
            }
            else
            {
                fprintf(intermediary_file,"\t\t\tRASN %s %s\n",(yyvsp[-3].en).id,(yyvsp[-1].en).id);
            }
            label_address++;
        }
    }
    else
    {
        output_Error_Msg(ID_HAS_NOT_BEEN_DEFINED);
    }
}
#line 1709 "Parser.tab.c"
    break;

  case 24: /* input_stmt: INPUT '(' ID ')' ';'  */
#line 208 "Parser.y"
                                    { 

    Entry *e = lookup((yyvsp[-2].en).id);
    if (e)
    {
        if (e->idtype == INTEGER) 
        {
            fprintf(intermediary_file,"\t\t\tIINP %s\n",e->id);
        }
        else
        {
            fprintf(intermediary_file,"\t\t\tRINP %s\n",e->id);
        }
        label_address++;
    }
    else
    {
        output_Error_Msg(ID_HAS_NOT_BEEN_DEFINED);
    }
}
#line 1734 "Parser.tab.c"
    break;

  case 26: /* output_stmt: OUTPUT '(' expression ')' ';'  */
#line 234 "Parser.y"
                                                { 

    if ((yyvsp[-2].en).idtype == DOUBLE)
    {
        fprintf(intermediary_file,"\t\t\tRPRT %s\n",(yyvsp[-2].en).id);
    }
    else
    {
        fprintf(intermediary_file,"\t\t\tIPRT %s\n",(yyvsp[-2].en).id);
    }
    label_address++;  
}
#line 1751 "Parser.tab.c"
    break;

  case 28: /* $@1: %empty  */
#line 263 "Parser.y"
                              {                                                /***** FIRST *****/
          
    push(&label_stack, Label_Generator("ELSE",if_counter));
    fprintf(intermediary_file,"\t\t\tJMPZ %s %s\n", peek(label_stack).label, (yyvsp[-1].en).id);
    push(&label_stack, Label_Generator("IF_END",if_counter));
    label_address++;
    if_counter++;  

}
#line 1765 "Parser.tab.c"
    break;

  case 29: /* $@2: %empty  */
#line 271 "Parser.y"
              {                                                                /***** SECOND *****/
    
    char exit_label[MAX_LABEL_LENGTH];
    strcpy(exit_label, peek(label_stack).label);
    pop(&label_stack);

    fprintf(intermediary_file,"\t\t\tJUMP %s\n%s:", exit_label, peek(label_stack).label); 
    label_address++;
    linsert(peek(label_stack).label, label_address);

    pop(&label_stack);
    push(&label_stack, exit_label);

}
#line 1784 "Parser.tab.c"
    break;

  case 30: /* if_stmt: IF '(' boolexpr ')' $@1 stmt ELSE $@2 stmt  */
#line 284 "Parser.y"
                   {                                                           /***** THIRD *****/
    
    fprintf(intermediary_file,"%s:", peek(label_stack).label);
    linsert(peek(label_stack).label, label_address); 
    pop(&label_stack);
    
}
#line 1796 "Parser.tab.c"
    break;

  case 35: /* $@3: %empty  */
#line 309 "Parser.y"
                                               {                               /***** FIRST *****/
    
    fprintf(intermediary_file,"\t\t\tJMPZ %s %s\n", peek(label_stack).label, (yyvsp[-1].en).id); 
    label_address++;

}
#line 1807 "Parser.tab.c"
    break;

  case 36: /* while_stmt: WHILE var1 '(' boolexpr ')' $@3 stmt  */
#line 314 "Parser.y"
          {                                                                    /***** SECOND *****/

    char exit_label[MAX_LABEL_LENGTH];
    strcpy(exit_label, peek(label_stack).label);
    pop(&label_stack);

    fprintf(intermediary_file,"\t\t\tJUMP %s\n%s:",peek(label_stack).label,exit_label); 
    label_address++;
    linsert(exit_label, label_address);
    pop(&label_stack);   
}
#line 1823 "Parser.tab.c"
    break;

  case 41: /* var1: %empty  */
#line 338 "Parser.y"
                       {                                                       /***** VAR1 *****/

    char start_label[MAX_LABEL_LENGTH];
    strcpy(start_label, Label_Generator("WHILE_START",while_counter));
    fprintf(intermediary_file,"%s:",start_label);
    linsert(start_label, label_address);
    push(&label_stack, start_label);  
    push(&label_stack, Label_Generator("WHILE_END",while_counter));                                                         
    while_counter++;                                                
                            
}
#line 1839 "Parser.tab.c"
    break;

  case 42: /* $@4: %empty  */
#line 413 "Parser.y"
                                    {
    
    if ((yyvsp[0].en).idtype == DOUBLE) 
    {
        output_Error_Msg(ILLEGAL_CONDITION);
    }
    
}
#line 1852 "Parser.tab.c"
    break;

  case 43: /* $@5: %empty  */
#line 420 "Parser.y"
                                      {                                      /***** FIRST *****/
    
    (yyvsp[0].caselist) = malloc(sizeof(Case));
    if (!(yyvsp[0].caselist)) 
    {
        output_Error_Msg(FAILED_TO_ALLOCATE_MEMORY); 
        return EXIT_FAILURE;
    } 
    strcpy((yyvsp[0].caselist)->case_label, Label_Generator("C",case_counter));
    fprintf(intermediary_file, "%s:", (yyvsp[0].caselist)->case_label); 
    linsert((yyvsp[0].caselist)->case_label, label_address);
    case_counter++;

}
#line 1871 "Parser.tab.c"
    break;

  case 44: /* switch_stmt: SWITCH '(' expression $@4 ')' var2 '{' caselist DEFAULT $@5 ':' stmtlist '}'  */
#line 433 "Parser.y"
                                {                                              /***** SECOND *****/

    char exit_label[MAX_LABEL_LENGTH];
    strcpy(exit_label, peek(label_stack).label);
    pop(&label_stack); 
    fprintf(intermediary_file,"\t\t\tJUMP %s\n%s:", exit_label, peek(label_stack).label);
    
    label_address++;
    linsert(peek(label_stack).label, label_address);                                                                                                                
    pop(&label_stack); 

    Case *caseptr = (yyvsp[-5].caselist)->next;
    while (caseptr) 
    {
        fprintf(intermediary_file, "\t\t\tINQL bflag1 %s %s\n\t\t\tJMPZ %s bflag1\n", (yyvsp[-10].en).id, caseptr->case_condition, caseptr->case_label); 
        label_address += 2;
        caseptr = caseptr->next;
    }

    fprintf(intermediary_file,"\t\t\tJUMP %s\n%s:",(yyvsp[-4].caselist)->case_label, exit_label);
    label_address++;
    linsert(exit_label, label_address);
    free((yyvsp[-4].caselist));
    (yyvsp[-4].caselist) = NULL;
                                                                                                                                                                                
    caseptr = (yyvsp[-5].caselist);
    Case **caseptr2 = &caseptr;
    while (*caseptr2)
    {
        caseptr = caseptr->next;
        free(*caseptr2);
        caseptr2 = NULL;
        caseptr2 = &caseptr;
    }
}
#line 1911 "Parser.tab.c"
    break;

  case 49: /* var2: %empty  */
#line 479 "Parser.y"
                        {                                                      /***** VAR2 *****/

    char start_label[MAX_LABEL_LENGTH];
    strcpy(start_label, Label_Generator("SWITCH_START",switch_counter));
    fprintf(intermediary_file,"\t\t\tJUMP %s\n",start_label); 
    label_address++;
    push(&label_stack, start_label); 
    push(&label_stack, Label_Generator("SWITCH_EXIT",switch_counter));                                                                  
    switch_counter++;                    
                        
 }
#line 1927 "Parser.tab.c"
    break;

  case 50: /* $@6: %empty  */
#line 500 "Parser.y"
                                  {                                            /***** FIRST *****/
        
    if ((yyvsp[0].en).idtype == DOUBLE)
    {
        output_Error_Msg(ILLEGAL_CONDITION);
    }
    else
    {
        strcpy((yyvsp[-2].caselist)->case_label, Label_Generator("C",case_counter)); 
        strcpy((yyvsp[-2].caselist)->case_condition, (yyvsp[0].en).id); 
        fprintf(intermediary_file,"%s:", (yyvsp[-2].caselist)->case_label); 
        linsert((yyvsp[-2].caselist)->case_label, label_address);
        case_counter++; 
    }
        
}
#line 1948 "Parser.tab.c"
    break;

  case 51: /* caselist: caselist CASE NUM $@6 ':' stmtlist  */
#line 515 "Parser.y"
                          {                                                    /***** SECOND *****/

    (yyval.caselist) = malloc(sizeof(Case));
    if (!(yyval.caselist)) 
    {
        output_Error_Msg(FAILED_TO_ALLOCATE_MEMORY); 
        return EXIT_FAILURE;
    } 
    (yyval.caselist)->next = (yyvsp[-5].caselist);
}
#line 1963 "Parser.tab.c"
    break;

  case 52: /* caselist: %empty  */
#line 526 "Parser.y"
                    {                                                          /***** THIRD *****/
    
    (yyval.caselist) = malloc(sizeof(Case)); 
    if (!(yyval.caselist)) 
    {
        output_Error_Msg(FAILED_TO_ALLOCATE_MEMORY); 
        return EXIT_FAILURE;
    }  
    (yyval.caselist)->next = NULL;  
}
#line 1978 "Parser.tab.c"
    break;

  case 53: /* break_stmt: BREAK ';'  */
#line 545 "Parser.y"
                            {

    Labels *temp_stack = NULL;
    bool label_found = false;

    while (label_stack)
    {
        if (strstr(peek(label_stack).label, "WHILE_END") || strstr(peek(label_stack).label, "SWITCH_EXIT"))
        {
            fprintf(intermediary_file, "\t\t\tJUMP %s\n", peek(label_stack).label);
            label_address++;
            label_found = true;
            break;
        }
        else
        {
            push(&temp_stack, peek(label_stack).label);
            pop(&label_stack);
        }
    }
     
    while (temp_stack)
    {
        push(&label_stack, peek(temp_stack).label);
        pop(&temp_stack);
    }

    if (!label_found)
    {
        output_Error_Msg(ILLEGAL_BREAK_STATEMENT);
    }
}
#line 2015 "Parser.tab.c"
    break;

  case 57: /* boolexpr: boolexpr OR boolterm  */
#line 594 "Parser.y"
                                        {

    char temp[LABEL_LENGTH];
    if ((yyvsp[-2].en).idtype != (yyvsp[0].en).idtype)
    {
        strcpy(temp, Label_Generator("tvar",temp_counter));
        temp_counter++;
        if ((yyvsp[-2].en).idtype == INTEGER)
        {
            fprintf(intermediary_file,"\t\t\tITOR %s %s\n",temp,(yyvsp[-2].en).id); 
            strcpy((yyvsp[-2].en).id, temp);
            (yyvsp[-2].en).idtype = DOUBLE;
        }
        if ((yyvsp[0].en).idtype == INTEGER)
        {
            fprintf(intermediary_file,"\t\t\tITOR %s %s\n",temp,(yyvsp[0].en).id); 
            strcpy((yyvsp[0].en).id, temp);
            (yyvsp[0].en).idtype = DOUBLE;
        }
        label_address++;
    }

    strcpy((yyval.en).id, Label_Generator("bflag",flag_counter));
    (yyval.en).idtype = select_OP_To_Print((yyvsp[-1].op), (yyvsp[-2].en).idtype, (yyvsp[0].en).idtype, (yyval.en).id, (yyvsp[-2].en).id, (yyvsp[0].en).id, &label_address);
    flag_counter++;
}
#line 2046 "Parser.tab.c"
    break;

  case 58: /* boolexpr: boolterm  */
#line 621 "Parser.y"
                                        {(yyval.en).idtype = (yyvsp[0].en).idtype; strcpy((yyval.en).id, (yyvsp[0].en).id);}
#line 2052 "Parser.tab.c"
    break;

  case 59: /* boolterm: boolterm AND boolfactor  */
#line 630 "Parser.y"
                                           {  

    char temp[LABEL_LENGTH];
    if ((yyvsp[-2].en).idtype != (yyvsp[0].en).idtype)
    {
        strcpy(temp, Label_Generator("tvar",temp_counter));
        temp_counter++;
        if ((yyvsp[-2].en).idtype == INTEGER)
        {
            fprintf(intermediary_file,"\t\t\tITOR %s %s\n",temp,(yyvsp[-2].en).id); 
            strcpy((yyvsp[-2].en).id, temp);
            (yyvsp[-2].en).idtype = DOUBLE;
        }
        if ((yyvsp[0].en).idtype == INTEGER)
        {
            fprintf(intermediary_file,"\t\t\tITOR %s %s\n",temp,(yyvsp[0].en).id); 
            strcpy((yyvsp[0].en).id, temp);
            (yyvsp[0].en).idtype = DOUBLE;
        }
        label_address++;
    }

    strcpy((yyval.en).id, Label_Generator("bflag",flag_counter));
    (yyval.en).idtype = select_OP_To_Print((yyvsp[-1].op), (yyvsp[-2].en).idtype, (yyvsp[0].en).idtype, (yyval.en).id, (yyvsp[-2].en).id, (yyvsp[0].en).id, &label_address);
    flag_counter++;
}
#line 2083 "Parser.tab.c"
    break;

  case 60: /* boolterm: boolfactor  */
#line 657 "Parser.y"
                                        {(yyval.en).idtype = (yyvsp[0].en).idtype; strcpy((yyval.en).id, (yyvsp[0].en).id);}
#line 2089 "Parser.tab.c"
    break;

  case 61: /* boolfactor: NOT '(' boolexpr ')'  */
#line 665 "Parser.y"
                                    { 
    
    strcpy((yyval.en).id, Label_Generator("bflag",flag_counter));
    (yyval.en).idtype = select_OP_To_Print((yyvsp[-3].op), UNDEFINED, (yyvsp[-1].en).idtype, (yyval.en).id, NULL, (yyvsp[-1].en).id, &label_address);
    flag_counter++;
    
}
#line 2101 "Parser.tab.c"
    break;

  case 62: /* boolfactor: expression RELOP expression  */
#line 677 "Parser.y"
                                    { 

    char temp[LABEL_LENGTH];
    if ((yyvsp[-2].en).idtype != (yyvsp[0].en).idtype)
    {
        strcpy(temp, Label_Generator("tvar",temp_counter));
        temp_counter++;
        if ((yyvsp[-2].en).idtype == INTEGER)
        {
            fprintf(intermediary_file,"\t\t\tITOR %s %s\n",temp,(yyvsp[-2].en).id); 
            strcpy((yyvsp[-2].en).id, temp);
            (yyvsp[-2].en).idtype = DOUBLE;
        }
        if ((yyvsp[0].en).idtype == INTEGER)
        {
            fprintf(intermediary_file,"\t\t\tITOR %s %s\n",temp,(yyvsp[0].en).id); 
            strcpy((yyvsp[0].en).id, temp);
            (yyvsp[0].en).idtype = DOUBLE;
        }
        label_address++;
    }

    strcpy((yyval.en).id, Label_Generator("bflag",flag_counter));
    (yyval.en).idtype = select_OP_To_Print((yyvsp[-1].op), (yyvsp[-2].en).idtype, (yyvsp[0].en).idtype, (yyval.en).id, (yyvsp[-2].en).id, (yyvsp[0].en).id, &label_address);
    flag_counter++;

}
#line 2133 "Parser.tab.c"
    break;

  case 63: /* expression: expression ADDOP term  */
#line 712 "Parser.y"
                                    { 

    strcpy((yyval.en).id, Label_Generator("tvar",temp_counter));
    (yyval.en).idtype = select_OP_To_Print((yyvsp[-1].op), (yyvsp[-2].en).idtype, (yyvsp[0].en).idtype, (yyval.en).id, (yyvsp[-2].en).id, (yyvsp[0].en).id, &label_address);
    temp_counter++;
}
#line 2144 "Parser.tab.c"
    break;

  case 64: /* expression: term  */
#line 719 "Parser.y"
            {(yyval.en).idtype = (yyvsp[0].en).idtype; strcpy((yyval.en).id, (yyvsp[0].en).id);}
#line 2150 "Parser.tab.c"
    break;

  case 65: /* term: term MULOP factor  */
#line 727 "Parser.y"
                                {         
    
    strcpy((yyval.en).id, Label_Generator("tvar",temp_counter));
    (yyval.en).idtype = select_OP_To_Print((yyvsp[-1].op), (yyvsp[-2].en).idtype, (yyvsp[0].en).idtype, (yyval.en).id, (yyvsp[-2].en).id, (yyvsp[0].en).id, &label_address);
    temp_counter++;

}
#line 2162 "Parser.tab.c"
    break;

  case 66: /* term: factor  */
#line 735 "Parser.y"
                                {(yyval.en).idtype = (yyvsp[0].en).idtype; strcpy((yyval.en).id, (yyvsp[0].en).id);}
#line 2168 "Parser.tab.c"
    break;

  case 67: /* factor: '(' expression ')'  */
#line 739 "Parser.y"
                                {(yyval.en).idtype = (yyvsp[-1].en).idtype; strcpy((yyval.en).id, (yyvsp[-1].en).id);}
#line 2174 "Parser.tab.c"
    break;

  case 68: /* factor: CAST '(' expression ')'  */
#line 746 "Parser.y"
                                {
    
    if ((yyvsp[-3].en).idtype == DOUBLE)
    {
        (yyval.en).idtype = DOUBLE; 
        if ((yyvsp[-1].en).idtype == INTEGER)
        {
            strcpy((yyval.en).id, Label_Generator("tvar",temp_counter));
            temp_counter++;
            fprintf(intermediary_file,"\t\t\tITOR %s %s\n",(yyval.en).id,(yyvsp[-1].en).id);
            label_address++;
        }
        else 
        {
            strcpy((yyval.en).id,(yyvsp[-1].en).id);
        }
    }
    else
    {
        (yyval.en).idtype = INTEGER; 
        if ((yyvsp[-1].en).idtype == DOUBLE)
        {
            strcpy((yyval.en).id, Label_Generator("tvar",temp_counter));
            temp_counter++;
            fprintf(intermediary_file,"\t\t\tRTOI %s %s\n",(yyval.en).id,(yyvsp[-1].en).id);
            label_address++;
        }
        else 
        {
            strcpy((yyval.en).id,(yyvsp[-1].en).id);
        }
    }
}
#line 2212 "Parser.tab.c"
    break;

  case 69: /* factor: ID  */
#line 783 "Parser.y"
                                {  
        
    Entry *e = lookup((yyvsp[0].en).id);
    if (e)
    {
        (yyval.en).idtype = e->idtype;
        strcpy((yyval.en).id, e->id);
    }
    else
    {
        output_Error_Msg(ID_HAS_NOT_BEEN_DEFINED);
    }
}
#line 2230 "Parser.tab.c"
    break;

  case 70: /* factor: NUM  */
#line 797 "Parser.y"
                                {(yyval.en).idtype = (yyvsp[0].en).idtype; strcpy((yyval.en).id, (yyvsp[0].en).id);}
#line 2236 "Parser.tab.c"
    break;


#line 2240 "Parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 800 "Parser.y"


/* Resets the necessary variables used throughout the compiler. */

void reset_Parameters(void)
{
    label_address = 1;
    temp_counter = 1; 
    flag_counter = 2; 
    case_counter = 1; 
    switch_counter = 1; 
    while_counter = 1; 
    if_counter = 1;
    errs = 0;
    yylineno = 1;
}

