/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** memory allocation fun
*/

#include "my_malloc.h"

const size_t ALIGNMENT = sizeof(void *);

/*
** Returns an memory aligned size.
*/
static size_t align_size(size_t size)
{
	return ((size + ALIGNMENT - 1) & ~(ALIGNMENT - 1));
}

/*
** Keeps track of the heap's head and allocates it on first call.
** returns :
** 	on success: the heap's head ;
** 	on failure: (void *) -1.
**
** 	TODO: upon heap creation, use getpagesize
**
*/
void *get_heap_head()
{
	static mblock_t	*head = NULL;

	if (!head) {
		head = sbrk(getpagesize());
		if (head == (void *) -1)
			return (head);
		head->previous = NULL;
		head->next = NULL;
		head->size = getpagesize() - sizeof(mblock_t);
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
void merge_blocks(mblock_t *to_split)
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

	// write(2, "malloc was called\n", 19);
	if (!size || find_free_block(size + sizeof(ALIGNMENT),
			&previous, &available) != 0)
		return (NULL);
	if (!available) {
		available = sbrk(aligned_size);
		if (available == (void *) - 1)
			return (NULL);
		available->previous = previous;
		available->next = NULL;
		available->size = aligned_size - sizeof(mblock_t);
		available->contents = available + 1;
		previous->next = available;
		// write(2, " --> alocated a block\n", 23);
	}
	else if (aligned_size + sizeof(ALIGNMENT) < available->size) {
		split_block(available, aligned_size);
		// write(2, " --> found an empty block\n", 27);
	}
	available->is_free = FALSE;
	return (available->contents);
}

void *realloc(void *ptr, size_t size)
{
	char		*n_ptr;
	mblock_t	*old = ptr - 1;
	char		*old_arr = ptr;

	if (!ptr || !(n_ptr = malloc(size)))
		return (NULL);
	for (size_t i = 0; i < old->size ; ++i)
		n_ptr[i] = (char) old_arr[i];
	free(ptr);
	return (n_ptr);
}

void *calloc(size_t nmemb, size_t size)
{
	char	*ptr = malloc(nmemb * size);

	if (!ptr)
		return (ptr);
	for (size_t i = 0; i < (nmemb * size) ; ++i)
		ptr[i] = 0;
	return (ptr);
}
