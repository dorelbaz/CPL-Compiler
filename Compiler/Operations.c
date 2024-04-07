#include "Data_File.h"
static void print_OP(enum op_types op, char *id1, char *id2, char *id3, int *laddr, char type);

/* Identifies the operation held by the lexer. */
enum op_types select_OP(char *op)
{
    for (int i = EQUALS; i < NOT_GATE; i++)
    {
        if (!strcmp(operations[i],op))
        {
            return i;
        }
    }
    return NOT_GATE;
}

/* Prints to intermediary file the appropriate quad operation(s) the parser is currently fixed upon
   and returns the correct id type to the destination variable.
   Destination variable means 2 things:
   For the parser - it is the non-terminal on the left hand side, as pointed to by $$, of the current derivation rule. 
   For a quad operation - the left most operand. */
enum id_types select_OP_To_Print(enum op_types op, enum id_types type1, enum id_types type2, char *id1, char *id2, char *id3, int *laddr)
{
    if (type1 == DOUBLE || type2 == DOUBLE)
    {
        print_OP(op, id1, id2, id3, laddr, 'R');
        return DOUBLE;
    }

    print_OP(op, id1, id2, id3, laddr, 'I');
    return INTEGER;
}

/* In case at least one of the operands are of type float, the quad operation(s), that will be printed, will refer to its operands as real variables. */
static void print_OP(enum op_types op, char *id1, char *id2, char *id3, int *laddr, char type)
{
    switch (op)
    {
        case EQUALS:
            fprintf(intermediary_file,"\t\t\t%cEQL %s %s %s\n",type,id1,id2,id3);
            (*laddr)++;
            break;

        case INEQUAL:
            fprintf(intermediary_file,"\t\t\t%cNQL %s %s %s\n",type,id1,id2,id3);
            (*laddr)++;
            break;

        case LESSER_EQUAL_THAN:
            fprintf(intermediary_file,"\t\t\t%cEQL %s %s %s\n",type,id1,id2,id3);
            fprintf(intermediary_file,"\t\t\t%cLSS bflag1 %s %s\n",type,id2,id3);
            fprintf(intermediary_file,"\t\t\tIADD %s %s bflag1\n",id1,id1);
            (*laddr) += 3;
            break;

        case GREATER_EQUAL_THAN:
            fprintf(intermediary_file,"\t\t\t%cEQL %s %s %s\n",type,id1,id2,id3);
            fprintf(intermediary_file,"\t\t\t%cGRT bflag1 %s %s\n",type,id2,id3);
            fprintf(intermediary_file,"\t\t\tIADD %s %s bflag1\n",id1,id1);
            (*laddr) += 3;
            break;

        case LESSER_THAN:
            fprintf(intermediary_file,"\t\t\t%cLSS %s %s %s\n",type,id1,id2,id3);
            (*laddr)++;
            break;

        case GREATER_THAN:
            fprintf(intermediary_file,"\t\t\t%cGRT %s %s %s\n",type,id1,id2,id3);
            (*laddr)++;
            break;

        case PLUS:
            fprintf(intermediary_file,"\t\t\t%cADD %s %s %s\n",type,id1,id2,id3);
            (*laddr)++;
            break;

        case MINUS:
            fprintf(intermediary_file,"\t\t\t%cSUB %s %s %s\n",type,id1,id2,id3);
            (*laddr)++;
            break;

        case DIVIDE:
            fprintf(intermediary_file,"\t\t\t%cDIV %s %s %s\n",type,id1,id2,id3);
            (*laddr)++;
            break;

        case MULTIPLY:
            fprintf(intermediary_file,"\t\t\t%cMLT %s %s %s\n",type,id1,id2,id3);
            (*laddr)++;
            break;

        case OR_GATE:
            fprintf(intermediary_file,"\t\t\t%cADD bflag1 %s %s\n",type,id2,id3);
            fprintf(intermediary_file,"\t\t\t%cLSS %s 0 bflag1\n",type,id1);
            (*laddr) += 2;
            break;

        case AND_GATE:
            fprintf(intermediary_file,"\t\t\t%cMLT %s %s %s\n",type,id1,id2,id3);
            (*laddr)++;
            break;

        case NOT_GATE:
            fprintf(intermediary_file,"\t\t\tJMPZ %d %s\n",(*laddr) + 3,id3);
            fprintf(intermediary_file,"\t\t\tIASN %s 0\n",id1);
            fprintf(intermediary_file,"\t\t\tJUMP %d\n",(*laddr) + 4);
            fprintf(intermediary_file,"\t\t\tIASN %s 1\n",id1);
            (*laddr) += 4;
            break;
    }
}

