#include <string.h>

int
main(void)
{
	const char *foo = "bar";
	size_t sz;

	sz = strnlen(foo, 1);
	return(1 != sz);
}
