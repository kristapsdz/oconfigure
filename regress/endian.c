#include "../config.h"

#include COMPAT_ENDIAN_H

int
main(void)
{
	return htobe32(be32toh(0x3a7d0cdb)) != 0x3a7d0cdb;
}
