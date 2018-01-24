/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** realloc
*/

#include "my_malloc.h"

void *realloc(void *ptr, size_t size)
{
	char		*n_ptr;
	mblock_t	*old = ptr - 1;
	char		*old_arr = ptr;

	if (!ptr || !(n_ptr = malloc(size)))
		return (NULL);
	for (size_t i = 0; i < old->size ; ++i)
		n_ptr[i] = (char) old_arr[i];
	free(ptr);
	return (n_ptr);
}
