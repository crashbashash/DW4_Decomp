typedef struct { unsigned int d4madr; unsigned int d4tadr; unsigned int d4qwc; unsigned int d4chcr; unsigned int d3madr; unsigned int d3qwc; unsigned int d3chcr; unsigned int ipubp; unsigned int ipuctrl; } Env;
void FUN_0010a4e0(unsigned int);
void setD3_CHCR(unsigned int);
#define R(a) (*(volatile unsigned int *)(a))
void sceIpuRestartDMA(Env *e) {
    unsigned int bp, ifc, fp, n, qwc, madr;
    bp = e->ipubp & 0x7f;
    fp = (e->ipubp >> 16) & 0x3;
    ifc = (e->ipubp >> 8) & 0xf;
    n = fp + ifc;
    madr = e->d4madr - (n << 4);
    qwc = e->d4qwc + n;
    if (e->d3madr && e->d3qwc) {
        R(0x1000b010) = e->d3madr;
        R(0x1000b020) = e->d3qwc;
        setD3_CHCR(e->d3chcr | 0x100);
    }
    while ((int)R(0x10002010) < 0);
    R(0x10002000) = bp;
    while ((int)R(0x10002010) < 0);
    if (madr && qwc) {
        R(0x1000b410) = madr;
        R(0x1000b430) = e->d4tadr;
        R(0x1000b420) = qwc;
        FUN_0010a4e0(e->d4chcr | 0x100);
    }
}
