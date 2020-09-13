#include "prompt.h"
#include <readline/readline.h>
#include <readline/history.h>


void killer_exit(int sign)
{
	if (sign == SIGINT)
	{
		write_history(HISTORY_FILE);
	}
	return;
}

void prompt(void)
{
	read_history(HISTORY_FILE);
	int status = 0;
	using_history();
	global_shell->is_interactive = 1;
	char *buff = NULL;
	while(status == 0)
	{
		char *buff = "42sh>$ ";
		buff = readline(buff);
		if (buff && strcmp("", buff) == 0)
		{
			free(buff);
			continue;
		}
		if (!buff) 
			break;
		if (buff[0] == '\0')
			break;
		signal(SIGINT, killer_exit);
		status = execute(buff);
		add_history(buff);
		free(buff);
	}
	free(buff);
	write_history(HISTORY_FILE);
}
