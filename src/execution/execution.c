#define _DEFAULT_SOURCE

#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "execution.h"
#include "tools.h"
#include "variable.h"

int execute(char *str)
{
	struct tokenlist *tok_l = lexer(str);
	global_shell->lexer = tok_l;
	
	set_var();
	struct node_list *list = rule_list();
	global_shell->list = list;
	
	if (!list && tok_l->head)
		return 1;

	int res = exec_list(list);
	if (res != 0)
		res = 127;

    destroy_node_list(list);

	char *cres = malloc(10);
    	push_pointer(cres, "exe");
    	cres = my_itoa(res, cres);
    	update_var("?", cres);
    	if (global_shell && global_shell->is_interactive == 1)
		return 0;
	return res;
}


int exec(char **args)
{
    pid_t pid = fork();
    int status;
    if (pid == -1)
    {
	errx(1,"Fork execution error");
    }
    if (pid == 0)
    {
        status = execvp(args[0], args);
	errx(127,"%s: command not found",args[0]);
    }
    else
    {
        do {
            pid_t wpid = waitpid(pid, &status, WUNTRACED);
            if (wpid == -1)
                return 1;
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return status;
}

int exec_and_or(struct node_and_or *node)
{
    if (node->type == NODE_NONE)
        return exec_pipeline(node->pipeline);

    int val = exec_pipeline(node->pipeline);
    enum and_or_type type = node->type;

    for (struct node_and_or *tmp = node->next; tmp; tmp = tmp->next)
    {
        if (type == NODE_AND)
            val = val && exec_pipeline(tmp->pipeline);
        else
            val = val || exec_pipeline(tmp->pipeline);
        type = tmp->type;
    }
    return val;
}

int exec_compound(struct node_compound *node)
{
    struct node_compound *tmp = node;
    for (; tmp->next; tmp = tmp->next)
    {
        exec_and_or(tmp->commands);
    }
    return exec_and_or(tmp->commands);
}

int exec_else(struct node_else *node)
{
	if (node->elif_condition != NULL)
	{
		if (exec_compound(node->elif_condition))
			return exec_compound(node->elif_body);
		else
			return exec_else(node->else_node);
	}
	else
	{
		return exec_else(node->else_node);
	}
}

int exec_if(struct node_if *node)
{
    if (exec_compound(node->condition))
    {
        return exec_compound(node->if_body);
    }
    else
    {
        return exec_else(node->else_body);
    }
}

int exec_while(struct node_while *node)
{
    int res = 0;
    while (exec_compound(node->condition))
    {
        res = exec_compound(node->body);
    }
    return res;
}

int exec_pipeline(struct node_pipeline *node)
{
    int res = 0;
    for (struct node_pipeline *tmp = node; tmp; tmp = tmp->next)
    {
        res = exec_command(node->command);
    }
    return res;
}

int exec_until(struct node_until *node)
{
    int res = 0;	
    while (!exec_compound(node->condition))
    {
        exec_compound(node->body);
    }
    return res;
}

int exec_for(struct node_for *node)
{
    int res = 0;
    for (int i = 0; node->words[i]; i++)
    {
        res = exec_compound(node->body);
    }
    return res;
}

int exec_shell(struct node_shell *node)
{
    if (node->type == NODE_IF)
    {
        return exec_if(node->child.node_if);
    }
    if (node->type == NODE_WHILE)
    {
        return exec_while(node->child.node_while);
    }
    if (node->type == NODE_UNTIL)
    {
        return exec_until(node->child.node_until);
    }
    if (node->type == NODE_FOR)
    {
        return exec_for(node->child.node_for);
    }
    return 0;
}

int exec_simple(struct node_simple *node)
{
    int cmd = 0;
    struct node_simple *tmp = node;
    size_t nb = 10;
    size_t size_args = 0;
    char **args = safe_malloc(sizeof(char*) * nb);
    push_pointer(args, "exec");
    int res = 0;
    for (; tmp; tmp = tmp->next)
    {
	if (size_args == nb - 1)
	{
	    nb += 10;
	    args = realloc(args, sizeof(char*) * nb);
	}
        if (tmp->element)
        {
	    if (tmp->next == NULL)
	    {
		char *tp = mystrdup(tmp->element->word);
		push_pointer(tp, "exec simple");
	        args[size_args] = tp;
		args[size_args+1] = NULL;
		cmd++;
		break;
	    }
	    char *tp = mystrdup(tmp->element->word);
	    push_pointer(tp, "exec simple");
	    args[size_args] = tp;
	    size_args++;
	    cmd++;
        }
	else if (tmp->prefix)
	{
		continue;
	}
    }
    if (cmd == 0)
	    return 0;
    size_args++;
    /*if (is_builtin(args, size_args))
	   res = exec_builtin(args, size_args);
    else*/
    {
	    args = replace_var(args, size_args);
	    res = exec(args);
    }
    return res;
}

int exec_command(struct node_command *node)
{
    if (node->type == SIMPLE)
    {
        return exec_simple(node->command);
    }
    if (node->type == SHELL)
    {
        return exec_shell(node->command);
    }
    if (node->type == FUNC)
    {
	    return 1;
    }
    return 0;

}

int exec_list(struct node_list *node)
{
    struct node_list *tmp;
    int res = 0;
    for (tmp = node; tmp; tmp = tmp->next)
    {
       res = exec_and_or(tmp->commands);
    }
    return res;
}

int exec_input(struct node_input *node)
{
    return exec_list(node->list);
}
