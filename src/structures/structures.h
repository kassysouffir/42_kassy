#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "lexer.h"
#include <stdio.h>
#include "ast.h"


/**
 * @brief struct shell
 * @param tokenlist, print_ast, node_list, is_interactive
 * @return
*/
struct shell
{
    struct tokenlist *lexer;
	int print_ast;
	struct node_list *list;
	int is_interactive;
	int is_not;
	//struct general ast;               
};


/**
 * @brief struct memory
 * @param ptr, next
 * @return
*/
struct memory
{
	void *ptr;
	struct memory *next;
	int nb;
	char *from;
};

/**
 * @brief global struct memory
 * @param 
 * @return
*/
struct memory *memo;

/**
 * @brief global struct shell
 * @param
 * @return
*/
struct shell *global_shell;


/**
 * @brief struct memory
 * @param
 * @return
*/
struct memory *init_memory(void);

/**
 * @brief struct memory
 * @param ptr
 * @return
*/
void push_pointer(void *ptr, char *str);

/**
 * @brief destroy memory 
 * @param memory
 * @return
*/
void destroy_memory();

#endif
