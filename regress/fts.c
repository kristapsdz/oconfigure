#include "../config.h"

#if HAVE_FTS
# include <sys/types.h>
# include <sys/stat.h>
# include <fts.h>
#endif
#if HAVE_ERR
# include <err.h>
#endif
#include <stddef.h> /* NULL */

int
main(void)
{
	const char	*argv[2];
	FTS		*ftsp;
	FTSENT		*entry;

	argv[0] = "/";
	argv[1] = (char *)NULL;

	ftsp = fts_open((char * const *)argv,
	    FTS_PHYSICAL | FTS_NOCHDIR, NULL);

	if (ftsp == NULL)
		err(1, "fts_open");

	entry = fts_read(ftsp);

	if (entry == NULL)
		err(1, "fts_read");

	if (fts_set(ftsp, entry, FTS_SKIP) != 0) 
		err(1, "fts_set");

	if (fts_close(ftsp) != 0)
		err(1, "fts_close");

	return 0;
}
