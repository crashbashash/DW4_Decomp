char *igMetaEnum_GetNamesByMask(char *arg0, int arg1, int arg2, int arg3) {
    int *sp9C;
    int *hdr;
    int cnt;
    int i;
    int n;
    int len;
    int v;
    n = 0;
    cnt = igMetaEnum_GetNameCount((igMetaEnum *)arg3);
    *arg0 = 0;
    i = 0;
    len = arg1 - 1;
    for (; i < cnt; i++) {
        if (arg2 & igMetaEnum_GetValueAt((void *)arg3, i)) {
            if (n != 0) {
                strncat(arg0, DAT_004f9950, len);
            }
            igMetaEnum_GetNameAt((int *)&sp9C, (void *)arg3, i);
            strncat(arg0, sp9C, len);
            if (sp9C != 0) {
                hdr = sp9C - 2;
                v = sp9C[-1] - 1;
                sp9C[-1] = v;
                if (v == 0) {
                    StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hdr), (int)hdr);
                }
            }
            n++;
        }
    }
    arg0[arg1 - 1] = 0;
    return arg0;
}

char *igMetaEnum_GetValueName(char *arg0, int arg1, int arg2, int arg3) {
    int *s;
    int *h;
    int c;

    igMetaEnum_GetNameByValue((int *)&s, (const igMetaEnum *)arg3, arg2);
    strncpy(arg0, s, arg1 - 1);
    *(arg0 + arg1 - 1) = 0;
    if (s != 0) {
        h = s - 2;
        c = s[-1] - 1;
        s[-1] = c;
        if (c == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*h), (int)h);
        }
    }
    return arg0;
}

