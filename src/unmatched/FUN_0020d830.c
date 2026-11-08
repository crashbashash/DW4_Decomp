int FUN_001236e8(char *);
int strlen(char *);
int strcmp(char *, int);
extern char DAT_00491910[];
extern int DAT_0056c2a8[];
extern int DAT_0056c2b0[];
int FUN_0020d830(int arg0) {
    int r;
    int off;
    char *p;
    r = -1;
    off = 0;
    do {
        p = DAT_00491910 + off;
        if (strcmp(p, arg0) == 0) {
            off = off + (strlen(p) + 1);
            r = DAT_0056c2b0[0] + FUN_001236e8(DAT_00491910 + off);
            break;
        }
        off = off + (strlen(p) + 1);
        off = off + (strlen(DAT_00491910 + off) + 1);
    } while (off < DAT_0056c2a8[0]);
    return r;
}
