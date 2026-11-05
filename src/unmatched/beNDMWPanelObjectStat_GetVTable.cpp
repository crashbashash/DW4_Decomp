/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; int w[20]; void *p[20]; char b[80]; };
extern "C" {
int ObjectRef_Destruct_001c6460(int *, int);
int FUN_003bde80(int *, int);
int FUN_003be240(char *, int);
int ObjectRef_Destruct_00150eb0(int *, int);
int igObject_InitHeader(char *);
extern int DAT_0053e0c0[4];
extern void * DAT_00586dc8[4];
int beNDMWPanelObjectStat_GetVTable(void);
}
int beNDMWPanelObjectStat_GetVTable(void) {
    union U u;
    int temp_s2;

    igObject_InitHeader(u.b);
    u.w[9] = 0;
    u.w[11] = 0;
    u.w[12] = 0;
    u.w[0] = (int)(&DAT_0053e0c0[0]);
    u.w[15] = 0;
    u.w[16] = 0;
    u.w[17] = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0053e0c0[0]);
    FUN_003bde80(&u.w[17], -1);
    ObjectRef_Destruct_00150eb0(&u.w[16], -1);
    ObjectRef_Destruct_001c6460(&u.w[15], -1);
    FUN_003be240(u.b, 0);
    return temp_s2;
}
