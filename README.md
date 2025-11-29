## Synopsis

This is a configuration system for writing portable C systems
with [OpenBSD](https://www.openbsd.org)-compatible features and functions.

To use:

1. copy
   [configure](https://raw.githubusercontent.com/kristapsdz/oconfigure/master/configure),
   [compats.c](https://raw.githubusercontent.com/kristapsdz/oconfigure/master/compats.c),
   and
   [tests.c](https://raw.githubusercontent.com/kristapsdz/oconfigure/master/tests.c)
   into your source tree, or grab files from a cloned repository or
   downloaded release
2. run `./configure` to create *Makefile.configure* and *config.h*
3. `include Makefile.configure` at the top of your Makefile (BSD or GNU
   make) and add *compats.c* to be linked into your binary or library
4. reference compatibility functions by adding `#include "config.h"` as
   the first inclusion in your sources

See the [main website](https://kristaps.bsd.lv/oconfigure) for details.
