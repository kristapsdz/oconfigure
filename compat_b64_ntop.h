/*
 * Compatibility for b64_ntop(3).
 */
extern int b64_ntop(unsigned char const *, size_t, char *, size_t);
extern int b64_pton(char const *, unsigned char *, size_t);
