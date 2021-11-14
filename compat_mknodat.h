#include <sys/types.h> /* size_t, mode_t, dev_t */

/*
 * Compatibility for mknodat(2).
 */
int mknodat(int, const char *, mode_t, dev_t);
