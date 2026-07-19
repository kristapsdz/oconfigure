#include "../config.h"

#if HAVE_MD5
# include <sys/types.h>
# include <md5.h>
#endif

#include <string.h> /* strcmp */

int 
main(void)
{
	MD5_CTX ctx;
	char result[MD5_DIGEST_STRING_LENGTH];

	MD5Init(&ctx);
	MD5Update(&ctx, (const uint8_t *)"abcd", 4);
	MD5End(&ctx, result);

	if (strcmp(result, "e2fc714c4727ee9395f324cd2e7f331f"))
		return 1;

	return 0;
}

