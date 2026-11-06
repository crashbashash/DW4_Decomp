union U { int vt; char b[128]; };
extern "C" {
int FUN_003ba3d0(char *, int);
int beNDMWStatusCtrlBaseEquip_Construct(char *);
extern int DAT_0053f0a0[4];
extern void * DAT_00586dc8[4];
int beNDMWStatusPowerSocket_GetVTable(void);
}
int beNDMWStatusPowerSocket_GetVTable(void) {
    union U u;
    int temp_s0;

    beNDMWStatusCtrlBaseEquip_Construct(u.b);
    u.vt = (int)&DAT_0053f0a0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053f0a0[0];
    FUN_003ba3d0(u.b, 0);
    return temp_s0;
}
