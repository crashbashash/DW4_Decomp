extern "C" {
int igObject_InitHeader(void *);
int igObject_Destroy(void *);
extern int DAT_00541b70[4];
extern void *DAT_00586dc8[4];
struct R { int vt; unsigned int rc; };
struct Obj { int *vt; char pad[12]; struct R *p; char pad2[12]; };
int igHotKeyBinding_GetVTable(void) {
    struct Obj o;
    struct R *t;
    int r;
    igObject_InitHeader(&o);
    o.vt = &DAT_00541b70[0];
    o.p = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00541b70[0];
    if (&o.p != 0) {
        t = o.p;
        if (t != 0) {
            t->rc = t->rc - 1;
            if ((t->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    return r;
}
}
