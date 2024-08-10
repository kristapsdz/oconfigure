#include <unistd.h>

int
main(void)
{
	const char	*v = "password";
	char		 hash[128];

	if (crypt_newhash(v, "bcrypt,a", hash, sizeof(hash)) == -1)
		return 1;
	if (crypt_checkpass(v, hash) == -1)
		return 1;

	return 0;
}
