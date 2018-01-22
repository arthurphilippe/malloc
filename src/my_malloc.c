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
	return (size + (sizeof(size_t) - 1)) & ~(sizeof(size_t) - 1);
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
		head->isFree = FALSE;
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
	while (head && (head->isFree || head->size  < size)) {
		*previous = head;
		head = head->next;
	}
	*available = head;
	return (0);
}

static void split_block(mblock_t *first, size_t size)
{
	mblock_t	*sub = first + size;

	sub->previous = first;
	sub->next = first->next;
	sub->size = first->size - size;
	sub->isFree = TRUE;
	sub->contents = sub + 1;
	if (first->next != NULL)
		first->next->previous = sub;
	first->next = sub;
	first->size = size - sizeof(mblock_t);
}

static void merge_blocks(mblock_t *merged)
{
	merged->size += merged->next->size + sizeof(mblock_t);
	merged->next = merged->next->next;
	if (merged->next != NULL)
		merged->next->previous = merged;
}

/*
** I do not belive this one needs an intro.
** Behold before the discount edition of malloc.
*/
void *malloc(size_t size)
{
	mblock_t	*previous;
	mblock_t	*available;
	size_t		aligned_size = align_size(size);

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
		available->isFree = FALSE;
		available->contents = available + 1;
		previous->next = available;
	}
	else if (aligned_size + sizeof(size_t) < available->size) {
		split_block(available, aligned_size);
		available->isFree = FALSE;
	}
	return (available->contents);
}

void free(void *ptr)
{
	mblock_t *toFree;

	write(2, "Freeing is futile\n", 19);
	if (!ptr)
		return;
	if (ptr < get_heap_head())
		write(2, "err 2", 6);
	// if (ptr > sbrk(0))
	// 	write(2, "err 3", 6);
	toFree = (mblock_t *) ptr - 1;

	if (toFree->next != NULL && toFree->next->isFree == TRUE)
		merge_blocks(toFree);
	if (toFree->previous->isFree == TRUE) {
		toFree = toFree->previous;
		merge_blocks(toFree);
	}
	if (!toFree->next) {
		toFree->previous->next = NULL;
		sbrk(- toFree->size - sizeof(mblock_t));
	}
	toFree->isFree = TRUE;
	write(2, "kappa\n", 7);
}
