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

struct			s_mblock {
	struct s_mblock	*previous;
	struct s_mblock	*next;
	size_t		size;
	enum boolean	is_free;
	void		*contents;
};

typedef struct s_mblock mblock_t;

void *malloc(size_t);
void free(void *ptr);
void *get_heap_head();
void merge_blocks(mblock_t *to_merge);
void split_block(mblock_t *to_split, size_t size);
void show_alloc_mem(void);
void show_all_alloc_mem(void);

#endif /* !MY_MALLOC_H_ */
