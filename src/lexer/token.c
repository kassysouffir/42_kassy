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

			assign_to_var(tok->str);
		}
	}
}

int update_var(char *name, char *value)
{
	if (global_var == NULL)
		return 1;
	else
	{
		struct var *var = global_var;
		for (; var; var = var->next)
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
	size_t name_length = 0;
	while (assignement[name_length] != '=')
		name_length++;
	size_t value_lenght = 0;
	size_t egal_pos = name_length + 1;
	while (assignement[egal_pos != '\0'])
	{
		value_lenght++;
		egal_pos++;
	}
	char *name = safe_malloc(name_length + 1);
	char *value = safe_malloc(value_lenght + 1);
	push_pointer(name, "Assign");
	push_pointer(value, "Assign");
	for (size_t i = 0; i < name_length; i++)
		name[i] = assignement[i];
	name[name_length] = '\0';
	size_t j = name_length + 1;
	size_t i = 0;
	for (; assignement[j] != '\0'; i++, j++)
	{
		value[i] = assignement[j];
	}
	value[i] = '\0';
	if (update_var(name, value) == 0)
		return;
	struct var *var = safe_malloc(sizeof(struct var));
	var->name = name;
	var->value = value;
	var->next = NULL;
	push_var(var);
}

struct tokenlist *tok_init()
{
	struct tokenlist *tok = safe_malloc(sizeof(struct token));
	push_pointer(tok, "tokinit");
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
{
	if (strcmp("\n", word) == 0)
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
	if (strcmp(">", word) == 0)
		return GREATER;
	if (strcmp("<", word) == 0)
		return LOWER;
	if (strcmp("&&", word) == 0)
		return AND;
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
	struct token *tok = safe_malloc(sizeof(struct token));
	if (!tok)
	{
		fprintf(stderr, "allocation error tok_create\n");
		return NULL;
	}
	push_pointer(tok, "token create");
	tok->type = type;
	tok->str = content;
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
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tok->prev = tmp;
		tmp->next = tok;
		tok->next = NULL;
	}
	token_list->tail = tok;
	token_list->len++;
	return token_list;
}

void token_pop()
{
	if (global_shell->lexer == NULL || global_shell->lexer->head == NULL)
		return;
	struct token *first = global_shell->lexer->head->next;
	global_shell->lexer->head = first;
}

void free_tok_list(struct tokenlist *tok_list)
{
	if (!tok_list)
	{
		return;
	}
	struct token *tmp = tok_list->head;
	while (tok_list->head != NULL)
	{
		if (tok_list->head->next == NULL)
		{
			free(tok_list->head);
			break;
		}
		tmp = tok_list->head->next;
		free(tok_list->head);
		tok_list->head = tmp;
	}
	free(tok_list);
}
