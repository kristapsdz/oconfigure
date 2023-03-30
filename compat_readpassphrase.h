#include <sys/types.h> /* size_t, mode_t, dev_t */

/*
 * Macros and function required for readpassphrase(3).
 */
#define RPP_ECHO_OFF 0x00
#define RPP_ECHO_ON 0x01
#define RPP_REQUIRE_TTY 0x02
#define RPP_FORCELOWER 0x04
#define RPP_FORCEUPPER 0x08
#define RPP_SEVENBIT 0x10
#define RPP_STDIN 0x20
char *readpassphrase(const char *, char *, size_t, int);
