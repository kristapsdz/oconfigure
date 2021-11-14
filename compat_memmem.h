#include <sys/types.h> /* size_t, mode_t, dev_t */

/*
 * Compatibility for memmem(3).
 */
void *memmem(const void *, size_t, const void *, size_t);
