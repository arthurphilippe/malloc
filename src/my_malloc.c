/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** memory allocation fun
*/

#include "my_malloc.h"
#include "alignment.h"
#include "pthread_lock.h"

pthread_mutex_t g_malloc_lock;

/*
** Keeps track of the heap's head and allocates it on first call.
** returns :
** 	on success: the heap's head;
** 	on failure: (void *) -1.
*/
void *get_heap_head()
{
	static mblock_t	*head = NULL;

	if (!head) {
		head = sbrk(getpagesize());
		if (head == (void *) -1) {
			write(2, "NOOOOOOOOOOOOOOO\n", 18);
			return (head);
		}
		head->previous = NULL;
		head->next = NULL;
		head->size = ((size_t) sbrk(0) - (size_t) head)
				- sizeof(mblock_t);
		head->is_free = TRUE;
		head->contents = head + 1;
	}
	return (head);
}

/*
** Finds a free block of adequate size.
** Takes:
** 	- a block size to match;
** 	- a double pointer to a block : will be filled with
** 		the address of the block prior to the free one;
** 	- a double pointer to a block : will be filled with
** 		the address of the soon-to-be found free block;
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

inline static size_t get_pages_to_alloc(mblock_t *previous, size_t size)
{
	size_t zeroed_prev = (size_t) previous
		- (size_t) get_heap_head();
	size_t pages_requiered;
	size_t pages_allocated;
	size_t page_size = getpagesize();

	pages_requiered = zeroed_prev + size;
	pages_requiered /= page_size;
	pages_requiered += 1;
	pages_allocated = (zeroed_prev / page_size) + 1; // <-- + 1 or not + 1 ?
	// if (previous)
	return ((pages_requiered - pages_allocated) * page_size);
	// return (page_size * pages_requiered);
}

/*
** Pushes back the page break.
** takes:
** 	- the last block of the heap;
** 	- the size requiered to fit the new block.
** returns:
** 	on success: a block ready to used;
** 	on failure: a NULL pointer.
*/
static void *push_back_pagebrk(mblock_t *previous, size_t size)
{
	mblock_t *available;
	size_t size_to_alloc = get_pages_to_alloc(previous, size);

	available = (size_to_alloc) ? sbrk(size_to_alloc) : (void *) -1;
	if (available == (void *) -1) {
		write(2, "NAYYYYYY\n", 10);
		return (NULL);
	}
	available->previous = previous;
	available->next = NULL;
	available->size = size_to_alloc - sizeof(mblock_t);
	available->contents = available + 1;
	previous->next = available;
	if (previous->is_free == TRUE) {
		available = previous;
		merge_blocks(available);
	}
	return (available);
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
	pthread_mutex_lock(&g_malloc_lock);
	if (!available) {
		available = push_back_pagebrk(previous, aligned_size);
		if (available == NULL) {
			pthread_mutex_unlock(&g_malloc_lock);
			return (NULL);
		}
		// write(2, " --> alocated a block\n", 23);
	}
	if (aligned_size + sizeof(ALIGNMENT) < available->size) {
		split_block(available, aligned_size);
		// write(2, " --> found an empty block\n", 27);
	}
	available->is_free = FALSE;
	pthread_mutex_unlock(&g_malloc_lock);
	return (available->contents);
}
