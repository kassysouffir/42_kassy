#ifndef READ_H
#define READ_H

#include <unistd.h>
#include "tools.h"


/**
 * @brief char read_file
 * @param path
 * @return
*/
char *read_file(char *file_name);

/**
 * @brief char read_stdin
 * @param 
 * @return
*/
char *read_stdin(void);

#endif
