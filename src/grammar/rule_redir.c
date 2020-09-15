#include "ast.h"
#include "grammar.h"
#include "lexer.h"

int is_redir (enum type type)
{
    if (type == GREATER)
        return 1;
    if (type == LOWER)
        return 1;
    if (type == DGREATER)
        return 1;
    if (type == DLOWER)
        return 1;
    if (type == DLOWERM)
        return 1;
    if (type == LESSAND)
        return 1;
    if (type == GREATAND)
        return 1;
    if (type == GREATOR)
        return 1;
    if (type == LG)
        return 1;
    return 0;
}

struct node_redir *rule_redir()
{
    struct node_redir *node_redir = malloc(sizeof(struct node_redir));
    node_redir->ionumber = -1;
    if (global_shell->lexer->head && global_shell->lexer->head->type == IONUMBER)
    {
        node_redir->ionumber = atoi(global_shell->lexer->head->str);
        token_pop();
    }
    if (global_shell->lexer->head && is_redir(global_shell->lexer->head->type) == 0)
    {
	free(node_redir);
        return NULL;
    }
    else
    {
        node_redir->word = global_shell->lexer->head->str;
        token_pop();
    }
    if (global_shell->lexer->head && global_shell->lexer->head->type == WORD)
    {
        node_redir->word = global_shell->lexer->head->str;
        return node_redir;
    }
    else
    {
        fprintf(stderr, "Syntax ERROR; expected WORD after redirection");
        free(node_redir);
	return NULL;
    }
    free(node_redir);
    return NULL;
}
