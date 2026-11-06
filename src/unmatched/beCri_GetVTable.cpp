/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w[19]; };
extern "C" {
int FUN_0014aa70(int *, int);
int FUN_001d35d0(int *, int);
int FUN_00231030(struct Obj *, int);
int FUN_00367a20(int *, int);
int FUN_00367aa0(int *, int);
int igObject_InitHeader(struct Obj *);
extern int DAT_0053a3e0[4];
extern void * DAT_00586dc8[4];
int beCri_GetVTable(void);
}
int beCri_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.vt = &DAT_0053a3e0[0];
    obj.w[7] = 0;
    obj.w[8] = 0;
    obj.w[9] = 0;
    obj.w[10] = 0;
    obj.w[11] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053a3e0[0];
    FUN_0014aa70(&obj.w[11], -1);
    FUN_001d35d0(&obj.w[10], -1);
    FUN_00367aa0(&obj.w[9], -1);
    FUN_00367a20(&obj.w[8], -1);
    FUN_00367a20(&obj.w[7], -1);
    FUN_00231030(&obj, 0);
    return r;
}
