#include <sys/types.h> /* size_t, mode_t, dev_t */

/*
 * Compatibility for strlcat(3).
 */
extern size_t strlcat(char *, const char *, size_t);
