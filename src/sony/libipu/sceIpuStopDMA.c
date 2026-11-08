typedef struct { unsigned int d4madr; unsigned int d4tadr; unsigned int d4qwc; unsigned int d4chcr; unsigned int d3madr; unsigned int d3qwc; unsigned int d3chcr; unsigned int ipubp; unsigned int ipuctrl; } Env;
void FUN_0010a4e0(unsigned int);
void setD3_CHCR(unsigned int);
#define R(a) (*(volatile unsigned int *)(a))
void sceIpuStopDMA(Env *e) {
    FUN_0010a4e0(1);
    e->d4madr = R(0x1000b410);
    e->d4tadr = R(0x1000b430);
    e->d4qwc = R(0x1000b420);
    e->d4chcr = R(0x1000b400);
    while (R(0x10002010) & 0xf0);
    setD3_CHCR(0);
    e->d3madr = R(0x1000b010);
    e->d3qwc = R(0x1000b020);
    e->d3chcr = R(0x1000b000);
    e->ipubp = R(0x10002020);
    e->ipuctrl = R(0x10002010);
}
