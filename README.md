# Introduction

This is a straightforward configuration system for writing portable C systems
with [OpenBSD](https://www.openbsd.org)-compatible features and functions.

To use:

1. copy
[configure](https://raw.githubusercontent.com/kristapsdz/oconfigure/master/configure),
[compats.c](https://raw.githubusercontent.com/kristapsdz/oconfigure/master/compats.c),
and
[tests.c](https://raw.githubusercontent.com/kristapsdz/oconfigure/master/tests.c)
into your source tree
2. have `include Makefile.configure` at the top of your Makefile
3. have `#include "config.h"` as the first inclusion in your sources
4. read over the documentation below in case you need to guard header
   inclusion
5. compile compats.o with your sources and link with it

It allows easy porting to Linux (glibc and musl), FreeBSD, NetBSD, Mac
OS X, and OmniOS (illumos).  SunOS (Solaris 11) is partially working.
These systems all have their support enforced by GitHub CI actions.
Other systems may also be supported: please let us know if they are.

See [versions.md](versions.md) for version information.

This framework was inspired by [mandoc](https://mandoc.bsd.lv)'s
`configure` script written by Ingo Schwarze.

## Users and maintainers

Run `./configure` prior to running `make`.  The `configure` script will
check for common features as noted in the test files, e.g.,
[pledge(2)](https://man.openbsd.org/pledge.2), and also provide
compatibility for other functions, e.g.,
[strlcpy(3)](https://man.openbsd.org/strlcpy.3).

The `./configure` script may be executed in a cross-compiling
environment with the compiler and linker set appropriately.

If you have Makefile flags you'd like to set, set them when you invoke
`configure` as key-value pairs on the command-line, e.g.,

```
./configure PREFIX=/opt
```

These are set in the generated *Makefile.configure*, which should be
included by the source's `Makefile`.  The following are recognised:

- `LDADD`: **-l** libraries and flags usually used for linking binaries
- `LDLIBS`: **-l** libraries and flags usually used for linking shared
  libraries (`LIBADD` is sometimes used for this)
- `LDFLAGS`: **-L** linker flags used for linking
- `CPPFLAGS`: C preprocessor flags used for compiling objects
- `DESTDIR`: prefixed to all install directories during installation,
  but not otherwise affecting install directories
- `PREFIX`: directory for default install directories (defaults to
  */usr/local*)
- `MANDIR`: install directory for manpages (defaults to *PREFIX/man*)
- `LIBDIR`: install directory for libraries (defaults to *PREFIX/lib*)
- `BINDIR`: install directory for binaries (defaults to *PREFIX/bin*)
- `SHAREDIR`: install directory for shared files (defaults to
  *PREFIX/share*)
- `SBINDIR`: install directory for system binaries (defaults to
  *PREFIX/sbin*)
- `INCLUDEDIR`: install directory for header files (defaults to
  *PREFIX/include*)
- `LINKER_SONAME`: linker command used to create shared libraries
  (defaults to **-soname** or **-install_name**)

Anything else is discarded and warned about.

If you want to use override the default `AR`, `CC`, or `CFLAGS`
variables, specify them as environmental variables.  (The results will
be set either way in *Makefile.configure*.)  For example:

```
CC=musl-gcc ./configure
```

The `CC`, `LDFLAGS`, `CPPFLAGS`, and `CFLAGS` are used when running the
configuration tests themselves.  If a default `cc` compiler is not found,
**oconfigure** will test for `clang` and `gcc` before giving up.

For Linux users with
[libbsd](https://libbsd.freedesktop.org) installed,
**oconfigure** can be instructed to use libbsd exclusively as follows:

```
CFLAGS=$(pkg-config --cflags libbsd-overlay) \
  ./configure LDFLAGS=$(pkg-config --libs libbsd-overlay)
```

For new versions of libbsd, this will pull in the library for all
compatibility replacements instead of those within *compats.c*.

For shared library generation, a `LINKER_SONAME` variable (which may be
overridden) is set in the generated *Makefile.configure* to assist in
Mac OS X portability.  Generating a shared library *lib.so.0* from
*lib.c* might look like:

```
cc -fPIC -o lib.o -c lib.c
cc -shared -o lib.so.0 -Wl,${LINKER_SONAME},lib.so.0 lib.o
```

The choice of **-fPIC** or **-fpic** is left for the user.

## Developers

Using **oconfigure** requires some work within your sources to node
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
		err(1, NULL);
#endif
	warnx("hello, world!"); /* compat provides this */
	return 0;
}
```

And then...

```sh
./configure
cc -o compats.o -c compats.c
cc -o main.o -c main.c
cc compats.o main.o
```

It's better to build this into your Makefile, as the output
*Makefile.configure* will set compiler, compiler flags, installation
utilities, and so on.

The following example also includes portable idioms for a depending
library.  It uses BSD make style.  The *compats.c* is as given in
**oconfigure**, and *Makefile.configure* and *config.h* are generated
when running `configure`.

```mk
include Makefile.configure

LDADD_PKG != pkg-config --libs zlib || echo "-lz"
CFLAGS_PKG != pkg-config --cflags zlib || echo ""
LDADD += $(LDADD_PKG)
CFLAGS += $(CFLAGS_PKG)

main: main.o compats.o
	$(CC) -o $@ main.o compats.o $(LDFLAGS) $(LDADD)

install:
	mkdir -p $(DESTDIR)$(BINDIR)
	$(INSTALL_PROGRAM) main $(DESTDIR)$(BINDIR)

main.o compats.o: config.h

clean:
	rm -f main main.o compats.o
```

# Features

What follows is a description of the features and facilities provided by
the package when included into your sources.

## arc4random(3)

Tests for the [arc4random(3)](https://man.openbsd.org/arc4random.3)
functions in *stdlib.h*, defining `HAVE_ARC4RANDOM` with the
result.

```c
#if HAVE_ARC4RANDOM
# include <stdlib.h> /* arc4random, arc4random_buf... */
#endif
```

If not found, provides compatibility functions.  The compatibility
functions provide the same quality (via the same source) as OpenBSD,
using the host's `getentropy` function for seed.

## blowfish(3)

Tests for the original [blf\_enc(3)](https://man.openbsd.org/blf_enc.3)
cipher functions including the raw block functions (not documented on
OpenBSD, but still in the public API.

```c
#if HAVE_BLOWFISH
# include <blf.h> /* blf_enc ... */
#endif
```

If not found, provides compatibility functions.

## b64\_ntop

This and its partner `b64_pton` are sometimes declared but not defined.
The following will guard against that in your sources.

```c
#if HAVE_B64_NTOP
# include <netinet/in.h>
# include <resolv.h>
#endif
```

Some systems (Linux in particular) with `HAVE_B64_NTOP` need `-lresolv`
during linking.  If so, set `LDADD_B64_NTOP` in *Makefile.configure* to
`-lresolv`.  Otherwise it is empty.

If the functions are not found, provides compatibility functions
`b64_ntop` and `b64_pton`.

Since these functions are always poorly documented, the following
demonstrates usage for `b64_ntop`, which translates `src` *into* an
encoded NUL-terminated string `dst` and returns the string length or -1.
The `dstsz` is the maximum size required for encoding.

```c
srcsz = strlen(src);
dstsz = ((srcsz + 2) / 3 * 4) + 1;
dst = malloc(dstsz);
if (b64_ntop(src, srcsz, dst, dstsz) == -1)
	goto bad_size;
```

`b64_pton` reverses this situation from an encoded NUL-terminated string
`src` into the decoded and NUL-terminated string `dst` (it's common not
to need the NUL-terminator for the decoded string, which is meant to be
binary).  The `dstsz` is the maximum size required for decoding.

```c
srcsz = strlen(src);
dstsz = srscsz / 4 * 3;
dst = malloc(dstsz + 1); /* NUL terminator */
if ((c = b64_pton(src, dst, dstsz)) == -1)
	goto bad_data;
dst[c] = '\0'; /* NUL termination */
```

## Capsicum

Tests for [FreeBSD](https://www.freebsd.org)'s
[Capsicum](https://www.freebsd.org/cgi/man.cgi?capsicum(4)) subsystem,
defining the `HAVE_CAPSICUM` variable with the result.
Does not provide any compatibility.

```c
#if HAVE_CAPSICUM
# include <sys/resource.h>
# include <sys/capsicum.h>
#endif
```

The guard is required for systems without these headers.

## crypt(3)

On OpenBSD, passwords are managed primarily through
[crypt\_newhash(3)](https://man.openbsd.org/crypt_newhash.3) and friends.
However, the old
[crypt(3)](https://man.openbsd.org/crypt.3) function is still used in
portable applications.  Even though it's not very portable.

This tests for [crypt(3)](https://man.openbsd.org/crypt.3),
defining `HAVE_CRYPT` with the result.

On many systems with `HAVE_CRYPT`, you'll also need to add `-lcrypt`
when you compile your system, else it will fail with undefined
references.

The `LDADD_CRYPT` value provided in *Makefile.configure* will be set to
`-lcrypt` if it's required. Otherwise it is empty.

## crypt\_newhash(3)

This tests for the [crypt(3)](https://man.openbsd.org/crypt.3)-replacing
functions [crypt\_newhash(3)](https://man.openbsd.org/crypt_newhash.3) and
[crypt\_checkpass(3)](https://man.openbsd.org/crypt_newhash.3)
functions, defining `HAVE_CRYPT_NEWHASH` with the result.  Provides
compatibility functions if not found.

Just as document, the portability functions only provide `bcrypt`
functionality.

## endian.h

On most operating systems (Linux, OpenBSD), *endian.h* provides the
POSIX.1 endian functions, e.g.,
[htole32(3)](https://man.openbsd.org/htole32.3),
[be32toh(3)](https://man.openbsd.org/be32toh.3), etc.
On FreeBSD, however, these are in *sys/endian.h*.
Mac OS X and SunOS have their own functions in their own places.

The required invocation to use the endian functions is:

```c
#if HAVE_ENDIAN_H
# include <endian.h>
#elif HAVE_SYS_ENDIAN_H
# include <sys/endian.h>
#elif HAVE_OSBYTEORDER_H
# include <libkern/OSByteOrder.h>
#elif HAVE_SYS_BYTEORDER_H
# include <sys/byteorder.h>
#endif
```

Compatibility for the Mac OS X and SunOS functions to the usual
`htole32` style is provided.

To make this easier, the `COMPAT_ENDIAN_H` is also defined:

```c
#include COMPAT_ENDIAN_H
```

This will paste the appropriate location.

## err.h

Tests for the [err(3)](https://man.openbsd.org/err.3) functions,
defining `HAVE_ERR` variable with the result.  If not found, provides
compatibility functions `err`, `errx`, `errc`, `warn`, `warnx`, `warnc`,
and the variable-argument versions of each.

```c
#if HAVE_ERR
# include <err.h>
#endif
```

The *err.h* header needs to be guarded to prevent systems using the
compatibility functions for failing, as the header does not exist.

It's worth noting that 
[glibc](https://www.gnu.org/software/libc/) defines many of these
functions, but misses the `errc` and `warnc` variations.  **oconfigure**
considers it all or nothing, so will not define `HAVE_ERR` in this case.

## explicit\_bzero(3)

Tests for [explicit\_bzero(3)](https://man.openbsd.org/explicit_bzero.3)
in *string.h*, defining `HAVE_EXPLICIT_BZERO` with the result.

```c
#include <string.h> /* explicit_bzero */
```

If not found, provides a compatibility function.  The compatibility
layer will use
[memset\_s](http://en.cppreference.com/w/c/string/byte/memset), if
found.  `HAVE_EXPLICIT_BZERO` shouldn't be directly used in most
circumstances.

## fts(3)

Tests for the
[fts\_open(3)](https://man.openbsd.org/fts_open.3) family of functions
in *fts.h*, defining `HAVE_FTS` with the result.  If not found, provides
compatibility functions.

```c
#if HAVE_FTS
# include <sys/types.h>
# include <fts.h> /* fts_open(3) et al. */
#endif
```

The *fts.h* header needs to be guarded to prevent systems using the
compatibility functions for failing, as the header does not exist.

## getprogname(3)

Tests for [getprogname(3)](https://man.openbsd.org/getprogname.3) in
*stdlib.h*, defining `HAVE_GETPROGNAME` with the result.  Provides a
compatibility function if not found.

```c
#include <stdlib.h> /* getprogname */
```

The compatibility function tries to use `__progname`,
`program_invocation_short_name`, or `getexecname()`.  If none of these
interfaces may be found, it will emit a compile-time error.
`HAVE_GETPROGNAME` shouldn't be directly used in most circumstances.

## INFTIM

Tests for `INFTIM` in [poll(2)](https://man.openbsd.org/poll.2),
defining `HAVE_INFTIM` with the result.  Provides a compatibility
value if not found.

```c
#include <poll.h> /* INFTIM */
```

Since a compatibility function is provided, `HAVE_INFTIM` shouldn't be
directly used in most circumstances.

## landlock

Tests for Linux's [landlock)](https://landlock.io/) LSM.  Defines
`HAVE_LANDLOCK` if found.  Does not provide any compatibility.

*This test does not mean that the module is enabled.* You'll need to perform a
run-time check for `landlock_restrict_self`'s return value in your sources.

To actually use Landlock, you'll need to modify your system's LSM at boot time.

## libsocket

On IllumOS-based distributions, all socket functions
([bind(2)](https://man.openbsd.org/bind.2),
[listen(2)](https://man.openbsd.org/listen.2),
[socketpair(2)](https://man.openbsd.org/socketpair.2), etc.)
require linking to the `-lsocket` and `-lnsl` libraries.

If this is required, the `LDADD_LIB_SOCKET` variable in *Makefile.configure*
will be set to the required libraries.

## md5.h

Tests for the standalone [md5(3)](https://man.openbsd.org/md5.3)
functions, defining `HAVE_MD5` with the result.

If not found, provides a full complement of standalone (i.e., not
needing any crypto libraries) MD5 hashing functions.  These are
`MD5Init`, `MD5Update`, `MD5Pad`, `MD5Transform`, `MD5End`, and
`MD5Final`.  The preprocessor macros `MD5_BLOCK_LENGTH`,
`MD5_DIGEST_LENGTH`, and `MD5_DIGEST_STRING_LENGTH` are also defined.  

These differ ever-so-slightly from the OpenBSD versions in that they use
C99 types for greater portability, e.g., `uint8_t` instead of
`u_int8_t`.

If using these functions, you'll want to guard an inclusion of the
system-default.  Otherwise a partial *md5.h* may conflict with results,
or a missing *md5.h* may terminate compilation.

```c
#if HAVE_MD5
# include <sys/types.h>
# include <md5.h>
#endif
```

On some systems (FreeBSD or those with [Guillem Jover's
libmd](https://www.hadrons.org/software/libmd/)) with `HAVE_MD5`, 
you'll also need to add `-lmd` when you compile your system, else it will
fail with undefined references.

The `LDADD_MD5` value provided in *Makefile.configure* will be set to
`-lmd` if it's required. Otherwise it is empty.

## memmem(3)

Tests for [memmem(3)](https://man.openbsd.org/memmem.3) in *string.h*,
defining `HAVE_MEMMEM` with the result.  Provides a compatibility
function if not found.

```c
#include <string.h> /* memmem */
```

Since a compatibility function is provided, `HAVE_MEMMEM` shouldn't be
directly used in most circumstances.

## memrchr(3)

Tests for [memrchr(3)](https://man.openbsd.org/memrchr.3) in *string.h*,
defining `HAVE_MEMRCHR` with the result.  Provides a compatibility
function if not found.

```c
#include <string.h> /* memrchr */
```

Since a compatibility function is provided, `HAVE_MEMRCHR` shouldn't be
directly used in most circumstances.

## minor(2)

[major(2)](https://man.openbsd.org/major.2),
[minor(2)](https://man.openbsd.org/minor.2),
and
[makedev(2)](https://man.openbsd.org/makedev.2)
all live in different places on different systems.

```c
#if HAVE_SYS_MKDEV_H
# include <sys/types.h> /* dev_t */
# include <sys/mkdev.h> /* minor/major/makedev */
#elif HAVE_SYS_SYSMACROS_H
# include <sys/sysmacros.h> /* minor/major/makedev */
#else
# include <sys/types.h> /* minor/major/makedev */
#endif
```

This can be made much easier as follows, where `COMPAT_MAJOR_MINOR_H` is
set to one of the above.  *sys/types.h* may be included twice.

```c
#include <sys/types.h>
#include COMPAT_MAJOR_MINOR_H
```

## mkfifoat(2)

Tests for the [mkfifoat(3)](https://man.openbsd.org/mkfifoat.3)
function, defining `HAVE_MKFIFOAT` with the result.
Provides a compatibility function if not found.

This is *not* a direct replacement, as the function is not atomic: it
internally gets a reference to the current directory, changes into the
"at" directory, runs the function, then returns to the prior current.

Upon errors, it makes a best effort to restore the current working
directory to what it was.

## mknodat(2)

Tests for the [mknodat(3)](https://man.openbsd.org/mknodat.3)
function, defining `HAVE_MKNODAT` with the result.
Provides a compatibility function if not found.

This is *not* a direct replacement, as the function is not atomic: it
internally gets a reference to the current directory, changes into the
"at" directory, runs the function, then returns to the prior current.

Upon errors, it makes a best effort to restore the current working
directory to what it was.

## PATH\_MAX

Tests for the `PATH_MAX` variable in *limits.h*, defining
`HAVE_PATH_MAX` with the result.  If not found, defines the `PATH_MAX`
macro to be 4096.

```c
#include <limits.h> /* PATH_MAX */
```

Since a compatibility value is provided, `HAVE_PATH_MAX` shouldn't be
directly used in most circumstances.

## pledge(2)

Test for [pledge(2)](https://man.openbsd.org/pledge.2), defining `HAVE_PLEDGE`
with the result.  Does not provide any compatibility.

```c
#include <unistd.h> /* pledge */
```

The `HAVE_PLEDGE` guard is not required except around the function invocation.

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

Tests for [reallocarray(3)](https://man.openbsd.org/reallocarray.3) in
*stdlib.h*, defining `HAVE_REALLOCARRAY` with the result.  Provides a
compatibility function if not found.

```c
#include <stdlib.h> /* reallocarray */
```

Since a compatibility function is provided, `HAVE_REALLOCARRAY` shouldn't be
directly used in most circumstances.

## recallocarray(3)

Tests for [recallocarray(3)](https://man.openbsd.org/recallocarray.3) in
*stdlib.h*, defining `HAVE_RECALLOCARRAY` with the result.  Provides a
compatibility function if not found.

```c
#include <stdlib.h> /* recallocarray */
```

Since a compatibility function is provided, `HAVE_RECALLOCARRAY` shouldn't be
directly used in most circumstances.

## sandbox\_init(3)

Tests for
[sandbox\_init(3)](https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sandbox_init.3.html),
defining `HAVE_SANDBOX_INIT` with the result.
Does not provide any compatibility.

## scan\_scaled(3), fmt\_scaled(3)

Tests for OpenBSD's [scan\_scaled(3)](https://man.openbsd.org/scan_scaled.3),
defining `HAVE_SCAN_SCALED` if it was found.  Provides a compatibility function
if not found.  If the function is not found, fmt\_scaled(3) is also part of the
compatibility package.

```c
#if HAVE_SCAN_SCALED
# include <util.h>
#endif
```

If this is required, the `LDADD_SCAN_SCALED` variable in *Makefile.configure*
will be set to the required library (**-lutil**).


## seccomp-filter(3)

Tests for Linux's
[prctl(2)](http://man7.org/linux/man-pages/man2/prctl.2.html) function,
which is the gateway for
[seccomp(2)](http://man7.org/linux/man-pages/man2/seccomp.2.html).
This defines several variables:

- `HAVE_SECCOMP_HEADER`: Compile-time support exists for seccomp.
- `SECCOMP_AUDIT_ARCH`: If `HAVE_SECCOMP_HEADER` is set, this is set to
  the architecture used for seccomp operations (e.g., `AUDIT_ARCH_ARM`).
  If this is not set and `HAVE_SECCOMP_HEADER` is set, seccomp is
  enabled in the kernel but the hardware architecture is not known by
  oconfigure.  Please create an issue or pull request with your
  `uname -m` and hardware profile.
- `HAVE_SECCOMP_FILTER`: Set if both `HAVE_SECCOMP_HEADER` and
  `SECCOMP_AUDIT_ARCH` are set.

Does not provide any compatibility.

*This test does not mean that the sandboxing is enabled.* You'll
need to perform a run-time check for `prctl`'s return value in your
sources.

## sha2.h

Tests for the standalone [sha2(3)](https://man.openbsd.org/sha2.3)
functions, defining `HAVE_SHA2` with the result.  This was previously
provided as `HAVE_SHA2_H`, which still works as an alias for
`HAVE_SHA2`.

If not found, provides a full complement of standalone SHA2 hashing
functions.  These are `SHA256Init`, `SHA256Transform`, `SHA256Update`,
`SHA256Pad`, `SHA256Final`, `SHA256End`, `SHA256File`,
`SHA256FileChunk`, and `SHA256Data`.  The preprocessor macros
`SHA256_BLOCK_LENGTH`, `SHA256_DIGEST_LENGTH`, and
`SHA256_DIGEST_STRING_LENGTH` are also defined.

The SHA2 functions and macros are provided for SHA256, SHA384, and
SHA512. So for example the `SHA512Final` function is also provided.

If using these functions, you'll want to guard an inclusion of the
system-default.  Otherwise a partial *sha2.h* may conflict with results,
or a missing *sha2.h* may terminate compilation.

```c
#if HAVE_SHA2
# include <sys/types.h>
# include <sha2.h>
#endif
```

On some systems (such as those with [Guillem Jover's
libmd](https://www.hadrons.org/software/libmd/)) with `HAVE_SHA2`,
you'll also need to add `-lmd` when you compile your system, else it
will fail with undefined references.

The `LDADD_SHA2` value provided in *Makefile.configure* will be set to
`-lmd` if it's required. Otherwise it is empty.

## SOCK\_NONBLOCK

Tests for [socketpair(2)](https://man.openbsd.org/socketpair.2) in
*sys/socket.h* supporting the `SOCK_NONBLOCK` mask as found on OpenBSD.
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

The guard is not required only around the variable usage, not header
inclusion.  However, the above example could have the *fcntl.h* header
guarded by `!HAVE_SOCK_NONBLOCK`.

## strlcat(3)

Tests for [strlcat(3)](https://man.openbsd.org/strlcat.3) in *string.h*,
defining `HAVE_STRLCAT` with the result.  Provides a compatibility function if
not found.

```c
#include <string.h> /* strlcat */
```

Since a compatibility function is provided, `HAVE_STRLCAT` shouldn't be
directly used in most circumstances.

## strlcpy(3)

Tests for [strlcpy(3)](https://man.openbsd.org/strlcpy.3) in *string.h*,
defining `HAVE_STRLCPY` with the result.  Provides a compatibility function if
not found.

```c
#include <string.h> /* strlcpy */
```

Since a compatibility function is provided, `HAVE_STRLCPY` shouldn't be
directly used in most circumstances.

## strndup(3)

Tests for [strndup(3)](https://man.openbsd.org/strndup.3)
in *string.h*, defining `HAVE_STRNDUP` with the result.  Provides a
compatibility function if not found.

```c
#include <string.h> /* strndup */
```

Since a compatibility function is provided, `HAVE_STRNDUP` shouldn't be
directly used in most circumstances.

## strnlen(3)

Tests for [strnlen(3)](https://man.openbsd.org/strnlen.3) in *string.h*,
defining `HAVE_STRNLEN` with the result.  Provides a compatibility function if
not found.

```c
#include <string.h> /* strnlen */
```

Since a compatibility function is provided, `HAVE_STRNLEN` shouldn't be
directly used in most circumstances.

## strtonum(3)

Tests for [strtonum(3)](https://man.openbsd.org/strtonum.3) in *stdlib.h*,
defining `HAVE_STRTONUM` with the result.  Provides a compatibility function if
not found.

```c
#include <stdlib.h> /* strtonum */
```

Since a compatibility value is provided, `HAVE_STRTONUM` shouldn't be directly
used in most circumstances.

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

Tests for the deprecated systrace(4) interface.  Defines `HAVE_SYSTRACE` if
found.  Does not provide any compatibility.

This function is never "found".

## termios(4)

Tests for whether [termios(4)](https://man.openbsd.org/termios.4) exists,
defining `HAVE_TERMIOS` with the result, specifically with the use case of
testing terminal widths via [ioctl(2)](https://man.openbsd.org/ioctl.2) and
`TIOCGWINSZ` (which must also exist).  Does not provide any compaibility.

## timingsafe\_bcmp(3)

Tests for the
[timingsafe\_bcmp(3)](https://man.openbsd.org/timingsafe_bcmp.3)
functions in *string.h*, defining `HAVE_TIMINGSAFE_BCMP` with the
result.

```c
#if HAVE_TIMINGSAFE_BCMP
# include <string.h> /* timingsafe_bcmp... */
#endif
```

If not found, provides compatibility functions.

## unveil(2)

Test for [unveil(2)](https://man.openbsd.org/unveil.2), defining `HAVE_UNVEIL`
with the result.  Does not provide any compatibility.

```c
#include <unistd.h> /* unveil */
```

The `HAVE_UNVEIL` guard is not required except around the function invocation.

## WAIT\_ANY

Tests for `WAIT_ANY` in [waitpid(2)](https://man.openbsd.org/waitpid.2),
defining `HAVE_WAIT_ANY` with the result.  Provides a compatibility
value for both `WAIT_ANY` and `WAIT_MYPGRP` if not found.

```c
#include <sys/wait.h> /* WAIT_ANY, WAIT_MYPGRP */
```

Since a compatibility function is provided, `HAVE_WAIT_ANY` shouldn't be
directly used in most circumstances.
