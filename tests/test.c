#include <unistd.h>

void myputchar(char c)
{
	write(1, &c, 1);
}

void *malloc(size_t kappa)
{
	write(2, "wololo\n", 8);
	return (0);
}
