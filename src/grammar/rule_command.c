#include "ast.h"
#include <stdbool.h>
#include "lexer.h"
#include "grammar.h"

struct node_command *rule_command()
{
	struct node_command *cmd = malloc(sizeof(struct node_command));
	struct node_simple *s_cmd = rule_simple_command();
	if (s_cmd)
	{
		cmd->command = s_cmd;;
		cmd->type = SIMPLE;
		return cmd;
	}
	struct node_shell *shell_cmd = rule_shell_cmd();
	if (shell_cmd)
	{
		cmd->command = shell_cmd;
		cmd->type = SHELL;
		return cmd;
	}
	struct node_func *fc_cmd = rule_funcdec();
	if (fc_cmd)
	{
		cmd->command = fc_cmd;
		cmd->type = FUNC;
		return cmd;
	}
	free(cmd);
	return NULL;
}
