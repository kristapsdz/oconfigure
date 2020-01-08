This file describes version information of this project.

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
