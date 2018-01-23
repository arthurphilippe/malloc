/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** memory allocation fun
*/

#include "my_malloc.h"

/*
** Returns an memory aligned size.
*/
static size_t align_size(size_t size)
{
	return (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
	// return (size + (sizeof(size_t) - 1)) & ~(sizeof(size_t) - 1);
}

/*
** Keeps track of the heap's head and allocates it on first call.
** returns :
** 	on success: the heap's head ;
** 	on failure: (void *) -1.
*/
static void *get_heap_head()
{
	static mblock_t	*head = NULL;

	if (!head) {
		head = sbrk(align_size(sizeof(mblock_t)));
		if (head == (void *) -1)
			return (head);
		head->previous = NULL;
		head->next = NULL;
		head->size = 0;
		head->is_free = FALSE;
		head->contents = NULL;
	}
	return (head);
}

/*
** Finds a free block of adequate size.
** Takes:
** 	- a block size to match ;
** 	- a double pointer to a block : will be filled with
** 		the address of the block prior to the free one ;
** 	- a double pointer to a block : will be filled with
** 		the address of the soon-to-be found free block ;
** returns on error: -1 (otherwise 0)
*/
static int find_free_block(size_t size, mblock_t **previous, mblock_t **available)
{
	mblock_t *head = get_heap_head();

	if (head == (void *) -1)
		return (-1);
	while (head && (!head->is_free || head->size < size)) {
		*previous = head;
		head = head->next;
	}
	*available = head;
	return (0);
}

/*
** Splits a memory block using some-kind of katana
** Takes:
** 	- a pointer to the block being splited ;
** 	- the size to keep on the first block.
** Uses:
**	- split a block to the size requested by the user if it is too large.
*/
static void split_block(mblock_t *to_split, size_t size)
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
static void merge_blocks(mblock_t *to_split)
{
	to_split->size += to_split->next->size + sizeof(mblock_t);
	to_split->next = to_split->next->next;
	if (to_split->next != NULL)
		to_split->next->previous = to_split;
}

/*
** I do not belive this one needs an intro.
** Behold before the discount edition of malloc.
*/
void *malloc(size_t size)
{
	mblock_t	*previous;
	mblock_t	*available;
	size_t		aligned_size = align_size(size + sizeof(mblock_t));

	write(2, "malloc was called\n", 19);
	if (!size || find_free_block(size, &previous, &available) != 0)
		return (NULL);
	if (!available) {
		available = sbrk(aligned_size);
		if (available == (void *) - 1)
			return (NULL);
		available->previous = previous;
		available->next = NULL;
		available->size = aligned_size - sizeof(mblock_t);
		available->is_free = FALSE;
		available->contents = available + 1;
		previous->next = available;
		write(2, " --> alocated a block\n", 23);
	}
	else if (aligned_size + sizeof(size_t) < available->size) {
		split_block(available, aligned_size);
		available->is_free = FALSE;
		write(2, " --> found an empty block\n", 27);
	}
	else
		write(2, "WTF\n", 4);
	return (available->contents);
}

void free(void *ptr)
{
	mblock_t *to_free;

	write(2, "free called\n", 13);
	if (!ptr)
		return;
	if (get_heap_head() == (void *) -1 || ptr < get_heap_head()) {
		write(2, "no heap or ptr under heap\n", 27);
		return;
	}
	// if (ptr > sbrk(0))
	// 	write(2, "err 3", 6);
	to_free = (mblock_t *) ptr - 1;

	if (to_free->next != NULL && to_free->next->is_free == TRUE)
		merge_blocks(to_free);
	if (to_free->previous->is_free == TRUE) {
		to_free = to_free->previous;
		merge_blocks(to_free);
	}
	to_free->is_free = TRUE;
	if (!to_free->next) {
		to_free->previous->next = NULL;
		sbrk(- (to_free->size - sizeof(mblock_t)));
	}
	write(2, " --> free finished\n", 20);
}

void *realloc(void *ptr , size_t size)
{
	(void) ptr;
	(void) size;
	write(2, "rea-what?\n", 11);
	return (NULL);
}
