union U { int vt; char b[96]; };
extern "C" {
int FUN_0019ab10(char *, int);
int FUN_001aaf00(char *, int);
int FUN_001d21b0(char *, int);
int FUN_00239200(char *, int);
int FUN_0036c450(char *, int);
int igObject_InitHeader(char *);
extern int DAT_005343b0[4];
extern void * DAT_00586dc8[4];
int beAction2InfoWork_GetVTable(void);
}
int beAction2InfoWork_GetVTable(void) {
    union U u;
    int temp_s;
    char *p184;
    char *p180;
    char *p176;
    char *p104;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_005343b0[0];
    p104 = &u.b[8];
    *(int *)p104 = 0;
    p176 = &u.b[80];
    *(int *)p176 = 0;
    p180 = &u.b[84];
    *(int *)p180 = 0;
    p184 = &u.b[88];
    *(int *)p184 = 0;
    *(int *)&u.b[92] = 0;
    temp_s = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_005343b0[0];
    FUN_00239200(&u.b[92], -1);
    FUN_001d21b0(p184, -1);
    FUN_001aaf00(p180, -1);
    FUN_0019ab10(p176, -1);
    FUN_0036c450(p104, -1);
    return temp_s;
}
