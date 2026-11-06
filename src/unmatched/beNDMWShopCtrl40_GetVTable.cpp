/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
union U { int vt; char b[96]; };
extern "C" {
int beNDMWWindowCtrl_Destroy(char *, int);
int igObject_InitHeader(char *);
extern int DAT_0053fd90[4];
extern void * DAT_00586dc8[4];
int beNDMWShopCtrl40_GetVTable(void);
}
int beNDMWShopCtrl40_GetVTable(void) {
    union U u;
    int t;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    u.vt = (int)&DAT_0053fd90[0];
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053fd90[0];
    beNDMWWindowCtrl_Destroy(u.b, 0);
    return t;
}
