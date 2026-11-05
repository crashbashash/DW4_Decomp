int FUN_001353b0();
int FUN_0044be30();
int FUN_0044bf10();
int StringRef_Destruct_00130720();
int igObject_InitHeader();
union U { int vt; int w[16]; void *p[16]; char b[64]; };
extern int DAT_00540c10[4];
extern void * DAT_00586dc8[4];
int igTextElement_GetVTable(void) {
    union U u;

    int temp_s2;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[10] = 0;
    u.w[0] = (int)(&DAT_00540c10[0]);
    u.w[11] = 0;
    u.w[12] = 0;
    u.w[13] = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00540c10[0]);
    StringRef_Destruct_00130720(&u.w[13], -1);
    FUN_001353b0(&u.w[12], -1);
    FUN_0044bf10(&u.w[11], -1);
    FUN_0044be30(u.b, 0);
    return temp_s2;
}

