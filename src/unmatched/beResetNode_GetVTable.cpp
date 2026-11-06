/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct W { int *vt; int w[11]; };
extern "C" {
int FUN_00195a90(struct W *, int);
int igObject_InitHeader(struct W *);
extern int DAT_00538810[4];
extern char *DAT_00586dc8[4];
int beResetNode_GetVTable(void);
}
int beResetNode_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[2] = 0;
    o.w[3] = 0;
    o.w[6] = 0;
    o.vt = DAT_00538810;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_00538810;
    FUN_00195a90(&o, 0);
    return r;
}
