/*
 * Linux doesn't (always?) have this.
 */

#include <sys/socket.h>

int
main(void)
{
	int fd[2];
	socketpair(AF_UNIX, SOCK_STREAM|SOCK_NONBLOCK, 0, fd);
	return 0;
}
