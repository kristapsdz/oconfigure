This file describes version information of this project.

## 0.3.7

Add a test for Linux's [landlock](https://landlock.io).

## 0.3.6

Add a check for
[crypt\_newhash(3)](https://man.openbsd.org/crypt_newhash.3).
No compatibility yet.

## 0.3.5

Have [explicit\_bzero(3)](https://man.openbsd.org/explicit_bzero.3) use
[memset(3)](https://man.openbsd.org/memset.3) internally instead of
[bzero(3)](https://man.openbsd.org/bzero.3), which is a macro on some
systems (e.g., Android).


## 0.3.4

Fix *sys/queue.h* so that it doesn't blow inclusion due to backticks.
Add instructions for using [libbsd](https://libbsd.freedesktop.org).
Use `command -v` instead of `which` for portability to systems that
don't include `which` by default.

## 0.3.3

Use newest OpenBSD *sys/queue.h*, which evicts `CIRCLEQ`, adds
`XSIMPLEQ`, and adds concatenation macros.

## 0.3.2

Fix recursive-make detection on FreeBSD machines.

## 0.3.1

Allow the SHA2 detection to pick up *-lmd*, so that external libraries
such as [libmd](https://www.hadrons.org/software/libmd/) may be
recognised.

## 0.3.0

Fix the [sha2(3)](https://man.openbsd.org/man3/SHA256Init.3) support, which
requires changing symbols from `HAVE_SHA2_H` to `HAVE_SHA2`, just like with
`HAVE_MD5`.  I'm bumping the minor version because of the change in symbols.
The documentation is also now fixed for this.

## 0.2.7

Check for `errc` and `warnc`, prompting some systems with partial
support for [err(3)](https://man.openbsd.org/warn.3) to pull in
compatibility to provide all functions.

## 0.2.6

Documentation for SHA2 compatibility and also remove a warning when
compiling on systems without OpenBSD-like SHA2 support.

## 0.2.5

Test for [fts\_open(3)](https://man.openbsd.org/fts_open.3) and provides
compatibility functions if not found.  These use the latest OpenBSD
source as a basis for the compatibility functions.  Required for
compiling on musl systems.

## 0.2.4

Test for [crypt(3)](https://man.openbsd.org/crypt.3).
Hopefully this will pave way for a future portable
[crypt\_newhash(3)](https://man.openbsd.org/crypt_newhash.3).

## 0.2.3

Back out test for zlib.  This is better handled by
[pkg-config(1)](https://man.openbsd.org/pkg-config.1).
Add more documentation on usage.

## 0.2.2

Fix regression in defining `_BSD_SOURCE` for Linux.

## 0.2.1

More portability for SunOS and IllumOS (OmniOS).  Also Linux/SunOS
portability for the [minor(2)](https://man.openbsd.org/minor.2) family
of functions.  Documentation throughout has improved considerably and
all (most?) functions are handle in the regression suite.

## 0.2.0

Extensive work for portability on SunOS, NetBSD, FreeBSD, and Linux.
A small regression framework is in place (still in development) to make sure
that these systems are continuously supported.

The system is now part of BSD.lv's 
[continuous integration](https://kristaps.bsd.lv/cgi-bin/minci.cgi/index.html?project-name=oconfigure)
suite.

## 0.1.24

Make sure that all (or at least most) of the MD5 functions are
available.  SunOS, for instance, only provides some of them.  Also make
the MD5 compatibility layer use C11 types for greater portability.

## 0.1.23

If <code>$CC</code> is not found, try to use <code>clang</code> then
<code>gcc</code> before giving up.
This is primarily for SunOS machines that define the compiler as
<code>cc</code>, but do not provide it as such.

Also support the SunOS byte order functions.

The system is now fully tested on SunOS.

## 0.1.22

Fix
[mknodat(2)](https://man.openbsd.org/mknodat.2)
and
[mkfifoat(2)](https://man.openbsd.org/mkfifoat.2)
and compatibility not to leak file descriptors and to properly clean up
on exit.

## 0.1.21

Provide
[mknodat(2)](https://man.openbsd.org/mknodat.2)
and
[mkfifoat(2)](https://man.openbsd.org/mkfifoat.2)
compatibility for Mac OS X.

## 0.1.20

Provide `COMPAT_ENDIAN_H` as short-hand for the three-phase conditional
for detecting endian functions.

## 0.1.19

Make the *endian.h* checks compatible with Mac OS X, which provides
neither an *endian.h* nor the functions therein.
Add another conditional to the required check (`HAVE_OSBYTEORDER_H`) and
provide compatibility functions as well.

## 0.1.18

Have checks that require external libraries (MD5, `b64_ntop`, etc.) set
those libraries in *Makefile.configure* if required.  This makes it
easier for software to add those libraries without requiring the porters
to do so.

## 0.1.17

Fix typo in
[readpassphrase(3)](https://man.openbsd.org/readpassphrase.3)
compatibility.

## 0.1.16

Support `getprogname()` on systems inheriting from SunOS.
Fix up the README documentation not to directly mention "supporting"
tools used in the compatibility layer, such as `memset_s` or
`__progname`.  These should not be used directly: the compatibility
functions should be used instead.

## 0.1.15

Add a header guard to the output *config.h*.

## 0.1.14

Add aarch64 to Linux seccomp tests.
This patch comes from [kcgi/pull/74](https://github.com/kristapsdz/kcgi/pull/74).

## 0.1.13

Test for [tree(3)](https://man.openbsd.org/tree.3) (*sys/tree.h*) macros
and provide compatibility macros if not found.

## 0.1.12

Fix [readpassphrase(3)](https://man.openbsd.org/readpassphrase.3)
compatibility to run on FreeBSD.

## 0.1.11

Test for (OpenBSD/Linux) *endian.h* or (FreeBSD) *sys/endian.h*.

## 0.1.10

Add a test and compatibility for 
[readpassphrase(3)](https://man.openbsd.org/readpassphrase.3).

## 0.1.9

Make the test for *sys/queue.h* look for the `TAILQ_FOREACH_SAFE`
function, as the glibc version of this header file does not include that
critical macro.

## 0.1.8

Test for [unveil(2)](https://man.openbsd.org/unveil.2) and some small
fixes to initialisations.

## 0.1.7

Fix the *sys/queue.h* check on non-OpenBSD systems (specifically
glibc and musl Linux systems) and fix MD5 test to catch -lmd on
FreeBSD.

## 0.1.6

Bundle a version of *sys/queue.h* if it's not found.

## 0.1.5

Improve test for b64 and also add compatibility functions.

## 0.1.4

Add a test for `b64_ntop` and also introduce cross-compilation support
by not actually executing tests---just compiling them.

## 0.1.3

Add `vwarn` and `vwarnx` to the `err.h` compatibility.

## 0.1.2

Accept multiple words when passing arguments on the command line.
For example,

```
./configure LDFLAGS="-L/usr/local/lib -L/usr/local/opt/lib"
```

Also specify the current known version in the `configure` script.
While there, start versioning.
