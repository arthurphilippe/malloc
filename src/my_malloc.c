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
int find_free_block(size_t size, mblock_t **previous, mblock_t **free)
{
	mblock_t *head = get_heap_head();

	if (head == (void *) -1)
		return (-1);
	while (head && (head->isFree || head->size  < size)) {
		*previous = head;
		head = head->next;
	}
	return (head);
}

/*
** I do not belive this one needs an intro.
** Behold before the discount edition of malloc.
*/
void *malloc(size_t size)
{
	mblock_t	*previous;
	mblock_t	*available;
	size_t		alligned_size = align_size(size);

	if (!size || find_free_block(size, &previous, &available) != 0)
		return (NULL);
	if (!available) {
		//set new block
	}
}
