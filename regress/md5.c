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
	uint8_t digest[MD5_DIGEST_LENGTH];

	MD5Init(&ctx);
	MD5Update(&ctx, (const uint8_t *)"abcd", 4);
	MD5Final(digest, &ctx);
	MD5End(&ctx, result);

	if (strcmp(result, "b0e641c998cc3eae6fa2f8726d98cddd"))
		return 1;

	return 0;
}

