/*
** EPITECH PROJECT, 2017
** malloc
** File description:
** show memory allocated
*/

#include <stdio.h>
#include "my_malloc.h"

void show_block(mblock_t *to_show, enum boolean all)
{
	if (to_show->is_free == TRUE)
		dprintf(1, "F ");
	else if (all == TRUE)
		dprintf(1, "A ");
	dprintf(1, "%p - %p : %lu bytes\n",
		to_show->contents,
		(void *) to_show->contents + to_show->size,
		to_show->size);
}

void show_alloc_mem(void)
{
	mblock_t *in_heap = get_heap_head();

	dprintf(1, "break : %p\n", sbrk(0));
	if (!in_heap)
		return;
	while (in_heap) {
		if (in_heap->is_free == FALSE)
			show_block(in_heap, FALSE);
		in_heap = in_heap->next;
	}
}

void show_all_alloc_mem(void)
{
	mblock_t *in_heap = get_heap_head();

	dprintf(1, "---------------\nbreak : %p\n", sbrk(0));
	if (!in_heap)
		return;
	while (in_heap) {
		show_block(in_heap, TRUE);
		in_heap = in_heap->next;
	}
}
