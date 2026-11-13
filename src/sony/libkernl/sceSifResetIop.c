typedef struct {
    unsigned int psize : 8;
    unsigned int dsize : 24;
    void *dest;
    int cid;
    unsigned int opt;
    int length;
    int arg;
    char name[80];
} __attribute__((aligned(8))) BootPacket;

typedef struct {
    void *src;
    void *dest;
    int size;
    int attr;
} DmaTransfer;

void sceSifExecNotifyHandler(int a, int b);
void FUN_0010b1b0(void);
unsigned int sceSifGetReg(unsigned int reg);
void FUN_0010b2e0(unsigned int reg, unsigned int value);
unsigned int FUN_0010b2a0(DmaTransfer *dma, int count);
void sceSifWriteBackDCache(void *addr, int size);
extern BootPacket D_00559680;

int sceSifResetIop(const char *name, int arg)
{
    DmaTransfer dma;
    void *dest;
    int i;
    sceSifExecNotifyHandler(0, 0);
    sceSifExecNotifyHandler(1, 0);
    FUN_0010b1b0();
    dest = (void *)sceSifGetReg(0x80000000);
    D_00559680.arg = arg;
    for (i = 0; name[i] != 0; i++) {
        D_00559680.name[i] = name[i];
    }
    D_00559680.dest = 0;
    D_00559680.dsize = 0;
    D_00559680.psize = 104;
    D_00559680.length = i;
    D_00559680.cid = 0x80000003;
    dma.src = &D_00559680;
    dma.dest = dest;
    dma.size = 104;
    dma.attr = 68;
    sceSifWriteBackDCache(&D_00559680, 104);
    FUN_0010b2e0(4, 0x40000);
    if (FUN_0010b2a0(&dma, 1) != 0) {
        FUN_0010b2e0(4, 0x10000);
        FUN_0010b2e0(4, 0x20000);
        FUN_0010b2e0(0x80000002, 0);
        FUN_0010b2e0(0x80000000, 0);
        return 1;
    }
    return 0;
}
