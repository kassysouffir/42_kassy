#include "ast.h"
#include "lexer.h"
#include "grammar.h"

struct node_element *init_element(char *word, struct node_redir *redir)
{
    struct node_element *new = malloc(sizeof(struct node_element));
    char *mot = my_strdup(word);
    push_pointer(mot, "rule elt");
    new->word = mot;
    new->redir = redir;
    return new; 
}

struct node_element *rule_element()
{
    if (g_shell->lexer->head && g_shell->lexer->head->type == WORD)
    {
        struct node_element *elt = init_element(g_shell->lexer->head->cont, NULL);
        token_pop();
        return elt;
    }

    struct node_redir *redir = rule_redir();
    if (redir)
    {
        struct node_element *elt = init_element(NULL, redir);
        return elt;
    }
    return NULL;
}
