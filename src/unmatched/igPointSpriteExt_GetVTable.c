
int FUN_001338d0(void *, int);
int FUN_0014c580(void *, int);
int igMatrix44f_SetIdentity(void *);
int igObject_InitHeader(void *);
extern int DAT_00526600[4];
extern void * DAT_00586dc8[4];
struct PointSpriteExtInstance { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; char t[368]; };
int igPointSpriteExt_GetVTable(void) {
    struct PointSpriteExtInstance o;
    int r;
    char *pa = (char *)&o;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.vt = &DAT_00526600[0];
    o.f16 = 0;
    o.f24 = 0;
    igMatrix44f_SetIdentity(&o.t[8]);
    igMatrix44f_SetIdentity(pa + 104);
    igMatrix44f_SetIdentity(pa + 168);
    igMatrix44f_SetIdentity(pa + 232);
    igMatrix44f_SetIdentity(pa + 296);
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00526600[0];
    FUN_001338d0(&o.f24, -1);
    FUN_0014c580(&o, 0);
    return r;
}

