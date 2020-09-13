#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structures.h"
#include "tools.h"
#include "variable.h"

enum type
{
    SEMICOLON,
    IF,
    FI,
    THEN,
    NONE,
    DOUBLEQ,
    SINGLEQ,
    ELIF,
    ELSE,
    DO,
    DONE,
    R_BRAC,
    L_BRAC,
    L_PAR,
    R_PAR,
    WORD,
    WHILE,
    UNTIL,
    BANG,
    IONUMBER,
    FUNCTION,
    PIPE,
    OR,
    AND,
    LG,
    GREATOR,
    GREANTAND,
    LESSAND,
    DLOWERM,
    DLOWER,
    LOWER,
    GREATER,
    DGREATER,
    NL,
    ENDOF,
    CASE,
    IN,
    FOR,
    ASSIGNEMENT,
};

struct token
{
    char *str;
    enum type type;
    struct token *next;
    struct token *prev;
};

struct tokenlist 
{
    struct token *head;
    struct token *tail;
    size_t len;
};

char *flush(char *buff);
struct tokenlist *lexer(char *input);
void pitoken(char * buff, struct token_list *token_listist)
int ignore_comment(int i, char *str);
int is_operator(char *input, int i);
void set_var();
int update_var(char *name, char *value);
void assign_to_var(char *assignement);
struct tokenlist * tok_init();

int is_assignement(char *w);
enum type type_check(char *word);

enum type get_type(char *word);
struct token *token_create(enum type type, char *content);
struct tokenlist *push_tok(struct tokenlist *token_list, struct token *tok);
void token_pop();
void free_tok_list(struct tokenlist *tok_list);