.PHONY: distcheck regress distclean

include Makefile.configure

OBJS	= compats.o
REGRESS	= regress/endian \
	  regress/explicit_bzero \
	  regress/md5 \
	  regress/strlcat

all: compats.o

distcheck:
	$(MAKE) -f Makefile.regen distcheck

.for r in $(REGRESS)
${r}: ${r}.c compats.o config.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ ${r}.c compats.o
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
