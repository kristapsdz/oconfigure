#include <sys/tree.h>
#include <stdlib.h>

struct node {
	RB_ENTRY(node) entry;
	int i;
};

static int
intcmp(struct node *e1, struct node *e2)
{
	return (e1->i < e2->i ? -1 : e1->i > e2->i);
}

RB_HEAD(inttree, node) head = RB_INITIALIZER(&head);
RB_PROTOTYPE(inttree, node, entry, intcmp)
RB_GENERATE(inttree, node, entry, intcmp)

int testdata[] = {
	20, 16, 17, 13, 3, 6, 1, 8, 2, 4
};

int
main(void)
{
	size_t i;
	struct node *n;

	for (i = 0; i < sizeof(testdata) / sizeof(testdata[0]); i++) {
		if ((n = malloc(sizeof(struct node))) == NULL)
			return 1;
		n->i = testdata[i];
		RB_INSERT(inttree, &head, n);
	}

	return 0;
}

