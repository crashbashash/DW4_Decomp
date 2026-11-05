/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct W { int *vt; int w[23]; };
extern "C" {
int beNDMWWindowCtrl_Destroy(struct W *, int);
int igObject_InitHeader(struct W *);
extern int DAT_0053ee70[4];
extern char *DAT_00586dc8[4];
int beNDMWStatusCtrlFolder_GetVTable(void);
}
int beNDMWStatusCtrlFolder_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.w[12] = 0;
    o.w[13] = 0;
    o.w[14] = 0;
    o.w[15] = 0;
    o.w[16] = 0;
    o.w[17] = 0;
    o.w[18] = 0;
    o.vt = DAT_0053ee70;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0053ee70;
    beNDMWWindowCtrl_Destroy(&o, 0);
    return r;
}
