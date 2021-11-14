#if !HAVE_ERR
/*
 * Compatibility functions for err(3).
 */
extern void err(int, const char *, ...) __attribute__((noreturn));
extern void errc(int, int, const char *, ...) __attribute__((noreturn));
extern void errx(int, const char *, ...) __attribute__((noreturn));
extern void verr(int, const char *, va_list) __attribute__((noreturn));
extern void verrc(int, int, const char *, va_list) __attribute__((noreturn));
extern void verrx(int, const char *, va_list) __attribute__((noreturn));
extern void warn(const char *, ...);
extern void warnx(const char *, ...);
extern void warnc(int, const char *, ...);
extern void vwarn(const char *, va_list);
extern void vwarnc(int, const char *, va_list);
extern void vwarnx(const char *, va_list);
#endif /* !HAVE_ERR */
#if !HAVE_B64_NTOP
/*
 * Compatibility for b64_ntop(3).
 */
extern int b64_ntop(unsigned char const *, size_t, char *, size_t);
extern int b64_pton(char const *, unsigned char *, size_t);
#endif /* !HAVE_B64_NTOP */
#if !HAVE_EXPLICIT_BZERO
/*
 * Compatibility for explicit_bzero(3).
 */
extern void explicit_bzero(void *, size_t);
#endif /* !HAVE_EXPLICIT_BZERO */
#if !HAVE_FTS
/*
 * Compatibility for fts(3) functions.
 */
typedef struct {
	struct _ftsent *fts_cur;	/* current node */
	struct _ftsent *fts_child;	/* linked list of children */
	struct _ftsent **fts_array;	/* sort array */
	dev_t fts_dev;			/* starting device # */
	char *fts_path;			/* path for this descent */
	int fts_rfd;			/* fd for root */
	size_t fts_pathlen;		/* sizeof(path) */
	int fts_nitems;			/* elements in the sort array */
	int (*fts_compar)(const struct _ftsent **, const struct _ftsent **); /* compare function */
#define	FTS_COMFOLLOW	0x0001		/* follow command line symlinks */
#define	FTS_LOGICAL	0x0002		/* logical walk */
#define	FTS_NOCHDIR	0x0004		/* don't change directories */
#define	FTS_NOSTAT	0x0008		/* don't get stat info */
#define	FTS_PHYSICAL	0x0010		/* physical walk */
#define	FTS_SEEDOT	0x0020		/* return dot and dot-dot */
#define	FTS_XDEV	0x0040		/* don't cross devices */
#define	FTS_OPTIONMASK	0x00ff		/* valid user option mask */
#define	FTS_NAMEONLY	0x1000		/* (private) child names only */
#define	FTS_STOP	0x2000		/* (private) unrecoverable error */
	int fts_options;		/* fts_open options, global flags */
} FTS;

typedef struct _ftsent {
	struct _ftsent *fts_cycle;	/* cycle node */
	struct _ftsent *fts_parent;	/* parent directory */
	struct _ftsent *fts_link;	/* next file in directory */
	long fts_number;	        /* local numeric value */
	void *fts_pointer;	        /* local address value */
	char *fts_accpath;		/* access path */
	char *fts_path;			/* root path */
	int fts_errno;			/* errno for this node */
	int fts_symfd;			/* fd for symlink */
	size_t fts_pathlen;		/* strlen(fts_path) */
	size_t fts_namelen;		/* strlen(fts_name) */
	ino_t fts_ino;			/* inode */
	dev_t fts_dev;			/* device */
	nlink_t fts_nlink;		/* link count */
#define	FTS_ROOTPARENTLEVEL	-1
#define	FTS_ROOTLEVEL		 0
#define	FTS_MAXLEVEL		 0x7fffffff
	int fts_level;		/* depth (-1 to N) */
#define	FTS_D		 1		/* preorder directory */
#define	FTS_DC		 2		/* directory that causes cycles */
#define	FTS_DEFAULT	 3		/* none of the above */
#define	FTS_DNR		 4		/* unreadable directory */
#define	FTS_DOT		 5		/* dot or dot-dot */
#define	FTS_DP		 6		/* postorder directory */
#define	FTS_ERR		 7		/* error; errno is set */
#define	FTS_F		 8		/* regular file */
#define	FTS_INIT	 9		/* initialized only */
#define	FTS_NS		10		/* stat(2) failed */
#define	FTS_NSOK	11		/* no stat(2) requested */
#define	FTS_SL		12		/* symbolic link */
#define	FTS_SLNONE	13		/* symbolic link without target */
	unsigned short fts_info;	/* user flags for FTSENT structure */
#define	FTS_DONTCHDIR	 0x01		/* don't chdir .. to the parent */
#define	FTS_SYMFOLLOW	 0x02		/* followed a symlink to get here */
	unsigned short fts_flags;	/* private flags for FTSENT structure */
#define	FTS_AGAIN	 1		/* read node again */
#define	FTS_FOLLOW	 2		/* follow symbolic link */
#define	FTS_NOINSTR	 3		/* no instructions */
#define	FTS_SKIP	 4		/* discard node */
	unsigned short fts_instr;	/* fts_set() instructions */
	unsigned short fts_spare;	/* unused */
	struct stat *fts_statp;		/* stat(2) information */
	char fts_name[1];		/* file name */
} FTSENT;

FTSENT	*fts_children(FTS *, int);
int	 fts_close(FTS *);
FTS	*fts_open(char * const *, int,
	    int (*)(const FTSENT **, const FTSENT **));
FTSENT	*fts_read(FTS *);
int	 fts_set(FTS *, FTSENT *, int);
#endif /* !HAVE_FTS */
#if !HAVE_GETPROGNAME
/*
 * Compatibility for getprogname(3).
 */
extern const char *getprogname(void);
#endif /* !HAVE_GETPROGNAME */
#if !HAVE_MD5
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
#endif /* !HAVE_MD5 */
#if !HAVE_MEMMEM
/*
 * Compatibility for memmem(3).
 */
void *memmem(const void *, size_t, const void *, size_t);
#endif /* !HAVE_MEMMEM */
#if !HAVE_MEMRCHR
/*
 * Compatibility for memrchr(3).
 */
void *memrchr(const void *b, int, size_t);
#endif /* !HAVE_MEMRCHR */
#if !HAVE_MKFIFOAT
/*
 * Compatibility for mkfifoat(2).
 */
int mkfifoat(int, const char *, mode_t);
#endif /* !HAVE_MKFIFOAT */
#if !HAVE_MKNODAT
/*
 * Compatibility for mknodat(2).
 */
int mknodat(int, const char *, mode_t, dev_t);
#endif /* !HAVE_MKNODAT */
#if !HAVE_READPASSPHRASE
/*
 * Macros and function required for readpassphrase(3).
 */
#define RPP_ECHO_OFF 0x00
#define RPP_ECHO_ON 0x01
#define RPP_REQUIRE_TTY 0x02
#define RPP_FORCELOWER 0x04
#define RPP_FORCEUPPER 0x08
#define RPP_SEVENBIT 0x10
#define RPP_STDIN 0x20
char *readpassphrase(const char *, char *, size_t, int);
#endif /* !HAVE_READPASSPHRASE */
#if !HAVE_REALLOCARRAY
/*
 * Compatibility for reallocarray(3).
 */
extern void *reallocarray(void *, size_t, size_t);
#endif /* !HAVE_REALLOCARRAY */
#if !HAVE_RECALLOCARRAY
/*
 * Compatibility for recallocarray(3).
 */
extern void *recallocarray(void *, size_t, size_t, size_t);
#endif /* !HAVE_RECALLOCARRAY */
#if !HAVE_SCAN_SCALED
/*
 * Compatibility for scan_scaled(3) and fmt_scaled(3).
 */
#define	FMT_SCALED_STRSIZE	7 /* minus sign, 4 digits, suffix, null byte */
int	fmt_scaled(long long, char *);
int	scan_scaled(char *, long long *);
#endif /* !HAVE_SCAN_SCALED */
#if !HAVE_SETRESGID
/*
 * Compatibility for setresgid(2).
 */
int setresgid(gid_t rgid, gid_t egid, gid_t sgid);
#endif /* !HAVE_SETRESGID */
#if !HAVE_SETRESUID
/*
 * Compatibility for setresuid(2).
 */
int setresuid(uid_t ruid, uid_t euid, uid_t suid);
#endif /* !HAVE_SETRESUID */
#if !HAVE_SHA2
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
#endif /* !HAVE_SHA2 */
#if !HAVE_STRLCAT
/*
 * Compatibility for strlcat(3).
 */
extern size_t strlcat(char *, const char *, size_t);
#endif /* !HAVE_STRLCAT */
#if !HAVE_STRLCPY
/*
 * Compatibility for strlcpy(3).
 */
extern size_t strlcpy(char *, const char *, size_t);
#endif /* !HAVE_STRLCPY */
#if !HAVE_STRNDUP
/*
 * Compatibility for strndup(3).
 */
extern char *strndup(const char *, size_t);
#endif /* !HAVE_STRNDUP */
#if !HAVE_STRNLEN
/*
 * Compatibility for strnlen(3).
 */
extern size_t strnlen(const char *, size_t);
#endif /* !HAVE_STRNLEN */
#if !HAVE_STRTONUM
/*
 * Compatibility for strotnum(3).
 */
extern long long strtonum(const char *, long long, long long, const char **);
#endif /* !HAVE_STRTONUM */
