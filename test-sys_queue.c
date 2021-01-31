#include <sys/queue.h>
#include <stddef.h>

struct foo {
	int bar;
	TAILQ_ENTRY(foo) entries;
};

TAILQ_HEAD(fooq, foo);

int
main(void)
{
	struct fooq foo_q, bar_q;
	struct foo *p, *tmp;
	int i = 0;

	TAILQ_INIT(&foo_q);
	TAILQ_INIT(&bar_q);

	/*
	 * Use TAILQ_FOREACH_SAFE because some systems (e.g., Linux)
	 * have TAILQ_FOREACH but not the safe variant.
	 */

	TAILQ_FOREACH_SAFE(p, &foo_q, entries, tmp)
		p->bar = i++;

	/* Test for newer macros as well. */

	TAILQ_CONCAT(&foo_q, &bar_q, entries);
	return 0;
}
