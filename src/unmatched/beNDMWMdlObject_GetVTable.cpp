/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct W { int *vt; int w[11]; };
extern "C" {
int FUN_003bf2f0(struct W *, int);
int igObject_InitHeader(struct W *);
extern int DAT_0053e480[4];
extern char *DAT_00586dc8[4];
int beNDMWMdlObject_GetVTable(void);
}
int beNDMWMdlObject_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[5] = 0;
    o.vt = DAT_0053e480;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0053e480;
    FUN_003bf2f0(&o, 0);
    return r;
}
