#include "option.h"
#include "execution.h"
#include <stdio.h>
#include "tools.h"

void display_help()
{
	printf("Interactive mode : ./42sh > [COMMAND]\n");
	printf("Stdin mode : [COMMAND] | ./42sh\n");
	printf("File mode : ./42sh [FILE PATH]\n");
	printf("cmd line : ./42sh -c [COMMAND LINE]\n");
}
int option_parser(char **argv, int argc)
{
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-help") == 0)
		{
			display_help();
			return 0;
		}
		else if (strcmp(argv[i], "-c") == 0)
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
		else 
		{
			fprintf(stderr, "Invalid option detected");
			return 1;
		}
	}
	return 0;
}