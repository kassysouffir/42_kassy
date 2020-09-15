#include "ast.h"
#include "grammar.h"
#include "lexer.h"

struct node_list *rule_list()
{
	struct node_and_or *and_or = rule_and_or(); //FIXME do rule_and_or
	if (!and_or)
		return NULL;
	struct node_list *node_list = malloc(sizeof(struct node_list));
	node_list->commands = and_or;
	node_list->next = NULL;

	struct node_list *curr_list = node_list;
	if (!global_shell->lexer->head)
		return NULL;
	while (global_shell->lexer->head->type == SEMICOLON 
			|| global_shell->lexer->head->type == AND
			|| global_shell->lexer->head->type == NL)
	{
		token_pop();
		while(global_shell->lexer->head->type == NL)
			token_pop();
		and_or = rule_and_or();
		if (and_or != NULL)
		{
			struct node_list *new_node = malloc(sizeof(struct node_list));
			new_node->next = NULL;
			new_node->commands = and_or;
			curr_list->next = new_node;
			curr_list = curr_list->next;
		}
		else
			return node_list;
	}
	if (global_shell->lexer->head->type == AND || global_shell->lexer->head->type == SEMICOLON)
		token_pop();
	return node_list;
}
