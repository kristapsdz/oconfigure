#if defined(__linux__) || defined(__wasi__)
# define _DEFAULT_SOURCE /* new glibc */
# define _XOPEN_SOURCE /* old glibc */
#endif
#if defined(__sun)
# ifndef _XOPEN_SOURCE /* SunOS already defines */
#  define _XOPEN_SOURCE /* XPGx */
# endif
# define _XOPEN_SOURCE_EXTENDED 1 /* XPG4v2 */
# ifndef __EXTENSIONS__ /* SunOS already defines */
#  define __EXTENSIONS__ /* reallocarray, etc. */
# endif
#endif
#include <unistd.h>

int main(void)
{
	char	*v;

	v = crypt("this_is_a_key", "123455");
	return v == NULL;
}
