/* stack-object GetVTable accessor with an inlined member release; verified by tools/verify.py. */
int StringChunk_ReleaseHeader();
typedef struct { int *vt; int w[2]; char *s; } Obj;
int igObject_InitHeader(void *);
extern int DAT_00542160[4];
extern void * DAT_00586dc8[4];
int igViewerModeChangeMessage_GetVTable(void) {
    Obj o;
    int r;
    char *p;
    int *hdr;
    int c;

    igObject_InitHeader(&o);
    o.vt = &DAT_00542160[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00542160[0];
    if (&o.s != 0) {
        p = (char *)o.s;
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
