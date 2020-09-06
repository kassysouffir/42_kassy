#include "read.h"
#include <stdio.h>
#include <stdlib.h>

char *read_file(char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
    { 
        fprintf(stderr, "42sh: %s: No such file or directory\n", file_name);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    size_t file_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buff = safe_malloc(file_size +1);
    fread(buff, 1, file_size, f);
    fclose(f);
    buff[file_size] = '\0';
    return buff;
}

char *read_stdin()
{
    int size = 1024;

    char *buff = ymalloc(size);

    if (!buff)
    {
        fprintf (stderr, "alloc error\n");
        return NULL;
    }
    read(0, buff, size);
    return buff;
}
