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
	mblock_t	*old = (mblock_t *) ptr - 1;
	char		*old_arr;

	if (!size)
		free(ptr);
	else if (!ptr || old->size < size)
		n_ptr = malloc(size);
	if (!n_ptr)
		return (ptr);
	if (!ptr)
		return (n_ptr);
	old = (mblock_t *) ptr - 1;
	old_arr = ptr;
	for (size_t i = 0; i < old->size && i < size ; i += 1)
		n_ptr[i] = (char) old_arr[i];
	free(ptr);
	return (n_ptr);
}
