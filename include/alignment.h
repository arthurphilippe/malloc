/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** allignment
*/

#ifndef ALIGNMENT_H_
	#define ALIGNMENT_H_

	#include <unistd.h>

const size_t ALIGNMENT = sizeof(void *);

/*
** Returns an memory aligned size.
*/
static inline size_t align_size(size_t size)
{
	return ((size + ALIGNMENT - 1) & ~(ALIGNMENT - 1));
}

#endif /* !ALIGNMENT_H_ */
