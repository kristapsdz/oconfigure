#include <sys/cdefs.h>

#ifndef __dead
# define __dead __attribute__((__noreturn__))
#endif /* !__dead */

#ifndef __pure
# define __pure __attribute__((__pure__))
#endif /* !__pure */

#ifndef __unused
# define __unused __attribute__((__unused__))
#endif /* !__unused */

#ifndef __used
# define __used __attribute__((__used__))
#endif /* !__used */
