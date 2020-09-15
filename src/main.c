#include "tools.h"
#include "structures.h"
#include "prompt.h"
#include "execution.h"
#include "tools.h"
#include "variable.h"
#include "lexer.h"
#include "option.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "read.h"

struct var *init()
{
	memo = init_memory();
	global_var = NULL;
	struct var *var = malloc(sizeof(struct var));
	var->next = NULL;
	var->name = "";
	var->value = NULL;
	global_shell = malloc (sizeof(struct shell));
	global_shell->lexer = NULL;
	global_shell->lexer = NULL;
	global_shell->print_ast = 0;
	global_shell->is_interactive = 0;
	return var;
}
int main(int argc, char **argv)
{
//initialization
	signal(SIGINT, killex);
	int return_value = 0;
	struct var *var = init();
	global_var = var;
//Mode
	if (isatty(0) && argc == 1) //interactive
	{
		prompt();
	}
	else if (isatty(1) && argc == 1) //stdin
	{
		char *buffer = read_stdin();
		if (!buffer)
			return 127;
		return_value = execute(buffer);
		free(buffer);
	}
	else if (argc == 2 && is_file(argv[1]) == 0) //file
	{
		char *buff = read_file(argv[1]);
		if (buff == NULL)
			return 127;
		return_value = execute(buff);
		free(buff);
	}
	else //commandline
	{
		option_parser(argv, argc);
	}
	//killing memory
	destroy_memory(memo);
	free(global_shell);
	free_var(var);
	return return_value;
}
