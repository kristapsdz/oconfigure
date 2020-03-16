.PHONY: distcheck regress distclean

include Makefile.configure

OBJS		= compats.o
REGRESS_MD5	= regress/md5
REGRESS_B64	= regress/b64_ntop
REGRESS_NODEP	= regress/capsicum \
		  regress/endian \
		  regress/err \
	  	  regress/explicit_bzero \
	  	  regress/getprogname \
	  	  regress/INFTIM \
	  	  regress/memmem \
	  	  regress/memrchr \
	  	  regress/PATH_MAX \
	  	  regress/pledge \
	  	  regress/reallocarray \
	  	  regress/recallocarray \
	  	  regress/SOCK_NONBLOCK \
	  	  regress/strndup \
	  	  regress/strnlen \
	  	  regress/strlcpy \
	  	  regress/strlcat \
	  	  regress/strtonum \
	  	  regress/systrace \
		  regress/unveil
REGRESS		= $(REGRESS_B64) \
		  $(REGRESS_MD5) \
		  $(REGRESS_NODEP)

all: compats.o

distcheck:
	$(MAKE) -f Makefile.regen distcheck

.for r in $(REGRESS_NODEP)
${r}: ${r}.c compats.o config.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ ${r}.c compats.o
.endfor

.for r in $(REGRESS_MD5)
${r}: ${r}.c compats.o config.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ ${r}.c compats.o $(LDADD_MD5)
.endfor

.for r in $(REGRESS_B64)
${r}: ${r}.c compats.o config.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ ${r}.c compats.o $(LDADD_B64_NTOP)
.endfor

install:
	# Do nothing.

regress: $(REGRESS)
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
