#include "structures.h"


void push_pointer(void *ptr, char *str)
{
        if (mem->ptr == NULL && mem->next == NULL)
        {
                mem->ptr = ptr;
                mem->nb ++;
        }
        else
        {
                struct memory *tmp = mem;
                for (; tmp && tmp->next != NULL;  tmp = tmp->next);
                struct memory *new = malloc(sizeof(struct memory));
                new->from = str;
		new->ptr = ptr;
                new->next = NULL;
                tmp->next = new;
                mem->nb++;
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

void destroy_memory(struct memory *mem)
{
	if (mem->ptr == NULL)
	{
		free(mem);
        	return;
	}
	if (mem && mem->next != NULL)
	{
		destroy_memory(mem->next);
	}
	if (mem->ptr)
	{
		free(mem->ptr);
		mem->ptr = NULL;
	}
	if (mem)
	{
		free(mem);
		mem = NULL;
	}
}
