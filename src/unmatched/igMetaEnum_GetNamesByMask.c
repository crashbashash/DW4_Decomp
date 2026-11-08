int strncat(char *, int *, int);
int StringChunk_ReleaseHeader(int, int *);
int igMetaEnum_GetNameAt(int **, int, int);
int igMetaEnum_GetNameCount(int);
int igMetaEnum_GetValueAt(int, int);
extern int DAT_004f9950[];
char *igMetaEnum_GetNamesByMask(char *arg0, int arg1, int arg2, int arg3) {
    int *sp9C;
    int *hdr;
    int cnt;
    int i;
    int n;
    int len;
    int v;
    n = 0;
    cnt = igMetaEnum_GetNameCount(arg3);
    *arg0 = 0;
    i = 0;
    len = arg1 - 1;
    for (; i < cnt; i++) {
        if (arg2 & igMetaEnum_GetValueAt(arg3, i)) {
            if (n != 0) {
                strncat(arg0, DAT_004f9950, len);
            }
            igMetaEnum_GetNameAt(&sp9C, arg3, i);
            strncat(arg0, sp9C, len);
            if (sp9C != 0) {
                hdr = sp9C - 2;
                v = sp9C[-1] - 1;
                sp9C[-1] = v;
                if (v == 0) {
                    StringChunk_ReleaseHeader(*hdr, hdr);
                }
            }
            n++;
        }
    }
    arg0[arg1 - 1] = 0;
    return arg0;
}
