#include "ast.h"
#include "lexer.h"
#include <stdio.h>
#include "grammar.h"

struct node_compound *rule_do_group()
{
    if (global_shell->lexer->head && global_shell->lexer->head->type == DO)
    {
        token_pop();
        struct node_compound *cmd = rule_compound();
        if (!cmd)
        {
            fprintf(stderr, "Syntax error: Expected compound");
            return NULL;
        }
        if (global_shell->lexer->head && global_shell->lexer->head->type != DONE)
        {
            fprintf (stderr, "Syntax error: expected DONE at the end of statement");
            return NULL;
        }
        token_pop();
        return cmd;
    }
    else
        return NULL;
}
