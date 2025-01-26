#include "../config.h"

#if HAVE_BLOWFISH
# include <sys/types.h>
# include <blf.h>
#endif
#include <string.h>

int
main(void)
{
	blf_ctx		 c;
	char		 key[] = "AAAAA";
	char		 key2[] = "abcdefghijklmnopqrstuvwxyz";
	uint32_t	 data[10];
	uint32_t	 data2[] = {0x424c4f57l, 0x46495348l};
	uint16_t	 i;

	/* First test */

	for (i = 0; i < 10; i++)
		data[i] = i;

	blf_key(&c, (uint8_t *) key, 5);
	blf_enc(&c, data, 5);
	blf_dec(&c, data, 1);
	blf_dec(&c, data + 2, 4);

	/* Second test */

	blf_key(&c, (uint8_t *) key2, strlen(key2));
	blf_enc(&c, data2, 1);
	blf_dec(&c, data2, 1);

	return 0;
}
