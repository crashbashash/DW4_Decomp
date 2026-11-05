extern "C" {
int igObject_InitHeader(void *);
int FUN_0019c1a0(void *, int);
int FUN_00195970(void *, int);
extern int DAT_00528c60[4];
extern void *DAT_00586dc8[4];
struct Obj { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; };
int igLightSet_GetVTable(void) {
    struct Obj o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f12 = 0;
    o.f16 = 0;
    o.vt = &DAT_00528c60[0];
    o.f28 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00528c60[0];
    FUN_0019c1a0(&o.f28, -1);
    FUN_00195970(&o, 0);
    return r;
}
}
