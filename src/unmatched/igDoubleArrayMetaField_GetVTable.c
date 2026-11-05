struct F { int *vt; char pad[8]; int *str; char pad2[48]; };
void StringChunk_ReleaseHeader(int, int *);
int igMetaField_Init(struct F *);
extern int DAT_0052f230[4];
extern int DAT_00530790[4];
extern char *DAT_00586dc8[4];
int igDoubleArrayMetaField_GetVTable(void) {
    struct F o;
    int r;
    int *s;
    int *h;
    int c;
    igMetaField_Init(&o);
    o.vt = DAT_00530790;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0052f230;
    if (&o.str != 0) {
        s = o.str;
        if (s != 0) {
            h = s - 2;
            c = s[-1] - 1;
            s[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*h, h);
        }
    }
    return r;
}
