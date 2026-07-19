#include "../config.h"

#include <sys/cdefs.h>
#include <stdlib.h>

__dead __used static void
exiter(int code, int __unused something)
{
	exit(code);
}

int
main(void)
{
	exiter(0, 1234);
}
