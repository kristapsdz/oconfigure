#include "../config.h"

#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#ifdef HAVE_TERMIOS
# include <termios.h>
#endif

int
main(void)
{
#if HAVE_TERMIOS
	struct winsize	 size;

	memset(&size, 0, sizeof(struct winsize));
	if (ioctl(1, TIOCGWINSZ, &size) == -1)
		return errno != ENOTTY;
#endif
	return 0;
}
