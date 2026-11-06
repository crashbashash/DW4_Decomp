union U { int vt; char b[48]; };
extern "C" {
int FUN_003bf2f0(char *, int);
int igObject_InitHeader(char *);
extern int DAT_0053e210[4];
extern void * DAT_00586dc8[4];
int beNDMWMdlEBullet_GetVTable(void);
}
int beNDMWMdlEBullet_GetVTable(void) {
    union U u;
    int temp_s0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_0053e210[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053e210[0];
    FUN_003bf2f0(u.b, 0);
    return temp_s0;
}
