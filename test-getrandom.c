#include <sys/random.h>
#include <stdlib.h>

int
main(void)
{
	ssize_t len;
	int num;

	len = getrandom(&num, sizeof(len), 0);
	return (len != -1) ? 0 : 1;
}
