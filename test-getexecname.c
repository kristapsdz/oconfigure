#include <stdlib.h>

int
main(void)
{
	const char * progname;

	progname = getexecname();
	return progname == NULL;
}
