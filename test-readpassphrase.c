#include <stddef.h>
#include <readpassphrase.h>

int
main(void)
{
	return !!readpassphrase("prompt: ", NULL, 0, 0);
}
