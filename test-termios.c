#include <sys/ioctl.h>
#include <string.h> /* memset */
#include <termios.h>

int
main(void)
{
	struct winsize	 size;

	memset(&size, 0, sizeof(struct winsize));
	if (ioctl(1, TIOCGWINSZ, &size) == -1)
		return 72;
	return size.ws_col;
}
