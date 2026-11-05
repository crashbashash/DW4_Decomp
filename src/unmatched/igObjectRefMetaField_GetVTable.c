/* stack-object GetVTable accessor with two inlined string releases; verified by tools/verify.py. */
typedef struct { int *vt; int p1; int p2; char *s1; int pad[12]; char *s2; int tail[1]; } Obj;
int igObjectRefMetaField_Init(void *);
int StringChunk_ReleaseHeader();
extern int DAT_00532c80[4];
extern int DAT_0052f230[4];
extern void * DAT_00586dc8[4];
int igObjectRefMetaField_GetVTable(void) {
    Obj o;
    int r;
    char *p;
    int *hdr;
    int c;

    igObjectRefMetaField_Init(&o);
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00532c80[0];
    if (&o.s2 != 0) {
        p = o.s2;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader(*hdr, hdr);
            }
        }
    }
    o.vt = &DAT_0052f230[0];
    if (&o.s1 != 0) {
        p = o.s1;
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
