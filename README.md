This is a simple configuration script use for some
[BSD.lv](https://www.bsd.lv) project sources.  It is not really ready
for general use, but is used in several projects
([ksql](https://kristaps.bsd.lv/ksql),
[sblg](https://kristaps.bsd.lv/sblg),
[lowdown](https://kristaps.bsd.lv/lowdown), etc.).

To use:

1. copy configure, compat\_\*.c, and test-\*.c into your sources
2. have `include Makefile.configure` at the top of your Makefile
3. have `#include "config.h"` as the first inclusion in your sources

Once prepared, a user just runs `./configure` prior to run `make` within
the source distribution.  The `configure` script will check for common
features as noted in the test files, e.g.,
[test-pledge.c](https://github.com/kristapsdz/oconfigure/blob/master/test-pledge.c).
Sometimes it provides compatibility functions; other times (the `pledge`
test is a good example), it simply notes the supported feature.

Sources may either just use whatever's provided in compatibility or use
the `HAVE\_FEATURE` macros for feature tests.

```c
#include "config.h"

#if HAVE_ERR
# include <err.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
#if HAVE_PLEDGE
	if (-1 == pledge("stdio", NULL))
		err(EXIT_FAILURE, NULL);
#endif
	return(EXIT_SUCCESS);
}
```

This framework was inspired by [mandoc](https://mdocml.bsd.lv)'s
`configure` script written by Ingo Schwarze, but has been expanded to
accept configuration values on the command line.

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

