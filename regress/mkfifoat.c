#include "../config.h"

#include <sys/stat.h> /* mkfifoat */
#include <fcntl.h> /* AT_FDCWD */
#include <stdio.h> /* tmpnam */

int
main(void)
{
	char	*str;

	str = tmpnam(NULL);
	if (mkfifoat(AT_FDCWD, str, 0600) == -1)
		return 1;
	remove(str);
	return 0;
}
