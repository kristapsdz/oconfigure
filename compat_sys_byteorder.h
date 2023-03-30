/*
 * endian.h compatibility with sys/byteorder.h.
 */
#if HAVE_SYS_BYTEORDER_H && !HAVE_ENDIAN_H && !HAVE_OSBYTEORDER_H && !HAVE_SYS_ENDIAN_H
#define htobe16(x) BE_16(x)
#define htole16(x) LE_16(x)
#define be16toh(x) BE_16(x)
#define le16toh(x) LE_16(x)
#define htobe32(x) BE_32(x)
#define htole32(x) LE_32(x)
#define be32toh(x) BE_32(x)
#define le32toh(x) LE_32(x)
#define htobe64(x) BE_64(x)
#define htole64(x) LE_64(x)
#define be64toh(x) BE_64(x)
#define le64toh(x) LE_64(x)
#endif /* HAVE_SYS_BYTEORDER_H && !HAVE_ENDIAN_H && !HAVE_OSBYTEORDER_H && !HAVE_SYS_ENDIAN_H */
