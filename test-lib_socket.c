#include <sys/socket.h>

int
main(void)
{
	int fds[2], c;

	c = socketpair(AF_UNIX, SOCK_STREAM, 0, fds);
	return c == -1;
}
