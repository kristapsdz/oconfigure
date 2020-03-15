.PHONY: distcheck regress distclean

include Makefile.configure

OBJS		= compats.o
REGRESS_MD5	= regress/md5
REGRESS_NODEP	= regress/endian \
	  	  regress/explicit_bzero \
	  	  regress/strlcat
REGRESS		= $(REGRESS_MD5) \
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

regress: $(REGRESS)
	@for f in $(REGRESS) ; \
	do \
		printf "%s... " "$$f" ; \
		set +e ; \
		./$$f ; \
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
