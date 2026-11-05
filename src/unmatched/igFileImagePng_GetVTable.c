int FUN_00150180();
int FUN_00150490();
int igObject_InitHeader();
extern int DAT_00525d20[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[96]; };
int igFileImagePng_GetVTable(void) {
    union U u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[88] = 0;
    u.vt = (int)&DAT_00525d20[0];
    p = (int *)&u.b[92];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00525d20[0];
    FUN_00150180(p, -1);
    FUN_00150490(u.b, 0);
    return temp_s0;
}
