typedef struct {
    unsigned int qwc;
    unsigned int addr;
} DmaChunk;
#define D_STAT (*(volatile unsigned int *)0x1000E010)
#define D4_CHCR (*(volatile unsigned int *)0x1000B400)
#define D4_MADR (*(volatile unsigned int *)0x1000B410)
#define D4_QWC (*(volatile unsigned int *)0x1000B420)
int _ch4dma(int channel, DmaChunk *chunk) {
    D_STAT = 0x10;
    if (chunk->qwc == 0) {
        __asm__ volatile("sync");
        __asm__ volatile("ei");
        return 1;
    }
    if (chunk->qwc > 0xFFFF) {
        D4_MADR = chunk->addr;
        D4_QWC = 0xFFFF;
        D4_CHCR = 0x101;
        chunk->addr = (chunk->addr + 0xFFFF0) & 0xFFFFFFF;
        chunk->qwc -= 0xFFFF;
    } else {
        D4_MADR = chunk->addr;
        D4_QWC = chunk->qwc;
        D4_CHCR = 0x101;
        chunk->qwc = 0;
    }
    __asm__ volatile("sync");
    __asm__ volatile("ei");
    return 0;
}
