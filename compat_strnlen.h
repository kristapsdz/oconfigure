#include <sys/types.h> /* size_t, mode_t, dev_t */

/*
 * Compatibility for strnlen(3).
 */
extern size_t strnlen(const char *, size_t);
