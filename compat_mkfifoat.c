#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>

int
mkfifoat(int fd, const char *path, mode_t mode)
{
	int	curfd, newfd;

	/* Get our current directory then switch to the given one. */

	if (fd != AT_FDCWD) {
		if ((curfd = open(".", O_RDONLY | O_DIRECTORY, 0)) == -1)
			return -1;
		if (fchdir(fd) == -1)
			return -1;
	}

	if ((newfd = mkfifo(path, mode)) == -1)
		return -1;

	/* This leaves the file if it fails. */

	if (fd != AT_FDCWD && fchdir(curfd) == -1)
		return -1;

	return newfd;
}
