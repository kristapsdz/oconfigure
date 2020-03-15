#include <sys/types.h>
#include <md5.h>

int main(void)
{
	MD5_CTX ctx;
	char result[MD5_DIGEST_STRING_LENGTH];

	MD5Init(&ctx);
	MD5Update(&ctx, "abcd", 4);
	MD5End(&ctx, result);

	return 0;
}
