#include "ast.h"
#include "lexer.h"
#include "stdio.h"
#include "grammar.h"

struct node_for *rule_for()
{
    struct node_for *node_for = NULL;
    if (g_shell->lexer->head && g_shell->lexer->head->type != FOR)
        return NULL;
    token_pop();
    if (g_shell->lexer->head && g_shell->lexer->head->type != WORD)
    {
        fprintf(stderr, "Syntax ERROR: expected WORD after 'for'");
        return NULL;
    }
    node_for = malloc(sizeof(struct node_for));
    node_for->word = g_shell->lexer->head->cont;
    token_pop();

    if (g_shell->lexer->head && g_shell->lexer->head->type == SEMICOLON)
       	token_pop();
    else
    {
        while (g_shell->lexer->head && g_shell->lexer->head->type == NL)
            token_pop();
        if (g_shell->lexer->head && g_shell->lexer->head->type != IN)
        {   
            fprintf(stderr, "Syntax ERROR: IN expected after WORD in for statement");
        }
        token_pop();
        int n = 0;
	int size = 10;
        node_for->words = ymalloc(sizeof(char*) * size);
        while (g_shell->lexer->head && g_shell->lexer->head->type == WORD)
        {
	    if (n == size - 1)
	    {
		    size += 10;
		    node_for->words = realloc(node_for->words, sizeof(char*)*size);
	    }
            node_for->words[n] = g_shell->lexer->head->cont;
            n++;
            if (n == 10)
                node_for->words = realloc(node_for->words, sizeof(char*) * 20 );
            token_pop();
        }
	node_for->words[n] = NULL;
        if (g_shell->lexer->head && (g_shell->lexer->head->type != SEMICOLON && g_shell->lexer->head->type != NL))
        {
            fprintf(stderr, "Syntax ERROR: expected ';' or 'NEWLINE' in for statement\n");
            free(node_for->words);
	    return NULL;
        }
	token_pop();
        while (g_shell->lexer->head->type == NL)
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
