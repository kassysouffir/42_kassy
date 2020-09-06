/**
 * @file grammar.h
 * @brief LEXER  STRUCTURES
 * @authors kassy souffir, adrien saleh
 * @version 1.0
 */

#ifndef GRAMMAR_H
#define GRAMMAR_H
#include "lexer.h"
#include <err.h>
#include <stdlib.h>
#include "ast.h"
#include "tools.h"

/**
 * @brief grammar rule redirection
 * @param 
 * @return node redir 
*/
struct node_redir *rule_redir();


/**
 * @brief initialisation node_and_or
 * @param node_piepline 
 * @return node_and_or
*/
struct node_and_or *init_and_or(struct node_pipeline *pipe);

/**
 * @brief grammar rule node_and_or
 * @param 
 * @return node_and_or 
*/
struct node_and_or *rule_and_or();

/**
 * @brief initiaslisation node_compound
 * @param node_and_or
 * @return node_compode
*/
struct node_compound *init_compound(struct node_and_or *cmd);

/**
 * @brief grammar rule node_compound
 * @param
 * @return node_compound
*/
struct node_compound *rule_compound();

/**
 * @brief grammar rule do_group
 * @param
 * @return node_compound
*/
struct node_compound *rule_do_group();

/**
 * @brief initialisation node_element
 * @param word, redir
 * @return node_element
*/
struct node_element *init_element(char *word, struct node_redir *redir);

/**
 * @brief grammar rule node_element
 * @param 
 * @return node_element
*/
struct node_element *rule_element();

/**
 * @brief grammar rule node_else
 * @param
 * @return node_else
*/

struct node_else *rule_else();

/**
 * @brief grammar rule node_for
 * @param
 * @return node_for
*/
struct node_for *rule_for();

/**
 * @brief grammar rule node_funcdec
 * @param
 * @return node_func
*/
struct node_func *rule_funcdec();

/**
 * @brief grammar rule node_command
 * @param
 * @return node_command
*/
struct node_command *rule_command();

/**
 * @brief initialisation node_if
 * @param condition, if_body
 * @return node_if
*/
struct node_if *init_if_node(struct node_compound *condition, struct node_compound *if_body);

/**
 * @brief grammar rule node_if
 * @param 
 * @return node_if
*/
struct node_if *rule_if();

/**
 * @brief grammar rule node_list
 * @param
 * @return node_list
*/
struct node_list *rule_list();

/**
 * @brief initialisation node_pipe
 * @param node_command
 * @return node_pipeline
*/
struct node_pipeline *init_pipe(struct node_command *cmd);

/**
 * @brief grammar rule node_pipeline
 * @param
 * @return node_pipeline
*/
struct node_pipeline *rule_pipeline();

/**
 * @brief initialisation node_prefix
 * @param word, redir
 * @return node_prefix
*/
struct node_prefix *init_prefix(char *word, struct node_redir *redir);

/**
 * @brief grammar rule node_prefix
 * @param
 * @return node_prefix
*/
struct node_prefix *rule_prefix();

//struct node_shell *init_shell_command(enum node_type type);

/**
 * @brief grammar rule node_shell_cmd
 * @param
 * @return node_shell
*/
struct node_shell *rule_shell_cmd();

/**
 * @brief initialisation node_simple_cmd
 * @param pref, elt
 * @return node_simple
*/
struct node_simple *init_simple_cmd(struct node_prefix *pref, struct node_element *elt);

/**
 * @brief grammar rule node_simple_command
 * @param
 * @return node_simple
*/
struct node_simple *rule_simple_command();

/**
 * @brief grammar rule node_until
 * @param
 * @return node_until
*/
struct node_until *rule_until();

/**
 * @brief grammar rule node_while
 * @param
 * @return node_while
*/
struct node_while *rule_while();


#endif
