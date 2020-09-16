#ifndef BUILTIN_H
#define BUILTIN_H
#include "ast.h"
#include "structures.h"
#include "variable.h"
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#define PATH_SIZE 1024
#define _GNU_SOURCE
#define _BSD_SOURCE ||_XOPEN_SOURCE >= 500

int ex_builtin(int argc, char **argv);

int cd_builtin(char **argv, int argc);

bool is_builtin(char **argv, int argc);

int exec_builtin(char **argv, int argc);

void builtin_exit();

int builtin_echo(int argc, char **argv);

int exec_builtin(char **argv, int argc);

#endif