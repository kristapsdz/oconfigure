#include <sys/sysmacros.h>

int
main(void)
{
	return !minor(0);
}
