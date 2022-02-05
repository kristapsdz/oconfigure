#include <linux/landlock.h>
#include <linux/prctl.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdint.h>

#ifndef landlock_create_ruleset
static inline int landlock_create_ruleset(const struct landlock_ruleset_attr *const attr,
	const size_t size, const __u32 flags)
{
	return syscall(__NR_landlock_create_ruleset, attr, size, flags);
}
#endif

#ifndef landlock_restrict_self
static inline int landlock_restrict_self(const int ruleset_fd,
	const __u32 flags)
{
	return syscall(__NR_landlock_restrict_self, ruleset_fd, flags);
}
#endif

int
main(void)
{
	uint64_t mask = LANDLOCK_ACCESS_FS_READ_FILE | LANDLOCK_ACCESS_FS_WRITE_FILE;
	struct landlock_ruleset_attr rules = {
		.handled_access_fs = mask
	};
	int fd = landlock_create_ruleset(&rules, sizeof(rules), 0);

	if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0))
		return 1;
	return landlock_restrict_self(fd, 0) ? 1 : 0;
}
