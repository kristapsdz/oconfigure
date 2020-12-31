#include <stddef.h> /* NULL */
#include <sys/types.h>
#include <sys/stat.h>
#include <fts.h>

int
main(void)
{
	const char	*argv[2];
	FTS		*ftsp;
	FTSENT		*entry;

	argv[0] = ".";
	argv[1] = (char *)NULL;

	ftsp = fts_open((char * const *)argv,
	    FTS_PHYSICAL | FTS_NOCHDIR, NULL);

	if (ftsp == NULL)
		return 1;

	entry = fts_read(ftsp);

	if (entry == NULL)
		return 1;

	if (fts_set(ftsp, entry, FTS_SKIP) != 0) 
		return 1;

	if (fts_close(ftsp) != 0)
		return 1;

	return 0;
}
