#if HAVE_ZLIB
# include <zlib.h>
#endif

int
main(void)
{
#if HAVE_ZLIB
	gzFile gz;

	if ((gz = gzopen("/dev/null", "w")) == NULL)
		return 1;
	gzputs(gz, "foo");
	gzclose(gz);
#endif
	return 0;
}
