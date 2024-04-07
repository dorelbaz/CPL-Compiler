#include "Data_File.h"

static void set_File_Directories(char *input, char *middle, char *output, char *argv);
FILE *intermediary_file;

/*
   Creates the intermediary (middle) file. 
   NOTE: Input CPL program must be found within input file in the project's folder. 
   You'll find the intermediary and output files within middle and output files respectively.
   We return to main in the event of an error
   As a precaution, we first remove middle and output files before we open them for the first time.
*/
void first_Passage(int n, char **argv)
{
    char input_file_directory[2 * MAX_LENGTH];
    char middle_file_directory[2 * MAX_LENGTH];
    char output_file_directory[2 * MAX_LENGTH];

    /* Copies the input file directory and sets the directories for the middle and output file. 
    Also, copies file name in the event of a future error and resets/initialises variables and tables. */
    if (!valid_File(argv[n])) 
    {
        strcpy(file_name, argv[n]);
        output_Error_Msg(INVALID_FILE); 
        return;
    }
    strcpy(file_name, argv[n]);
    set_File_Directories(input_file_directory, middle_file_directory, output_file_directory, argv[n]);

    // Opens the input file and creates the middle file with the directories above.
    remove(middle_file_directory);
    if (!open_File(&yyin, input_file_directory, "r")) {return;}
    if (!open_File(&intermediary_file, middle_file_directory, "a")) {fclose(yyin); return;}

    
    // Responsible for the lexical, syntax and semantic analysis of the given CPL program.
    yyparse();

    // Deletes the middle file in the event of an error.
    if (errs) {remove(middle_file_directory); return;}

    // Prepares the middle and output files for the optimisation and backpatch phases respectively. 
    fclose(intermediary_file);
    if (!open_File(&intermediary_file, middle_file_directory, "r")) {fclose(yyin); return;}
    remove(output_file_directory);
    if (!open_File(&yyout, output_file_directory, "a")) 
    {
        fclose(intermediary_file);
        fclose(yyin); 
        return;
    }

    print_Label_Table();
}

static void set_File_Directories(char *input, char *middle, char *output, char *argv)
{
    char helper[MAX_LENGTH];
    strncpy(helper, "\0", MAX_LENGTH);
    strncpy(helper, argv, strlen(argv)-strlen("ou"));
    sprintf(input, "%s%s", INPUT_FILE_RELATIVE_PATH, argv);   
    sprintf(middle, "%s%s%s", MIDDLE_FILE_RELATIVE_PATH, helper, "txt");
    sprintf(output, "%s%s%s", OUTPUT_FILE_RELATIVE_PATH, helper, "qud");
}

// This function is used for both the initialisation and reset of tables and variables.
void reset_Tables_And_Parameters(bool init_flag)
{
    if (!init_flag)
    {
        free_Label_Table();
        free_Symbol_Table(); 
    }
    init_Symbol_Table();
    init_Label_Table();
    reset_Parameters();  
}


