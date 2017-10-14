This is a simple configuration script use for some
[BSD.lv](https://www.bsd.lv) project sources.  It is not really ready
for general use, but is used in several projects
([ksql](https://kristaps.bsd.lv/ksql),
[sblg](https://kristaps.bsd.lv/sblg),
[lowdown](https://kristaps.bsd.lv/lowdown), etc.).

To use:

1. copy
   [configure](https://raw.githubusercontent.com/kristapsdz/oconfigure/master/configure), [compats.c](https://raw.githubusercontent.com/kristapsdz/oconfigure/master/compats.c), and [tests.c](https://raw.githubusercontent.com/kristapsdz/oconfigure/master/tests.c) into your sources
2. have `include Makefile.configure` at the top of your Makefile
3. have `#include "config.h"` as the first inclusion in your sources
4. compile compile.o and link to it

Once prepared, a user just runs `./configure` prior to running `make`.
The `configure` script will check for common features as noted in the
test files, e.g., [pledge(2)](https://man.openbsd.org/pledge.2), and also provide compatibility for other
functions, e.g., [strlcpy(3)](https://man.openbsd.org/strlcpy.3).

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

## err.h

If not found, provides error functions `err`, `errx`, `warn`, `warnx`.
The `<err.h>` header inclusion needs to be guarded for systems that
include it.

```c
#if HAVE_ERR
# include <err.h>
#endif
```

## PATH\_MAX

If not already defined, defines the `PATH\_MAX` CPP value to be 4096.

## capsicum

Tests for [FreeBSD](https://www.freebsd.org)'s
[Capsicum](https://www.freebsd.org/cgi/man.cgi?capsicum(4)) support.
Does not provide any compatibility.

## explicit\_bzero

If not found, provides an `explicit\_bzero` function.

## md5
## memset\_s
## pledge
## progname
## reallocarray
## recallocarray
## strlcpy
## strlcat
## strtonum

