%{
 
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

%}

/*
    <...> is the sole variable non-terminals (words in small letters) or terminals (words in capital letters) can access within the union.
    Those without <...> can not access any variables within the union. Each node in the parse tree represents a single non-terminal or terminal, 
    and the node either has a field, one of the four variables defined in the union, or does not have a field.
*/

%union {
    Entry en;               // Keeps track of information about identifiers and numbers.
    enum op_types op;       // Keeps track about the types of operations that need to be performed.
    Id *idlist;             // Keeps a list of identifiers that need to be inserted into symbol table.
    Case *caselist;         // Keeps a list of case labels and their conditions.
};

%token BREAK CASE ELSE IF INPUT OUTPUT SWITCH WHILE

%token <op> RELOP ADDOP MULOP OR AND NOT

%token <en> FLOAT INT CAST NUM ID 
%nterm <en> type expression factor term boolfactor boolterm boolexpr

%nterm <idlist> idlist

%token <caselist> DEFAULT
%nterm <caselist> caselist

/*
   In the event of an error, the parser might pull symbols from its stack. 
   In that case, the parser will execute the code that is associated with the symbol.
*/
%destructor {strcpy($$.id, "\0"); $$.idtype = UNDEFINED;} <en> 
%destructor {free ($$); $$ = NULL;} <idlist>
%destructor {free ($$); $$ = NULL;} <caselist>


%define parse.error verbose
/* %error-verbose */

%%




program :   declarations stmt_block                         {fprintf(intermediary_file,"\t\t\tHALT\n\nDor Elbaz --- CPL-to-Quad Compiler Project\n");}




declarations : declarations declaration 

| /* empty */



/*  Takes the id list and their type, kept by idlist and type respectively, 
    and inserts them into symbol table. Then, we free the id list from memory. */

declaration : idlist ':' type ';'   { 
                                                     
    Id *idptr = $1; 
    while (idptr) 
    { 
        insert(idptr->id, $3.idtype);
        idptr = idptr->next;
    }

    idptr = $1;
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

| error  ':' 
                                  
| error  ';'    
 



type : INT | FLOAT          {$$.idtype = $1.idtype;}




/* Creates an instance of an id and adds it to the id list.  */

idlist : idlist ',' ID      {
    
    $$ = malloc(sizeof(Id));
    if (!$$) 
    {
        output_Error_Msg(FAILED_TO_ALLOCATE_MEMORY); 
        return EXIT_FAILURE;
    } 
    strcpy($$->id,$3.id); 
    $$->next = $1; 
}




/* Creates the first instance of an id. */

idlist : ID                 { 
    
    $$ = malloc(sizeof(Id));
    if (!$$) 
    {
        output_Error_Msg(FAILED_TO_ALLOCATE_MEMORY); 
        return EXIT_FAILURE;
    } 
    strcpy($$->id,$1.id); 
    $$->next = NULL; 
}

stmt : assignment_stmt | input_stmt | output_stmt | if_stmt | while_stmt | switch_stmt | break_stmt | stmt_block 
  
| error ';'



/* Checks if ID has been defined then examines the types of both sides of the "=", 
   casts according to the type of ID (if necessary) and assigns to it. 
   NOTE: We can not cast float to int as per the project's document. */

assignment_stmt : ID '=' expression ';' { 

    char temp[LABEL_LENGTH];
    Entry *e = lookup($1.id);
    if (e)
    {
        if ($1.idtype != $3.idtype)
        {
            strcpy(temp, Label_Generator("tvar",temp_counter));
            temp_counter++;
            if ($1.idtype == DOUBLE)
            {
                fprintf(intermediary_file,"\t\b\t\tITOR %s %s\n\t\t\tRASN %s %s\n",temp,$3.id,$1.id,temp); 
                label_address += 2;
            }
            else
            {
                output_Error_Msg(ILLEGAL_ASSIGNMENT);
            }
        }
        else
        {
            if ($1.idtype == INTEGER)
            {
                fprintf(intermediary_file,"\t\t\tIASN %s %s\n",$1.id,$3.id);
            }
            else
            {
                fprintf(intermediary_file,"\t\t\tRASN %s %s\n",$1.id,$3.id);
            }
            label_address++;
        }
    }
    else
    {
        output_Error_Msg(ID_HAS_NOT_BEEN_DEFINED);
    }
}

| error  '='    

| ID error  ';' 




/* Examines if id has been defined then prints it according to its type. */ 

input_stmt : INPUT '(' ID ')' ';'   { 

    Entry *e = lookup($3.id);
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

| INPUT error  ';'       


/* Examines expression's type and prints it accordingly. */

output_stmt : OUTPUT '(' expression ')' ';'     { 

    if ($3.idtype == DOUBLE)
    {
        fprintf(intermediary_file,"\t\t\tRPRT %s\n",$3.id);
    }
    else
    {
        fprintf(intermediary_file,"\t\t\tIPRT %s\n",$3.id);
    }
    label_address++;  
}

| OUTPUT error  ';'       


 




/*  
    Creates labels for the else statement and end-of-if then prints the labels and their respective JUMP or JMPZ operations as necessary.
    At the first {...}, we create and push the labels into the stack and print a jump operation to the else statement. 
    At the second {...}, we print a jump to the end-of-if (in the event the if statement has been executed)
    then we print the label for the else statement.
    At the third {...}, we print the end-of-if label.
*/ 

if_stmt : IF '(' boolexpr ')' {                                                /***** FIRST *****/
          
    push(&label_stack, Label_Generator("ELSE",if_counter));
    fprintf(intermediary_file,"\t\t\tJMPZ %s %s\n", peek(label_stack).label, $3.id);
    push(&label_stack, Label_Generator("IF_END",if_counter));
    label_address++;
    if_counter++;  

}   stmt ELSE {                                                                /***** SECOND *****/
    
    char exit_label[MAX_LABEL_LENGTH];
    strcpy(exit_label, peek(label_stack).label);
    pop(&label_stack);

    fprintf(intermediary_file,"\t\t\tJUMP %s\n%s:", exit_label, peek(label_stack).label); 
    label_address++;
    linsert(peek(label_stack).label, label_address);

    pop(&label_stack);
    push(&label_stack, exit_label);

}   stmt           {                                                           /***** THIRD *****/
    
    fprintf(intermediary_file,"%s:", peek(label_stack).label);
    linsert(peek(label_stack).label, label_address); 
    pop(&label_stack);
    
}

| IF error ')'

| IF error '{'

| IF error '}'

| IF error ';' 



/*  
    Creates labels for the start and end of a while loop then prints them and their respective JUMP or JMPZ operations as necessary.
    At var1, we create the loop's start and end labels and push them into the stack then we print the label of the start. 
    At the first {...}, we print a jump to the end of the loop.
    At the second {...}, we print a jump to the beginning of the loop then we print the loop's end label.
*/ 

while_stmt : WHILE  var1  '(' boolexpr ')'     {                               /***** FIRST *****/
    
    fprintf(intermediary_file,"\t\t\tJMPZ %s %s\n", peek(label_stack).label, $4.id); 
    label_address++;

}  stmt   {                                                                    /***** SECOND *****/

    char exit_label[MAX_LABEL_LENGTH];
    strcpy(exit_label, peek(label_stack).label);
    pop(&label_stack);

    fprintf(intermediary_file,"\t\t\tJUMP %s\n%s:",peek(label_stack).label,exit_label); 
    label_address++;
    linsert(exit_label, label_address);
    pop(&label_stack);   
}

| WHILE error ')'

| WHILE error '{'

| WHILE error '}'

| WHILE error ';'          




                                                       
var1 : /* empty */     {                                                       /***** VAR1 *****/

    char start_label[MAX_LABEL_LENGTH];
    strcpy(start_label, Label_Generator("WHILE_START",while_counter));
    fprintf(intermediary_file,"%s:",start_label);
    linsert(start_label, label_address);
    push(&label_stack, start_label);  
    push(&label_stack, Label_Generator("WHILE_END",while_counter));                                                         
    while_counter++;                                                
                            
}                                                                                                                                                                                                            












/*  

    This is the description of the general structure of our switch case statement:

    Jump to beginning of the case conditions list
    
    - C1:      code of the first block.  
               if break statement appeared - jump to end of switch
               else continue to next case code block.
    - C2:      code of the second block.  
               if break statement appeared - jump to end of switch
               else continue to next case code block.

              .
              .
              .

    - Cn:      code of the nth's block.  
               if break statement appeared - jump to end of switch
               else continue to default case code block.
    - Default: code of the default block.  
               jump to end of switch

    ***** Beginning of the case conditions list (marked by the switch start label) *****

    - Condition of the nth's case with its jump operation (last case gets printed first since we build the case list from the bottom up)
    - Condition of the (n-1)th's case with its jump operation.

    .
    .
    .

    - Condition of the first case with its jump operation
    - jump to the default case

    ***** End of the case conditions list (marked by the switch exit label) *****


    First, we print each case label and the code within its block (will be printed by stmtlist) including the default case and its block code.
    Then, we print the list of case conditions with their respective jump operations.
    At var2, we create the switch's start and end labels and push them into the stack then we print the label of the start.
    Read the documentation for caselist below. 
    At the first {...}, we create an instance of Case for the default case and we print its case label.
    At the second {...}:
    first, we print a jump to the end of the switch case (it marks the end of the execution of the default case code) 
    followed by the start of the case conditions list (marked by the switch's start label)
    second, we print each case from the case list, conditions, labels and the necessary jump operations.
    third, we print a jump to the default case and the switch's exit label.
    lastly, we free the case list from memory.

*/ 

switch_stmt : SWITCH '(' expression {
    
    if ($3.idtype == DOUBLE) 
    {
        output_Error_Msg(ILLEGAL_CONDITION);
    }
    
} ')'  var2  '{' caselist DEFAULT     {                                      /***** FIRST *****/
    
    $9 = malloc(sizeof(Case));
    if (!$9) 
    {
        output_Error_Msg(FAILED_TO_ALLOCATE_MEMORY); 
        return EXIT_FAILURE;
    } 
    strcpy($9->case_label, Label_Generator("C",case_counter));
    fprintf(intermediary_file, "%s:", $9->case_label); 
    linsert($9->case_label, label_address);
    case_counter++;

}         ':' stmtlist '}'      {                                              /***** SECOND *****/

    char exit_label[MAX_LABEL_LENGTH];
    strcpy(exit_label, peek(label_stack).label);
    pop(&label_stack); 
    fprintf(intermediary_file,"\t\t\tJUMP %s\n%s:", exit_label, peek(label_stack).label);
    
    label_address++;
    linsert(peek(label_stack).label, label_address);                                                                                                                
    pop(&label_stack); 

    Case *caseptr = $8->next;
    while (caseptr) 
    {
        fprintf(intermediary_file, "\t\t\tINQL bflag1 %s %s\n\t\t\tJMPZ %s bflag1\n", $3.id, caseptr->case_condition, caseptr->case_label); 
        label_address += 2;
        caseptr = caseptr->next;
    }

    fprintf(intermediary_file,"\t\t\tJUMP %s\n%s:",$9->case_label, exit_label);
    label_address++;
    linsert(exit_label, label_address);
    free($9);
    $9 = NULL;
                                                                                                                                                                                
    caseptr = $8;
    Case **caseptr2 = &caseptr;
    while (*caseptr2)
    {
        caseptr = caseptr->next;
        free(*caseptr2);
        caseptr2 = NULL;
        caseptr2 = &caseptr;
    }
}  

| SWITCH error ')'

| SWITCH error '{'

| SWITCH error '}'

| SWITCH error ';'  


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
var2 : /* empty */      {                                                      /***** VAR2 *****/

    char start_label[MAX_LABEL_LENGTH];
    strcpy(start_label, Label_Generator("SWITCH_START",switch_counter));
    fprintf(intermediary_file,"\t\t\tJUMP %s\n",start_label); 
    label_address++;
    push(&label_stack, start_label); 
    push(&label_stack, Label_Generator("SWITCH_EXIT",switch_counter));                                                                  
    switch_counter++;                    
                        
 }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              


 /*   
    At the first {...}, we examine the type of NUM (must be int) then we copy its value (as case condition) 
    and its respective case label, and we print it, into an instance of a Case and add it into case list.
    At the second {...}, we create an instance of a Case for the next case.
    At the third {...}, we create the first instance of a Case that represents the last case (not the default case).
    NOTE: We construct the case list from the bottom up, meaning from the last case up to the first.
*/     

caselist :    caselist CASE NUM   {                                            /***** FIRST *****/
        
    if ($3.idtype == DOUBLE)
    {
        output_Error_Msg(ILLEGAL_CONDITION);
    }
    else
    {
        strcpy($1->case_label, Label_Generator("C",case_counter)); 
        strcpy($1->case_condition, $3.id); 
        fprintf(intermediary_file,"%s:", $1->case_label); 
        linsert($1->case_label, label_address);
        case_counter++; 
    }
        
}     ':'     stmtlist    {                                                    /***** SECOND *****/

    $$ = malloc(sizeof(Case));
    if (!$$) 
    {
        output_Error_Msg(FAILED_TO_ALLOCATE_MEMORY); 
        return EXIT_FAILURE;
    } 
    $$->next = $1;
}

| /* empty */       {                                                          /***** THIRD *****/
    
    $$ = malloc(sizeof(Case)); 
    if (!$$) 
    {
        output_Error_Msg(FAILED_TO_ALLOCATE_MEMORY); 
        return EXIT_FAILURE;
    }  
    $$->next = NULL;  
}



/*  
    Prints jump to either the end of a loop or a switch. 
    Goes through label stack, with the help of temp stack, untill it finds a suitable exit label or it reached the end of label stack.
    Then, it restores label stack and examines whether a suitable exit label has been found or not.
*/ 

break_stmt : BREAK ';'      {

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





stmt_block : '{' stmtlist '}'



stmtlist : stmtlist stmt 

| /* empty */



/* Examines the type of both operands, and casts to float if necessary, then prints the OR operation according to the operands type. */ 

boolexpr : boolexpr OR boolterm         {

    char temp[LABEL_LENGTH];
    if ($1.idtype != $3.idtype)
    {
        strcpy(temp, Label_Generator("tvar",temp_counter));
        temp_counter++;
        if ($1.idtype == INTEGER)
        {
            fprintf(intermediary_file,"\t\t\tITOR %s %s\n",temp,$1.id); 
            strcpy($1.id, temp);
            $1.idtype = DOUBLE;
        }
        if ($3.idtype == INTEGER)
        {
            fprintf(intermediary_file,"\t\t\tITOR %s %s\n",temp,$3.id); 
            strcpy($3.id, temp);
            $3.idtype = DOUBLE;
        }
        label_address++;
    }

    strcpy($$.id, Label_Generator("bflag",flag_counter));
    $$.idtype = select_OP_To_Print($2, $1.idtype, $3.idtype, $$.id, $1.id, $3.id, &label_address);
    flag_counter++;
}

| boolterm                              {$$.idtype = $1.idtype; strcpy($$.id, $1.id);}






/* Examines the type of both operands, and casts to float if necessary, then prints the AND operation according to the operands type.*/ 

boolterm : boolterm AND boolfactor         {  

    char temp[LABEL_LENGTH];
    if ($1.idtype != $3.idtype)
    {
        strcpy(temp, Label_Generator("tvar",temp_counter));
        temp_counter++;
        if ($1.idtype == INTEGER)
        {
            fprintf(intermediary_file,"\t\t\tITOR %s %s\n",temp,$1.id); 
            strcpy($1.id, temp);
            $1.idtype = DOUBLE;
        }
        if ($3.idtype == INTEGER)
        {
            fprintf(intermediary_file,"\t\t\tITOR %s %s\n",temp,$3.id); 
            strcpy($3.id, temp);
            $3.idtype = DOUBLE;
        }
        label_address++;
    }

    strcpy($$.id, Label_Generator("bflag",flag_counter));
    $$.idtype = select_OP_To_Print($2, $1.idtype, $3.idtype, $$.id, $1.id, $3.id, &label_address);
    flag_counter++;
}

| boolfactor                            {$$.idtype = $1.idtype; strcpy($$.id, $1.id);}





/* Prints the NOT procedure (composed of several quad operations). */ 

boolfactor : NOT '(' boolexpr ')'   { 
    
    strcpy($$.id, Label_Generator("bflag",flag_counter));
    $$.idtype = select_OP_To_Print($1, UNDEFINED, $3.idtype, $$.id, NULL, $3.id, &label_address);
    flag_counter++;
    
}


/* Examines the type of both operands, and casts to float if necessary, then prints the relational operation (as received from the lexer)
   according to the operands type. */ 

| expression RELOP expression       { 

    char temp[LABEL_LENGTH];
    if ($1.idtype != $3.idtype)
    {
        strcpy(temp, Label_Generator("tvar",temp_counter));
        temp_counter++;
        if ($1.idtype == INTEGER)
        {
            fprintf(intermediary_file,"\t\t\tITOR %s %s\n",temp,$1.id); 
            strcpy($1.id, temp);
            $1.idtype = DOUBLE;
        }
        if ($3.idtype == INTEGER)
        {
            fprintf(intermediary_file,"\t\t\tITOR %s %s\n",temp,$3.id); 
            strcpy($3.id, temp);
            $3.idtype = DOUBLE;
        }
        label_address++;
    }

    strcpy($$.id, Label_Generator("bflag",flag_counter));
    $$.idtype = select_OP_To_Print($2, $1.idtype, $3.idtype, $$.id, $1.id, $3.id, &label_address);
    flag_counter++;

}






/* Prints the addition or subtraction operations according to the operands type. */ 

expression : expression ADDOP term  { 

    strcpy($$.id, Label_Generator("tvar",temp_counter));
    $$.idtype = select_OP_To_Print($2, $1.idtype, $3.idtype, $$.id, $1.id, $3.id, &label_address);
    temp_counter++;
}

| term      {$$.idtype = $1.idtype; strcpy($$.id, $1.id);}





/* Prints the division or multiplication operations according to the operands type. */ 

term : term MULOP factor        {         
    
    strcpy($$.id, Label_Generator("tvar",temp_counter));
    $$.idtype = select_OP_To_Print($2, $1.idtype, $3.idtype, $$.id, $1.id, $3.id, &label_address);
    temp_counter++;

}

| factor                        {$$.idtype = $1.idtype; strcpy($$.id, $1.id);}



factor : '(' expression ')'     {$$.idtype = $2.idtype; strcpy($$.id, $2.id);}




/* Prints the cast operation according to the type CAST received from the lexer. */

| CAST '(' expression ')'       {
    
    if ($1.idtype == DOUBLE)
    {
        $$.idtype = DOUBLE; 
        if ($3.idtype == INTEGER)
        {
            strcpy($$.id, Label_Generator("tvar",temp_counter));
            temp_counter++;
            fprintf(intermediary_file,"\t\t\tITOR %s %s\n",$$.id,$3.id);
            label_address++;
        }
        else 
        {
            strcpy($$.id,$3.id);
        }
    }
    else
    {
        $$.idtype = INTEGER; 
        if ($3.idtype == DOUBLE)
        {
            strcpy($$.id, Label_Generator("tvar",temp_counter));
            temp_counter++;
            fprintf(intermediary_file,"\t\t\tRTOI %s %s\n",$$.id,$3.id);
            label_address++;
        }
        else 
        {
            strcpy($$.id,$3.id);
        }
    }
}


/* Examines whether ID is kept by the symbol table, if yes then it forwards the identifier's name and type upwards in the parse tree. */

| ID                            {  
        
    Entry *e = lookup($1.id);
    if (e)
    {
        $$.idtype = e->idtype;
        strcpy($$.id, e->id);
    }
    else
    {
        output_Error_Msg(ID_HAS_NOT_BEEN_DEFINED);
    }
}

| NUM                           {$$.idtype = $1.idtype; strcpy($$.id, $1.id);}


%%

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

