/* stack-object GetVTable accessor with an inlined string release; verified by tools/verify.py. */
typedef struct { int *vt; int p1; int p2; char *str; int pad[12]; } Obj;
int igMetaField_Init(void *);
int StringChunk_ReleaseHeader();
extern int DAT_0052f230[4];
extern int DAT_0052fb50[4];
extern void * DAT_00586dc8[4];
int igLongArrayMetaField_GetVTable(void) {
    Obj o;
    int r;
    char *p;
    int *hdr;
    int c;

    igMetaField_Init(&o);
    o.vt = &DAT_0052fb50[0];
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0052f230[0];
    if (&o.str != 0) {
        p = o.str;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader(*hdr, hdr);
            }
        }
    }
    return r;
}
