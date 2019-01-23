#include <unistd.h>

int
main(void)
{
	return -1 != unveil(NULL, NULL);
}
