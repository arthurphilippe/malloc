/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** header
*/

#ifndef MY_MALLOC_H_
	#define MY_MALLOC_H_

	#include <unistd.h>

const size_t ALIGNMENT = sizeof(void *);

enum boolean {
	FALSE = 0,
	TRUE = 1
};

typedef struct		s_mblock {
	struct s_mblock	*previous;
	struct s_mblock	*next;
	size_t		size;
	enum boolean	is_free;
	void		*contents;
}			mblock_t;

#endif /* !MY_MALLOC_H_ */
