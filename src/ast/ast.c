#include <stdlib.h>

#include "ast.h"

struct node_and_or *create_node_and_or(enum and_or_type type,
                                       struct node_pipeline *pipeline)
{
    struct node_and_or *node = malloc(sizeof(struct node_and_or));
    if (!node)
        return NULL;
    node->type = type;
    node->pipeline = pipeline;
    node->next = NULL;
    return node;
}

void destroy_node_and_or(struct node_and_or *node)
{
    if (!node)
        return;
    destroy_node_and_or(node->next);
    destroy_node_pipeline(node->pipeline);
    free(node);
}


struct node_pipeline *create_node_pipeline(struct node_command *command)
{
    struct node_pipeline *node = malloc(sizeof(struct node_pipeline));
    if (!node)
        return NULL;
    node->command = command;
    node->next = NULL;
    return node;
}

void destroy_node_pipeline(struct node_pipeline* node)
{
    if (!node)
        return;
    destroy_node_pipeline(node->next);
    destroy_node_command(node->command);
    free(node);
}


struct node_compound *create_node_compound(struct node_and_or *commands)
{
    struct node_compound *node = malloc(sizeof(struct node_compound));
    if (!node)
        return NULL;
    node->commands = commands;
    node->next = NULL;
    return node;
}

void destroy_node_compound(struct node_compound *node)
{
    if (!node)
        return;
    if (node->commands && node->next)
    	destroy_node_compound(node->next);
    if (node->commands)
    	destroy_node_and_or(node->commands);
    if (!node->commands && node->next)
	    return;
    free(node);
}


struct node_if *create_node_if(struct node_compound *condition,
                               struct node_compound *if_body,
                               struct node_else *else_body)
{
    struct node_if *node = malloc(sizeof(struct node_if));
    if (!node)
        return NULL;
    node->condition = condition;
    node->if_body = if_body;
    node->else_body = else_body;
    return node;
}

void destroy_node_else(struct node_else *node)
{
    if (!node)
        return;
    if (node->else_node)
        destroy_node_else(node->else_node);
    destroy_node_compound(node->elif_body);
    destroy_node_compound(node->elif_condition);
    free(node->elif_body);
    free(node);
}

void destroy_node_if(struct node_if *node)
{
    destroy_node_compound(node->condition);
    destroy_node_compound(node->if_body);
    destroy_node_else(node->else_body);
    free(node);
}


struct node_while *create_node_while(struct node_compound *condition,
                                     struct node_compound *body)
{
    struct node_while *node = malloc(sizeof(struct node_while));
    if (!node)
        return NULL;
    node->condition = condition;
    node->body = body;
    return node;
}

void destroy_node_while(struct node_while *node)
{
    destroy_node_compound(node->condition);
    destroy_node_compound(node->body);
    free(node);
}


struct node_until *create_node_until(struct node_compound *condition,
                                     struct node_compound *body)
{
    struct node_until *node = malloc(sizeof(struct node_until));
    if (!node)
        return NULL;
    node->condition = condition;
    node->body = body;
    return node;
}

void destroy_node_until(struct node_until *node)
{
    destroy_node_compound(node->condition);
    destroy_node_compound(node->body);
    free(node);
}

struct node_for *create_node_for(char *word, char **words,
                                 struct node_compound *body)
{
    struct node_for *node = malloc(sizeof(struct node_for));
    if (!node)
        return NULL;
    node->word = word;
    node->words = words;
    node->body = body;
    return node;
}

void destroy_node_for(struct node_for *node)
{
    node->word = NULL;
    free(node->words);
    destroy_node_compound(node->body);
    free(node);
}

struct node_shell *create_node_shell(enum node_type type,
                                     union shell_command child)
{
    struct node_shell *node = malloc(sizeof(struct node_shell));
    if (!node)
        return NULL;
    node->type = type;
    node->child = child;
    return node;
}

void destroy_node_shell(struct node_shell *node)
{
    if (node->type == NODE_IF)
        destroy_node_if(node->child.node_if);
    else if (node->type == NODE_WHILE)
        destroy_node_while(node->child.node_while);
    else if (node->type == NODE_UNTIL)
        destroy_node_until(node->child.node_until);
    else if(node->type == NODE_FOR)
	destroy_node_for(node->child.node_for);
    else 
	destroy_node_compound(node->child.node_compound);
    free(node);
}

struct node_redir *create_node_redir(int io, char *op, char *word)
{
    struct node_redir *node = malloc(sizeof(struct node_redir));
    if (!node)
        return NULL;
    node->ionumber = io;
    node->op = op;
    node->word = word;
    return node;
}

void destroy_node_redir(struct node_redir *node)
{
    free(node->op);
    free(node->word);
    free(node);
}

struct node_element *create_node_element(char *word, struct node_redir *redir)
{
    struct node_element *node = malloc(sizeof(struct node_element));
    if (!node)
        return NULL;
    node->word = word;
    node->redir = redir;
    return node;
}

void destroy_node_element(struct node_element *node)
{
    if (node->redir)
    	destroy_node_redir(node->redir);
    free(node);
}

struct node_prefix *create_node_prefix(char *word, struct node_redir *redir)
{
    struct node_prefix *node = malloc(sizeof(struct node_element));
    if (!node)
        return NULL;
    node->word = word;
    node->redir = redir;
    return node;
}

void destroy_node_prefix(struct node_prefix *node)
{
    if (node->redir)
    	destroy_node_redir(node->redir);
    free(node);
}

struct node_func *create_node_func(char *word, struct node_shell *shell)
{
    struct node_func *node = malloc(sizeof(struct node_func));
    if (!node)
        return NULL;
    node->word = word;
    node->shell = shell;
    return node;
}

void destroy_node_func(struct node_func *node)
{
    free(node->word);
    destroy_node_shell(node->shell);
    free(node);
}

struct node_simple *create_node_simple(struct node_prefix *prefix,
                                      struct node_element *element)
{
    struct node_simple *node = malloc(sizeof(struct node_simple));
    if (!node)
        return NULL;
    node->prefix = prefix;
    node->element = element;
    node->next = NULL;
    return node;
}

void destroy_node_simple(struct node_simple *node)
{
    if (!node)
        return;
    destroy_node_simple(node->next);
    if (node->prefix)
    	destroy_node_prefix(node->prefix);
    if (node->element)
    	destroy_node_element(node->element);
    free(node);
}

struct node_command *create_node_command(enum command_type type, void* command)
{
    struct node_command *node = malloc(sizeof(struct node_command));
    if (!node)
        return NULL;
    node->type = type;
    node->command = command;
    return node;
}

void destroy_node_command(struct node_command *node)
{
    if (node->type == SIMPLE)
        destroy_node_simple(node->command);
    else if (node->type == SHELL)
        destroy_node_shell(node->command);
    else if (node->type == FUNC)
        destroy_node_func(node->command);
    free(node);
}

struct node_list *create_node_list(struct node_and_or *commands)
{
    struct node_list *node = malloc(sizeof(struct node_list));
    if (!node)
        return NULL;
    node->commands = commands;
    node->next = NULL;
    return node;
}

void destroy_node_list(struct node_list *node)
{
    if (!node)
        return;
    destroy_node_list(node->next);
    destroy_node_and_or(node->commands);
    free(node);
}

struct node_input *create_node_input(struct node_list *list)
{
    struct node_input *node = malloc(sizeof(struct node_input));
    if (!node)
        return NULL;
    node->list = list;
    return node;
}

void destroy_node_input(struct node_input *node)
{
    destroy_node_list(node->list);
    free(node);
}