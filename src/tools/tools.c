#include "tools.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void *safe_malloc(size_t size)
{
	void *ptr = malloc(size);
	if (!ptr)
	{
		fprintf(stderr, "Allocation error\n");
		return NULL;
	}
	return ptr;	
}

void *safe_calloc(size_t nmemb, size_t size)
{
	void *ptr = calloc(nmemb, size);
	if (!ptr)
	{
		fprintf(stderr, "Allocation error\n");
		return NULL;
	}
	return ptr;
}

char *my_strdup(char *str)
{
	int j = 0;
	for (; str[j] != '\0'; j++);
	char *s = malloc(j+1);
	int i = 0;
	for (; i < j; i++)
	{
		s[i] = str[i];
	}
	s[i] = '\0';
	return s;
}

char *my_itoa(int value, char *s)
{
    size_t num = 0;
    int neg = 0;

    if (value <= 0)
    {
        *s = '0';
        num = 1;
        neg = value;
        value = -value;
    }

    for (int i = value; i; i = i/10)
        num++;
    for (size_t j = num; j > 0; j--)
    {
        *(s + j - 1) = value % 10 +'0';
        value = value / 10;
    }
    if (neg)
        *s = '-';
    *(s + num) = 0;
    return s;
}