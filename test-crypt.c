#define _GNU_SOURCE /* old linux */
#define _DEFAULT_SOURCE /* new linux */
#include <unistd.h>

int main(void)
{
	char	*v;

	v = crypt("this_is_a_key", "123455");
	return v == NULL;
}
