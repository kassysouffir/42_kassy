#include "ast.h"
#include "lexer.h"
#include "grammar.h"

struct node_compound *init_compound(struct node_and_or *cmd)
{
	struct node_compound *new = malloc(sizeof(struct node_compound));
	new->commands = cmd;
	new->next = NULL;
	return new;
}

struct node_compound *rule_compound()
{
	while (global_shell->lexer->head && global_shell->lexer->head->type == NL)
	{
		token_pop();
	}
	struct node_compound *compound = NULL;
	struct node_and_or *cmd = rule_and_or();
	if (cmd)
	{
		struct node_compound *compound = init_compound(cmd);
		struct node_compound *cur = compound;
		while (global_shell->lexer->head && (global_shell->lexer->head->type == SEMICOLON 
				|| global_shell->lexer->head->type == AND 
				|| global_shell->lexer->head->type == NL))
		{
			token_pop();
			while (global_shell->lexer->head && (global_shell->lexer->head->type == AND 
						|| global_shell->lexer->head->type == SEMICOLON 
						|| global_shell->lexer->head->type == NL))
				token_pop();
			cmd = rule_and_or();
			if (cmd != NULL)
			{
				struct node_compound *new = init_compound(cmd);
				cur->next = new;
				cur = new;
			}
		}
		if (global_shell->lexer->head && (global_shell->lexer->head->type == SEMICOLON 
					|| global_shell->lexer->head->type == AND))
			token_pop();
		return compound;
	}
	return compound;
}
