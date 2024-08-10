#include <string.h>

int main(void)
{
	const char *a = "foo", *b = "bar";

	if (timingsafe_bcmp(a, b, 2) &&
	    timingsafe_memcmp(a, b, 2))
		return 1;

	return 0;
}
