/*
** EPITECH PROJECT, 2018
** tests
** File description:
** test
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void *malloc(size_t size);
void free(void *ptr);
void show_alloc_mem(void);
void show_all_alloc_mem(void);

int main(void)
{
	show_all_alloc_mem();
	write(1, "\n", 1);
	write(1, "\n", 1);

	char *kappa = malloc(4090);
	show_all_alloc_mem();
	free(kappa);
	show_all_alloc_mem();
	return (0);

	kappa[0] = '1';
	kappa[2] = '3';
	kappa[1] = '2';
	kappa[3] = '4';
	kappa[4] = '5';
	kappa[5] = '6';
	kappa[6] = '7';
	kappa[7] = 0;
	write(1, kappa, 8);
	write(1, "\n", 1);

	char *badabou = malloc(15);

	badabou[0] = '1';
	badabou[2] = '3';
	badabou[1] = '2';
	badabou[3] = '4';
	badabou[4] = '5';
	badabou[5] = '6';
	badabou[6] = '7';
	badabou[7] = 0;
	write(1, badabou, 8);
	write(1, "\n", 1);
	// free(badabou);
	free(kappa);

	badabou = realloc(badabou, 300);

	int i = 0;
	while (i < 300) {
		badabou[i] = 'z';
		i+= 1;
	}
	char *bsartek = malloc(6000);

	i = 0;
	while (i < 6000) {
		bsartek[i] = 'z';
		i+= 1;
	}

	free(badabou);
	free(bsartek);
	bsartek = realloc(bsartek, 1120000);
	bsartek = malloc(1120000);
	char *foo1 = realloc(NULL, 1120003);
	char *foo2 = malloc(11200);
	char *foo3 = calloc(11207650, 1);
	show_all_alloc_mem();
	free(foo1);
	free(foo3);
	free(foo2);
	show_all_alloc_mem();

	i = 0;
	while (i < 1120000) {
		bsartek[i] = 'z';
		i+= 1;
	}

	free(bsartek);

	kappa = malloc(8);


	kappa[0] = '1';
	kappa[2] = '3';
	kappa[1] = '2';
	kappa[3] = '4';
	kappa[4] = '5';
	kappa[5] = '6';
	kappa[6] = '7';
	kappa[7] = 0;
	write(1, kappa, 8);
	write(1, "\n", 1);
	kappa = realloc(kappa, 3);
	write(1, "\n", 1);
	write(1, kappa, 3);
	write(1, "\n", 1);
	write(1, "\n", 1);
	kappa[0] = '1';
	kappa[2] = '3';
	kappa[1] = '2';
	write(1, kappa, 3);
	free(kappa);

	kappa = calloc(12, 1);
	free(kappa);
	show_all_alloc_mem();
}
