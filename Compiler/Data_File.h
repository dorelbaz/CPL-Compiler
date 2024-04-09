#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

/* General constants */
/* Max length constant determines max length of an id, of a case condition and file's name. 
   It also assists in reading lines from a file and setting file directories.        */
#define MAX_LENGTH 32 
#define MIN_LENGTH 4
#define MAX_LETTERS 26
#define MAX_LABEL_LENGTH 14 
#define LABEL_LENGTH 4
#define LABEL_TYPES 4
#define INPUT_FILE_RELATIVE_PATH "./inputfile/"
#define MIDDLE_FILE_RELATIVE_PATH "./middlefile/"
#define OUTPUT_FILE_RELATIVE_PATH "./outputfile/"

/* Error codes */
#define EXCEEDING_INTEGER_LENGTH 0
#define EXCEEDING_IDENTIFIER_LENGTH 1
#define ILLEGAL_IDENTIFIER 2
#define EXCEEDING_FLOAT_LENGTH 3
#define ILL_FORMED_NUMBER 4
#define ILLEGAL_CHARACTER 5
#define INCOMPLETE_COMMENT 6
#define FAILED_TO_ALLOCATE_MEMORY 7
#define FAILED_TO_OPEN_FILE 8  
#define ID_CANNOT_BE_QUAD_COMMAND 9
#define ID_CANNOT_BE_RESERVED_WORD 10
#define ID_HAS_ALREADY_BEEN_DEFINED 11
#define ID_HAS_NOT_BEEN_DEFINED 12
#define ILLEGAL_BREAK_STATEMENT 13
#define ILLEGAL_CONDITION 14  
#define ILLEGAL_ASSIGNMENT 15
#define NO_INPUT_FILE_FOUND 16
#define INVALID_FILE 17


enum id_types {
    UNDEFINED,
    INTEGER,
    DOUBLE
};

typedef struct symbol_table
{
    char id[MAX_LENGTH];
    enum id_types idtype;
    struct symbol_table *next;
}Entry;

typedef struct idlist {
    char id[MAX_LENGTH];
    struct idlist *next;
}Id;

typedef struct case_conditions {
    char case_label[LABEL_LENGTH];
    char case_condition[MAX_LENGTH];
    struct case_conditions *next;
}Case;

typedef struct label {
    char label[MAX_LABEL_LENGTH];
    int addr;
    struct label *next;
}Labels;

/* Function and variable declarations for first passage file */
void first_Passage(int n, char **);
void reset_Tables_And_Parameters(bool);
extern FILE *intermediary_file;

/* Function and variable declarations for error file */
void yyerror(const char *);
bool valid_File(char *);
bool open_File(FILE **, char *, char *);
bool integer_Errors(void);
bool id_Errors(void);
bool float_Errors(void);
void examine_Error(void);
void output_Error_Msg(int);
extern int errs;
extern char file_name[MAX_LENGTH];

/* Function declarations for symbol table file */
void init_Symbol_Table(void);
void insert(char *, enum id_types);
Entry *lookup(char *);
void print_Symbol_Table(void);
void free_Symbol_Table(void);

/* Flex and Bison function and variable declarations */
extern int yyparse();
extern void yyrestart();
extern int yylex();
void reset_Parameters(void);
extern FILE *yyin;
extern FILE *yyout;
extern int yylineno;
extern char *yytext;

/* Function declarations for operations file */
enum op_types select_OP(char *);
enum id_types select_OP_To_Print(enum op_types, enum id_types, enum id_types, char *, char *, char *, int *);

/* Function and variable declarations for label manager file */
void push(Labels **, char *);
void pop(Labels **);
Labels peek(Labels *);
void init_Label_Table(void);
void linsert(char *, int);
void update_Label_Table(int);
void print_Label_Table(void);
void free_Label_Table(void);
char *Label_Generator(char *, int);
extern Labels ltable[LABEL_TYPES];
extern Labels *label_stack;

/* Function declarations for backpatch file */
void backpatch(void);

/*Function declarations for optimiser file */
void optimise(void);

/* Error messages */
extern const char *error_msgs[];

/*Logical, arithmatical and relational operations */
extern const char *operations[];

/* All possible operations in a typical CPL program */
enum op_types {
    EQUALS,
    INEQUAL,
    LESSER_EQUAL_THAN,
    GREATER_EQUAL_THAN,
    LESSER_THAN,
    GREATER_THAN,
    PLUS,
    MINUS,
    DIVIDE,
    MULTIPLY,
    OR_GATE,
    AND_GATE,
    NOT_GATE,
};








