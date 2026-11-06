/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
union U { int vt; char b[32]; };
extern "C" {
int FUN_0033ec80(char *, int);
int igObject_InitHeader(char *);
extern int DAT_0053d9d0[4];
extern void * DAT_00586dc8[4];
int beNDMWStageCtlInfo_GetVTable(void);
}
int beNDMWStageCtlInfo_GetVTable(void) {
    union U u;
    int temp_s0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_0053d9d0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053d9d0[0];
    FUN_0033ec80(u.b, 0);
    return temp_s0;
}
