#include "../config.h"

#include <sys/socket.h> /* socketpair */

#if !HAVE_SOCK_NONBLOCK
# include <fcntl.h> /* fcntl */
#endif

int
main(void)
{
	int fds[2];

#if HAVE_SOCK_NONBLOCK
	if (socketpair(AF_UNIX, SOCK_STREAM|SOCK_NONBLOCK, 0, fds) == -1)
		return 1;
#else
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds) == -1)
		return 1;
	if (fcntl(fds[0], F_SETFL, fcntl(fds[0], F_GETFL, 0)|O_NONBLOCK) == -1)
		return 1;
	if (fcntl(fds[1], F_SETFL, fcntl(fds[1], F_GETFL, 0)|O_NONBLOCK) == -1)
		return 1;
#endif

	/* For simplicity, don't close fds. */
	return 0;

}
