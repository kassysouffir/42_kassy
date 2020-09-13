#ifndef PROMPT_H
#define PROMPT_H

#include "execution.h"
#include <signal.h>
#include "structures.h"
#define HISTORY_FILE ".42sh_history"


void prompt(void);
void killex(int sign);

#endif
