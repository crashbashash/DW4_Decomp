struct W { int *vt; int w[7]; };
extern "C" {
int FUN_0033ec80(struct W *, int);
int igObject_InitHeader(struct W *);
extern int DAT_00538fa0[4];
extern char *DAT_00586dc8[4];
int beSeInfo_GetVTable(void);
}
int beSeInfo_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[4] = 0;
    o.w[5] = 0;
    o.vt = DAT_00538fa0;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_00538fa0;
    FUN_0033ec80(&o, 0);
    return r;
}
