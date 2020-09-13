#include "variable.h"

void free_var(struct var *var)
{
	if (!var)
		return;
	if (var && var->next)
		free_var(var->next);
	free(var);
}

void push_var(struct var *var)
{
        if (g_var == NULL)
        {
                g_var = var;
        }       
        else
        {
                struct var *tmp = g_var;
                for (; tmp && tmp->next != NULL; tmp = tmp->next);
                tmp->next = var;
        }
}

int match_var(const char *name, const char *cmd)
{
	if (cmd[0] != '$')
		return 1;
	if (strlen(cmd) <= strlen(name))
		return 1;
	char *st = calloc(sizeof(char*), strlen(cmd));
	strcat(st, "$");
	strcat(st, name);
	if (strcmp(st, cmd) == 0)
	{
		free(st);
		return 0;
	}
	char *str = calloc(sizeof(char*), strlen(cmd));
	strcat(str, "${");
	strcat(str, name);
	strcat(str, "}");
	if (strcmp(str, cmd) == 0)
	{
		free(st);
		free(str);
		return 0;
	}
	free(st);
	free(str);
	return 1;
}

char **replace_var(char **args, size_t nb)
{
	if (!g_var)
		return args;
    	struct var *var = g_var;
	while (var)
	{
		for (size_t i = 0; i < nb; i++)
		{
			//if (strcmp(var->name, args[i]) == 0) // if (mtch_var) == 0)
			if (match_var(var->name, args[i]) == 0)
				args[i] = var->value;
		}
		var = var->next;
	}

                //compare args[i] avec var->name
                //if same args[i] = var->value;

        return args;
}