#include "Data_File.h"
static bool search_Line_For_Labels(char *line, char *label, int *addr);

/* Removes the labels generated for the intermediary file, the labels followed by ':', and replaces their mentions with their addresses
   and prints to output file with the rest of the line. 
   The other lines will be printed to output file as they are. */
void backpatch(void)
{
    char line[2 * MAX_LENGTH];
    char *tok = NULL;
    int buffer = 0;
    Labels temp;
    bool flag;

    /* Read intermediary file line by line untill HALT is encountered. */
    while (!strstr(fgets(line, 2 * MAX_LENGTH, intermediary_file), "HALT"))
    {
        /* Buffer counts the length the label, if there is any, including ':'. */
        while (line[buffer] != '\t') {buffer++;}
        /* Sets buffer to after the '\t' padding. */
        while (line[buffer] == '\t') {buffer++;}

        /* Labels will be mentioned only by JUMP and JMPZ. */
        if (strstr(line + buffer,"JUMP") || strstr(line + buffer,"JMPZ"))
        {
            flag = search_Line_For_Labels(line + buffer, temp.label, &temp.addr);
        }
        else
        {
            flag = false;
        }
        
        
        /* If any mention of a label has been found, replace it with its address and print it to output file with the rest of the line. 
           Else, print line as it is. */
        if (flag) 
        {
            tok = strtok(line + buffer, temp.label);
            fprintf(yyout, "%s%d%s", tok, temp.addr, line + buffer + strlen(tok) + strlen(temp.label));
        }
        else 
        {
            fprintf(yyout, "%s", line + buffer);
        }

        buffer = 0;
    }

    fprintf(yyout, "%s", "HALT\n\nDor Elbaz --- CPL-to-Quad Compiler Project\n");
}

/* Searches a given line for any mention of a label. */
static bool search_Line_For_Labels(char *line, char *label, int *addr)
{
    Labels *lptr;

    /* Goes through the label table and examine if a label is present within the line. */
    for (int i = 0; i < LABEL_TYPES; i++)
    {
        lptr = &ltable[i];
        while (lptr)
        {
            if (strcmp(lptr->label,"\0") && strstr(line,lptr->label))
            {
                strcpy(label, lptr->label);
                *addr = lptr->addr;
                return true;
            }
            lptr = lptr->next;
        }
    }

    strcpy(label, "\0");
    *addr = 0;

    return false;
}
