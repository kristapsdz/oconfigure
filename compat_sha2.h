/*
 * Compatibility for sha2(3).
 */

/*** SHA-256/384/512 Various Length Definitions ***********************/
#define SHA256_BLOCK_LENGTH		64
#define SHA256_DIGEST_LENGTH		32
#define SHA256_DIGEST_STRING_LENGTH	(SHA256_DIGEST_LENGTH * 2 + 1)
#define SHA384_BLOCK_LENGTH		128
#define SHA384_DIGEST_LENGTH		48
#define SHA384_DIGEST_STRING_LENGTH	(SHA384_DIGEST_LENGTH * 2 + 1)
#define SHA512_BLOCK_LENGTH		128
#define SHA512_DIGEST_LENGTH		64
#define SHA512_DIGEST_STRING_LENGTH	(SHA512_DIGEST_LENGTH * 2 + 1)
#define SHA512_256_BLOCK_LENGTH		128
#define SHA512_256_DIGEST_LENGTH	32
#define SHA512_256_DIGEST_STRING_LENGTH	(SHA512_256_DIGEST_LENGTH * 2 + 1)

/*** SHA-224/256/384/512 Context Structure *******************************/
typedef struct _SHA2_CTX {
	union {
		uint32_t	st32[8];
		uint64_t	st64[8];
	} state;
	uint64_t	bitcount[2];
	uint8_t		buffer[SHA512_BLOCK_LENGTH];
} SHA2_CTX;

void SHA256Init(SHA2_CTX *);
void SHA256Transform(uint32_t state[8], const uint8_t [SHA256_BLOCK_LENGTH]);
void SHA256Update(SHA2_CTX *, const uint8_t *, size_t);
void SHA256Pad(SHA2_CTX *);
void SHA256Final(uint8_t [SHA256_DIGEST_LENGTH], SHA2_CTX *);
char *SHA256End(SHA2_CTX *, char *);
char *SHA256File(const char *, char *);
char *SHA256FileChunk(const char *, char *, off_t, off_t);
char *SHA256Data(const uint8_t *, size_t, char *);

void SHA384Init(SHA2_CTX *);
void SHA384Transform(uint64_t state[8], const uint8_t [SHA384_BLOCK_LENGTH]);
void SHA384Update(SHA2_CTX *, const uint8_t *, size_t);
void SHA384Pad(SHA2_CTX *);
void SHA384Final(uint8_t [SHA384_DIGEST_LENGTH], SHA2_CTX *);
char *SHA384End(SHA2_CTX *, char *);
char *SHA384File(const char *, char *);
char *SHA384FileChunk(const char *, char *, off_t, off_t);
char *SHA384Data(const uint8_t *, size_t, char *);

void SHA512Init(SHA2_CTX *);
void SHA512Transform(uint64_t state[8], const uint8_t [SHA512_BLOCK_LENGTH]);
void SHA512Update(SHA2_CTX *, const uint8_t *, size_t);
void SHA512Pad(SHA2_CTX *);
void SHA512Final(uint8_t [SHA512_DIGEST_LENGTH], SHA2_CTX *);
char *SHA512End(SHA2_CTX *, char *);
char *SHA512File(const char *, char *);
char *SHA512FileChunk(const char *, char *, off_t, off_t);
char *SHA512Data(const uint8_t *, size_t, char *);
