#include <string.h>

int
main(void)
{
	const char *foo = "bar";
	char *baz;

	baz = strndup(foo, 1);
	return(0 != strcmp(baz, "b"));
}
