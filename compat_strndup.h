#include <sys/types.h> /* size_t, mode_t, dev_t */

/*
 * Compatibility for strndup(3).
 */
extern char *strndup(const char *, size_t);
