/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" {
int FUN_00231030(char *, int);
int FUN_00232ae0(int *, int);
int FUN_00335930(int *, int);
int FUN_00336d90(int *, int);
int FUN_00336e10(int *, int);
int FUN_00336e90(int *, int);
int igObject_InitHeader(char *);
extern int DAT_00533e50[4];
extern void * DAT_00586dc8[4];
int igMovieManager_GetVTable(void);
}
int igMovieManager_GetVTable(void) {
    union U u;
    int temp_s4;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[0] = (int)(&DAT_00533e50[0]);
    u.w[4] = 0;
    u.w[6] = 0;
    u.w[7] = 0;
    u.w[8] = 0;
    u.w[9] = 0;
    temp_s4 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00533e50[0]);
    FUN_00232ae0(&u.w[9], -1);
    FUN_00336e90(&u.w[8], -1);
    FUN_00336e10(&u.w[7], -1);
    FUN_00335930(&u.w[6], -1);
    FUN_00336d90(&u.w[4], -1);
    FUN_00231030(u.b, 0);
    return temp_s4;
}
