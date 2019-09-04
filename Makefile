VERSION	= 0.1.9
COMPATS	= compat_err.c \
	  compat_b64_ntop.c \
	  compat_explicit_bzero.c \
	  compat_getprogname.c \
	  compat_md5.c \
	  compat_memmem.c \
	  compat_memrchr.c \
	  compat_readpassphrase.c \
	  compat_reallocarray.c \
	  compat_recallocarray.c \
	  compat_strlcat.c \
	  compat_strlcpy.c \
	  compat_strndup.c \
	  compat_strnlen.c \
	  compat_strtonum.c
TESTS	= test-__progname.c \
	  test-arc4random.c \
	  test-b64_ntop.c \
	  test-capsicum.c \
	  test-err.c \
	  test-explicit_bzero.c \
	  test-getprogname.c \
	  test-INFTIM.c \
	  test-md5.c \
	  test-memmem.c \
	  test-memrchr.c \
	  test-memset_s.c \
	  test-PATH_MAX.c \
	  test-pledge.c \
	  test-program_invocation_short_name.c \
	  test-readpassphrase.c \
	  test-reallocarray.c \
	  test-recallocarray.c \
	  test-sandbox_init.c \
	  test-seccomp_filter.c \
	  test-SOCK_NONBLOCK.c \
	  test-strlcat.c \
	  test-strlcpy.c \
	  test-strndup.c \
	  test-strnlen.c \
	  test-strtonum.c \
	  test-sys_queue.c \
	  test-systrace.c \
	  test-unveil.c \
	  test-zlib.c

all: compats.c tests.c configure

configure: configure.in Makefile
	rm -f $@
	sed "s!@VERSION@!$(VERSION)!g" configure.in >$@
	chmod 555 $@

compats.c: $(COMPATS)
	echo "#include \"config.h\"" >$@
	for f in $(COMPATS) ; \
	do \
		ff="`echo $$f | sed -e 's!\.c$$!!' -e 's!^compat_!!'`" ; \
		up="`echo $$ff | tr '[:lower:]' '[:upper:]'`" ; \
		echo "#if !HAVE_$${up}" ; \
		cat "$$f" ; \
		echo "#endif /* !HAVE_$${up} */" ; \
	done >>$@

tests.c: $(TESTS)
	for f in $(TESTS) ; \
	do \
		ff="`echo $$f | sed -e 's!\.c$$!!' -e 's!^test-!!'`" ; \
		up="`echo $$ff | tr '[:lower:]' '[:upper:]'`" ; \
		echo "#if TEST_$${up}" ; \
		cat "$$f" ; \
		echo "#endif /* TEST_$${up} */" ; \
	done >$@

clean:
	rm -f configure compats.c tests.c compats.o tests.o Makefile.configure config.h config.log
