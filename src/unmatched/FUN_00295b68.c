/* Copies a file name into the handle's +440 buffer, truncating to the +444 capacity (and reporting
 * it) when the name is longer. */
extern int strlen(const char *s);
extern char *strcpy(char *dst, const char *src);
extern char *strncpy(char *dst, const char *src, int n);
extern void FUN_0029a320(const char *msg);
extern char DAT_004f38f8[]; /* "E211121: filename is longer." */

typedef struct {
    char pad0[440];
    char *fname;    /* 440 */
    int fnameMax;   /* 444 */
} Ply295b68;

void FUN_00295b68(Ply295b68 *ply, const char *fname) {
    if (ply->fnameMax < strlen(fname)) {
        FUN_0029a320(DAT_004f38f8);
        strncpy(ply->fname, fname, ply->fnameMax);
        return;
    }
    strcpy(ply->fname, fname);
}
