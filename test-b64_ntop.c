#include <netinet/in.h>
#include <resolv.h>

int
main(void)
{
	const char *src = "hello world";
	char output[1024];

	return b64_ntop(src, 11, output, sizeof(output)) > 0 ? 0 : 1;
}
