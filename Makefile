.PHONY: distcheck regress distclean

include Makefile.configure

OBJS			= compats.o
REGRESS_MD5		= regress/md5
REGRESS_SHA2		= regress/sha2
REGRESS_CRYPT		= regress/crypt
REGRESS_B64		= regress/b64_ntop
REGRESS_LIB_SOCKET	= regress/SOCK_NONBLOCK
REGRESS_SCAN_SCALED	= regress/scan_scaled
REGRESS_NODEP		= regress/capsicum \
			  regress/endian \
			  regress/err \
			  regress/explicit_bzero \
			  regress/fts \
			  regress/getprogname \
			  regress/INFTIM \
			  regress/memmem \
			  regress/memrchr \
			  regress/minor \
			  regress/mkfifoat \
			  regress/mknodat \
			  regress/PATH_MAX \
			  regress/pledge \
			  regress/reallocarray \
			  regress/recallocarray \
			  regress/setresgid \
			  regress/setresuid \
			  regress/strndup \
			  regress/strnlen \
			  regress/strlcpy \
			  regress/strlcat \
			  regress/strtonum \
			  regress/sys_queue \
			  regress/systrace \
			  regress/termios \
			  regress/unveil \
			  regress/WAIT_ANY
REGRESS			= $(REGRESS_B64) \
			  $(REGRESS_CRYPT) \
			  $(REGRESS_LIB_SOCKET) \
			  $(REGRESS_MD5) \
			  $(REGRESS_NODEP) \
			  $(REGRESS_SCAN_SCALED) \
			  $(REGRESS_SHA2)

all: $(REGRESS)

distcheck:
	$(MAKE) -f Makefile.regen distcheck

.for r in $(REGRESS_NODEP)
${r}: ${r}.c compats.o config.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ ${r}.c compats.o $(LDFLAGS)
.endfor

.for r in $(REGRESS_LIB_SOCKET)
${r}: ${r}.c compats.o config.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ ${r}.c compats.o $(LDADD_LIB_SOCKET) $(LDFLAGS)
.endfor

.for r in $(REGRESS_MD5)
${r}: ${r}.c compats.o config.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ ${r}.c compats.o $(LDADD_MD5) $(LDFLAGS)
.endfor

.for r in $(REGRESS_SHA2)
${r}: ${r}.c compats.o config.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ ${r}.c compats.o $(LDADD_SHA2) $(LDFLAGS)
.endfor

.for r in $(REGRESS_SCAN_SCALED)
${r}: ${r}.c compats.o config.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ ${r}.c compats.o $(LDADD_SCAN_SCALED) $(LDFLAGS)
.endfor

.for r in $(REGRESS_B64)
${r}: ${r}.c compats.o config.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ ${r}.c compats.o $(LDADD_B64_NTOP) $(LDFLAGS)
.endfor

.for r in $(REGRESS_CRYPT)
${r}: ${r}.c compats.o config.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ ${r}.c compats.o $(LDADD_CRYPT) $(LDFLAGS)
.endfor

install:
	# Do nothing.

regress: $(REGRESS)
	rm -rf .regress
	mkdir .regress
	cp configure tests.c .regress
	( cd .regress ; printf "all:\\n\\t./configure\n" | make -sf - )
	rm -rf .regress
	@for f in $(REGRESS) ; \
	do \
		printf "%s... " "$$f" ; \
		set +e ; \
		./$$f 2>/dev/null ; \
		if [ $$? -ne 0 ]; then \
			echo "FAIL"; \
			exit 1 ; \
		else \
			echo "ok" ; \
		fi ; \
		set -e ; \
	done

clean:
	rm -f compats.o $(REGRESS)

distclean:
	rm -f Makefile.configure config.log config.h
