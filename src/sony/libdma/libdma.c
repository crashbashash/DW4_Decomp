/* libdma: the EE DMA controller's channels and their environment (libdma.a's libdma.o). */

typedef struct {
    unsigned int DIR : 1;
    unsigned int p0 : 1;
    unsigned int MOD : 2;
    unsigned int ASP : 2;
    unsigned int TTE : 1;
    unsigned int TIE : 1;
    unsigned int STR : 1;
} tD_CHCR;

typedef union {
    tD_CHCR f;
    unsigned int word;
} uD_CHCR;

/* One channel's register block in the 0x10008000.. DMAC space. */
typedef struct {
    uD_CHCR chcr;
    unsigned int p0[3];
    unsigned int madr;
    unsigned int p1[3];
    unsigned int qwc;
    unsigned int p2[3];
    unsigned int tadr;
    unsigned int p3[3];
    unsigned int as0;
    unsigned int p4[3];
    unsigned int as1;
    unsigned int p5[11];
    unsigned int sadr;
} sceDmaChan;

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
} sceDmaEnv;

#define D_CTRL (*(volatile unsigned int *)0x1000e000)
#define D_STAT (*(volatile unsigned int *)0x1000e010)
#define D_PCR (*(volatile unsigned int *)0x1000e020)
#define D_SQWC (*(volatile unsigned int *)0x1000e030)
#define D_RBSR (*(volatile unsigned int *)0x1000e040)
#define D_RBOR (*(volatile unsigned int *)0x1000e050)
#define D_STADR (*(volatile unsigned int *)0x1000e060)
#define D_ENABLER (*(volatile unsigned int *)0x1000f520)
#define D_ENABLEW (*(volatile unsigned int *)0x1000f590)

#define D_CHCR_STR 0x100
#define D_ENABLE_CPND 0x10000
#define DMA_CHANNELS 10

int scePrintf(const char *fmt, ...);
int DIntr(void);
int EIntr(void);
unsigned int sceDmaPause(sceDmaChan *d);
int sceDmaPutEnv(sceDmaEnv *env);

static char __ps2_libinfo__[16] = "PsIIlibdma  2800";

static sceDmaChan *dch[DMA_CHANNELS] = {
    (sceDmaChan *)0x10008000, (sceDmaChan *)0x10009000, (sceDmaChan *)0x1000a000, (sceDmaChan *)0x1000b000,
    (sceDmaChan *)0x1000b400, (sceDmaChan *)0x1000c000, (sceDmaChan *)0x1000c400, (sceDmaChan *)0x1000c800,
    (sceDmaChan *)0x1000d000, (sceDmaChan *)0x1000d400,
};

sceDmaEnv sceDmaCurrentEnv;

/* Spins while the channel runs; after about 16M polls it reports and pauses it. */
static void WaitDma(sceDmaChan *d)
{
    int n = 0x1000000;

    while (*(volatile unsigned int *)&d->chcr.word & D_CHCR_STR) {
        if (--n < 0) {
            scePrintf("libdma: sync timeout\n");
            sceDmaPause(d);
        }
    }
}

/* Spins until the channel's address passes addr, with the same timeout as WaitDma. */
static void WatchDma(sceDmaChan *d, unsigned int addr, int limit)
{
    int n = limit ? limit : 0x1000000;

    while (*(volatile unsigned int *)&d->madr < addr) {
        if (--n < 0) {
            scePrintf("libdma: sync timeout\n");
            sceDmaPause(d);
        }
    }
}

/* Channels sceDmaReset clears: not SIF0..SIF2 (5..7), which the IOP side owns. */
static const int isclr[DMA_CHANNELS] = {1, 1, 1, 1, 1, 0, 0, 0, 1, 1};
/* D_CTRL STS, STD and MFD field codes for a channel number. */
static const unsigned char ststbl[DMA_CHANNELS] = {0, 0, 0, 3, 0, 1, 0, 0, 2, 0};
static const unsigned char stdtbl[DMA_CHANNELS] = {0, 1, 2, 0, 0, 0, 3, 0, 0, 0};
static const unsigned char mfdtbl[DMA_CHANNELS] = {0, 2, 3, 0, 0, 0, 0, 0, 0, 0};

/* A scratchpad address (0x7xxxxxxx) becomes the DMAC's SPR form (bit 31 set). */
static unsigned int CheckAddress(unsigned int addr)
{
    if ((addr >> 28) == 7) {
        addr &= 0x0fffffff;
        addr |= 0x80000000;
    }
    return addr;
}

static void memclr(char *p, int size)
{
    int n = size - 1;

    if (size != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != -1);
    }
}

sceDmaChan *sceDmaGetChan(unsigned int id)
{
    if (id < DMA_CHANNELS) {
        return dch[id];
    }
    return 0;
}

int sceDmaReset(int enable)
{
    int was_enabled = D_CTRL & 1;
    int i;
    sceDmaEnv env;

    for (i = 0; i < DMA_CHANNELS; i++) {
        if (isclr[i]) {
            sceDmaChan *d = dch[i];

            d->chcr.word = 0;
            d->madr = d->tadr = 0;
            d->as0 = d->as1 = 0;
            d->sadr = 0;
        }
    }
    D_STAT = 0xff1f;
    D_STAT = D_STAT & 0xff1f0000;
    memclr((char *)&env, sizeof(env));
    sceDmaPutEnv(&env);
    if (enable == 1) {
        D_CTRL = D_CTRL | 1;
    }
    return was_enabled;
}

int sceDmaPutEnv(sceDmaEnv *env)
{
    unsigned int ctrl, pcr, sqwc, rbor, rbsr;

    ctrl = D_CTRL;
    pcr = D_PCR;
    sqwc = D_SQWC;
    rbor = D_RBOR;
    rbsr = D_RBSR;
    if (env->sts >= DMA_CHANNELS) {
        return -1;
    }
    if (env->std >= DMA_CHANNELS) {
        return -2;
    }
    if (env->mfd >= DMA_CHANNELS) {
        return -3;
    }
    if (env->rcycle >= 7) {
        return -4;
    }
    ctrl = (ctrl & ~0x30) | (ststbl[env->sts] << 4);
    ctrl = (ctrl & ~0xc0) | (stdtbl[env->std] << 6);
    ctrl = (ctrl & ~0xc) | (mfdtbl[env->mfd] << 2);
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
    D_CTRL = ctrl;
    D_PCR = pcr;
    D_SQWC = sqwc;
    D_RBOR = rbor;
    D_RBSR = rbsr;
    sceDmaCurrentEnv = *env;
    return 0;
}

sceDmaEnv *sceDmaGetEnv(sceDmaEnv *env)
{
    *env = sceDmaCurrentEnv;
    return env;
}

unsigned int sceDmaPutStallAddr(unsigned int addr)
{
    unsigned int old = D_STADR;

    D_STADR = addr;
    return old;
}

/* Chain mode from the tag at tag. */
void sceDmaSend(sceDmaChan *d, void *tag)
{
    unsigned int addr = CheckAddress((unsigned int)tag);

    WaitDma(d);
    if (d->tadr != 0xffffffff) {
        d->tadr = addr;
    }
    d->qwc = 0;
    d->chcr.f.MOD = 1;
    d->chcr.f.DIR = 1;
    d->chcr.f.STR = 1;
}

/* Normal mode: qwc quadwords from addr. */
void sceDmaSendN(sceDmaChan *d, void *addr, int qwc)
{
    unsigned int madr = CheckAddress((unsigned int)addr);

    WaitDma(d);
    if (d->madr != 0xffffffff) {
        d->madr = madr;
    }
    d->qwc = qwc;
    d->chcr.f.MOD = 0;
    d->chcr.f.DIR = 1;
    d->chcr.f.STR = 1;
}

/* Interleave mode. */
void sceDmaSendI(sceDmaChan *d, void *addr, int qwc)
{
    unsigned int madr = CheckAddress((unsigned int)addr);

    WaitDma(d);
    if (d->madr != 0xffffffff) {
        d->madr = madr;
    }
    d->qwc = qwc;
    d->chcr.f.MOD = 2;
    d->chcr.f.DIR = 1;
    d->chcr.f.STR = 1;
}

/* Chain mode into memory: the destination tags come from the source side. */
void sceDmaRecv(sceDmaChan *d)
{
    WaitDma(d);
    d->qwc = 0;
    d->chcr.f.MOD = 1;
    d->chcr.f.DIR = 0;
    d->chcr.f.STR = 1;
}

void sceDmaRecvN(sceDmaChan *d, void *addr, int qwc)
{
    unsigned int madr = CheckAddress((unsigned int)addr);

    WaitDma(d);
    if (d->madr != 0xffffffff) {
        d->madr = madr;
    }
    d->qwc = qwc;
    d->chcr.f.MOD = 0;
    d->chcr.f.DIR = 0;
    d->chcr.f.STR = 1;
}

void sceDmaRecvI(sceDmaChan *d, void *addr, int qwc)
{
    unsigned int madr = CheckAddress((unsigned int)addr);

    WaitDma(d);
    if (d->madr != 0xffffffff) {
        d->madr = madr;
    }
    d->qwc = qwc;
    d->chcr.f.MOD = 2;
    d->chcr.f.DIR = 0;
    d->chcr.f.STR = 1;
}

/* mode 1 polls once: nonzero while the channel runs; otherwise waits for it. */
int sceDmaSync(sceDmaChan *d, int mode)
{
    if (mode == 1) {
        return (d->chcr.word >> 8) & 1;
    }
    WaitDma(d);
    return 0;
}

/* mode 1 polls once: nonzero while the channel is still before addr; otherwise waits. */
int sceDmaWatch(sceDmaChan *d, unsigned int addr, int mode, int limit)
{
    if (mode == 1) {
        return d->madr < addr;
    }
    WatchDma(d, addr, limit);
    return 0;
}

/* Stops the channel with the DMAC's interrupts held, returning its control word for sceDmaRestart. */
unsigned int sceDmaPause(sceDmaChan *d)
{
    int intr;
    unsigned int enable;
    unsigned int old;

    intr = DIntr();
    enable = D_ENABLER;
    if (!(enable & D_ENABLE_CPND)) {
        D_ENABLEW = enable | D_ENABLE_CPND;
    }
    D_CTRL;
    old = *(volatile unsigned int *)&d->chcr.word;
    d->chcr.word = old & ~D_CHCR_STR;
    D_ENABLEW = enable;
    if (intr) {
        EIntr();
    }
    return old;
}

/* Writes back the control word sceDmaPause returned; the result is whether the channel was running. */
unsigned int sceDmaRestart(sceDmaChan *d, unsigned int stat)
{
    unsigned int old = d->chcr.word;

    d->chcr.word = stat;
    return (old >> 8) & 1;
}
