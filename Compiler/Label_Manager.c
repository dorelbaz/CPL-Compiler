#include "Data_File.h"
static int lhash(char *l);

static char temp_label[MAX_LABEL_LENGTH];
Labels ltable[LABEL_TYPES];
Labels *label_stack = NULL;
/* NOTE: For every call for push, there is an equivalent call for pop. Hence no free stack function.
   This file is split into 2 sections, functions for label stack and functions for label table. 
   We solve collisions with singly linked lists.                                                          */


/* Takes a label name, allocates memory for a label and pushes it unto the label stack. 
   Since only the label name is needed for the label stack, it initialises the label's address with an arbitually 0. */
void push(Labels **stack, char *label)
{

    Labels *new_label = malloc(sizeof(Labels));
    if (!new_label) 
    {
        output_Error_Msg(FAILED_TO_ALLOCATE_MEMORY); 
        exit(1);
    }
    strcpy(new_label->label,label);
    new_label->addr = 0;

    if (!stack)
    {
        new_label->next = NULL;
        *stack = new_label;
    }
    else
    {
        new_label->next = *stack;
        *stack = new_label;
    }
}

/* Pops a label from the label stack and frees it from memory. */
void pop(Labels **stack)
{

    Labels *l = *stack;
    *stack = (*stack)->next;
    free(l);
    l = NULL;

}

/* Returns the head of the label stack. */
Labels peek(Labels *stack)
{
    return *stack;
}

/* Hash function for ltable. */
static int lhash(char *l)
{
    switch (l[0])
    {
        case 'C':
            return 0;

        case 'E':
        case 'I':
            return 1;

        case 'S':
            return 2;
    }

    return 3;
}

void init_Label_Table(void)
{

    for (int i = 0; i < LABEL_TYPES; i++)
    {
        strcpy(ltable[i].label, "\0");
        ltable[i].addr = 0;
        ltable[i].next = NULL;
    }
}

/* Takes label name and its declaration address, according to the intermediary file, 
and creates an instance of a label from them and inserts it into ltable. */
void linsert(char *label, int address)
{

    int index = lhash(label);
 
    if (!ltable[index].addr) 
    {
        strcpy(ltable[index].label, label);
        ltable[index].addr = address;
        ltable[index].next = NULL;
    }
    else
    {

        Labels **lptr = &ltable[index].next;
        while ((*lptr)) 
        {
            lptr = &((*lptr)->next);
        }

        (*lptr) = malloc(sizeof(Labels));
        if (!(*lptr)) 
        {
            output_Error_Msg(FAILED_TO_ALLOCATE_MEMORY); 
            exit(1);
        }
        strcpy((*lptr)->label, label);
        (*lptr)->addr = address;
        (*lptr)->next = NULL;
    } 
}

// Updates addresses of labels relative to number of line. Is used for optimisation.
void update_Label_Table(int address)
{
    Labels **lptr;
    for (int i = 0; i < LABEL_TYPES; i++)
    {
        if (ltable[i].addr > address)
        {
            ltable[i].addr = ltable[i].addr - 1;
        }
        lptr = &ltable[i].next;
        while (*lptr)
        {
            if ((*lptr)->addr > address)
            {
                (*lptr)->addr = (*lptr)->addr-1;
            }    
            lptr = &((*lptr)->next);   
        }
    }
}

void print_Label_Table(void)
{
    Labels *lptr;
    for (int i = 0; i < LABEL_TYPES; i++)
    {
        lptr = &ltable[i];
        printf("\n");
        while (lptr)
        {
            printf("Label: %s\t\tAddress: %d\t\t",lptr->label, lptr->addr); 
            lptr = lptr->next;
        }
    }
    printf("\n");
}

void free_Label_Table(void)
{
    Labels **lptr1, **lptr2;
    for (int i = 0; i < LABEL_TYPES; i++)
    {
        lptr1 = &ltable[i].next;
        while (*lptr1)
        {
            lptr2 = lptr1;
            lptr1 = &((*lptr1)->next);
            free(*lptr2);
            lptr2 = NULL;
        }
    } 

}

/* Generates labels for switch-case statements, if-else statements, while loops. 
   This function also generates temp variables and boolean flags. */
char *Label_Generator(char *label_type, int instance)
{
    sprintf(temp_label, "%s%d", label_type, instance);
    return temp_label;
}