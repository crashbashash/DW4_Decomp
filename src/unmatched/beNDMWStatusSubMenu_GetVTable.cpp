/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; int w[28]; void *p[28]; char b[112]; };
extern "C" {
int FUN_003b90a0(int *, int);
int ObjectRef_Destruct_00150eb0(int *, int);
int beNDMWWindowCtrl_Destroy(char *, int);
int igObject_InitHeader(char *);
extern int DAT_0053ec20[4];
extern void * DAT_00586dc8[4];
int beNDMWStatusSubMenu_GetVTable(void);
}
int beNDMWStatusSubMenu_GetVTable(void) {
    union U u;
    int temp_s2;

    igObject_InitHeader(u.b);
    u.w[13] = 0;
    u.w[14] = 0;
    u.w[15] = 0;
    u.w[16] = 0;
    u.w[17] = 0;
    u.w[18] = 0;
    u.w[19] = 0;
    u.w[0] = (int)(&DAT_0053ec20[0]);
    u.w[22] = 0;
    u.w[24] = 0;
    u.w[25] = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0053ec20[0]);
    ObjectRef_Destruct_00150eb0(&u.w[25], -1);
    ObjectRef_Destruct_00150eb0(&u.w[24], -1);
    FUN_003b90a0(&u.w[22], -1);
    beNDMWWindowCtrl_Destroy(u.b, 0);
    return temp_s2;
}
