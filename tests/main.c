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

int main(void)
{
	char *kappa = malloc(15);


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
	free(badabou);
	free(kappa);

	char *zoum = malloc(300);

	int i = 0;
	while (i < 300) {
		zoum[i] = 'z';
		i+= 1;
	}
	write(1, zoum, 300);

	char *bsartek = malloc(6000);

	i = 0;
	while (i < 6000) {
		bsartek[i] = 'z';
		i+= 1;
	}
	write(1, bsartek, 6000);

	free(zoum);
	free(bsartek);
	bsartek = malloc(1120000);
	bsartek = malloc(1120000);
	char *foo1 = malloc(1120003);
	char *foo2 = malloc(11200);
	char *foo3 = calloc(11207650, 1);
	free(foo1);
	free(foo3);
	free(foo2);

	i = 0;
	while (i < 1120000) {
		bsartek[i] = 'z';
		i+= 1;
	}
	// write(1, bsartek, 1120000);

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
	kappa[0] = '1';
	kappa[2] = '3';
	kappa[1] = '2';
	write(1, kappa, 3);
	free(kappa);

	kappa = calloc(12, 1);
	free(kappa);
}
