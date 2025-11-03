#include "../config.h"

#include <stdlib.h>
#include <string.h> /* strcmp */
#include <unistd.h>

#if HAVE_CRYPT
/*
 * This uses the bcrypt format found on OpenBSD (and others?).
 */
static const char *
_gensalt_bcrypt(void)
{
	size_t		  i;
	static char 	  salt[] = "$2b$12$......................";
	const char *const seedchars =
		"./0123456789ABCDEFGHIJKLMNOPQRST"
		"UVWXYZabcdefghijklmnopqrstuvwxyz";

	for (i = 0; i < 22; i++)
		salt[i + 7] = seedchars[random() % 64];

	return salt;
}

/*
 * This uses the traditional version.
 */
static const char *
_gensalt_trad(void)
{
	size_t		  i;
	static char 	  salt[] = "$1$........";
	const char *const seedchars =
		"./0123456789ABCDEFGHIJKLMNOPQRST"
		"UVWXYZabcdefghijklmnopqrstuvwxyz";

	for (i = 0; i < 8; i++)
		salt[i + 3] = seedchars[random() % 64];

	return salt;
}

int 
main(void)
{
	const char	*hash, *result, *seed;
	char	 	 buf[64];

	/* Hash the password. */

	seed = _gensalt_bcrypt();
	hash = crypt("this_is_a_password", seed);
	if (hash == NULL ||
	    (strlen(hash) < 13 && strcmp(hash, seed))) {
		/* puts("falling back to traditional"); */
		hash = crypt("this_is_a_password", _gensalt_trad());
	}

	/* Compare the hash and the password. */

	memcpy(buf, hash, sizeof(buf));
	result = crypt("this_is_a_password", buf);
	return strcmp(result, buf) == 0 ? 0 : 1;
}

#else

int 
main(void)
{
	return 0;
}

#endif
