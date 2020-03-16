#include "../config.h"

#include <sys/stat.h> /* mknodat */
#include <fcntl.h> /* AT_FDCWD */
#include <stdio.h> /* tmpnam */

int
main(void)
{
	char	*str;

	str = tmpnam(NULL);
	if (mknodat(AT_FDCWD, str, S_IFIFO | 0600, 0) == -1)
		return 1;
	remove(str);
	return 0;
}
