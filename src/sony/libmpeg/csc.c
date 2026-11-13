#include "dw4/sony/libmpeg.h"

int DIntr(void);
int EIntr(void);
void _ipuCommand(_sceMpegDecoder *dec, unsigned int command);

/* The progress of a colour-space conversion the channel-3 handler feeds in 1023-macroblock chunks. */
typedef struct {
    volatile int count;
    int done;
    int remain;
    unsigned int addr;
    int total;
} CscDmaState;

/* What the channel-4 handler still has to send to the IPU. */
typedef struct {
    unsigned int qwc;
    unsigned int addr;
} DmaChunk;

#define D_STAT (*(volatile unsigned int *)0x1000E010)
#define D3_CHCR (*(volatile unsigned int *)0x1000B000)
#define D3_MADR (*(volatile unsigned int *)0x1000B010)
#define D3_QWC (*(volatile unsigned int *)0x1000B020)
#define D4_CHCR (*(volatile unsigned int *)0x1000B400)
#define D4_MADR (*(volatile unsigned int *)0x1000B410)
#define D4_QWC (*(volatile unsigned int *)0x1000B420)
#define IPU_CMD (*(volatile unsigned int *)0x10002000)

/* Clears `size` bytes at `addr` in the scratchpad with an IPU-to-memory transfer. */
void _sprClear(unsigned int addr, int size) {
    int intr = DIntr();
    *(volatile unsigned int *)0x1000B010 = (addr & 0x0FFFFFFF) | 0x80000000;
    *(volatile int *)0x1000B020 = size >> 4;
    *(volatile int *)0x1000B000 = 0x100;
    if (intr) {
        EIntr();
    }
}

/* Converts `count` macroblocks to RGB32 at `addr` in one transfer, running the background callback
 * while the IPU works. */
void _doCSC(_sceMpegDecoder *dec, unsigned int addr, int count) {
    sceMpegCbData cbdata;
    int intr;

    while (*(volatile int *)0x10002010 < 0);
    intr = DIntr();
    *(volatile unsigned int *)0x1000B010 = addr & 0x0FFFFFFF;
    *(volatile unsigned int *)0x1000B020 = count << 6;
    *(volatile unsigned int *)0x1000B000 = 0x100;
    if (intr) {
        EIntr();
    }
    _ipuCommand(dec, count | 0x70000000);
    cbdata.type = sceMpegCbBackground;
    _sceMpegDispatchMpegCallback(dec->mp, &cbdata);
    while ((*(volatile unsigned int *)0x1000B000 >> 8) & 1);
    while (*(volatile int *)0x10002010 < 0);
}

int _ch3dmaCSC(int channel, CscDmaState *state) {
    D_STAT = 8;
    state->count++;
    if (D3_QWC != 0 || (D3_CHCR & 0x100)) {
        state->done = 1;
        __asm__("sync");
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
    __asm__("sync");
    __asm__ volatile("ei");
    return 0;
}

int _ch4dma(int channel, DmaChunk *chunk) {
    D_STAT = 0x10;
    if (chunk->qwc == 0) {
        __asm__("sync");
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
    __asm__("sync");
    __asm__ volatile("ei");
    return 0;
}
