/*
 * Compatibility for md4(3).
 */
#define MD5_BLOCK_LENGTH 64
#define MD5_DIGEST_LENGTH 16
#define MD5_DIGEST_STRING_LENGTH (MD5_DIGEST_LENGTH * 2 + 1)

typedef struct MD5Context {
	uint32_t state[4];
	uint64_t count;
	uint8_t buffer[MD5_BLOCK_LENGTH];
} MD5_CTX;

extern void MD5Init(MD5_CTX *);
extern void MD5Update(MD5_CTX *, const uint8_t *, size_t);
extern void MD5Pad(MD5_CTX *);
extern void MD5Transform(uint32_t [4], const uint8_t [MD5_BLOCK_LENGTH]);
extern char *MD5End(MD5_CTX *, char *);
extern void MD5Final(uint8_t [MD5_DIGEST_LENGTH], MD5_CTX *);
