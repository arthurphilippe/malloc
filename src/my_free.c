/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** free
*/

#include "my_malloc.h"
#include "pthread_lock.h"

pthread_mutex_t g_malloc_lock;

/*
** Computes how much to free when a page has been emptied
*/
static void free_out_of_page(mblock_t *to_free, mblock_t *heap)
{
	size_t page_size = getpagesize();
	size_t current_page_pos = (((size_t) to_free - (size_t) heap) + 1) * page_size;
	size_t diff;

	if ((to_free->size + ((size_t) to_free) - (size_t) heap) > page_size) {
		if (to_free->previous)
			to_free->previous->next = NULL;
		diff = (size_t) ((to_free + to_free->size) - heap)
			- current_page_pos;
		to_free->size = (size_t) to_free->size - diff;
		sbrk(-diff);
	}
}

/*
** The almight free function.
*/
void free(void *ptr)
{
	mblock_t *to_free;

	if (!ptr || get_heap_head() == (void *) -1 || ptr < get_heap_head()) {
		// write(2, "no heap or ptr under heap\n", 27);
		return;
	}
	pthread_mutex_lock(&g_malloc_lock);
	to_free = (mblock_t *) ptr - 1;
	if (to_free->next != NULL && to_free->next->is_free == TRUE)
		merge_blocks(to_free);
	if (to_free->previous && to_free->previous->is_free == TRUE) {
		to_free = to_free->previous;
		merge_blocks(to_free);
	}
	to_free->is_free = TRUE;
	if (!to_free->next)
		free_out_of_page(to_free, get_heap_head());
	pthread_mutex_unlock(&g_malloc_lock);
}
