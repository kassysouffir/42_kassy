#include "ast.h"
#include "grammar.h"
#include "lexer.h"

struct node_pipeline *init_pipeline(struct node_command *cmd)
{
	struct node_pipeline *new = malloc(sizeof(struct node_pipeline));
	new->next = NULL;
	new->command = cmd;
	return new;
}

struct node_pipeline *rule_pipeline()
{
	if (!g_shell->lexer->head)
		return NULL;
	if (g_shell->lexer->head->type == BANG)
	{
		g_shell->is_not = 1;
		token_pop();
	}
	struct node_command *cmd = rule_command();
	if (cmd)
	{
		struct node_pipeline *pipe = init_pipeline(cmd);
		struct node_pipeline *cur = pipe;
		while (g_shell->lexer->head && g_shell->lexer->head->type == PIPE)
		{
			token_pop();
			while (g_shell->lexer->head && g_shell->lexer->head->type == NL)
				token_pop();
			cmd = rule_command();
			if (cmd)
			{
				struct node_pipeline *new = init_pipeline(cmd);
				cur->next = new;
				cur = new;
			}
			else 
				errx(1, "Syntax error: Unexpected '%s' after '|'", g_shell->lexer->head->cont);
		}
		return pipe;
	}
	else
		return NULL;
}
