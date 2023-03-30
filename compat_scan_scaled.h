/*
 * Compatibility for scan_scaled(3) and fmt_scaled(3).
 */
#define	FMT_SCALED_STRSIZE	7 /* minus sign, 4 digits, suffix, null byte */
int	fmt_scaled(long long, char *);
int	scan_scaled(char *, long long *);
