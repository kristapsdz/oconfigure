This is a simple configuration script use for some
[BSD.lv](https://www.bsd.lv) project sources.  It is not really ready
for general use, but is used in several projects
([ksql](https://kristaps.bsd.lv/ksql),
[sblg](https://kristaps.bsd.lv/sblg),
[lowdown](https://kristaps.bsd.lv/lowdown), etc.).

In general, a user runs `./configure` prior to run `make`.  The
`configure` script will check for common features as noted in the test
files, e.g.,
[test-pledge.c](https://github.com/kristapsdz/oconfigure/blob/master/test-pledge.c).
The source, which must include `config.h` as the first inclusion, may
then use the CPP variable `HAVE_FEATURE`. In this case this would be
`HAVE_PLEDGE`.
If not found, it provides a compatibility function.

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
