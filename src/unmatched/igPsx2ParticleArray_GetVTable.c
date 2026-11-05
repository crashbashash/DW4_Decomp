int FUN_0014caf0();
int igObject_InitHeader();
extern int DAT_005253e0[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[128]; };
int igPsx2ParticleArray_GetVTable(void) {
    union U u;
    int t;
    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[40] = 0;
    *(int *)&u.b[44] = 0;
    *(int *)&u.b[48] = 0;
    *(int *)&u.b[68] = 0;
    u.vt = (int)&DAT_005253e0[0];
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_005253e0[0];
    FUN_0014caf0(u.b, 0);
    return t;
}
