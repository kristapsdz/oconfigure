/*
 * Linux doesn't  have this.
 */

#include <pwd.h>
#include <stdio.h>

int
main(void)
{
	printf("_PASSWORD_LEN is defined to be %ld\n", (long)_PASSWORD_LEN);
	return 0;
}
