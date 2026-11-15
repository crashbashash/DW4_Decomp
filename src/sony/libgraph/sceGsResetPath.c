typedef int quadword __attribute__((mode(TI)));

#define VIF1_FBRST (*(volatile unsigned int *)0x10003c10)
#define VIF1_ERR (*(volatile unsigned int *)0x10003c20)
#define VIF1_FIFO (*(volatile quadword *)0x10005000)
#define GIF_CTRL (*(volatile unsigned int *)0x10003000)

static unsigned int init_vif_regs[8] = {0x01000404, 0x20000000, 0, 0x05000000, 0x06000000, 0x03000000, 0x02000000, 0x04000000};

void sceGsResetPath(void)
{
    unsigned int status = 0;

    VIF1_FBRST = 1;
    VIF1_ERR = 2;
    __asm__("sync.l");
    __asm__("cfc2 %0, $vi28\n"
            "ori  %0, %0, 0x0200\n"
            "ctc2 %0, $vi28\n"
            "sync.p\n"
            : : "r"(status));
    VIF1_FIFO = *(quadword *)&init_vif_regs[0];
    VIF1_FIFO = *(quadword *)&init_vif_regs[4];
    GIF_CTRL = 1;
}
