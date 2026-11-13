typedef struct {
    volatile int count;
    int done;
    int remain;
    unsigned int addr;
    int total;
} CscDmaState;
#define D_STAT (*(volatile unsigned int *)0x1000E010)
#define D3_CHCR (*(volatile unsigned int *)0x1000B000)
#define D3_MADR (*(volatile unsigned int *)0x1000B010)
#define D3_QWC (*(volatile unsigned int *)0x1000B020)
#define IPU_CMD (*(volatile unsigned int *)0x10002000)
int _ch3dmaCSC(int channel, CscDmaState *state) {
    D_STAT = 8;
    state->count++;
    if (D3_QWC != 0 || (D3_CHCR & 0x100)) {
        state->done = 1;
        __asm__ volatile("sync");
        __asm__ volatile("ei");
        return 0;
    }
    if (state->count < state->total - 1) {
        D3_MADR = state->addr;
        D3_QWC = 0xFFC0;
        D3_CHCR = 0x100;
        IPU_CMD = 0x700003FF;
        state->addr = (state->addr + 0xFFC00) & 0xFFFFFFF;
    } else if (state->count == state->total - 1) {
        state->remain -= state->count * 1023;
        D3_MADR = state->addr;
        D3_QWC = state->remain << 6;
        D3_CHCR = 0x100;
        IPU_CMD = state->remain | 0x70000000;
    }
    __asm__ volatile("sync");
    __asm__ volatile("ei");
    return 0;
}
