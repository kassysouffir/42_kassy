#include "ast.h"
#include "lexer.h"
#include "stdio.h"
#include "grammar.h"

struct node_for *rule_for()
{
    struct node_for *node_for = NULL;
    if (global_shell->lexer->head && global_shell->lexer->head->type != FOR)
        return NULL;
    token_pop();
    if (global_shell->lexer->head && global_shell->lexer->head->type != WORD)
    {
        fprintf(stderr, "Syntax ERROR: expected WORD after 'for'");
        return NULL;
    }
    node_for = malloc(sizeof(struct node_for));
    node_for->word = global_shell->lexer->head->str;
    token_pop();

    if (global_shell->lexer->head && global_shell->lexer->head->type == SEMICOLON)
       	token_pop();
    else
    {
        while (global_shell->lexer->head && global_shell->lexer->head->type == NL)
            token_pop();
        if (global_shell->lexer->head && global_shell->lexer->head->type != IN)
        {   
            fprintf(stderr, "Syntax ERROR: IN expected after WORD in for statement");
        }
        token_pop();
        int n = 0;
	int size = 10;
        node_for->words = safe_malloc(sizeof(char*) * size);
        while (global_shell->lexer->head && global_shell->lexer->head->type == WORD)
        {
	    if (n == size - 1)
	    {
		    size += 10;
		    node_for->words = realloc(node_for->words, sizeof(char*)*size);
	    }
            node_for->words[n] = global_shell->lexer->head->str;
            n++;
            if (n == 10)
                node_for->words = realloc(node_for->words, sizeof(char*) * 20 );
            token_pop();
        }
	node_for->words[n] = NULL;
        if (global_shell->lexer->head && (global_shell->lexer->head->type != SEMICOLON && global_shell->lexer->head->type != NL))
        {
            fprintf(stderr, "Syntax ERROR: expected ';' or 'NEWLINE' in for statement\n");
            free(node_for->words);
	    return NULL;
        }
	token_pop();
        while (global_shell->lexer->head->type == NL)
        {
            token_pop();
        }

        struct node_compound *cmd = rule_do_group();
        if (cmd)
        {
            node_for->body = cmd;
            return node_for;
        }
        else
        {
            fprintf(stderr, "Syntax Error: expected 'do' in for statement");
            return NULL;
        }          
    }
    return NULL;
}
