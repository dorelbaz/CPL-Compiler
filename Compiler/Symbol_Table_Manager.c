#include "Data_File.h"
static int hash(char *id);

Entry symbol_table[MAX_LETTERS];

/* NOTE: We solve collisions with a linked list. */

/* Hash function for symbol table. */
static int hash(char *id)
{
    return id[0] % MAX_LETTERS;
}

void init_Symbol_Table(void)
{
    for (int i = 0; i < MAX_LETTERS; i++)
    {
        strcpy(symbol_table[i].id, "\0");
        symbol_table[i].idtype = UNDEFINED;
        symbol_table[i].next = NULL;
    }
}

/* Takes id name and type, creates an instance of a symbol from them and inserts it in the symbol table. */
void insert(char *id, enum id_types type)
{

    Entry *eptr = lookup(id);
    if (eptr) {output_Error_Msg(ID_HAS_ALREADY_BEEN_DEFINED); return;}

    int index = hash(id);

    if (symbol_table[index].idtype == UNDEFINED) 
    {
        strcpy(symbol_table[index].id, id);
        symbol_table[index].idtype = type;
        symbol_table[index].next = NULL;
    }
    else
    {
        Entry **eptr2 = &symbol_table[index].next;
        while ((*eptr2)) 
        {
            eptr2 = &((*eptr2)->next);
        }

        (*eptr2) = malloc(sizeof(Entry));
        if (!(*eptr2)) 
        {
            output_Error_Msg(FAILED_TO_ALLOCATE_MEMORY); 
            exit(1);
        }
        strcpy((*eptr2)->id, id);
        (*eptr2)->idtype = type;
        (*eptr2)->next = NULL;
    }
}


Entry *lookup(char *id)
{

    int index = hash(id);

    Entry *eptr = &symbol_table[index];
    if (!eptr) {return NULL;}

    while (eptr)
    {
        if (!strcmp(eptr->id,id))
        {
            return eptr;
        }
        eptr = eptr->next;
    }

    return NULL;
}


void print_Symbol_Table(void)
{
    Entry *eptr;
    for (int i = 0; i < MAX_LETTERS; i++)
    {
        eptr = &symbol_table[i];
        printf("\n");
        while (eptr)
        {
            printf("ID: %s\t\t",eptr->id); 
            if (eptr->idtype == INTEGER)
            {
                printf("Type: %s\t\t", "INT");
            }
            else if (eptr->idtype == DOUBLE)
            {
                printf("Type: %s\t\t", "FLOAT");
            }
            else
            {
                printf("Type: %s\t\t", "UNDEFINED");
            }
            eptr = eptr->next;
        }
    }
    printf("\n");
}

void free_Symbol_Table(void)
{
    Entry **eptr1, **eptr2;
    for (int i = 0; i < MAX_LETTERS; i++)
    {
        eptr1 = &symbol_table[i].next;
        while (*eptr1)
        {
            eptr2 = eptr1;
            eptr1 = &((*eptr1)->next); 
            free(*eptr2);
            eptr2 = NULL;
        }
    } 
}