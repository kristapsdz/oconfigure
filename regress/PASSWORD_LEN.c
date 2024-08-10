#include "../config.h"

#include <pwd.h>

int
main(void)
{
#ifdef _PASSWORD_LEN
	return 0;
#else
	return 1;
#endif
}
