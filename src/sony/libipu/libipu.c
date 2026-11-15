typedef struct sceIpuDmaEnv {
    unsigned int d4madr;
    unsigned int d4tadr;
    unsigned int d4qwc;
    unsigned int d4chcr;
    unsigned int d3madr;
    unsigned int d3qwc;
    unsigned int d3chcr;
    unsigned int ipubp;
    unsigned int ipuctrl;
} sceIpuDmaEnv;

#define IPU_CMD (*(volatile unsigned int *)0x10002000)
#define IPU_CTRL (*(volatile unsigned int *)0x10002010)
#define IPU_BP (*(volatile unsigned int *)0x10002020)
#define D3_CHCR (*(volatile unsigned int *)0x1000b000)
#define D3_MADR (*(volatile unsigned int *)0x1000b010)
#define D3_QWC (*(volatile unsigned int *)0x1000b020)
#define D4_CHCR (*(volatile unsigned int *)0x1000b400)
#define D4_MADR (*(volatile unsigned int *)0x1000b410)
#define D4_QWC (*(volatile unsigned int *)0x1000b420)
#define D4_TADR (*(volatile unsigned int *)0x1000b430)
#define D_ENABLER (*(volatile unsigned int *)0x1000f520)
#define D_ENABLEW (*(volatile unsigned int *)0x1000f590)

#define D_CHCR_STR 0x100
#define D_ENABLE_CPND 0x10000
#define IPU_CTRL_BUSY 0x80000000
#define IPU_CTRL_IFC_FP_MASK 0xf0

int DIntr(void);
int EIntr(void);

static void setD3_CHCR(unsigned int chcr)
{
    int intr = DIntr();

    D_ENABLEW = D_ENABLER | D_ENABLE_CPND;
    D3_CHCR = chcr;
    D_ENABLEW = D_ENABLER & ~D_ENABLE_CPND;
    if (intr) EIntr();
}

static void setD4_CHCR(unsigned int chcr)
{
    int intr = DIntr();

    D_ENABLEW = D_ENABLER | D_ENABLE_CPND;
    D4_CHCR = chcr;
    D_ENABLEW = D_ENABLER & ~D_ENABLE_CPND;
    if (intr) EIntr();
}

void sceIpuStopDMA(sceIpuDmaEnv *env)
{
    setD4_CHCR(1);
    env->d4madr = D4_MADR;
    env->d4tadr = D4_TADR;
    env->d4qwc = D4_QWC;
    env->d4chcr = D4_CHCR;
    while (IPU_CTRL & IPU_CTRL_IFC_FP_MASK);
    setD3_CHCR(0);
    env->d3madr = D3_MADR;
    env->d3qwc = D3_QWC;
    env->d3chcr = D3_CHCR;
    env->ipubp = IPU_BP;
    env->ipuctrl = IPU_CTRL;
}

void sceIpuRestartDMA(sceIpuDmaEnv *env)
{
    unsigned int bp = env->ipubp & 0x7f;
    unsigned int fifo = ((env->ipubp >> 16) & 0x3) + ((env->ipubp >> 8) & 0xf);
    unsigned int madr = env->d4madr - (fifo << 4);
    unsigned int qwc = env->d4qwc + fifo;

    if (env->d3madr && env->d3qwc) {
        D3_MADR = env->d3madr;
        D3_QWC = env->d3qwc;
        setD3_CHCR(env->d3chcr | D_CHCR_STR);
    }
    while ((int)IPU_CTRL < 0);
    IPU_CMD = bp;
    while ((int)IPU_CTRL < 0);
    if (madr && qwc) {
        D4_MADR = madr;
        D4_TADR = env->d4tadr;
        D4_QWC = qwc;
        setD4_CHCR(env->d4chcr | D_CHCR_STR);
    }
}

int sceIpuSync(int mode)
{
    int busy = 0;

    switch (mode) {
    case 0:
        while ((int)IPU_CTRL < 0);
        busy = 0;
        break;
    case 1:
        busy = IPU_CTRL >> 31;
        break;
    }
    return busy;
}
