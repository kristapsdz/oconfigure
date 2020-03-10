int
mkfifoat(int fd, const char *path, mode_t mode)
{
	int	curfd;

	/* Get our current directory then switch to the given one. */

	if (fd != AT_FDCWD) {
		if ((curfd = open(".", O_RDONLY | O_DIRECTORY, 0)) == -1)
			return -1;
		if (fchdir(fd) == -1)
			return -1;
	}

	if (mkfifof(path, mode) == -1)
		return -1;
	if (fd != AT_FDCWD && fchdir(curfd) == -1)
		return -1;
}
