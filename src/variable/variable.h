#ifndef VARIABLE_H
#define VARIABLE_H

#include "tools.h"
#include "exec.h"


struct var
{
	char *name;
	char *value;
	struct var *next;
};

struct var* global_var;

void push_var(struct var *var);

char **replace_var(char **args, size_t nb);

void free_var(struct var *var);

void set_base_var();

#endif