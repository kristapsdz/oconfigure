#include <expat.h>

int
main(void)
{
	XML_Parser	p;

	if ((p = XML_ParserCreate(NULL)) == NULL)
		return 1;

	XML_ParserFree(p);
	return 0;
}
