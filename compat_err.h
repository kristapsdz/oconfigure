#include <stdarg.h>

/*
 * Compatibility functions for err(3).
 */
extern void err(int, const char *, ...) __attribute__((noreturn));
extern void errc(int, int, const char *, ...) __attribute__((noreturn));
extern void errx(int, const char *, ...) __attribute__((noreturn));
extern void verr(int, const char *, va_list) __attribute__((noreturn));
extern void verrc(int, int, const char *, va_list) __attribute__((noreturn));
extern void verrx(int, const char *, va_list) __attribute__((noreturn));
extern void warn(const char *, ...);
extern void warnx(const char *, ...);
extern void warnc(int, const char *, ...);
extern void vwarn(const char *, va_list);
extern void vwarnc(int, const char *, va_list);
extern void vwarnx(const char *, va_list);
