/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** header
*/

#ifndef MY_MALLOC_H_
	#define MY_MALLOC_H_

	#include <unistd.h>

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

void free(void *ptr);
void *get_heap_head();
void merge_blocks(mblock_t *to_split);

#endif /* !MY_MALLOC_H_ */
