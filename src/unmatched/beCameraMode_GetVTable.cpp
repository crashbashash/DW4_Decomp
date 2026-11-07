struct Obj { int *vt; char p4[8]; int sub[4]; char pad[48]; int *r1; int *r2; char pe[44]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int igMatrix44f_SetIdentity(int *);
int igObject_Destroy(int *);
extern int DAT_0053a2b0[4];
extern int DAT_00542960[4];
extern void * DAT_00586dc8[4];
int beCameraMode_GetVTable(void);
}
int beCameraMode_GetVTable(void) {
    struct Obj o;
    int r;
    int *t;

    igObject_InitHeader(&o);
    o.vt = &DAT_00542960[0];
    igMatrix44f_SetIdentity(o.sub);
    o.vt = &DAT_0053a2b0[0];
    o.r1 = 0;
    o.r2 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0053a2b0[0];
    if (&o.r2 != 0) {
        t = o.r2;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    if (&o.r1 != 0) {
        t = o.r1;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    return r;
}
