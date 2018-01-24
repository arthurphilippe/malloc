/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** blocks
*/

#include "my_malloc.h"

/*
** Splits a memory block using some-kind of katana
** Takes:
** 	- a pointer to the block being splited ;
** 	- the size to keep on the first block.
** Uses:
**	- split a block to the size requested by the user if it is too large.
*/
void split_block(mblock_t *to_split, size_t size)
{
	mblock_t	*sub = to_split + size;

	sub->previous = to_split;
	sub->next = to_split->next;
	sub->size = to_split->size - size;
	sub->is_free = TRUE;
	sub->contents = sub + 1;
	if (to_split->next != NULL)
		to_split->next->previous = sub;
	to_split->next = sub;
	to_split->size = size - sizeof(mblock_t);
}

/*
** Merges two blocks using some kind of powerfull welder
** Takes:
** 	- a pointer to the first block of the two being merged.
** Uses:
** 	- merge to blocks that are free in order to facilitate re-allocation
** 		or memory release.
*/
void merge_blocks(mblock_t *to_merge)
{
	to_merge->size += to_merge->next->size + sizeof(mblock_t);
	to_merge->next = to_merge->next->next;
	if (to_merge->next != NULL)
		to_merge->next->previous = to_merge;
}
