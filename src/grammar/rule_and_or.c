#include "ast.h"
#include "../lexer/lexer.h"
#include "grammar.h"

struct node_and_or *init_and_or(struct node_pipeline *pipe)
{
	struct node_and_or *new = malloc(sizeof(struct node_and_or)); 
	new->next = NULL;
	new->pipeline = pipe;
	new->type = NODE_NONE;
	return new;
}

struct node_and_or *rule_and_or()
{
	if (g_shell->lexer->head->type == ENDOF)
		return NULL;
	struct node_pipeline *pipe = rule_pipeline();
	if (pipe)
	{
		struct node_and_or *andor = init_and_or(pipe);
		struct node_and_or *cur = andor;
		while (g_shell->lexer->head && (g_shell->lexer->head->type == OR || g_shell->lexer->head->type == AND))
		{
			if (g_shell->lexer->head->type == OR)
				cur->type = NODE_OR;
			else if (g_shell->lexer->head->type == AND)
				cur->type = NODE_AND;
			token_pop();

			while (g_shell->lexer->head && g_shell->lexer->head->type == NL)
				token_pop();

			pipe = rule_pipeline();
			if (pipe)
			{
				struct node_and_or *next = init_and_or(pipe);
				cur->next = next;
				cur = next;
			}
			else
			{
				errx(1, "Wrong syntax: expected 'pipeline'");
				return NULL;
			}
		}
		return andor;
	}
	return NULL;
}

