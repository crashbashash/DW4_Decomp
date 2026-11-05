int strncpy();
int StringChunk_ReleaseHeader();
int igMetaEnum_GetNameByValue();
char *igMetaEnum_GetValueName(char *arg0, int arg1, int arg2, int arg3) {
    int *s;
    int *h;
    int c;

    igMetaEnum_GetNameByValue(&s, arg3);
    strncpy(arg0, s, arg1 - 1);
    *(arg0 + arg1 - 1) = 0;
    if (s != 0) {
        h = s - 2;
        c = s[-1] - 1;
        s[-1] = c;
        if (c == 0) {
            StringChunk_ReleaseHeader(*h, h);
        }
    }
    return arg0;
}
