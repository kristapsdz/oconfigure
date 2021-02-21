#include "../config.h"

#if HAVE_SYS_QUEUE
# include <sys/queue.h>
#endif

struct foo {
	int bar;
	TAILQ_ENTRY(foo) entries;
};

TAILQ_HEAD(fooq, foo);

int
main(void)
{
	struct foo foo;
	struct fooq q;

	foo.bar = 1;

	TAILQ_INIT(&q);
	TAILQ_INSERT_TAIL(&q, &foo, entries);
	return 0;
}
