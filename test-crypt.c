#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char	*v;

	v = crypt("this_is_a_key", "123455");
	return v == NULL;
}
