/* p2dma.h - the p2 renderer's DMA packet rings.
 *
 * Each of the three DMA channels the renderer drives (VIF0, VIF1 and GIF) owns a ring of packets.
 * The renderer appends DMA chain data at a packet's cursor; submitting the packet closes the chain
 * and makes the next packet in the ring current. A ready packet starts once its channel is idle and
 * every predicate attached to it holds; when its transfer ends, the channel's DMAC handler runs its
 * completion callbacks and starts the next ready packet. Every packet carries a sequence number one
 * higher than the packet before it on the same channel, so "the data handed over so far" is one
 * 64-bit value a caller can wait on. */
#ifndef DW4_P2DMA_H
#define DW4_P2DMA_H

enum p2DmaChannel {
    P2_DMA_VIF0,
    P2_DMA_VIF1,
    P2_DMA_GIF,
    P2_DMA_CHANNEL_COUNT
};

/* A condition a packet waits for before it may start: test(arg) must return nonzero. */
typedef struct p2DmaPredicate {
    long long arg;
    int f8;
    struct p2DmaPredicate *next;
    int (*test)(long long arg);
} p2DmaPredicate;

/* A function a packet's DMAC handler calls once the transfer has ended. */
typedef struct p2DmaCompletion {
    int f0;
    struct p2DmaCompletion *next;
    void (*func)(void *arg);
    void *arg;
} p2DmaCompletion;

/* Where a GS-to-memory transfer queued behind a packet goes, and its size in quadwords. */
typedef struct p2StoreImageTarget {
    unsigned int addr;
    unsigned int qwc;
} p2StoreImageTarget;

typedef struct p2DmaPacket {
    long long sequence;
    long long f8;
    p2DmaPredicate *predicates;
    p2DmaPredicate *lastPredicate;
    p2DmaCompletion *completions;
    void *memory;                     /* the allocation a packet heading a block owns */
    unsigned int chain;               /* the first DMA tag, where the transfer starts */
    int f36;
    int f40;
    int f44;
    unsigned int cursor;              /* where the next chain data goes; equals chain while empty */
    struct p2DmaPacket *next;
    p2StoreImageTarget storeImageTarget;
    unsigned char ready : 1;          /* submitted; may start */
    unsigned char finishPredicate : 1; /* waits for the previous GS FINISH functions */
    unsigned char signalWait : 1;     /* a thread waits on this packet's sequence */
    unsigned char b3 : 1;
    unsigned char blockHead : 1;      /* first packet of an allocation block */
    unsigned char storeImage : 1;     /* storeImageTarget is to be read back */
    unsigned char b6 : 2;
} p2DmaPacket;

/* Words a watchdog thread checks: code that waits on the DMA sets a bit in busy and the DMAC
 * handler clears it; each tick the watchdog copies busy into seen and gives up if the bits it copied
 * last time are still set. */
typedef struct p2DmaWatch {
    int busy;
    int f4;
    int seen;
} p2DmaWatch;

#endif
