#include "structures.h"


void push_pointer(void *ptr, char *str)
{
        if (memoo->ptr == NULL && memoo->next == NULL)
        {
                memo->ptr = ptr;
                memo->nb ++;
        }
        else
        {
                struct memory *tmp = memoo;
                for (; tmp && tmp->next != NULL;  tmp = tmp->next);
                struct memory *new = malloc(sizeof(struct memory));
                new->from = str;
		new->ptr = ptr;
                new->next = NULL;
                tmp->next = new;
                memo->nb++;
        }
}

struct memory *init_memory(void)
{
        struct memory *new = malloc(sizeof(struct memory));
        if (!new)
        {
                fprintf(stderr, "Alloc error: init memory list\n");
                return NULL;
        }
        new->ptr = NULL;
        new->next = NULL;
        return new;
}

void destroy_memory(struct memory *memo)
{
	if (memo->ptr == NULL)
	{
		free(memo);
        	return;
	}
	if (memo && memo->next != NULL)
	{
		destroy_memory(memo->next);
	}
	if (memo->ptr)
	{
		free(memo->ptr);
		memo->ptr = NULL;
	}
	if (memo)
	{
		free(memo);
		memo = NULL;
	}
}
