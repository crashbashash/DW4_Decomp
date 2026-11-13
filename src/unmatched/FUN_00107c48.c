int DIntr(void);
int EIntr(void);
void FUN_00107c48(char *d, int *pic) {
    int fields;
    unsigned int src = pic[0] & 0x0FFFFFFF;
    unsigned int dst = *(unsigned int *)(d + 240) & 0x0FFFFFFF;
    unsigned int out;
    int srcstep, dststep, qwc;
    int f, i, intr;

    if (*(int *)(d + 396) == 3 || *(int *)(d + 248) == 0) {
        srcstep = pic[4] * 384;
        qwc = srcstep >> 4;
        if (*(int *)(d + 248)) {
            dststep = (*(int *)(d + 248) >> 4) * 384;
        } else {
            dststep = srcstep;
        }
        fields = 1;
    } else {
        dststep = (*(int *)(d + 248) >> 4) * 192;
        srcstep = (pic[4] >> 1) * 384;
        fields = 2;
        qwc = srcstep >> 4;
    }
    for (f = 0; f < fields; f++) {
        out = dst;
        for (i = 0; i < pic[3]; i++) {
            intr = DIntr();
            *(volatile unsigned int *)0x1000D480 = 0;
            *(volatile unsigned int *)0x1000D410 = src;
            *(volatile unsigned int *)0x1000D420 = qwc;
            *(volatile unsigned int *)0x1000D400 = 0x101;
            if (intr) {
                EIntr();
            }
            while (*(volatile unsigned int *)0x1000D400 & 0x100);
            intr = DIntr();
            *(volatile unsigned int *)0x1000D080 = 0;
            *(volatile unsigned int *)0x1000D010 = out;
            *(volatile unsigned int *)0x1000D020 = qwc;
            *(volatile unsigned int *)0x1000D000 = 0x100;
            if (intr) {
                EIntr();
            }
            while (*(volatile unsigned int *)0x1000D000 & 0x100);
            while (*(volatile unsigned int *)0x1000D020);
            out += dststep;
            src += srcstep;
        }
        dst += *(int *)(d + 252) * 192;
    }
}
