int FUN_0013bfe0();
int FUN_00151090();
int FUN_0018f980();
int FUN_00199970();
int FUN_0019ab10();
int FUN_0019ac10();
int FUN_0019c0e0();
int FUN_0019c1a0();
int FUN_0019c220();
int FUN_0019c2a0();
int FUN_0019c320();
int FUN_0019c330();
int FUN_0019c340();
int FUN_0019c350();
int FUN_0019c360();
int FUN_0019c370();
int FUN_0019c380();
extern int DAT_005289f0[4];
extern int D_005289f0[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[112]; };
int igPlanarShadowShader_GetVTable(void) {
    union U u;


    int temp_s5;

    FUN_0019c380(u.b);
    u.vt = (int)&DAT_005289f0[0];
    FUN_0019c370(&u.b[40]);
    FUN_0019c360(&u.b[44]);
    FUN_00151090(&u.b[48]);
    FUN_00151090(&u.b[64]);
    FUN_0019c360(&u.b[80]);
    FUN_0019c350(&u.b[84]);
    FUN_0019c340(&u.b[88]);
    FUN_0019c330(&u.b[92]);
    FUN_0019c330(&u.b[96]);
    FUN_0019ac10(&u.b[100]);
    FUN_0019c320(&u.b[104]);
    temp_s5 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&D_005289f0[0];
    FUN_0019c2a0(&u.b[104], -1);
    FUN_0019ab10(&u.b[100], -1);
    FUN_0018f980(&u.b[96], -1);
    FUN_0018f980(&u.b[92], -1);
    FUN_0013bfe0(&u.b[88], -1);
    FUN_0019c220(&u.b[84], -1);
    FUN_00199970(&u.b[80], -1);
    FUN_00199970(&u.b[44], -1);
    FUN_0019c1a0(&u.b[40], -1);
    FUN_0019c0e0(u.b, 0);
    return temp_s5;
}
