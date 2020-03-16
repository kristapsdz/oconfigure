#include "../config.h"

#include <stdlib.h> /* recallocarray */

int
main(void)
{
	char	*ptr = NULL;
	size_t	 nm = 10, sz = 10, i;

	if ((ptr = recallocarray(ptr, 0, nm, sz)) == NULL)
		return 1;

	for (i = 0; i < nm * sz; i++) {
		if (ptr[i] != 0)
			return 1;
		ptr[i] = 1;
	}

	if ((ptr = recallocarray(ptr, nm, nm + 20, sz)) == NULL)
		return 1;

	for (i = 0; i < nm * sz; i++)
		if (ptr[i] != 1)
			return 1;
	for ( ; i < (nm + 20) * sz; i++)
		if (ptr[i] != 0)
			return 1;

	/* For brevity, don't free. */

	return 0;
}
