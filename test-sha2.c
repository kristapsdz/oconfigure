#include <sys/types.h>
#include <sha2.h>

int main(void)
{
	SHA2_CTX ctx;
	char result[SHA256_DIGEST_STRING_LENGTH];

	SHA256Init(&ctx);
	SHA256Update(&ctx, (const unsigned char *)"abcd", 4);
	SHA256End(&ctx, result);

	return 0;
}
