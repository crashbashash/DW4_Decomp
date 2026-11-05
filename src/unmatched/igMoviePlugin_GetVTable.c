/* stack-object GetVTable accessor with an inlined member release; verified by tools/verify.py. */
typedef struct Q { char pad4[4]; int f4; } Q;
int igObject_Destroy(void *);
typedef struct { int *vt; int w[1]; Q *s; } Obj;
int igObject_InitHeader(void *);
extern int DAT_00533ee0[4];
extern void * DAT_00586dc8[4];
int igMoviePlugin_GetVTable(void) {
    Obj o;
    int r;
    Q *q;

    igObject_InitHeader(&o);
    o.vt = &DAT_00533ee0[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00533ee0[0];
    if (&o.s != 0) {
        q = o.s;
        if (q != 0) {
            q->f4 -= 1;
            if ((q->f4 & 0x7fffff) == 0) {
                igObject_Destroy(q);
            }
        }
    }
    return r;
}
