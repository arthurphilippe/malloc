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

void molest_malloc(void)
{
	char **molestor = malloc(sizeof(char *) * 101);
	size_t i = 0;

	while (i < 50) {
		molestor[i] = malloc(96777773);
		++i;
	}
	while (i < 101) {
		molestor[i] = malloc(7774373);
		++i;
	}
	show_all_alloc_mem();
	molestor = realloc(molestor, sizeof(char *) * 68765);

	while (i < 68765) {
		molestor[i] = malloc(64);
		++i;
	}
	i -= 1;

	while (i > 0) {
		free(molestor[i]);
		--i;
	}
	free(molestor[i]);
	free(molestor);
	show_all_alloc_mem();

	char **str = malloc(sizeof(char *) * 2345);
	for (int idx = 0; idx < 2345; ++idx)
		str[idx] = malloc(sizeof(char) * 1004);
	show_all_alloc_mem();
	for (int idx = 0; idx < 2345; ++idx)
		free(str[idx]);
	free(str);
	show_all_alloc_mem();
	str = malloc(sizeof(char *) * 2345);
	for (int i = 0; i < 2345; ++i)
		str[i] = malloc(sizeof(char) * 123445);
	for (int i = 0; i < 2345; ++i)
		for (int z = 0; z < 123445; ++z)
			str[i][z] = 'a';
	for (int i = 0; i < 2345; ++i)
		str[i][123444] = '\0';
	for (int i = 0; i < 2345; ++i)
		printf("%s\n", str[i]);

}

int main(void)
{
	show_all_alloc_mem();
	write(1, "\n", 1);
	write(1, "\n", 1);

	char *kappa = malloc(4090);
	show_all_alloc_mem();
	free(kappa);
	show_all_alloc_mem();
	// return (0);

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
	// free(bsartek);
	bsartek = realloc(bsartek, 1120000);
	free(bsartek);
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

	kappa = malloc(2);

	write(1, "\n", 1);
	write(1, "\n", 1);

	kappa[0] = '1';
	kappa[1] = '2';
	kappa = realloc(kappa, 8);
	kappa[2] = '3';
	kappa[3] = '4';
	kappa[4] = '5';
	kappa[5] = '6';
	kappa[6] = '7';
	kappa[7] = 0;
	write(1, kappa, 8);
	write(1, "\n", 1);
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
	realloc(kappa, 0);

	kappa = calloc(12, 1);
	free(kappa);
	show_all_alloc_mem();
	molest_malloc();
}
