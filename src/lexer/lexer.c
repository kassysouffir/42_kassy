#include "lexer.h"
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "tools.h"

char *flush(char *buff)
{
	free(buff);
	char * f = calloc(sizeof(char*), 200);
	return f;
}

struct tokenlist *lexer(char *input)
{
    int k = 0;
    struct tokenlist *token_list = tok_init();
    if (!token_list)
    {
        fprintf(stderr, "alloc error lexer\n");
		return NULL;
    }
    token_list->len = 0;
    token_list->head = NULL;
    char *buff = safe_calloc(sizeof(char *), 200);
    int len = strlen(input);
    int po = 0;
    int co = 0;
    for (int i = 0; i < len; i++)
    {
        po = is_operator(buff, k-1);
        co = is_operator(buff, i);

        if (input[i] == '\0')
            break;
        else if (strcmp(buff, "") == 0 && input[0] == ' ')
            continue;
        else if (po > 0 && po == co)
        {
            buff[k] = input[i];
            k++;
        }
        else if (co > 0 && buff && buff[0] != '\0')
        {
            pitoken(buff, token_list);
			k = 0;
            buff[k] = input[i];
        }
        if (po > 0 && po != co)
        {
            pitoken(buff, token_list);
            if (input[i] != ' ')
            {
                buff[k] = input[i];
            }
        }
        else if (input[i] == '!')
        {
            if (strcmp(buff, "") != 0)
            {
                pitoken(buff, token_list);
				k = 0;
            }
            struct token *token = token_create(BANG, "!");
            token_list = push_tok(token_list, token);
        }
        else if (input[i] == '\'')
		{
			if (strcmp(buff, "") != 0)
			{
                pitoken(buff, token_list);
				k = 0;
			}
			struct token *tok = token_create(SINGLEQ, "'");
			token_list = push_tok(token_list, tok);
		}
        else if (input[i] == '"')
		{
			if (strcmp(buff, "") != 0)
			{
				pitoken(buff, token_list);
				k = 0;
			}
			struct token *tok = token_create(DOUBLEQ, "'");
			token_list = push_tok(token_list, tok);
        }
        else if (input[i] == '#')
		{
			i = ignore_comment(i, input);
		}
        else if (input[i] == ' ' || input[i] == ';' || input[i] == '\n')
		{
			pitoken(buff, token_list);
			k = 0;
			if (input[i] == ';') 
			{
				struct token *token = token_create(SEMICOLON, ";");
				token_list = push_tok(token_list, token);
				continue;
			}
			else if (input[i] == '\n')
			{
				struct token *token = token_create(NL, "\n");
				token_list = push_tok(token_list, token);
				continue;
			}
		}
        else 
        {
            buff[k] = input[i];
            k++;
        }
    }    
    if (strcmp(buff, "") != 0)	
	{
		pitoken(buff, token_list);
	}
	if (token_list->tail->type != SEMICOLON && token_list->tail->type != ENDOF)
		token_list = push_tok(token_list,token_create(ENDOF, "eof"));

	free(buff);
	return token_list;     
}

void pitoken(char * buff, struct tokenlist *token_list)
{
    char *tmp = mystrdup(buff);
    push_pointer(tmp, "lexer");
    struct token *token = token_create(get_type(buff), tmp);
    token_list = push_tok(token_list, token);
    buff = flush(buff);
}

int ignore_comment(int i, char *str)
{
	while(str[i] != '\n')
        i++;
	return i;
}

int is_operator(char *input, int i)
{
	if (input && i >= 0)
	{
		char c = input[i];
		switch(c)
		{
			case '&':
				return 1;
			case '|':
				return 2;
			case ';':
				return 3;
			case ')':
				return 4;
			case '(':
				return 5;
			default:
				return 0;

		}
	}
	return -1;
}
