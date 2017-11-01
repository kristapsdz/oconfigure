#include <sys/capsicum.h>

int
main(void)
{
	cap_enter();
	return(0);
}
