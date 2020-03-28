#include <stdlib.h>
#include <string.h> /* strcmp */
#include <unistd.h>

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

int main(void)
{
	const char	*hash, *result;

	/* Hash the password. */

	hash = crypt("this_is_a_password", _gensalt_bcrypt());
	if (hash == NULL)
		hash = crypt("this_is_a_password", _gensalt_trad());

	/* Compare the hash and the password. */

	result = crypt("this_is_a_pasword", hash);
	return strcmp(result, hash) == 0 ? 0 : 1;
}
