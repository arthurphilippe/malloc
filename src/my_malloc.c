/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** memory allocation fun
*/

#include "my_malloc.h"
#include "alignment.h"

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
inline static int find_free_block(size_t size, mblock_t **previous, mblock_t **available)
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
