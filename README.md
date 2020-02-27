This is a simple configuration script use for some
[BSD.lv](https://www.bsd.lv) project sources.
Its mission is to provide [OpenBSD](https://www.openbsd.org) portability
functions and feature testing.

It allows easy porting to Linux (glibc and musl), FreeBSD, Mac OSX, and
some derivatives of SunOS.  Other systems may also be supported: please
let us know if they are!

See [versions.md](versions.md) for version information.

To use:

1. copy
[configure](https://raw.githubusercontent.com/kristapsdz/oconfigure/master/configure),
[compats.c](https://raw.githubusercontent.com/kristapsdz/oconfigure/master/compats.c),
and
[tests.c](https://raw.githubusercontent.com/kristapsdz/oconfigure/master/tests.c)
into your source tree
2. have `include Makefile.configure` at the top of your Makefile
3. have `#include "config.h"` as the first inclusion in your sources
4. read over the included bits below in case you need to guard header inclusion
5. compile compile.o and link to it

Once prepared, a user just runs `./configure` prior to running `make`.
The `configure` script will check for common features as noted in the
test files, e.g., [pledge(2)](https://man.openbsd.org/pledge.2), and
also provide compatibility for other functions, e.g.,
[strlcpy(3)](https://man.openbsd.org/strlcpy.3).

The `./configure` script may be executed in a cross-compiling
environment with the compiler and linker set appropriately.

If you have Makefile flags you'd like to set, set them when you invoke
`configure` as key-value pairs on the command-line, e.g.,

```
./configure PREFIX=/opt
```

The following flags are recognised and accepted: `LDADD`, `LDFLAGS`,
`CPPFLAGS`, `DESTDIR`, `PREFIX`, `MANDIR`, `LIBDIR`, `BINDIR`,
`SHAREDIR`, `SBINDIR`, and `INCLUDEDIR`.  Un-recognised flags are
discarded and warned about.

If, however, you want to use an alternative CC or CFLAGS, specify them
as an environmental variable.  (This may be fixed in future versions.)

```
CC=musl-gcc ./configure
```

Using oconfigure requires some work within your sources to node
compatibility areas, then some in your build environment:

```c
#include "config.h" /* required inclusion */

#if HAVE_ERR /* sometimes err.h exists, sometimes not */
# include <err.h>
#endif
#include <stdio.h>
#include <unistd.h>

int main(void) {
#if HAVE_PLEDGE /* do we have pledge? */
	if (pledge("stdio", NULL) == -1)
		err(EXIT_FAILURE, NULL);
#endif
	warnx("hello, world!"); /* compat provides this */
	return 0;
}
```

And then...

```sh
./configure
cc -o config.o -c config.c
cc -o main.o -c main.c
cc config.o main.o
```

It's better to build this into your Makefile, as the output
*Makefile.configure* will set compiler, compiler flags, installation
utilities, and so on.

This framework was inspired by [mandoc](https://mandoc.bsd.lv)'s
`configure` script written by Ingo Schwarze.

What follows is a description of the features and facilities provided by
the package when included into your sources.

The compatibility layer is generally provided by the excellent portable
[OpenSSH](https://www.openssh.com/).  All copyrights are in their
respective sources.

## b64\_ntop

This function, annoyingly, is sometimes declared but not defined.  The
following will guard against that in your sources.

```c
#if HAVE_B64_NTOP
# include <netinet/in.h>
# include <resolv.h>
#endif
```

On some systems (Linux in particular) with `HAVE_B64_NTOP`, you'll
also need to add `-lresolv` when you compile your system, else it will
fail with undefined references.

The `LDADD_B64_NTOP` value provided in *Makefile.configure* will be set
to `-lresolv` if required.  Otherwise it is empty.

If not found, provides compatibility functions `b64_ntop` and
`b64_pton`.

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

## endian.h

On most operating systems (Linux, OpenBSD), *endian.h* provides the
POSIX.1 endian functions, e.g.,
[htole32(3)](https://man.openbsd.org/htole32.3).
On FreeBSD, however, these are in *sys/endian.h*.
If this macro is defined, the functions are in the usual place; if not,
they're in *sys* (or don't exist at all).

The usual invocation is:

```c
#if HAVE_ENDIAN_H
# include <endian.h>
#else
# include <sys/endian.h>
#endif
```

If you like breaking apart *sys* headers, use the invocation twice, once
with `if HAVE_ENDIAN_H` and the other with `if !HAVE_ENDIAN_H`.

## err.h

Tests for the [err(3)](https://man.openbsd.org/err.3) functions,
defining `HAVE_ERR` variable with the result.

If not found, provides compatibility functions `err`, `errx`, `warn`,
`warnx`, `vwarn`, `vwarnx`.  The `<err.h>` header inclusion needs to be
guarded for systems that include it by default; otherwise, the
definitions are provided in the generated `config.h`.

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
The compatibility layer will use
[memset\_s](http://en.cppreference.com/w/c/string/byte/memset), if
found.

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

On some systems (FreeBSD in particular) with `HAVE_MD5`, you'll
also need to add `-lmd` when you compile your system, else it will
fail with undefined references.

The `LDADD_MD5` value provided in *Makefile.configure* will be set to
`-lmd` if it's required. Otherwise it is empty.

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

## unveil(2)

Test for [OpenBSD](https://www.openbsd.org)'s
[unveil(2)](https://man.openbsd.org/unveil.2) function,
defining `HAVE_UNVEIL` with the result.
Does not provide any compatibility.
For example,

```c
#if HAVE_UNVEIL
# include <unistd.h> /* unveil(2) */
#endif
```

## getprogname(3)

Tests for the [getprogname(3)](https://man.openbsd.org/getprogname.3)
function, defining `HAVE_GETPROGNAME` with the result.
Provides a compatibility function if not found.

The compatibility function tries to use `__progname`,
`program_invocation_short_name`, or `getexecname()`.  If none of these
interfaces may be found, it will emit a compile-time error.  

## readpassphrase(3)

Tests for the [readpassphrase(3)](https://man.openbsd.org/readpassphrase.3)
function, defining `HAVE_READPASSPHRASE` with the result.
Provides a compatibility function if not found.
The `<readpassphrase.h>` header inclusion needs to be
guarded for systems that include it by default; otherwise, the
definitions are provided in the generated `config.h`:

```c
#if HAVE_READPASSPHRASE
# include <readpassphrase.h>
#endif
```

If using this function, makes sure you explicitly zero the passphrase
buffer as described in
[readpassphrase(3)](https://man.openbsd.org/readpassphrase.3).

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

*Note: this test does not mean that the sandboxing is enabled.* You'll
need to perform a run-time check for `prctl`'s return value in your
sources.

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

## strnlen(3)

Tests for the [strnlen(3)](https://man.openbsd.org/strnlen.3)
function, defining `HAVE_STRNLEN` with the result.
Provides a compatibility function if not found.

## strtonum(3)

Tests for the [strtonum(3)](https://man.openbsd.org/strtonum.3)
function, defining `HAVE_STRTONUM` with the result.
Provides a compatibility function if not found.

## sys/queue.h

Tests for the [queue(3)](https://man.openbsd.org/queue.3) header,
*sys/queue.h*.  Defines `HAVE_SYS_QUEUE` if found and provides all of
the queue macros if not.  To use these macros, make sure to guard
inclusion:

```c
#if HAVE_SYS_QUEUE
# include <sys/queue.h>
#endif
```

This uses `TAILQ_FOREACH_SAFE` as a basis for determining whether the
header exists and is well-formed.
This is because glibc provides a skeleton *sys/queue.h* without this
critical macro.

## sys/tree.h

Tests for the [tree(3)](https://man.openbsd.org/tree.3) header,
*sys/tree.h*.  Defines `HAVE_SYS_TREE` if found and provides all of the
tree macros if not.  To use these macros, make sure to guard
inclusion:

```c
#if HAVE_SYS_TREE
# include <sys/tree.h>
#endif
```

## systrace(4)

Tests for OpenBSD's deprecated systrace(4) interface.
Defines `HAVE_SYSTRACE` if found.
Does not provide any compatibility.

## zlib(3)

Tests for zlib(3) compilation and linking.  Defines `HAVE_ZLIB` if
found.  Does not provide any compatibility.

The `LDADD_ZLIB` value provided in *Makefile.configure* will be set to
`-lz` if found. Otherwise it is empty.
