#define _GNU_SOURCE
#include <string.h>

int
main(void)
{
	char *a = memmem("hello, world", strlen("hello, world"), "world", strlen("world"));
	return(NULL == a);
}
