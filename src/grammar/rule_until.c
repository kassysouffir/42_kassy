#include "ast.h"
#include "lexer.h"
#include <stdio.h>
#include "grammar.h"

struct node_until *rule_until()
{
    struct node_until *node_until = NULL;
    if (g_shell->lexer->head && g_shell->lexer->head->type == UNTIL)
    {
        token_pop();
        struct node_compound *condition = rule_compound();
        if (g_shell->lexer->head)
        {
            node_until = malloc(sizeof(struct node_until));
            node_until->condition = condition;
        }
        else
        {
            return NULL;
        }
        struct node_compound *body = rule_do_group();
        if (body)
        {
            node_until->body = body;
            return node_until;
        }
        else
        {
            return NULL;
        }        
    }
    return node_until;
}
