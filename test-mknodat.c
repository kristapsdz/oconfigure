#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
	mknodat(AT_FDCWD, "this/path/should/not/exist", S_IFIFO | 0600, 0);
	return 0;
}
