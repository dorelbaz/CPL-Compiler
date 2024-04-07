#include "Data_File.h"

// NOTE: in this project, tvar and bflag are reserved words. 

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        output_Error_Msg(NO_INPUT_FILE_FOUND); 
        return EXIT_FAILURE; 
    }

    int n = 1; 
    reset_Tables_And_Parameters(true);

    // Creates the middle file and if no errors have been found then we go on to create the output quad file.
    while (n < argc)
    { 
        first_Passage(n, argv);

        if (!errs)
        {
            optimise();
            // The only error that could occur from the optimiser is failure to open files.
            if (!errs)
            {
                backpatch();
                fclose(yyin);
                fclose(intermediary_file);
                fclose(yyout);
            }
        }

        reset_Tables_And_Parameters(false); 
        n++;
    }

    return 0;
}










