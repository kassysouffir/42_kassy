#include "ast.h"
#include "lexer.h"
#include "grammar.h"

struct node_while *rule_while()
{
    struct node_while *node_while = NULL;
    if (global_shell->lexer->head->type == WHILE)
    {
        token_pop();
        struct node_compound *condition = rule_compound();
        if (!condition)
        {
            fprintf(stderr, "Syntax ERRROR: compound expected in while statement\n");
            return NULL;
        }
        node_while = malloc(sizeof(struct node_while));
        node_while->condition = condition; 
        struct node_compound *body = rule_do_group();
        if (!body)
        {
            fprintf(stderr, "Syntax Error: compound expected after 'while'\n");
            return NULL;
        }
        node_while->body = body;
        return node_while;      
    }
    else
    {
        return NULL;
    }
    return NULL;
}
