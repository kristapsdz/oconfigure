#include <sys/types.h> /* size_t, mode_t, dev_t */

/*
 * Compatibility for reallocarray(3).
 */
extern void *reallocarray(void *, size_t, size_t);
