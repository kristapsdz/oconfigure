#include "../config.h"

#include <sys/types.h>
#include <unistd.h>

int
main(void)
{
	uid_t uid = getuid();

	if (setresuid(uid, uid, uid) == -1)
		return 1;
	return 0;
}
