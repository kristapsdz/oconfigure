#include <sys/types.h> /* size_t, mode_t, dev_t */

/*
 * Compatibility for mkfifoat(2).
 */
int mkfifoat(int, const char *, mode_t);
