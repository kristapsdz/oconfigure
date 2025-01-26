.PHONY: distcheck regress distclean

include Makefile.configure

OBJS			= compats.o
REGRESS_MD5		= regress/md5
REGRESS_SHA2		= regress/sha2
REGRESS_CRYPT		= regress/crypt
REGRESS_B64		= regress/b64_ntop
REGRESS_LIB_SOCKET	= regress/SOCK_NONBLOCK
REGRESS_SCAN_SCALED	= regress/scan_scaled
REGRESS_NODEP		= regress/arc4random \
			  regress/blowfish \
			  regress/capsicum \
			  regress/crypt_newhash \
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
			  regress/PASSWORD_LEN \
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
			  regress/timingsafe_bcmp \
			  regress/unveil \
			  regress/WAIT_ANY
REGRESS			= $(REGRESS_B64) \
			  $(REGRESS_CRYPT) \
			  $(REGRESS_LIB_SOCKET) \
			  $(REGRESS_MD5) \
			  $(REGRESS_NODEP) \
			  $(REGRESS_SCAN_SCALED) \
			  $(REGRESS_SHA2)
SRCS		       != for f in $(REGRESS) ; do echo $$f.c ; done

all: $(REGRESS)

$(REGRESS): compats.o config.h $(SRCS)

$(REGRESS_NODEP):
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $@.c compats.o $(LDFLAGS)

$(REGRESS_LIB_SOCKET):
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $@.c compats.o $(LDADD_LIB_SOCKET) $(LDFLAGS)

$(REGRESS_MD5):
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $@.c compats.o $(LDADD_MD5) $(LDFLAGS)

$(REGRESS_SHA2):
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $@.c compats.o $(LDADD_SHA2) $(LDFLAGS)

$(REGRESS_SCAN_SCALED):
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $@.c compats.o $(LDADD_SCAN_SCALED) $(LDFLAGS)

$(REGRESS_B64):
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $@.c compats.o $(LDADD_B64_NTOP) $(LDFLAGS)

$(REGRESS_CRYPT):
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $@.c compats.o $(LDADD_CRYPT) $(LDFLAGS)

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
