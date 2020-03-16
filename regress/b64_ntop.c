#include "../config.h"

#if HAVE_B64_NTOP
# include <netinet/in.h>
# include <resolv.h>
#endif

#include <string.h> /* strlen, strcmp */

int
main(void)
{
	const char	*src = "abcdefg";
	char		 dst[64], rsrc[64];
	size_t		 srcsz, dstsz;
	int		 c, rsrcsz;

	/*
	 * Use static buffers for everything, making sure that they're
	 * big enough to hold results.
	 */

	srcsz = strlen(src);
	dstsz = ((srcsz + 2) / 3 * 4) + 1;

	if (dstsz >= sizeof(dst))
		return 1;
	c = b64_ntop((const unsigned char *)src, srcsz, dst, dstsz);
	if (c == -1)
		return 1;
	if (strcmp(dst, "YWJjZGVmZw=="))
		return 1;

	rsrcsz = (size_t)c / 4 * 3;
	if ((size_t)rsrcsz >= sizeof(rsrc) - 1) /* NUL terminator */
		return 1;
	c = b64_pton(dst, rsrc, rsrcsz);
	if (c == -1)
		return 1;
	rsrc[(size_t)c] = '\0';

	if (strcmp(rsrc, "abcdefg"))
		return 1;

	return 0;
}
