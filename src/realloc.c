/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** realloc
*/

#include "my_malloc.h"

void *realloc(void *ptr, size_t size)
{
	char		*n_ptr = NULL;
	mblock_t	*old;
	char		*old_arr;

	if (!size)
		free(ptr);
	else
		n_ptr = malloc(size);
	if (!n_ptr)
		return (NULL);
	if (!ptr)
		return (n_ptr);
	old = (mblock_t *) ((void *) ptr - 1);
	old_arr = ptr;
	for (size_t i = 0; i < old->size && i < size ; ++i)
		n_ptr[i] = (char) old_arr[i];
	free(ptr);
	return (n_ptr);
}
