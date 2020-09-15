#include "option.h"
#include "execution.h"
#include <stdio.h>
#include "tools.h"


int option_parser(char **argv, int argc)
{
	int i = 1;
	while (i < argc)
	{
		if (strcmp(argv[i], "-c") == 0)
		{
			if (argv[i+1] != NULL)
			{
				return execute(argv[i+1]);
			}
			else
			{
				fprintf(stderr, "42sh: -c: option requires an argument");
				return 1;
			}
		}
		else if (strcmp(argv[i], "--norc") == 0)
		{
			//TODO
			return 0;
		}
		else if (strcmp(argv[i], "--ast-print") == 0)
		{
			global_shell->print_ast = 1;
			return 0;
		}
		else if (strcmp(argv[i], "+O") == 0)
		{
			//TODO
			return 0;
		}
		else if (strcmp(argv[i], "-O") == 0)
		{		
			//TODO
			return 0;
		}
		else 
		{
			fprintf(stderr, "Invalid option detected");
			return 1;
		}
	}
	return 0;
}