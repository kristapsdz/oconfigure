#include "../config.h"

#include <string.h> /* memrchr */

int
main(void)
{
	const char *v = "abcdefgh";

	if (memrchr(v, 'a', 8) == NULL)
		return 1;
	if (memrchr(v, 'z', 8) != NULL)
		return 1;

	return 0;
}
