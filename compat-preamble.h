#ifdef __cplusplus
# error "Do not use C++: this is a C application."
#endif
#if !defined(__GNUC__) || (__GNUC__ < 4)
# define __attribute__(x)
#endif
#if defined(__linux__) || defined(__MINT__) || defined(__wasi__)
# define _GNU_SOURCE /* memmem, memrchr, setresuid... */
# define _DEFAULT_SOURCE /* le32toh, crypt, ... */
#endif
#if defined(__NetBSD__)
# define _OPENBSD_SOURCE /* reallocarray, etc. */
#endif
#if defined(__sun)
# ifndef _XOPEN_SOURCE /* SunOS already defines */
#  define _XOPEN_SOURCE /* XPGx */
# endif
# define _XOPEN_SOURCE_EXTENDED 1 /* XPG4v2 */
# ifndef __EXTENSIONS__ /* SunOS already defines */
#  define __EXTENSIONS__ /* reallocarray, etc. */
# endif
#endif
#if !defined(__BEGIN_DECLS)
# define __BEGIN_DECLS
#endif
#if !defined(__END_DECLS)
# define __END_DECLS
#endif

