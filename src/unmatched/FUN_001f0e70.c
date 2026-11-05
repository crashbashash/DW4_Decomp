extern short DAT_00490e00[8];
extern int D_00490e00[4];
extern unsigned char DAT_00490e02[16];
union U { short s[8]; int w[4]; };
extern union U DAT_00490e10;
extern int DAT_00490e14[4];
extern int DAT_00490e18[4];
extern int DAT_00490e1c[4];
extern short DAT_0049149a[8];
extern int DAT_004e50f0[4];
void FUN_001f0e70(unsigned int arg0, short *arg1, int arg2, char * volatile *arg3) {
    short *src = arg1 + arg2;
    unsigned int i = 0;
    char *start = *arg3;
    char *p; char *cur;
    *arg3 = start + 16;
    DAT_00490e02[0] = arg0;
    DAT_00490e00[0] = DAT_0049149a[0] | 0xC000;
    p = *arg3;
    *arg3 = p + 4;
    *(int *)p = D_00490e00[0];
    for (; i < arg0; i++) {
        *(*(short * volatile *)arg3)++ = *src++;
    }
    while ((int)*arg3 & 3) {
        p = *arg3;
        *arg3 = p + 1;
        *p = 0;
    }
    while ((int)(cur = *arg3) & 15) {
        p = *arg3;
        *arg3 = p + 4;
        *(int *)p = DAT_004e50f0[0];
    }
    DAT_00490e10.s[0] = (cur - start) / 16 - 1;
    ((int *)start)[0] = DAT_00490e10.w[0];
    ((int *)start)[1] = DAT_00490e14[0];
    ((int *)start)[2] = DAT_00490e18[0];
    ((int *)start)[3] = DAT_00490e1c[0];
}
