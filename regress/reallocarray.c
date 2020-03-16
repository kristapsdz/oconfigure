#include "../config.h"

#include <stdlib.h> /* reallocarray */

int
main(void)
{
	char	*ptr = NULL;
	size_t	 nm = 10, sz = 10;

	if ((ptr = reallocarray(ptr, nm, sz)) == NULL)
		return 1;
	if ((ptr = reallocarray(ptr, nm + 20, sz)) == NULL)
		return 1;

	/* For brevity, don't free. */

	return 0;
}
