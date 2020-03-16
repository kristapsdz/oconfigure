#include "../config.h"

#include <sys/types.h>
#include COMPAT_MAJOR_MINOR_H

int
main(void)
{
	minor(0);
	return 0;
}
