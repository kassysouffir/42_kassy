#include "lexer.h"
#include "ast.h"
#include <stdio.h>
#include "grammar.h"

struct node_else *rule_else()
{
    struct node_else *node = NULL;
    if (g_shell->lexer->head->type == ELSE)
    {
        token_pop();
        struct node_compound *body = rule_compound();
        if (body)
        {
            node = malloc(sizeof(struct node_else));
            node->elif_condition = NULL;
            node->else_node = NULL;
            node->elif_body = body;
            return node;
        }
    }
    else if (g_shell->lexer->head && g_shell->lexer->head->type == ELIF)
    {
        token_pop();
        struct node_compound *condition = rule_compound();
        if (condition)
        {
            node = malloc(sizeof(struct node_else));
            node->elif_condition = condition;
        }
        else 
        {
            fprintf (stderr, "Syntax ERROR: conditon expected after ELIF");
            return NULL;
        }
        if (g_shell->lexer->head && g_shell->lexer->head->type == THEN)
        {
            token_pop();
        }
        else
        {
            fprintf(stderr, "Syntax ERROR: THEN expected after condition");
            return NULL;
        }
        struct node_compound *body = rule_compound();
        if (body)
        {
            node->elif_body = body;
        }
        else 
            return NULL;

        node->else_node = rule_else();
        return node;       
    }
    else 
        return NULL;
    return node;
}
