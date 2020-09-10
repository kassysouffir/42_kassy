#ifndef TOOLS_H
#define TOOLS_H

#include <stdlib.h>
#include <stdio.h>
#include "structures.h"

/**
 * @brief safe malloc
 * @param size
 * @return
*/
void *safe_malloc(size_t size);

/**
 * @brief safe calloc
 * @param nmemb, size 
 * @return
*/
void *safe_calloc(size_t nmemb, size_t size);

/**
 * @brief reproduction of strdup
 * @param string str
 * @return a duplication of the given string
*/ 
char *mystrdup(char *str);

/**
 * @brief char my_itoa
 * @param value, s
 * @return
*/
char *my_itoa(int value, char *s);



#endif
