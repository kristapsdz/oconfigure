#include <sys/types.h>
#include <unistd.h>

int
main(void)
{
	if (setresuid(-1, -1, -1) == -1)
		return 1;
	return 0;
}
