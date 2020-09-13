#include "lexer.h"

void set_var()
{
	if (global_shell->lexer->head == NULL || global_shell->lexer->head->type == ENDOF)
	{
		return;
	}
	struct token *tok = global_shell->lexer->head;
	for (; tok && tok->next != NULL && tok->type != ENDOF; tok = tok->next)
	{
		if (tok->type == ASSIGNEMENT)
		{

			assign_to_var(tok->cont);
		}
	}
}

int update_var(char *name, char *value)
{
	if (g_var == NULL)
		return 1;
	else 
	{
		struct var *var = g_var;
		for (; var ; var = var->next)
		{
			if (strcmp(var->name, name) == 0)
			{
				var->value = value;
				return 0;
			}
		}
		return 1;
	}
}

void assign_to_var(char *assignement)
{
	size_t name_len = 0;
	for (; assignement[name_len] != '='; name_len++);
	size_t value_len = 0;
	size_t egal_pos = name_len + 1;
	for (; assignement[egal_pos] != '\0'; value_len++, egal_pos++);
	char *name = ymalloc(name_len+1);
	char *value = ymalloc(value_len+1);
	push_pointer(name, "Assign");
	push_pointer(value, "Assign");
	for (size_t i = 0; i < name_len; i++)
        {
                name[i] = assignement[i];
        }
        name[name_len] = '\0';
        size_t j = name_len + 1;
        size_t i = 0;
	for (; assignement[j] != '\0' ; i++, j++)
        {
                value[i] = assignement[j];
        }
        value[i] = '\0';
	//comapre name with g_var names
	if (update_var(name, value) == 0)
	       return;	
	struct var *var = ymalloc(sizeof(struct var));
	var->name = name;
	var->value = value;
	var->next = NULL;
	push_var(var);
}

struct tokenlist * tok_init()
{
	struct tokenlist *tok = ymalloc(sizeof(struct token));
	push_pointer(tok, "tokinit");
	if (!tok)
	{
		fprintf(stderr, "allocation error token_init\n");
		return NULL;
	}
	tok->len = 0;
	tok->head = NULL;
	return tok;
}

int is_assignement(char *w)
{
	int len = strlen(w);
	for (int i = 0; i < len; i++)
	{
		if (w[i] == '=')
			return 1;
	}
	return 0;
}

enum type type_check(char *word)
{	if (strcmp("\n", word) == 0)
		return NL;
	if (strcmp("if", word) == 0)
		return IF;
	if (strcmp("then", word) == 0)
		return THEN;
	if (strcmp("else", word) == 0)
		return ELSE;
	if (strcmp("elif", word) == 0)
		return ELIF;
	if (strcmp("fi", word) == 0)
		return FI;
	if (strcmp("do", word) == 0)
		return DO;
	if (strcmp("done", word) == 0)
		return DONE;
	if (strcmp(";", word) == 0)
		return SEMICOLON;
	if (strcmp("(", word) == 0)
		return L_PAR;
	if (strcmp(")", word) == 0)
		return R_PAR;
	if (strcmp("{", word) == 0)
		return L_BRAC;
	if (strcmp("}", word) == 0)
		return R_BRAC;
	if (strcmp("|", word) == 0)
		return PIPE;
	if (strcmp("while", word) == 0)
		return WHILE;
	if (strcmp("until", word) == 0)
		return UNTIL;
	if (strcmp("in", word) == 0)
		return IN;
	if (strcmp("case", word) == 0)
		return CASE;
	if (strcmp("for", word) == 0)
		return FOR;
	if (strcmp("EOF", word) == 0)
		return ENDOF;
	if (strcmp(">",word) == 0)
		return GREATER ;
	if (strcmp("<", word) == 0)
		return LOWER;
	if (strcmp("&&", word) == 0)
		return AND ;
	if (strcmp("||", word) == 0)
		return OR;
	if (is_assignement(word) == 1)
		return ASSIGNEMENT;
	if (strcmp("function", word) == 0)
		return FUNCTION;
	return NONE;
}

enum type get_type(char *word)
{
	enum type ret = type_check(word);
	if (ret != NONE)
		return ret;
	else
		return WORD;
	return NONE;
}

struct token *token_create(enum type type, char *content)
{
	struct token *tok = ymalloc(sizeof(struct token));
	if (!tok)
	{
		fprintf(stderr, "allocation error tok_create\n");
		return NULL;
	}
	push_pointer(tok, "token create");
	tok->type = type;
	tok->cont = content;
	return tok;
}

struct tokenlist *push_tok(struct tokenlist *token_list, struct token *tok)
{
	if (token_list->head == NULL)
	{
		token_list->head = tok;
		tok->prev = NULL;
		tok->next = NULL;	
	}
	else 
	{
		struct token *tmp = token_list->head;
		for (; tmp->next != NULL; tmp = tmp->next);
		tok->prev = tmp;
		tmp->next = tok;
		tok->next = NULL;
	}
	token_list->tail = tok;
	token_list->len ++;
	return token_list;
}

struct token *delete_none_token(struct token *tok)
{
	struct token *t = tok;
	for (; t != NULL; t=t->next)
	{
		if (t->type == NONE)
		{
			struct token *tmp = t;
			t->prev->next = t->next;
			t->next->prev = t->prev;
			free(tmp->cont);
			free(tmp);
		}
	}
	return t;
}

void token_pop()
{
	if (global_shell->lexer == NULL || global_shell->lexer->head == NULL)
		return;
	struct token *first = global_shell->lexer->head->next;
	global_shell->lexer->head = first;
}

void free_tok_list(struct tokenlist *tokl)
{
	if (!tokl)
	{
		return;
	}
	struct token *tmp = tokl->head;
	while (tokl->head != NULL)
	{
		if (tokl->head->next == NULL)
		{
			free(tokl->head);
			break;
		}
		tmp = tokl->head->next;
		free(tokl->head);
		tokl->head = tmp;
	}
	free(tokl);
}
