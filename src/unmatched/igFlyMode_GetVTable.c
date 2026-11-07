struct Obj { int *vt; char p4[8]; int sub[4]; char pad[108]; int *ref; char pe[20]; };
int igObject_InitHeader(struct Obj *);
int igMatrix44f_SetIdentity(int *);
int igObject_Destroy();
extern int DAT_00542840[4];
extern int DAT_00542960[4];
extern void * DAT_00586dc8[4];
int igFlyMode_GetVTable(void) {
    struct Obj o;
    int r;
    int *t;
    igObject_InitHeader(&o);
    o.vt = &DAT_00542960[0];
    igMatrix44f_SetIdentity(o.sub);
    o.vt = &DAT_00542840[0];
    o.ref = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00542840[0];
    if (&o.ref != 0) {
        t = o.ref;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    return r;
}
