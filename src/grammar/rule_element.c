#include "ast.h"
#include "lexer.h"
#include "grammar.h"

struct node_element *init_element(char *word, struct node_redir *redir)
{
    struct node_element *new = malloc(sizeof(struct node_element));
    char *mot = mystrdup(word);
    push_pointer(mot, "rule elt");
    new->word = mot;
    new->redir = redir;
    return new; 
}

struct node_element *rule_element()
{
    if (global_shell->lexer->head && global_shell->lexer->head->type == WORD)
    {
        struct node_element *elt = init_element(global_shell->lexer->head->str, NULL);
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
