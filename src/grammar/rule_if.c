#include "lexer.h"
#include "ast.h"
#include "grammar.h"
struct node_if *init_if_node(struct node_compound *condition, struct node_compound *if_body)
{
	struct node_if *new = malloc(sizeof(struct node_if));
	new->condition = condition;
	new->if_body = if_body;
	new->else_body = NULL;
	return new;
}


struct node_if *rule_if()
{
	if (!global_shell->lexer->head)
		return NULL;
	if (global_shell->lexer->head->type != IF)
		return NULL;
	token_pop();
	struct node_compound *condition = rule_compound();
	if (!condition)
	{
		errx(1, "Wrong syntax : compound expected after 'if'");
	}
	if (global_shell->lexer->head && global_shell->lexer->head->type != THEN)
		errx(1, "Wrong syntax: missing 'then' after 'if' statement");
	token_pop();
	struct node_compound *if_body = rule_compound();
	if (!if_body)
		errx(1, "Syntax error: compound expected after 'then'");
	struct node_if *node_if= init_if_node(condition, if_body);
	node_if->else_body = rule_else();
	if (global_shell->lexer->head && (global_shell->lexer->head && global_shell->lexer->head->type != FI))
		errx(1, "Syntax error: 'fi' expected at the end of 'if' statement");
	token_pop();
	return node_if;
}
