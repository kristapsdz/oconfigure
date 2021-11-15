/*
 * Make it easier to include endian.h forms.
 */
#if HAVE_ENDIAN_H
# define COMPAT_ENDIAN_H <endian.h>
#elif HAVE_SYS_ENDIAN_H
# define COMPAT_ENDIAN_H <sys/endian.h>
#elif HAVE_OSBYTEORDER_H
# define COMPAT_ENDIAN_H <libkern/OSByteOrder.h>
#elif HAVE_SYS_BYTEORDER_H
# define COMPAT_ENDIAN_H <sys/byteorder.h>
#else
# warning No suitable endian.h could be found.
# warning Please e-mail the maintainers with your OS.
# define COMPAT_ENDIAN_H <endian.h>
#endif
