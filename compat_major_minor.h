/*
 * Handle the various major()/minor() header files.
 * Use sys/mkdev.h before sys/sysmacros.h because SunOS
 * has both, where only the former works properly.
 */
#if HAVE_SYS_MKDEV_H
# define COMPAT_MAJOR_MINOR_H <sys/mkdev.h>
#elif HAVE_SYS_SYSMACROS_H
# define COMPAT_MAJOR_MINOR_H <sys/sysmacros.h>
#else
# define COMPAT_MAJOR_MINOR_H <sys/types.h>
#endif
