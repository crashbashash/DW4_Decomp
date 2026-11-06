struct W { int *vt; int w[27]; };
extern "C" {
int FUN_003b4050(struct W *, int);
int igObject_InitHeader(struct W *);
extern int DAT_0053ff10[4];
extern char *DAT_00586dc8[4];
int beNDMWShopSelectB0_GetVTable(void);
}
int beNDMWShopSelectB0_GetVTable(void) {
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
    o.w[19] = 0;
    o.w[26] = 0;
    o.vt = DAT_0053ff10;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0053ff10;
    FUN_003b4050(&o, 0);
    return r;
}
