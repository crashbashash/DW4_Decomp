struct Obj { int *vt; char p4[8]; int *m12; int *m16; char pe[44]; };
int igObject_InitHeader(struct Obj *);
int StringChunk_ReleaseHeader();
int igObject_Destroy();
extern int DAT_00529d30[4];
extern void * DAT_00586dc8[4];
int igAnimationCombinerBoneInfo_GetVTable(void) {
    struct Obj o;
    int r;
    int *t;
    int *p;
    int c;
    igObject_InitHeader(&o);
    o.vt = &DAT_00529d30[0];
    o.m12 = 0;
    o.m16 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00529d30[0];
    if (&o.m16 != 0) {
        t = o.m16;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    if (&o.m12 != 0) {
        t = o.m12;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    return r;
}
