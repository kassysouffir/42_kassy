#ifndef AST_H
#define AST_H

#include <stdio.h>


/**
 * @brief enume and_or_type
 * @param NODE_AND, NODE_OR, NODE_NONE
 * @return 
 */
enum and_or_type
{
    NODE_AND,
    NODE_OR,
    NODE_NONE
};



/**
 * @brief struct node_pipeline
 * @param node_command, node_pipeline
 * @return
 */
struct node_pipeline
{
    struct node_command *command;
    struct node_pipeline *next;
};


/**
 * @brief struct node_and_or
 * @param and_or_type, node_pipeline, node_and_or
 * @return
 */
struct node_and_or
{
    enum and_or_type type;
    struct node_pipeline *pipeline;
    struct node_and_or *next;
};


/**
 * @brief struct node_compound
 * @param node_and_or, node_compound
 * @return
 */
struct node_compound
{
    struct node_and_or *commands;
    struct node_compound *next;
};


/**
 * @brief struct node_if
 * @param condition, if_body, else_body
 * @return 
 */
struct node_if
{
    struct node_compound *condition;
    struct node_compound *if_body;
    struct node_else *else_body;
};



/**
 * @brief struct node_else
 * @param elif_condition, elif_body, else_node
 * @return
 */
struct node_else
{
    struct node_compound *elif_condition;
    struct node_compound *elif_body;
    struct node_else *else_node;
};


/**
 * @brief struct node_while
 * @param condition, body
 * @return
 */
struct node_while
{
    struct node_compound *condition;
    struct node_compound *body;
};



/**
 * @brief struct node_until
 * @param condition, body
 * @return
 */
struct node_until
{
    struct node_compound *condition;
    struct node_compound *body;
};



/**
 * @brief struct node_for
 * @param word, words, body
 * @return
 */
struct node_for
{
    char *word;
    char **words;
    struct node_compound *body;
};




/**
 * @brief enum node_type
 * @param COMPOUND, NODE_IF, NODE_WHILE, NODE_UNTIL, NODE_FOR, NODE_CASE
 * @return
 */
enum node_type
{
    COMPOUND,
    NODE_IF,
    NODE_WHILE,
    NODE_UNTIL,
    NODE_FOR,
    NODE_CASE
};



/**
 * @brief union shell_command
 * @param node_if, node_while, node_until, node_for, node_compound
 * @return
 */
union shell_command
{
    struct node_if *node_if;
    struct node_while *node_while;
    struct node_until *node_until;
    struct node_for *node_for;
    struct node_compound *node_compound;
};



/**
 * @brief struct node_shell
 * @param node_type, shell_command
 * @return
 */
struct node_shell
{
    enum node_type type;
    union shell_command child;
};



/**
 * @brief struct node_redir
 * @param ionumber, op, word
 * @return
 */
struct node_redir
{
    int ionumber;
    char *op;
    char *word;
};



/**
 * @brief struct node_element
 * @param word, redir
 * @return
 */
struct node_element
{
    char *word;
    struct node_redir *redir;
};



/**
 * @brief struct node_prefix
 * @param word, redir
 * @return
 */
struct node_prefix
{
    char *word;
    struct node_redir *redir;
};



/**
 * @brief struct node_func
 * @param word, shell
 * @return
 */
struct node_func
{
    char *word;
    struct node_shell *shell;
};



/**
 * @brief struct node_simple
 * @param node_prefix, node_element, node_simple
 * @return
 */
struct node_simple
{
    struct node_prefix *prefix;
    struct node_element *element;
    struct node_simple *next;
};



/**
 * @brief enum command_type
 * @param SIMPLE, SHELL, FUNC
 * @return
 */
enum command_type
{
    SIMPLE,
    SHELL,
    FUNC
};



/**
 * @brief union command
 * @param node_simple, node_shell, node_func
 * @return
 */
union command
{
    struct node_simple *simple;
    struct node_shell *shell;
    struct node_func *func;
};


/**
 * @brief struct node_command
 * @param command_type, command
 * @return
 */
struct node_command
{
    enum command_type type;
    void *command;
    //union command command;
};


/**
 * @brief struct node_list
 * @param node_and_or, node_list
 * @return
 */
struct node_list
{
    struct node_and_or *commands;
    struct node_list *next;
};


/**
 * @brief struct node_input
 * @param node_list
 * @return 
 */
struct node_input
{
    struct node_list *list;
};



/**
 * @brief Create node_pipeline
 * @param node_command
 * @return node_pipleine
 */
struct node_pipeline *create_node_pipeline(struct node_command *command);

/**
 * @brief destroy  node_pipeline
 * @param node_pipeline
 * @return 
 */
void destroy_node_pipeline(struct node_pipeline* node);


/**
 * @brief Create node_and_or
 * @param and_or_type, node_pipeline
 * @return node_and_or
 */
struct node_and_or *create_node_and_or(enum and_or_type type,
                                       struct node_pipeline *pipeline);


/**
 * @brief destroy node_and_or
 * @param node_and_or
 * @return 
 */
void destroy_node_and_or(struct node_and_or *node);

/**
 * @brief Create node_compound
 * @param node_and_or
 * @return node_compound
 */
struct node_compound *create_node_compound(struct node_and_or *commands);

/**
 * @brief destroy node_compound
 * @param node_compound
 * @return 
 */
void destroy_node_compound(struct node_compound *node);

/**
 * @brief Create node_if
 * @param condition, if_body, else_body
 * @return node_if
 */
struct node_if *create_node_if(struct node_compound *condition,
                               struct node_compound *if_body,
                               struct node_else *else_body);

/**
 * @brief destroy node_if
 * @param node_compound
 * @return 
 */
void destroy_node_if(struct node_if *node);


/**
 * @brief Create node_while
 * @param condition, body
 * @return node_while
 */
struct node_while *create_node_while(struct node_compound *condition,
                                     struct node_compound *body);

/**
 * @brief destroy node_while
 * @param node_while
 * @return 
 */
void destroy_node_while(struct node_while *node);


/**
 * @brief Create node_until
 * @param condition, body
 * @return node_until
 */
struct node_until *create_node_until(struct node_compound *condition,
                                     struct node_compound *body);

/**
 * @brief destroy node_until
 * @param node_until
 * @return 
 */
void destroy_node_until(struct node_until *node);


/**
 * @brief Create node_for
 * @param word, words, body
 * @return node_for
 */
struct node_for *create_node_for(char *word, char **words,
                                 struct node_compound *body);

/**
 * @brief destroy node_for
 * @param node_for
 * @return 
 */
void destroy_node_for(struct node_for *node);

/**
 * @brief Create node_shell
 * @param node_type, shell_command
 * @return node_shell
 */
struct node_shell *create_node_shell(enum node_type type,
                                                   union shell_command child);

/**
 * @brief Create node_shell
 * @param node_shell
 * @return 
 */
void destroy_node_shell(struct node_shell *node);


/**
 * @brief Create node_redir
 * @param io, op, word
 * @return node_redir
 */
struct node_redir *create_node_redir(int io, char *op, char *word);

/**
 * @brief destroy node_redir
 * @param node_redir
 * @return 
 */
void destroy_node_redir(struct node_redir *node);


/**
 * @brief Create node_element
 * @param word, redir
 * @return node_element
 */
struct node_element *create_node_element(char *word, struct node_redir *redir);

/**
 * @brief destroy node_element
 * @param node_element 
 * @return 
 */
void destroy_node_element(struct node_element *node);


/**
 * @brief Create node_prefix
 * @param word, redir
 * @return node_prefix
 */
struct node_prefix *create_node_prefix(char *word, struct node_redir *redir);


/**
 * @brief destroy node_prefix
 * @param node_prefix
 * @return 
 */
void destroy_node_prefix(struct node_prefix *node);


/**
 * @brief Create node_func
 * @param word, shell
 * @return node_func
 */
struct node_func *create_node_func(char *word, struct node_shell *shell);


/**
 * @brief destroy node_func
 * @param node_func
 * @return 
 */
void destroy_node_func(struct node_func *node);


/**
 * @brief Create node_simple
 * @param prefix, element
 * @return node_simple
 */
struct node_simple *create_node_simple(struct node_prefix *prefix,
                                      struct node_element *element);

/**
 * @brief destroy node_simple
 * @param node_simple
 * @return 
 */
void destroy_node_simple(struct node_simple *node);


/**
 * @brief Create node_command
 * @param type, command
 * @return node_command
 */
struct node_command *create_node_command(enum command_type type, void* command);
/**
 * @brief destroy  node_command
 * @param node_command
 * @return 
 */

void destroy_node_command(struct node_command *node);


/**
 * @brief Create node_list
 * @param node_and_or
 * @return node_list
 */
struct node_list *create_node_list(struct node_and_or *commands);


/**
 * @brief destroy node_list
 * @param node_list
 * @return 
 */
void destroy_node_list(struct node_list *node);


/**
 * @brief Create node_input
 * @param node_list
 * @return node_input
 */
struct node_input *create_node_input(struct node_list *list);


/**
 * @brief destroy node_input
 * @param node_input
 * @return 
 */
void destroy_node_input(struct node_input *node);


/**
 * @brief print dot
 * @param node_input
 * @return 0 or 1
 */
int print_dot(struct node_input *root);



/**
 * @brief print pipeline
 * @param node, stream
 * @return 
 */
void print_pipeline(struct node_pipeline *node, FILE *stream);


/**
 * @brief print node_and_or
 * @param node, stream
 * @return
 */
void print_node_and_or(struct node_and_or *node, FILE *stream);


/**
 * @brief print node_compound
 * @param node, stream
 * @return
 */
void print_node_compound(struct node_compound *node, FILE *stream);


/**
 * @brief print node_if
 * @param node, stream
 * @return
 */
void print_node_if(struct node_if *node, FILE *stream);


/**
 * @brief print node_until
 * @param node, stream
 * @return 
 */
void print_node_until(struct node_until *node, FILE *stream);


/**
 * @brief print node_while
 * @param node, stream
 * @return
 */
void print_node_while(struct node_while *node, FILE *stream);


/**
 * @brief print node_for
 * @param node, stream
 * @return
 */
void print_node_for(struct node_for *node, FILE *stream);


/**
 * @brief print node_shell
 * @param node, stream
 * @return
 */
void print_node_shell(struct node_shell *node, FILE *stream);


/**
 * @brief print node_redir
 * @param node, stream
 * @return
 */
void print_node_redir(struct node_redir *node, FILE *stream);


/**
 * @brief print node_element
 * @param node, stream
 * @return
 */
void print_node_element(struct node_element *node, FILE *stream);


/**
 * @brief print node_prefix
 * @param node, stream
 * @return
 */
void print_node_prefix(struct node_prefix *node, FILE *stream);


/**
 * @brief print node_simple
 * @param node, stream
 * @return
 */
void print_node_simple(struct node_simple *node, FILE *stream);


/**
 * @brief print node_func
 * @param node, stream
 * @return
 */
void print_node_func(struct node_func *node, FILE *stream);


/**
 * @brief print node_command
 * @param node, stream
 * @return
 */
void print_node_command(struct node_command *node, FILE *stream);


/**
 * @brief print node_list
 * @param node, stream
 * @return
 */
void print_node_list(struct node_list *node, FILE *stream);


/**
 * @brief print node_input
 * @param node, stream
 * @return
 */
void print_node_input(struct node_input *node, FILE *stream);


#endif /* ! AST_H */