#include "ast.h"
#include "lexer.h"
#include "grammar.h"

struct node_shell *rule_shell_cmd()
{
	union shell_command cmd; 
	struct node_shell *shell_cmd = malloc (sizeof(struct node_shell));
	if (global_shell->lexer->head && global_shell->lexer->head->type == L_BRAC)
	{
		token_pop();
		cmd.node_compound = rule_compound();
		if (!cmd.node_compound)
			errx(1, "Syntax error: expected compound '{'");
		shell_cmd->type = COMPOUND;
		shell_cmd->child = cmd;	
		if (global_shell->lexer->head->type != R_BRAC)
			errx(1, "Syntax error: expected '}'");
		token_pop();
		return shell_cmd;
	}

	if (global_shell->lexer->head && global_shell->lexer->head->type == L_PAR)
	{
		token_pop();
		cmd.node_compound = rule_compound();
		if (!cmd.node_compound)
			errx(1, "Syntax error: expected compound '('");
		shell_cmd->type = COMPOUND;
		shell_cmd->child = cmd;
		if (global_shell->lexer->head->type != R_PAR)
			errx(1, "Syntax error: expected ')'");
		token_pop();
		return shell_cmd;
	}

	cmd.node_for = rule_for();
	if (cmd.node_for)
	{
		shell_cmd->type = NODE_FOR;
		shell_cmd->child = cmd;
		return shell_cmd;
	}

	cmd.node_while = rule_while();
	if (cmd.node_while)
	{
		shell_cmd->type = NODE_WHILE;
		shell_cmd->child = cmd;
		return shell_cmd;
	}

	cmd.node_until = rule_until();
	if (cmd.node_until)
	{	
		shell_cmd->type = NODE_UNTIL;
		shell_cmd->child = cmd;
		return shell_cmd;
	}
	
	cmd.node_if = rule_if();
	if (cmd.node_if)
	{
		shell_cmd->type = NODE_IF;
		shell_cmd->child = cmd;
		return shell_cmd;
	}
	return shell_cmd;
}
