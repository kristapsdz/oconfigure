#include <sys/types.h> /* size_t, mode_t, dev_t */

/*
 * Compatibility for strlcpy(3).
 */
extern size_t strlcpy(char *, const char *, size_t);
