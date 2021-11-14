#include <sys/types.h> /* size_t, mode_t, dev_t */

/*
 * Compatibility for recallocarray(3).
 */
extern void *recallocarray(void *, size_t, size_t, size_t);
