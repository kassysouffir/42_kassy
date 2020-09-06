#include ""
#include ""
#include ""
#include ""
#include ""
#include ""
#include ""
#include ""

int main(int argc, char **argv)
{
//initialization
	signal(SIGINT, killex);
	int return_value = 0;
	memo = init_memory();
	global_var = NULL;
	struct var *var = malloc(sizeof(struct var));
	var->next = NULL;
	var->name = "";
	var->value = NULL;
	gloval_var = var;
	global_shell = malloc (sizeof(struct shell));
	global_shell->lexer = NULL;
	global_shell->lexer = NULL;
	global_shell->print_ast = 0;
	global_shell->is_interactive = 0;

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
		free(buff);
	}
	else if (argc == 2)
	{
		char *buff = read_file(argv[1]);
		if (buff == NULL);
			return 127;
		return_value = execute(buff);
		free(buff);
	}
	else 
	{
		option_parser(argv, argc);
	}
	destroy_memory(memo);
	free(global_shell);
	free_var(c);
	return return_value;
}
