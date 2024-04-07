#include "Data_File.h"

int errs;
char file_name[MAX_LENGTH];
const char *error_msgs[] = {
    "Exceeding length of integers",                                                 
    "Exceeding length for identifiers", 
    "Illegal identifier", 
    "Exceeding length of floats", 
    "An ill-formed number", 
    "Illegal character", 
    "Incomplete comment",
    "Failed to allocate memory",
    "Failed to open file",
    "ID can not be a quad command",
    "ID can not be a reserved word",
    "ID has already been defined",
    "ID has not been defined",
    "Illegal break statement",
    "Can not convert float to int without cast",
    "No input file(s) found",
    "Invalid file name"
};

/* Start line for when the beginning of a comment is encountered */
extern int start_line;

/* Examines whether a file is valid, meaning if it ends with ".ou" and its name's length is between 4 and 32.*/
bool valid_File(char *file)
{
    if (MIN_LENGTH <= strlen(file) && strlen(file) < MAX_LENGTH  && file[strlen(file)-3] == '.' && file[strlen(file)-2] == 'o' && file[strlen(file)-1] == 'u' )
    {
        return true;
    }
    return false;
}

/* Attempts to opens a given file and notifies if an error has occured. */
bool open_File(FILE **fptr, char *file, char *mode) 
{
    *fptr = fopen(file, mode);
    if (!(*fptr)) 
    {
        output_Error_Msg(FAILED_TO_OPEN_FILE);  
        return false;         
    }
    return true;
}

/* Examines whether an integer exceeds its max or min value */
bool integer_Errors()
{
    long i = atol(yytext);

    if (i < INT_MIN || INT_MAX < i)
    {
        output_Error_Msg(EXCEEDING_INTEGER_LENGTH);
        return false;
    }

    return true;
}

/* Examines whenter an identifier exceeds max length, starts with a number, contains illegal character, named after a quad operation or reserved word. */
bool id_Errors()
{
    const char *ops[] = {
        "IASN",
        "IPRT",
        "IINP",
        "IEQL",
        "INQL",
        "IASN",
        "ILSS",
        "IGRT",
        "IADD",                                                 
        "ISUB", 
        "IMLT", 
        "IDIV", 
        "RASN",
        "RPRT",
        "RINP",
        "REQL",
        "RNQL",
        "RASN",
        "RLSS",
        "RGRT",
        "RADD", 
        "RSUB", 
        "RMLT",
        "RDIV",
        "ITOR",
        "RTOI", 
        "JUMP", 
        "JMPZ",
        "HALT"  
    };

    for (int i = 0; i < sizeof(ops) / sizeof(ops[0]); i++) 
    {
        if (!strcmp(yytext, ops[i]))
        {
            output_Error_Msg(ID_CANNOT_BE_QUAD_COMMAND);
            return false;
        }
    }

    if (strstr(yytext, "tvar") || strstr(yytext, "bflag"))
    {
        output_Error_Msg(ID_CANNOT_BE_RESERVED_WORD);
        return false;
    }

    if (strlen(yytext) > MAX_LENGTH)
    {
        output_Error_Msg(EXCEEDING_IDENTIFIER_LENGTH);
        return false;
    }

    if (!('a' <= yytext[0] && yytext[0] <= 'z') && !('A' <= yytext[0] && yytext[0] <= 'Z'))
    {
        output_Error_Msg(ILLEGAL_IDENTIFIER);
        return false;
    }
    return true;
}

/* Examines whether a float exceeds its max or min value */
bool float_Errors()
{
    double d = atof(yytext);

    if (d < FLT_MIN || FLT_MAX < d)
    {
        output_Error_Msg(EXCEEDING_FLOAT_LENGTH);
        return false;
    }

    return true;
}

/* Examines wheter a number is legal or an illegal character (non token) */
void examine_Error()
{
    if (yytext[0] == ' ' || yytext[0] == '\t' || yytext[0] == '\r') {return;}

    for (int i = 0; i < strlen(yytext); i++)
    {
        if ('0' <= yytext[i] && yytext[i] <= '9')
        {
            output_Error_Msg(ILL_FORMED_NUMBER);
            return;
        }
    }
 
    output_Error_Msg(ILLEGAL_CHARACTER);
}

/* Prints the error to screen together with the file name and line in which it occured. */
void yyerror(const char *s)
{
    errs++;
    if (errs == 1) {fprintf(stderr, "\nDor Elbaz --- CPL-to-Quad Compiler Project\nError in file: %s\n",file_name);}
    fprintf (stderr, "Line %d: %s.", yylineno, s);
    if (strstr(s, "unexpected ID")) 
    {
        fprintf (stderr, " Source of error: %s",yytext);
    }
    fprintf (stderr, "\n");
}

/* Prints to screen and output file the error message */
void output_Error_Msg(int msg)
{
    errs++;
    if (errs == 1) {fprintf(stderr, "\nDor Elbaz --- CPL-to-Quad Compiler Project\nError in file: %s\n",file_name);}
    if (msg != ILLEGAL_CHARACTER && msg != ILLEGAL_IDENTIFIER)
    {
        /* The lexer examines whether a comment is complete or not */
        if (msg == INCOMPLETE_COMMENT)
        {
            fprintf(stderr, "Line %d: %s\n",start_line,error_msgs[msg]);
            return;
        }
        fprintf(stderr, "Line %d: %s\n",yylineno,error_msgs[msg]);  
    }
    else
    {
        fprintf(stderr, "Line %d: %s %s\n",yylineno,yytext,error_msgs[msg]);
    }
}
