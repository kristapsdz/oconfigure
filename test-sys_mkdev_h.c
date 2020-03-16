#include <sys/types.h>
#include <sys/mkdev.h>

int
main(void)
{
	return !minor(0);
}
