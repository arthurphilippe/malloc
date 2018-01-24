/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** calloc
*/

#include "my_malloc.h"

void *calloc(size_t nmemb, size_t size)
{
	char	*ptr = malloc(nmemb * size);

	if (!ptr)
		return (ptr);
	for (size_t i = 0; i < (nmemb * size) ; ++i)
		ptr[i] = 0;
	return (ptr);
}
