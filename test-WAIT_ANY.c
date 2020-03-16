#include <sys/wait.h>

int
main(void)
{
	int st;

	return waitpid(WAIT_ANY, &st, WNOHANG) != -1;
}
