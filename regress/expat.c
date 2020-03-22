#if HAVE_EXPAT
# include <expat.h>
#endif

int
main(void)
{
#if HAVE_EXPAT
	XML_Parser	p;

	if ((p = XML_ParserCreate(NULL)) == NULL)
		return 1;

	XML_ParserFree(p);
#endif
	return 0;
}
