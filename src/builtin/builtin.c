#include "builtin.h"

bool is_builtin(char **argv, int argc)
{
    if (argc != 0)
    {
        if ((strcmp(argv[0], "cd")) == 0)
            return true;
        else if ((strcmp(argv[0], "exit")) == 0)
            return true;
        else
            return false;
    }
    return false;
}

int exec_builtin(char **argv, int argc)
{
    if ((strcmp(argv[0], "echo")) == 0)
    {
	return builtin_echo(argc, argv);
    }
    else if ((strcmp(argv[0], "exit")) == 0)
    {
        return ex_builtin(argc, argv);
    }
    return 0;
}

int builtin_echo(int argc, char **argv)
{
	if (strcmp(argv[0], "--help") == 0)
	{
		printf("open man : echo");
	}	
	if (argv[0][0] == '-')
	{
		if (argv[0][1] == 'e')
		{
		}
		else if (argv[0][1] == 'n')
		{}
		else if (argv[0][1] == 'E')
		{
		}

	}
	else 
	{
		int i = 1;
		for (; i < argc; i++)
		{
			printf("%s", argv[i]);
		}
	}
	return 0;
}

void builtin_exit()
{
	destroy_node_list(global_shell->list);
	destroy_memory(memo);
	free(global_shell);
	free_var(global_var);
}

int ex_builtin(int argc, char **argv)
{
	if (argc == 1)
	{
		builtin_exit();
		exit(1);
	}
	else if (argc == 2)
	{
		builtin_exit();
		exit(atoi(argv[1]));
	}
	else
	{
		fprintf(stderr, "exit: too many arguments\n");
		return 2;
	}
}

