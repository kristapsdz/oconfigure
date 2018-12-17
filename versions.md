This file describes version information of this project.

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
