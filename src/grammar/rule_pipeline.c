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
	if (!global_shell->lexer->head)
		return NULL;
	if (global_shell->lexer->head->type == BANG)
	{
		global_shell->is_not = 1;
		token_pop();
	}
	struct node_command *cmd = rule_command();
	if (cmd)
	{
		struct node_pipeline *pipe = init_pipeline(cmd);
		struct node_pipeline *cur = pipe;
		while (global_shell->lexer->head && global_shell->lexer->head->type == PIPE)
		{
			token_pop();
			while (global_shell->lexer->head && global_shell->lexer->head->type == NL)
				token_pop();
			cmd = rule_command();
			if (cmd)
			{
				struct node_pipeline *new = init_pipeline(cmd);
				cur->next = new;
				cur = new;
			}
			else 
				errx(1, "Syntax error: Unexpected '%s' after '|'", global_shell->lexer->head->str);
		}
		return pipe;
	}
	else
		return NULL;
}
