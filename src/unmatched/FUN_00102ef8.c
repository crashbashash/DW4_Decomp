typedef struct {
    unsigned char sts;
    unsigned char std;
    unsigned char mfd;
    unsigned char rcycle;
    unsigned short express;
    unsigned short notify;
    unsigned short sqwc;
    unsigned short tqwc;
    void *rbadr;
    unsigned int rbmsk;
} DmaEnv;
extern unsigned char DAT_004d1eb0[];
extern unsigned char DAT_004d1ec0[];
extern unsigned char DAT_004d1ed0[];
extern DmaEnv DAT_00555050;
int FUN_00102ef8(DmaEnv *env) {
    unsigned int ctrl, pcr, sqwc, rbor, rbsr;

    ctrl = *(volatile unsigned int *)0x1000E000;
    pcr = *(volatile unsigned int *)0x1000E020;
    sqwc = *(volatile unsigned int *)0x1000E030;
    rbor = *(volatile unsigned int *)0x1000E050;
    rbsr = *(volatile unsigned int *)0x1000E040;
    if (env->sts >= 10) return -1;
    if (env->std >= 10) return -2;
    if (env->mfd >= 10) return -3;
    if (env->rcycle >= 7) return -4;
    ctrl = (ctrl & ~0x30) | (DAT_004d1eb0[env->sts] << 4);
    ctrl = (ctrl & ~0xC0) | (DAT_004d1ec0[env->std] << 6);
    ctrl = (ctrl & ~0xC) | (DAT_004d1ed0[env->mfd] << 2);
    if (env->rcycle) {
        ctrl |= 2;
        ctrl = (ctrl & ~0x300) | ((env->rcycle - 1) << 8);
    } else {
        ctrl &= ~2;
    }
    pcr = (env->express << 16) | env->notify;
    sqwc = (env->tqwc << 16) | env->sqwc;
    rbor = (unsigned int)env->rbadr;
    rbsr = env->rbmsk;
    *(volatile unsigned int *)0x1000E000 = ctrl;
    *(volatile unsigned int *)0x1000E020 = pcr;
    *(volatile unsigned int *)0x1000E030 = sqwc;
    *(volatile unsigned int *)0x1000E050 = rbor;
    *(volatile unsigned int *)0x1000E040 = rbsr;
    DAT_00555050 = *env;
    return 0;
}
