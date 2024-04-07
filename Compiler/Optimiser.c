#include "Data_File.h"
static void examine_Line_For_Operations(char *line, char *var);
static void examine_Next_Line_For_ASN(char *var, char *line);

static bool operations_array[] = {false,false,false,false,false,false,false,false};
static bool update_label_address = false;
static int op;
static const int idiv = 3, number_of_operations = 8;


/*
    Removes redundant quad commands of the type:
    IADD tvar5 a b   ---   or any other arithmetical operation
    IASN a tvar5     ---   or RASN
    and replaces them with 
    IADD a a b                                      */
void optimise(void)
{
    FILE *fptr;
    char line[2 * MAX_LENGTH], temp_line[2 * MAX_LENGTH];
    char variable[MAX_LENGTH];
    char optimised_file[2 * MAX_LENGTH];
    char helper[MAX_LENGTH];
    int line_number = 1;

    // Sets the file for the optimisation and opens it.
    strncpy(helper, "\0", MAX_LENGTH);
    strncpy(helper, file_name, strlen(file_name)-strlen("ou"));
    sprintf(optimised_file, "%s%s%s%s", MIDDLE_FILE_RELATIVE_PATH, "optimised_", helper, "txt");
    remove(optimised_file);
    if (!open_File(&fptr, optimised_file, "a")) 
    {
        fclose(yyin);
        fclose(intermediary_file);
        fclose(yyout);
        return;
    }

    /* Read intermediary file line by line untill HALT is encountered. */
    while (!strstr(fgets(line, 2 * MAX_LENGTH, intermediary_file), "HALT"))
    {
        // variable will hold the reocurring variable. In the example above it is a.
        strncpy(variable, "\0", MAX_LENGTH);
        strcpy(temp_line, line);

        // Examines line for real or integer arithmetical operations.
        examine_Line_For_Operations(temp_line, variable);
        // Reset temp line for reasons explained further down.
        strcpy(temp_line, "\0");

        // If an operation was found in current line, we examine the next line for an real or integer assign operation.
        for (int i = 0; i < number_of_operations; i++)
        {
            if (operations_array[i])
            {
                // temp line will hold the next line.
                examine_Next_Line_For_ASN(variable, temp_line);
                line_number++;
            }
        }
     
        if (update_label_address)
        {
            char *first_part = NULL, *second_part = NULL;

            // -1 since we reduce the total lines by 1.
            line_number--;
            update_Label_Table(line_number);

            /* Removes the redundant variable. In the example above:
               IADD tvar5 a b   becomes     IADD a a b*/
            first_part = strtok(line, " ");
            second_part = strtok(NULL, " ");
            second_part = strtok(NULL, " ");
            second_part = strtok(NULL, " ");

            fprintf(fptr, "%s %s %s %s", first_part, variable, variable, second_part);
        }
        else
        {
            /* If temp line is not reset, meaning it holds an assign command but is not tied to operation in current line. 
               Then, we must print it to file. */
            if (!strcmp(temp_line, "\0"))
            {
                fprintf(fptr, "%s", line);
            }
            else
            {
                fprintf(fptr, "%s%s", line, temp_line);
            }
            
        }

        // Resets the boolean flags and increments the line number of the optimised file.
        for (int i = 0; i < number_of_operations; i++)
        {
            operations_array[i] = false;   
        }
        update_label_address = false;
        line_number++;
    }

    fprintf(fptr, "%s\nDor Elbaz --- CPL-to-Quad Compiler Project", line);

    // Prepares the optimised file for the backpatch phase.
    fclose(fptr);
    fclose(intermediary_file);
    if (!open_File(&intermediary_file, optimised_file, "r")) 
    {
        fclose(yyin); 
        fclose(yyout);
        return;
    }
}

// Examines a given line for arithmetical operations that can be seen in the array below.
static void examine_Line_For_Operations(char *line, char *var) 
{
    const char *ops[] = {
    "IADD",                                                 
    "ISUB", 
    "IMLT", 
    "IDIV", 
    "RADD", 
    "RSUB", 
    "RMLT",
    "RDIV"
    };
    op = number_of_operations;
    char *tok = NULL;

    // Examines whether one of the operations appears in the line and saves its index.
    for (int i = 0; i < number_of_operations; i++)
    {
        if(strstr(line,ops[i]))
        {
            op = i;
        }
    }

    if (op != number_of_operations)
    {
        // Marks that an operations appears in line.
        operations_array[op] = true;

        // Extracts the reoccuring variable. In the example above, it is a.
        tok = strtok(line, " ");
        tok = strtok(NULL, " ");
        tok = strtok(NULL, " ");
        strcpy(var, tok);
    }
}

// Examines next line for IASN or RASN.
static void examine_Next_Line_For_ASN(char *var, char *line)
{
    char next_line[2 * MAX_LENGTH];
    char *tok = NULL;

    // Gets next line and copies it to temp.
    fgets(next_line, 2 * MAX_LENGTH, intermediary_file);
    strcpy(line, next_line);

    /*  If next line is an assign command, we extract its assignment variable and compare it with the reoccuring variable.
        If they're the same and an arithmetical operation appears in the current line, then we must decrease the labels, that appear further
        down in the middle file, addresses by 1, since we'll remove 1 line.  */
        
    if (strstr(next_line,"IASN"))
    {
        tok = strtok(next_line, " ");
        tok = strtok(NULL, " ");

        if (op <= idiv && operations_array[op] && !strcmp(var,tok))
        {
            update_label_address = true;
        }
        return;
    }

    if (strstr(next_line,"RASN"))
    {
        tok = strtok(next_line, " ");
        tok = strtok(NULL, " ");

        if (idiv < op && operations_array[op] && !strcmp(var,tok))
        {
            update_label_address = true;
        }
    }
}

