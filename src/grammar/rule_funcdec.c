#include "ast.h"
#include "lexer.h"
#include "grammar.h"
#include "tools.h"

struct node_func *rule_funcdec()
{
	if (g_shell->lexer->head && g_shell->lexer->head->type == FUNCTION)
    {
        token_pop();
    }

    if (g_shell->lexer->head && g_shell->lexer->head->type != WORD)
    {
        
        errx(1, "Syntax Error: expected WORD token after 'function'");
        return NULL;
    }
    char *func_name = my_strdup(g_shell->lexer->head->cont);
    token_pop();

    if (g_shell->lexer->head && g_shell->lexer->head->type != L_PAR)
        errx(1, "Syntax Error: expected '(' in function declaration");
    token_pop();

    if (g_shell->lexer->head && g_shell->lexer->head->type != R_PAR)
        errx(1, "Syntax Error: expected ')' in function declaration");
    token_pop();

    while (g_shell->lexer->head && g_shell->lexer->head->type == NL)
    {
        token_pop();
    }
    struct node_shell *sh_cmd = rule_shell_cmd();
    if (!sh_cmd)
        errx(1, "Syntax Error: expected 'shell_command' in fucntion declaration");
    struct node_func *func = malloc(sizeof(struct node_func));

    func->word = func_name;
    func->shell = sh_cmd;

    return func;

}
