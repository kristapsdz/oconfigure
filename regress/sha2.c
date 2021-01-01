#include "../config.h"

#if HAVE_SHA2
# include <sys/types.h>
# include <sha2.h>
#endif

#include <string.h> /* strcmp */

int 
main(void)
{
	SHA2_CTX ctx;
	char result[SHA256_DIGEST_STRING_LENGTH];
	uint8_t digest[SHA256_DIGEST_LENGTH];

	SHA256Init(&ctx);
	SHA256Update(&ctx, (const uint8_t *)"abcd", 4);
	SHA256Final(digest, &ctx);
	SHA256End(&ctx, result);

	if (strcmp(result, "361ab6322fa9e7a7bb23818d839e01bddafdf47305426edd297aedb9f6202bae"))
		return 1;

	return 0;
}
