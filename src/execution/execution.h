#ifndef EXECUTION_H
#define EXECUTION_H

#include "ast.h"
#include "structures.h"
#include "grammar.h"
#include "builtin.h"
#include "tools.h"
#include "variable.h"


int execute(char *str);

int exec(char **args);

int exec_pipeline(struct node_pipeline *node);

int exec_and_or(struct node_and_or *node);

int exec_compound(struct node_compound *node);

int exec_if(struct node_if *node);

int exec_while(struct node_while *node);

int exec_until(struct node_until *node);

int exec_for(struct node_for *node);

int exec_shell(struct node_shell *node);

int exec_element(struct node_element *node);

int exec_simple(struct node_simple *node);

int exec_command(struct node_command *node);

int exec_list(struct node_list *node);

int exec_input(struct node_input *node);

#endif /* !EXECUTION_H */
