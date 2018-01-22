/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** header
*/

#ifndef MALLOC_H_
	#define MALLOC_H_

	#include <unistd.h>


enum boolean {
	FALSE = 0,
	TRUE = 1
};

typedef struct		s_mblock {
	struct s_mblock	*previous;
	struct s_mblock	*next;
	size_t		size;
	enum boolean	isFree;
	void		*contents;
}			mblock_t;

#endif /* !MALLOC_H_ */
