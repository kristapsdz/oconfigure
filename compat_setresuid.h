#include <sys/types.h> /* size_t, mode_t, dev_t */

/*
 * Compatibility for setresuid(2).
 */
int setresuid(uid_t ruid, uid_t euid, uid_t suid);
