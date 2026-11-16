#include "dw4/sony/libmpeg.h"
#include "dw4/libkernl.h"


#define D4_CHCR (*(volatile unsigned int *)0x1000B400)
#define D4_QWC (*(volatile unsigned int *)0x1000B420)
#define D4_TADR (*(volatile unsigned int *)0x1000B430)

#define DMA_TAG_REF 3
#define DMA_CHCR_CHAIN_START 0x105
/* The most one tag sends: 0xFFF4 quadwords. */
#define MAX_TRANSFER_BYTES 0xFFF40

/* Feeds `size` bytes of bitstream (a multiple of 16) to the IPU through channel 4, one chain tag per transfer:
 * REF tags while data remains, REFE on the last. */
void _sendDataToIPU(_sceMpegDecoder *dec, unsigned char *data, int size)
{
    unsigned long long *tag = (unsigned long long *)(((unsigned int)dec->ipu_tags + 15) >> 4 << 4);
    unsigned long long *first = tag;
    int intr;

    while (size > 0) {
        int chunk = size < MAX_TRANSFER_BYTES ? size : MAX_TRANSFER_BYTES;
        unsigned long long addr = (unsigned int)data & 0x0FFFFFFF;
        unsigned long long ref = DMA_TAG_REF;
        int qwc = (chunk + 15) / 16;
        unsigned long long id;

        size -= chunk;
        id = size ? ref : 0;
        *tag = (addr << 32) | (id << 28) | (unsigned int)qwc;
        __asm__("sync");
        data += chunk;
        tag += 2;
    }
    FlushCache(0);
    intr = DIntr();
    D4_TADR = (unsigned int)first & 0x0FFFFFFF;
    D4_QWC = 0;
    D4_CHCR = DMA_CHCR_CHAIN_START;
    if (intr) {
        EIntr();
    }
}
