#include "../config.h"

#if HAVE_PASSWORD_LEN
# include <pwd.h> /* _PASSWORD_LEN */
#endif
#include <unistd.h>

int
main(void)
{
	const char	*v = "password";
	char		 hash[_PASSWORD_LEN];

	if (crypt_newhash(v, "bcrypt,a", hash, sizeof(hash)) == -1)
		return 1;
	if (crypt_checkpass(v, hash) == -1)
		return 1;

	return 0;
}
