#include <stdlib.h>

int
main(void)
{
	return (arc4random() + 1) ? 0 : 1;
}
