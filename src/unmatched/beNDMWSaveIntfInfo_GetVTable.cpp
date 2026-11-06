/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
union U { int vt; int w[8]; void *p[8]; char b[32]; };
extern "C" {
int FUN_0033ec80(int *, int);
int igObject_InitHeader(char *);
extern int DAT_0053d960[4];
extern void * DAT_00586dc8[4];
int beNDMWSaveIntfInfo_GetVTable(void);
}
int beNDMWSaveIntfInfo_GetVTable(void) {
    union U u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[5] = 0;
    u.w[6] = 0;
    u.w[0] = (int)(&DAT_0053d960[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0053d960[0]);
    FUN_0033ec80(&u.w[0], 0);
    return temp_s0;
}
