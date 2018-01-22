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
}
