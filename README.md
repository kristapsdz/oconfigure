This is a simple configuration script use for some
[BSD.lv](https://www.bsd.lv) project sources.  It is not really ready
for general use, but is used in several projects
([ksql](https://kristaps.bsd.lv/ksql),
[sblg](https://kristaps.bsd.lv/sblg),
[lowdown](https://kristaps.bsd.lv/lowdown), etc.).
Its mission is to provide [OpenBSD](https://www.openbsd.org) portability
functions and feature testing for system-specific security facilities.

To use:

1. copy
[configure](https://raw.githubusercontent.com/kristapsdz/oconfigure/master/configure),
[compats.c](https://raw.githubusercontent.com/kristapsdz/oconfigure/master/compats.c),
and
[tests.c](https://raw.githubusercontent.com/kristapsdz/oconfigure/master/tests.c)
into your source tree
2. have `include Makefile.configure` at the top of your Makefile
3. have `#include "config.h"` as the first inclusion in your sources
4. compile compile.o and link to it

Once prepared, a user just runs `./configure` prior to running `make`.
The `configure` script will check for common features as noted in the
test files, e.g., [pledge(2)](https://man.openbsd.org/pledge.2), and
also provide compatibility for other functions, e.g.,
[strlcpy(3)](https://man.openbsd.org/strlcpy.3).

If you have Makefile flags you'd like to set, set them when you invoke
`configure` as key-value pairs on the command-line, e.g.,

```
./configure PREFIX=/opt
```

The following flags are recognised and accepted: `LDFLAGS`, `CPPFLAGS`,
`DESTDIR`, `PREFIX`, `MANDIR`, `LIBDIR`, `BINDIR`, `SHAREDIR`,
`SBINDIR`, and `INCLUDEDIR`.  Un-recognised flags are discarded and
warned about.

Using oconfigure requires some work within your sources to node
compatibility areas, then some in your build environment:

```c
#include "config.h" /* required inclusion */

#if HAVE_ERR /* sometimes err.h exists, sometimes not */
# include <err.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
#if HAVE_PLEDGE /* do we have pledge? */
	if (-1 == pledge("stdio", NULL))
		err(EXIT_FAILURE, NULL);
#endif
	warnx("hello, world!"); /* compat provides this */
	return(EXIT_SUCCESS);
}
```

And then...

```sh
./configure
cc -o config.o -c config.c
cc -o main.o -c main.c
cc config.o main.o
```

Though you can just build this into your Makefile.

This framework was inspired by [mandoc](https://mdocml.bsd.lv)'s
`configure` script written by Ingo Schwarze, but has been expanded to
accept configuration values on the command line.

What follows is a description of the features and facilities provided by
the package when included into your sources.

The compatibility layer is generally provided by the excellent portable
[OpenSSH](https://www.openssh.com/).  All copyrights are noted within
the included sources.

## Capsicum

Tests for [FreeBSD](https://www.freebsd.org)'s
[Capsicum](https://www.freebsd.org/cgi/man.cgi?capsicum(4)) subsystem,
defining the `HAVE_CAPSICUM` variable with the result.
Does not provide any compatibility.
For example,

```c
#if HAVE_CAPSICUM
# include <sys/resource.h>
# include <sys/capsicum.h>
#endif
```

## err.h

Tests for the [err(3)](https://man.openbsd.org/err.3) functions,
defining `HAVE_ERR` variable with the result.

If not found, provides compatibility functions `err`, `errx`, `warn`,
`warnx`.  The `<err.h>` header inclusion needs to be guarded for systems
that include it by default; otherwise, the definitions are provided in
the generated `config.h`.

```c
#if HAVE_ERR
# include <err.h>
#endif
```

## explicit\_bzero(3)

Tests for
[explicit\_bzero(3)](https://man.openbsd.org/explicit_bzero.3), defining
`HAVE_EXPLICIT_BZERO` variable with the result.

If not found, provides a compatibility function.

## INFTIM

Some systems (like OpenBSD) define INFTIM for use with
[poll(2)](https://man.openbsd.org/poll.2).
Others don't.
This defines the `HAVE_INFTIM` variable with the results and, if not
found, defines `INFTIM` to be the proper value.

## memmem(3)

Tests for the [memmem(3)](https://man.openbsd.org/memmem.3)
function, defining `HAVE_MEMMEM` with the result.
Provides a compatibility function if not found.

## memrchr(3)

Tests for the [memrchr(3)](https://man.openbsd.org/memrchr.3)
function, defining `HAVE_MEMRCHR` with the result.
Provides a compatibility function if not found.

## memset\_s

Tests for the C11
[memset\_s](http://en.cppreference.com/w/c/string/byte/memset) function,
defining the `HAVE_MEMSET_S` variable with the result.
Does not provide a compatibility function.

## md5.h

Tests for the standalone [md5(3)](https://man.openbsd.org/md5.3)
functions, defining `HAVE_MD5` with the result.

If not found, provides a full complement of standalone (i.e., not
needing any crypto libraries) MD5 hashing functions.  These are
`MD5Init`, `MD5Update`, `MD5Pad`, `MD5Transform`, `MD5End`, and
`MD5Final`.  The preprocessor macros `MD5_BLOCK_LENGTH`,
`MD5_DIGEST_LENGTH`, and `MD5_DIGEST_STRING_LENGTH` are also defined.  

If using these functions, you'll want to guard an inclusion of the
system-default:

```c
#if HAVE_MD5
# include <md5.h>
#endif
```

## PATH\_MAX

Tests for the `PATH_MAX` variable, defining `HAVE_PATH_MAX` with the
result.
If not found, defines the `PATH_MAX` macro to be 4096.

## pledge(2)

Test for [OpenBSD](https://www.openbsd.org)'s
[pledge(2)](https://man.openbsd.org/pledge.2) function,
defining `HAVE_PLEDGE` with the result.
Does not provide any compatibility.
For example,

```c
#if HAVE_PLEDGE
# include <unistd.h> /* pledge(2) */
#endif
```

## getprogname(3)

Tests for the [getprogname(3)](https://man.openbsd.org/getprogname.3)
function, defining `HAVE_GETPROGNAME` with the result.
Provides a compatibility function if not found.

This internally tests for `__progname` and
`program_invocation_short_name` if not found, so the 
`HAVE___PROGNAME` AND `HAVE_PROGRAM_INVOCATION_SHORT_NAME` macros will
also be defined.  Do not use these: use
[getprogname(3)](https://man.openbsd.org/getprogname.3) instead.

## reallocarray(3)

Tests for the [reallocarray(3)](https://man.openbsd.org/reallocarray.3)
function, defining `HAVE_REALLOCARRAY` with the result.
Provides a compatibility function if not found.

## recallocarray(3)

Tests for the [recallocarray(3)](https://man.openbsd.org/recallocarray.3)
function, defining `HAVE_RECALLOCARRAY` with the result.
Provides a compatibility function if not found.

## sandbox\_init(3)

Tests for
[sandbox\_init(3)](https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sandbox_init.3.html),
defining `HAVE_SANDBOX_INIT` with the result.
Does not provide any compatibility.

## seccomp-filter(3)

Tests for Linux's
[prctl(2)](http://man7.org/linux/man-pages/man2/prctl.2.html) function,
which is the gateway for
[seccomp(2)](http://man7.org/linux/man-pages/man2/seccomp.2.html).
Defines `HAVE_SECCOMP_FILTER` if found.
Does not provide any compatibility.

## SOCK\_NONBLOCK

Tests for [socketpair(2)](https://man.openbsd.org/socketpair.2)
supporting the `SOCK_NONBLOCK` mask as found on OpenBSD.
Defines the `HAVE_SOCK_NONBLOCK` variable.

```c
#if HAVE_SOCK_NONBLOCK
	socketpair(AF_UNIX, flags|SOCK_NONBLOCK, 0, fd);
#else
	socketpair(AF_UNIX, flags, 0, fd);
	fcntl(fd[0], F_SETFL, 
	      fcntl(fd[0], F_GETFL, 0)|O_NONBLOCK);
	fcntl(fd[1], F_SETFL, 
	      fcntl(fd[1], F_GETFL, 0)|O_NONBLOCK);
#endif
```

Does not provide any compatibility.

## strlcat(3)

Tests for the [strlcat(3)](https://man.openbsd.org/strlcat.3)
function, defining `HAVE_STRLCAT` with the result.
Provides a compatibility function if not found.

## strlcpy(3)

Tests for the [strlcpy(3)](https://man.openbsd.org/strlcpy.3)
function, defining `HAVE_STRLCPY` with the result.
Provides a compatibility function if not found.

## strndup(3)

Tests for the [strndup(3)](https://man.openbsd.org/strndup.3)
function, defining `HAVE_STRNDUP` with the result.
Provides a compatibility function if not found.

## strtonum(3)

Tests for the [strtonum(3)](https://man.openbsd.org/strtonum.3)
function, defining `HAVE_STRTONUM` with the result.
Provides a compatibility function if not found.

## systrace(4)

Tests for OpenBSD's deprecated systrace(4) interface.
Defines `HAVE_SYSTRACE` if found.
Does not provide any compatibility.

## zlib(3)

Tests for zlib(3) compilation and linking.  Defines `HAVE_ZLIB` if
found.  Does not provide any compatibility.
