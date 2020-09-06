#include "ast.h"
#include "lexer.h"
#include "grammar.h"

/*struct node_shell *init_shell_command(enum node_type type)
{
	struct node_shell *sh_cmd = malloc(sizeof(struct node_shell));
	sh_cmd->type = type;
	return sh_cmd;
}*/

struct node_shell *rule_shell_cmd()
{
	union shell_command cmd; 
	struct node_shell *shell_cmd = malloc (sizeof(struct node_shell));
	if (g_shell->lexer->head && g_shell->lexer->head->type == L_BRAC)
	{
		token_pop();
		cmd.node_compound = rule_compound();
		if (!cmd.node_compound)
			errx(1, "Syntax error: expected compound '{'");
		shell_cmd->type = COMPOUND;
		shell_cmd->child = cmd;//.node_compound;	
		if (g_shell->lexer->head->type != R_BRAC)
			errx(1, "Syntax error: expected '}'");
		token_pop();
		return shell_cmd;
	}

	if (g_shell->lexer->head && g_shell->lexer->head->type == L_PAR)
	{
		token_pop();
		cmd.node_compound = rule_compound();
		if (!cmd.node_compound)
			errx(1, "Syntax error: expected compound '('");
		shell_cmd->type = COMPOUND;
		shell_cmd->child = cmd;//.node_compound;
		if (g_shell->lexer->head->type != R_PAR)
			errx(1, "Syntax error: expected ')'");
		token_pop();
		return shell_cmd;
	}

	cmd.node_for = rule_for();
	if (cmd.node_for)
	{
		shell_cmd->type = NODE_FOR;
		shell_cmd->child = cmd;//.node_for;
		return shell_cmd;
	}

	cmd.node_while = rule_while();
	if (cmd.node_while)
	{
		shell_cmd->type = NODE_WHILE;
		shell_cmd->child = cmd;//.node_while;
		return shell_cmd;
	}

	cmd.node_until = rule_until();
	if (cmd.node_until)
	{	
		shell_cmd->type = NODE_UNTIL;
		shell_cmd->child = cmd;//.node_until;
		return shell_cmd;
	}
	
	/*struct node_case *node_case = rule_case(g_shell->lexer->head);
	if (node_case)
	{
		shell_cmd = init_shell_command(node_case, NODE_CASE);
		return shell_cmd;
	}*/
	
	cmd.node_if = rule_if();
	if (cmd.node_if)
	{
		shell_cmd->type = NODE_IF;
		shell_cmd->child = cmd;//.node_if;
		return shell_cmd;
	}
	return shell_cmd;
}
