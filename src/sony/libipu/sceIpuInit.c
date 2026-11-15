typedef int quadword __attribute__((mode(TI)));


#define IPU_CMD (*(volatile unsigned int *)0x10002000)
#define IPU_CTRL (*(volatile unsigned int *)0x10002010)
#define IPU_IN_FIFO (*(volatile quadword *)0x10007010)
#define D4_CHCR (*(volatile unsigned int *)0x1000b400)
#define D_ENABLER (*(volatile unsigned int *)0x1000f520)
#define D_ENABLEW (*(volatile unsigned int *)0x1000f590)

#define D_ENABLE_CPND 0x10000
#define IPU_CTRL_RST 0x40000000
#define IPU_CMD_BCLR 0x00000000
#define IPU_CMD_SETIQ_INTRA 0x50000000
#define IPU_CMD_SETIQ_NONINTRA 0x58000000
#define IPU_CMD_SETVQ 0x60000000
#define IPU_CMD_FDEC 0x90000000

int DIntr(void);
int EIntr(void);

static char __ps2_libinfo__[16] = "PsIIlibipu  2800";

static unsigned char iqval[80] __attribute__((aligned(16))) = {
    0x08, 0x10, 0x10, 0x13, 0x10, 0x13, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x1a, 0x18, 0x1a, 0x1b,
    0x1b, 0x1b, 0x1a, 0x1a, 0x1a, 0x1a, 0x1b, 0x1b, 0x1b, 0x1d, 0x1d, 0x1d, 0x22, 0x22, 0x22, 0x1d,
    0x1d, 0x1d, 0x1b, 0x1b, 0x1d, 0x1d, 0x20, 0x20, 0x22, 0x22, 0x25, 0x26, 0x25, 0x23, 0x23, 0x22,
    0x23, 0x26, 0x26, 0x28, 0x28, 0x28, 0x30, 0x30, 0x2e, 0x2e, 0x38, 0x38, 0x3a, 0x45, 0x45, 0x53,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
};

/* 16-colour VQ palette, RGB555 */
static unsigned short vqval[16] __attribute__((aligned(16))) = {
    0x0000, 0x0421, 0x0842, 0x03e0, 0x1084, 0x14a5, 0x18c6, 0x1ce7,
    0x001f, 0x2529, 0x294a, 0x7c00, 0x318c, 0x35ad, 0x7fff, 0x39ce,
};

static void setD4_CHCR(unsigned int chcr)
{
    int intr = DIntr();

    D_ENABLEW = D_ENABLER | D_ENABLE_CPND;
    D4_CHCR = chcr;
    D_ENABLEW = D_ENABLER & ~D_ENABLE_CPND;
    if (intr) EIntr();
}

void sceIpuInit(void)
{
    quadword *p = 0;    /* set twice: alias analysis cannot fold p to iqval, so each read of p[4] is reissued */

    setD4_CHCR(1);
    IPU_CTRL = IPU_CTRL_RST;
    while ((int)IPU_CTRL < 0);
    IPU_CMD = IPU_CMD_BCLR;
    while ((int)IPU_CTRL < 0);

    p = (quadword *)iqval;
    IPU_IN_FIFO = p[0];
    IPU_IN_FIFO = p[1];
    IPU_IN_FIFO = p[2];
    IPU_IN_FIFO = p[3];
    IPU_IN_FIFO = p[4];
    IPU_IN_FIFO = p[4];
    IPU_IN_FIFO = p[4];
    IPU_IN_FIFO = p[4];
    IPU_CMD = IPU_CMD_SETIQ_INTRA;
    while ((int)IPU_CTRL < 0);
    IPU_CMD = IPU_CMD_SETIQ_NONINTRA;
    while ((int)IPU_CTRL < 0);

    IPU_IN_FIFO = ((quadword *)vqval)[0];
    IPU_IN_FIFO = ((quadword *)vqval)[1];
    IPU_CMD = IPU_CMD_SETVQ;
    while ((int)IPU_CTRL < 0);
    IPU_CMD = IPU_CMD_FDEC;
    while ((int)IPU_CTRL < 0);

    IPU_CTRL = IPU_CTRL_RST;
    while ((int)IPU_CTRL < 0);
    IPU_CMD = IPU_CMD_BCLR;
    while ((int)IPU_CTRL < 0);
}
