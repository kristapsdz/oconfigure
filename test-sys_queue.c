#include <sys/queue.h>

struct foo {
	int bar;
	TAILQ_ENTRY(foo) entries;
};

TAILQ_HEAD(fooq, foo);

int
main(void)
{
	struct fooq foo_q;

	TAILQ_INIT(&foo_q);
	return 0;
}
