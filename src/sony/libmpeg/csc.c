#include "dw4/sony/libmpeg.h"

int DIntr(void);
int EIntr(void);
void _ipuCommand(_sceMpegDecoder *dec, unsigned int command);
int AddDmacHandler2(int channel, int (*handler)(int, void *), int next, void *arg);
int RemoveDmacHandler(int channel, int id);
int EnableDmac(int channel);
int DisableDmac(int channel);
void _doCSC2(_sceMpegDecoder *dec, unsigned int addr, int count);

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
#define D9_CHCR (*(volatile unsigned int *)0x1000D400)
#define D9_QWC (*(volatile unsigned int *)0x1000D420)
#define D9_TADR (*(volatile unsigned int *)0x1000D430)
#define D9_SADR (*(volatile unsigned int *)0x1000D480)
#define IPU_CMD (*(volatile unsigned int *)0x10002000)
#define IPU_CTRL (*(volatile int *)0x10002010)

#define DMA_CHAN_IPU_TO 4
#define IPU_CTRL_ECD 0x4000
#define IPU_CTRL_RST 0x40000000

/* Pulls each prediction's reference blocks into the scratchpad with a source-chain transfer of two
 * 48-quadword pieces per prediction. */
void _dmaRefImage(_sceMpegDecoder *dec)
{
    static unsigned long long _sprtagdata[64] __attribute__((aligned(64)));
    unsigned long long *tag = (unsigned long long *)(((unsigned int)_sprtagdata & 0x0FFFFFFF) | 0x20000000);
    int count = dec->spr[dec->mb_buffer].pred_count;
    int intr = 0;
    int i;

    for (i = 0; i < count; i++) {
        unsigned long long addr;
        unsigned long long id;

        tag[0] = ((unsigned long long)((unsigned int)dec->spr[dec->mb_buffer].block[i] & 0x0FFFFFFF) << 32) | 0x30000030;
        addr = (unsigned int)dec->spr[dec->mb_buffer].block_right[i] & 0x0FFFFFFF;
        id = i == count - 1 ? 0 : 3;
        tag[2] = (addr << 32) | (id << 28) | 48;
        tag += 4;
    }
    intr = DIntr();
    __asm__("sync");
    D9_SADR = dec->spr[dec->mb_buffer].src;
    D9_TADR = (unsigned int)_sprtagdata;
    D9_QWC = 0;
    D9_CHCR = 0x105;
    if (intr) {
        EIntr();
    }
}

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

/* Converts more than 1023 macroblocks: channel 3 is started on the first 1023 and its handler sends the rest. */
void _doCSC2(_sceMpegDecoder *dec, unsigned int addr, int count)
{
    sceMpegCbData cbdata;
    CscDmaState state;
    int handler;
    int intr;
    unsigned int qwc = 1023 * 64; /* matching construct: decomp-permuter — the first chunk's size set up before the wait */

    state.total = count / 1023 + 1;
    state.done = 0;
    state.count = 0;
    state.remain = count;
    state.addr = (addr + 0xFFC00) & 0x0FFFFFFF;
    while (IPU_CTRL < 0);
    handler = AddDmacHandler2(3, _ch3dmaCSC, 0, &state);
    D_STAT = 8;
    EnableDmac(3);
    intr = DIntr();
    D3_MADR = addr & 0x0FFFFFFF;
    D3_QWC = qwc;
    D3_CHCR = 0x100;
    if (intr) {
        EIntr();
    }
    IPU_CMD = 0x700003FF;
    cbdata.type = sceMpegCbBackground;
    _sceMpegDispatchMpegCallback(dec->mp, &cbdata);
    while (state.count < state.total);
    if (state.done) {
        _sceMpegError(dec, "CSC handler error\n");
    }
    while (IPU_CTRL < 0);
    DisableDmac(3);
    RemoveDmacHandler(3, handler);
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

/* Converts a decoded picture to RGB32 in the image buffer: channel 4 feeds the picture to the IPU while
 * the conversion drains it, the handler sending what is left past one transfer's 0xFFFF quadwords. */
void _cscStoreImage(_sceMpegDecoder *dec, _sceMpegPicture *picture) {
    sceMpegCbData cbdata;
    DmaChunk chunk;
    int count = picture->mb_width * picture->mb_height;
    int handler;
    int intr;

    cbdata.type = sceMpegCbStopDMA;
    _sceMpegDispatchMpegCallback(dec->mp, &cbdata);
    if (IPU_CTRL & IPU_CTRL_ECD) {
        IPU_CTRL = IPU_CTRL_RST;
    }
    while (IPU_CTRL < 0);
    _ipuCommand(dec, 0);
    while (IPU_CTRL < 0);
    chunk.addr = (unsigned int)picture->base & 0x0FFFFFFF;
    chunk.qwc = count * 24;
    if (chunk.qwc > 0xFFFF) {
        handler = AddDmacHandler2(DMA_CHAN_IPU_TO, _ch4dma, 0, &chunk);
        D_STAT = 0x10;
        EnableDmac(DMA_CHAN_IPU_TO);
        intr = DIntr();
        D4_MADR = chunk.addr;
        D4_QWC = 0xFFFF;
        D4_CHCR = 0x101;
        if (intr) {
            EIntr();
        }
        chunk.addr = (chunk.addr + 0xFFFF0) & 0x0FFFFFFF;
        chunk.qwc -= 0xFFFF;
        if (count < 1024) {
            _doCSC(dec, dec->image_buff, count);
        } else {
            _doCSC2(dec, dec->image_buff, count);
        }
        DisableDmac(DMA_CHAN_IPU_TO);
        RemoveDmacHandler(DMA_CHAN_IPU_TO, handler);
    } else {
        intr = DIntr();
        D4_MADR = (unsigned int)picture->base & 0x0FFFFFFF;
        D4_QWC = chunk.qwc;
        D4_CHCR = 0x101;
        if (intr) {
            EIntr();
        }
        chunk.qwc = 0;
        if (count < 1024) {
            _doCSC(dec, dec->image_buff, count);
        } else {
            _doCSC2(dec, dec->image_buff, count);
        }
    }
    cbdata.type = sceMpegCbRestartDMA;
    _sceMpegDispatchMpegCallback(dec->mp, &cbdata);
}
