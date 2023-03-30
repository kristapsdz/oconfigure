#include <sys/types.h> /* size_t, mode_t, dev_t */

/*
 * Compatibility for explicit_bzero(3).
 */
extern void explicit_bzero(void *, size_t);
