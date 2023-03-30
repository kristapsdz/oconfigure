#include <sys/types.h> /* size_t, mode_t, dev_t */

/*
 * Compatibility for memrchr(3).
 */
void *memrchr(const void *b, int, size_t);
