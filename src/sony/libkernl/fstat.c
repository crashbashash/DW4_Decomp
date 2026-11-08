/* Fills a stat-like record for a character device: mode 0x2000, 64-bit field at +72 cleared. */

typedef struct {
    int f0;
    int mode;           /* +4: 0x2000 is S_IFCHR in the newlib <sys/stat.h> encoding */
    char pad8[64];
    long f72;           /* +72: EE GCC `long` is 64 bits (stored with sd) */
} StatRecord10b698;

int fstat(int fd, StatRecord10b698 *st) {
    st->f72 = 0;
    st->mode = 0x2000;
    return 0;
}
