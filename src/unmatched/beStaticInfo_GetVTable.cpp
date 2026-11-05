/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; char b[32]; };
extern "C" {
int FUN_0033ec80(char *, int);
int igObject_InitHeader(char *);
extern int DAT_00539420[4];
extern void * DAT_00586dc8[4];
int beStaticInfo_GetVTable(void);
}
int beStaticInfo_GetVTable(void) {
    union U u;
    int t;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_00539420[0];
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00539420[0];
    FUN_0033ec80(u.b, 0);
    return t;
}
