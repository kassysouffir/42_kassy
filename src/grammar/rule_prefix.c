#include "ast.h"
#include "../lexer/lexer.h"
#include "grammar.h"

struct node_prefix *init_prefix(char *word, struct node_redir *redir)
{
    struct node_prefix *new = malloc(sizeof(struct node_prefix));
    new->redir = redir; 
    new->word = word;
    return new;
}

struct node_prefix *rule_prefix()
{
    struct node_prefix *pref = NULL;
    if (g_shell->lexer->head && g_shell->lexer->head->type == ASSIGNEMENT)
    {
        pref = init_prefix(g_shell->lexer->head->cont, NULL);
        token_pop();
        return pref;
    }
    struct node_redir *redir = rule_redir();
    if (redir)
    {
        pref = init_prefix(NULL, redir);
        return pref;
    }
    return NULL;


}
