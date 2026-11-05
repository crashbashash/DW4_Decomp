int FUN_0014c440();
int igMatrix44f_SetIdentity();
int igObject_InitHeader();
extern int DAT_00525320[4];
extern int DAT_00526600[4];
extern void * DAT_00586dc8[4];
struct O { int vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; char t[368]; };
int igPsx2PointSpriteExt_GetVTable(void) {
    struct O o;
    int temp_s0;
    char *pa = (char *)&o;

    igObject_InitHeader(&o);
    o.f8 = 0;
    o.vt = (int)&DAT_00526600[0];
    o.f16 = 0;
    o.f24 = 0;
    igMatrix44f_SetIdentity(&o.t[8]);
    igMatrix44f_SetIdentity(pa + 104);
    igMatrix44f_SetIdentity(pa + 168);
    igMatrix44f_SetIdentity(pa + 232);
    igMatrix44f_SetIdentity(pa + 296);
    o.vt = (int)&DAT_00525320[0];
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = (int)&DAT_00525320[0];
    FUN_0014c440(&o, 0);
    return temp_s0;
}
