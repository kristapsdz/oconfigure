#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
	mkfifoat(AT_FDCWD, "this/path/should/not/exist", 0600);
	return 0;
}
