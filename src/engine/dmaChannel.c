#include "dw4/p2/p2dma.h"
#include "dw4/p2/dmaChannel.h"
#include "dw4/p2/p2core.h"
#include "dw4/p2/p2gs.h"
#include "dw4/p2/p2pool.h"
#include "dw4/p2/p2swap.h"
#include "dw4/p2/p2timer.h"
#include "dw4/p2/p2watchdog.h"
#include "dw4/support/eekernel.h"
#include "dw4/sony/libkernl.h"
#include "dw4/core/igMemory.h"
#define D_CTRL ((unsigned int *)0x1000e000)
#define D0_CHCR ((unsigned int *)0x10008000)
#define D0_QWC ((unsigned int *)0x10008020)
#define D0_TADR ((unsigned int *)0x10008030)
#define D1_CHCR ((unsigned int *)0x10009000)
#define D1_QWC ((unsigned int *)0x10009020)
#define D1_TADR ((unsigned int *)0x10009030)
#define D2_CHCR ((unsigned int *)0x1000a000)
#define D2_QWC ((unsigned int *)0x1000a020)
#define D2_TADR ((unsigned int *)0x1000a030)

typedef struct p2PredicateName {
    int (*predicate)(long long arg);
    const char *name;
} p2PredicateName;

int AddDmacHandler(int channel, int (*handler)(int channel), int next);

void p2CompleteDmaPacket(int channel, p2DmaPacket *packet);
void p2SignalDmaWait(int unused);
int p2DmaPredicatesSatisfied(int channel);
void p2FreeDmaCompletions(int channel);
int p2Vif1DmaHandler(int channel);
int p2GifDmaHandler(int channel);
void p2InitDmaPredicatePool(void);
void p2InitDmaCompletionPool(void);
int p2PreviousFinishFuncDonePredicate(long long arg);
void p2StartDmaPacket(int channel);

extern p2DmaPacket *p2DmaActivePacket[P2_DMA_CHANNEL_COUNT];
extern long long p2DmaStartedSequence[P2_DMA_CHANNEL_COUNT];
extern long long p2DmaCompletedSequence[P2_DMA_CHANNEL_COUNT];
extern long long p2DmaWaitSequence[P2_DMA_CHANNEL_COUNT];
extern char p2DmaChannelIdle[P2_DMA_CHANNEL_COUNT];
extern int p2DmaFreePackets[P2_DMA_CHANNEL_COUNT];
extern p2PredicateName p2PredicateNames[10];
extern char p2StoreImagePending;
extern int p2DmaWaitSema;
extern struct SemaParam p2DmaWaitSemaParam;
extern struct SemaParam p2DmaFreePacketSemaParam;
extern int p2DmaPacketReserveVif0;
extern int p2DmaPacketReserveVif1;
extern int p2DmaPacketReserveGif;
extern int p2DmaFreePacketSema[P2_DMA_CHANNEL_COUNT];
extern char p2DmaWaitingForPacket[P2_DMA_CHANNEL_COUNT];
extern const char text_p2PreviousFinishFuncDonePredicat[];

#include "dw4/p2/p2core.h"

extern unsigned int p2DmaEndTag[4];
extern long long p2DmaOverlapStartTime;

typedef struct DmaTagHead {
    unsigned int qwc : 16;
    unsigned int pad : 10;
    unsigned int pce : 2;
    unsigned int id : 3;
    unsigned int irq : 1;
} DmaTagHead;

typedef struct p2DmaCallback {
    void (*func)(void *arg);
    void *arg;
} p2DmaCallback;
extern p2DmaCallback p2DmaCompletionCallbacks[P2_DMA_CHANNEL_COUNT];

static inline int p2HasFinishPredicate(const p2DmaPacket *packet) {
    return packet->finishPredicate;
}

static inline void p2EndDmaChain(int channel) {
    /* matching construct: manual variant search — the byte offset keeps the slot address apart from
     * p2SubmitDmaPacket's `current`, so it is rebuilt here as retail does */
    unsigned int *p = (unsigned int *)(*(p2DmaPacket **)((char *)p2DmaCurrentPacket + channel * 4))->cursor;
    p[0] = p2DmaEndTag[0];
    p[1] = p2DmaEndTag[1];
    p[2] = p2DmaEndTag[2];
    p[3] = p2DmaEndTag[3];
}

void p2SubmitDmaPacket(int channel) {
    p2DmaPacket *packet;
    p2DmaPacket **current;
    long long sequence;
    p2DmaPacket *next;

    current = p2DmaCurrentPacket + channel;
    packet = *current;
    if (channel == P2_DMA_VIF1) {
        p2StatVif1DmaCount++;
    }
    if (channel == P2_DMA_VIF1 && packet->cursor < packet->limit) {
        p2StatVif1PartialPackets++;
    }
    if (channel == P2_DMA_GIF) {
        p2StatGifDmaCount++;
    }
    if (channel == P2_DMA_GIF && packet->cursor < packet->limit) {
        p2StatGifPartialPackets++;
    }
    p2WatchdogTicks = 0;
    if (channel == P2_DMA_VIF1) {
        if (p2HasFinishPredicate(packet)) {
            ((unsigned int *)&p2CurrentGsRegisters->f432[1])[0] = (unsigned int)packet->sequence;
            ((unsigned int *)&p2CurrentGsRegisters->f432[1])[1] = 0xFFFF;
            p2AppendGsFinish();
        } else if (packet->restartProgram) {
            p2AppendProgramRestart();
            p2AppendProgramRestart();
        }
    }
    p2EndDmaChain(channel);
    FlushCache(0);
    DIntr();
    packet->ready = 1;
    if (p2DmaChannelIdle[channel] && *current == p2DmaActivePacket[channel] &&
        p2DmaPredicatesSatisfied(channel) && p2StoreImagePending == 0) {
        p2StartDmaPacket(channel);
    }
    EIntr();
    if (p2DmaFreePackets[channel] < 2) {
        p2GrowPool(channel, &(*current)->next);
        FlushCache(0);
        DIntr();
        if (p2DmaFreePackets[channel] < 2) {
            p2DmaWaitingForPacket[channel] = 1;
            EIntr();
            {
                int *sema = &p2DmaFreePacketSema[channel];
                p2BlockedSema = *sema;
                WaitSema(*sema);
            }
            p2BlockedSema = -1;
        } else {
            EIntr();
        }
    }
    DIntr();
    p2DmaFreePackets[channel]--;
    EIntr();
    sequence = packet->sequence;
    p2DmaLastPacket[channel] = packet;
    next = packet->next;
    *current = next;
    next->cursor = next->chain;
    next->sequence = sequence + 1;
}

void p2CompleteDmaPacket(int channel, p2DmaPacket *packet) {
    p2DmaCompletion *node;

    packet->ready = 0;
    packet->waitSequence = -1;
    p2DmaOverlapStartTime = 0;
    p2DmaChannelIdle[channel] = 1;
    p2DmaCompletedSequence[channel] = p2DmaStartedSequence[channel];
    if (p2DmaCompletionCallbacks[channel].func != 0) {
        p2DmaCompletionCallbacks[channel].func(p2DmaCompletionCallbacks[channel].arg);
    }
    for (node = packet->completions; node != 0; node = node->next) {
        node->func(node->arg);
    }
    if (packet->signalWait) {
        p2SignalDmaWait(0);
        packet->signalWait = 0;
    } else if (p2DmaWaitSequence[channel] > 0 && p2DmaWaitSequence[channel] <= p2DmaCompletedSequence[channel]) {
        struct SemaParam info;
        iReferSemaStatus(p2DmaWaitSema, &info);
        if (info.currentCount != info.maxCount) {
            iSignalSema(p2DmaWaitSema);
        }
    }
    if (p2DmaWaitingForPacket[channel]) {
        struct SemaParam info;
        iReferSemaStatus(p2DmaFreePacketSema[channel], &info);
        if (info.currentCount != info.maxCount) {
            iSignalSema(p2DmaFreePacketSema[channel]);
        }
        p2DmaWaitingForPacket[channel] = 0;
    }
    p2FreeDmaCompletions(channel);
    p2DmaFreePackets[channel]++;
    packet = packet->next;
    p2DmaActivePacket[channel] = packet;
    if (packet->ready && p2DmaPredicatesSatisfied(channel) && p2StoreImagePending == 0) {
        p2StartDmaPacket(channel);
    }
}

/* The DMAC handler of channel 0 (VIF0): the transfer of the active packet has ended. */
int p2Vif0DmaHandler(int channel) {
    p2DmaPacket *packet = p2DmaActivePacket[P2_DMA_VIF0];
    if (packet != 0) {
        p2DmaWatchFlags.busy &= ~0x20;
        p2DmaWatchFlags.seen &= ~0x20;
        p2CompleteDmaPacket(channel, packet);
    }
    asm { sync }
    asm { ei }
    return 0;
}

/* Gives a packet its chain buffer: size quadwords from the driver heap, 128-byte aligned and reached
 * through the uncached-accelerated segment, with reserve quadwords kept back below the end. */
void p2InitDmaPacket(p2DmaPacket *packet, int size, int reserve, int f44) {
    packet->memory = Memory_AllocateAligned16(size * sizeof(unsigned __int128) + 127, 22);
    packet->chain = (((unsigned int)packet->memory + 127) & ~127) | 0x30000000;
    packet->cursor = packet->chain;
    packet->end = packet->chain + size * 16 - 16;
    packet->limit = packet->end - reserve * 16;
    packet->f44 = packet->chain + f44 * 16;
    packet->sequence = 0;
    packet->predicates = 0;
    packet->completions = 0;
    packet->ready = 0;
    packet->blockHead = 0;
    packet->storeImage = 0;
    packet->finishPredicate = 0;
    packet->restartProgram = 0;
    packet->signalWait = 0;
    packet->storeImageTarget.qwc = 0;
    packet->storeImageTarget.addr = 0;
    packet->waitSequence = -1;
    ((DmaTagHead *)packet->chain)->id = 7;
    ((DmaTagHead *)packet->chain)->qwc = 0;
}

/* Sets up one channel's packet ring and installs its DMAC handler. */
void p2InitDmaChannel(int channel) {
    if (p2DmaPacketCount[channel] == -1) {
        p2DmaPacketCount[channel] = 20;
    }
    p2DmaFreePackets[channel] = -1;
    p2DmaCurrentPacket[channel] = 0;
    p2DmaLastPacket[channel] = 0;
    p2GrowPool(channel, &p2DmaCurrentPacket[channel]);
    p2DmaCompletedSequence[channel] = -1;
    p2DmaStartedSequence[channel] = -1;
    p2DmaWaitSequence[channel] = 0;
    p2DmaActivePacket[channel] = p2DmaCurrentPacket[channel];
    p2DmaChannelIdle[channel] = 1;
    if (channel == P2_DMA_VIF1) {
        p2DmaHandlerIds[channel] = AddDmacHandler(channel, p2Vif1DmaHandler, 0);
    } else if (channel == P2_DMA_GIF) {
        p2DmaHandlerIds[channel] = AddDmacHandler(channel, p2GifDmaHandler, 0);
    } else if (channel == P2_DMA_VIF0) {
        p2DmaHandlerIds[channel] = AddDmacHandler(channel, p2Vif0DmaHandler, 0);
    }
    EnableDmac(channel);
}

/* Creates the wait semaphores, sets the pool sizes and brings up VIF1, GIF and (when it has packets)
 * VIF0, then enables the DMAC. */
void p2InitDmaChannels(void) {
    struct SemaParam wait = p2DmaWaitSemaParam;
    struct SemaParam lock = p2DmaFreePacketSemaParam;

    if (p2FirstOpen != 0) {
        p2DmaWaitSema = CreateSema(&wait);
        p2DmaFreePacketSema[P2_DMA_VIF0] = 0;
        p2DmaFreePacketSema[P2_DMA_VIF1] = CreateSema(&lock);
        p2DmaFreePacketSema[P2_DMA_GIF] = CreateSema(&lock);
    }
    p2DmaPacketReserveVif0 = 64;
    p2DmaPacketReserveVif1 = 320;
    p2DmaPacketReserveGif = 96;
    p2StoreImagePending = 0;
    p2DmaWaitingForPacket[P2_DMA_VIF0] = 0;
    p2DmaWaitingForPacket[P2_DMA_VIF1] = 0;
    p2DmaWaitingForPacket[P2_DMA_GIF] = 0;
    if (p2DmaPacketSizeVif0 == -1) p2DmaPacketSizeVif0 = 256;
    if (p2DmaPacketSizeVif1 == -1) p2DmaPacketSizeVif1 = 2048;
    if (p2DmaPacketSizeGif == -1) p2DmaPacketSizeGif = 256;
    p2InitDmaPredicatePool();
    p2InitDmaCompletionPool();
    p2InitDmaChannel(P2_DMA_VIF1);
    p2InitDmaChannel(P2_DMA_GIF);
    if (p2DmaPacketSizeVif0 != 0 && p2DmaPacketCount[P2_DMA_VIF0] != 0) {
        p2InitDmaChannel(P2_DMA_VIF0);
    } else {
        p2DmaHandlerIds[P2_DMA_VIF0] = -1;
    }
    *D_CTRL = 1;
}

void p2InitDmaPredicatePool(void) {
    p2DmaPredicatePool = 0;
    p2GrowPool(P2_POOL_DMA_PREDICATE, &p2DmaPredicatePool);
    if (p2FirstOpen != 0) {
        p2RegisterPredicateName(p2PreviousFinishFuncDonePredicate, text_p2PreviousFinishFuncDonePredicat);
    }
}

void p2ReserveDmaPredicates(int count) {
    int i = 0;
    p2DmaPredicate *node = p2DmaPredicatePool;
    while (i < count) {
        if (node == 0) {
            break;
        }
        node = node->next;
        i++;
    }
    if (i != count) {
        p2GrowPool(P2_POOL_DMA_PREDICATE, &p2DmaPredicatePool);
    }
}

void p2AddDmaPredicate(int channel, int (*predicate)(long long), long long arg) {
    p2DmaPacket *packet = p2DmaCurrentPacket[channel];
    p2DmaPredicate *node;
    unsigned int status;
    if (p2DmaPredicatePool == 0) {
        p2GrowPool(P2_POOL_DMA_PREDICATE, &p2DmaPredicatePool);
    }
    __asm__("mfc0 %0, $12\n\tsrl $6, %0, 16\n\tand %0, %0, $6" : "=r"(status) : : "$6");
    if (status & 1) {
        DIntr();
        node = p2DmaPredicatePool;
        p2DmaPredicatePool = node->next;
        EIntr();
    } else {
        node = p2DmaPredicatePool;
        p2DmaPredicatePool = node->next;
    }
    node->test = predicate;
    node->arg = arg;
    node->next = packet->predicates;
    if (packet->predicates == 0) {
        packet->lastPredicate = node;
    }
    packet->predicates = node;
}

static void p2FreeDmaPredicates(int channel) {
    p2DmaPacket *packet = p2DmaActivePacket[channel];
    if (packet->predicates != 0) {
        packet->lastPredicate->next = p2DmaPredicatePool;
        p2DmaPredicatePool = packet->predicates;
        packet->predicates = 0;
    }
}

int p2DmaPredicatesSatisfied(int channel) {
    int satisfied;
    int result;
    p2DmaPredicate *node = p2DmaActivePacket[channel]->predicates;
    satisfied = 1;
    while (node != 0) {
        result = node->test(node->arg) != 0 ? 1 : 0;
        satisfied &= result;
        if (satisfied == 0) {
            break;
        }
        node = node->next;
    }
    return satisfied;
}

void p2InitDmaCompletionPool(void) {
    p2DmaCompletionPool = 0;
    p2GrowPool(P2_POOL_DMA_COMPLETION, &p2DmaCompletionPool);
}

void p2ReserveDmaCompletions(int count) {
    int i = 0;
    p2DmaCompletion *node = p2DmaCompletionPool;
    while (i < count) {
        if (node == 0) {
            break;
        }
        node = node->next;
        i++;
    }
    if (i != count) {
        p2GrowPool(P2_POOL_DMA_COMPLETION, &p2DmaCompletionPool);
    }
}

void p2AddDmaCompletion(int channel, void (*func)(void *), void *arg) {
    p2DmaPacket *packet = p2DmaCurrentPacket[channel];
    p2DmaCompletion *node;
    unsigned int status;
    if (p2DmaCompletionPool == 0) {
        p2GrowPool(P2_POOL_DMA_COMPLETION, &p2DmaCompletionPool);
    }
    __asm__("mfc0 %0, $12\n\tsrl $6, %0, 16\n\tand %0, %0, $6" : "=r"(status) : : "$6");
    if (status & 1) {
        DIntr();
        node = p2DmaCompletionPool;
        p2DmaCompletionPool = node->next;
        EIntr();
    } else {
        node = p2DmaCompletionPool;
        p2DmaCompletionPool = node->next;
    }
    node->func = func;
    node->arg = arg;
    node->next = packet->completions;
    packet->completions = node;
}

void p2FreeDmaCompletions(int channel) {
    p2DmaPacket *packet = p2DmaActivePacket[channel];
    p2DmaCompletion *node = packet->completions;
    p2DmaCompletion *next;
    while (node != 0) {
        next = node->next;
        node->next = p2DmaCompletionPool;
        p2DmaCompletionPool = node;
        node = next;
    }
    packet->completions = 0;
}

extern long long p2Vif1DmaStartTime;
extern long long p2GifDmaStartTime;

void p2StartDmaPacket(int channel) {
    p2DmaPacket *packet = p2DmaActivePacket[channel];
    int v;

    p2FreeDmaPredicates(channel);
    p2DmaChannelIdle[channel] = 0;
    if (packet->finishPredicate) {
        p2PreviousFinishFuncDone = 0;
        packet->finishPredicate = 0;
    }
    packet->restartProgram = 0;
    packet->ready = 0;
    if (packet->storeImage) {
        p2StoreImagePending = 1;
    }
    p2DmaStartedSequence[channel] = packet->sequence;
    __asm__ volatile("sync");
    switch (channel) {
    case P2_DMA_VIF0:
        p2DmaWatchFlags.busy |= 0x20;
        *D0_QWC = 0;
        v = packet->chain & 0x0fffffff;
        *D0_TADR = v;
        v = 389;
        *D0_CHCR = v;
        __asm__("nop");
        break;
    case P2_DMA_VIF1:
        p2DmaWatchFlags.busy |= 0x40;
        p2ReadClock(&p2Vif1DmaStartTime);
        if (p2DmaChannelIdle[P2_DMA_VIF1] == 0 && p2DmaChannelIdle[P2_DMA_GIF] == 0) {
            p2DmaOverlapStartTime = p2Vif1DmaStartTime;
        }
        *D1_QWC = 0;
        v = packet->chain & 0x0fffffff;
        *D1_TADR = v;
        v = 389;
        *D1_CHCR = v;
        __asm__("nop");
        break;
    case P2_DMA_GIF:
        p2DmaWatchFlags.busy |= 0x80;
        p2ReadClock(&p2GifDmaStartTime);
        if (p2DmaChannelIdle[P2_DMA_VIF1] == 0 && p2DmaChannelIdle[P2_DMA_GIF] == 0) {
            p2DmaOverlapStartTime = p2GifDmaStartTime;
        }
        *D2_QWC = 0;
        v = packet->chain & 0x0fffffff;
        *D2_TADR = v;
        v = 389;
        *D2_CHCR = v;
        break;
    }
}

void p2TryStartDmaPacket(int channel) {
    p2DmaPacket *packet = p2DmaActivePacket[channel];
    if (p2DmaChannelIdle[channel] != 0 && packet->ready && p2DmaPredicatesSatisfied(channel) != 0 &&
        p2StoreImagePending == 0) {
        p2StartDmaPacket(channel);
    }
}

int p2PreviousFinishFuncDonePredicate(long long arg) {
    return p2PreviousFinishFuncDone;
}

long long p2AddPreviousFinishFuncPredicate(void) {
    p2DmaPacket *packet = p2DmaCurrentPacket[P2_DMA_VIF1];
    if (p2HasFinishPredicate(packet) != 1) {
        packet->finishPredicate = 1;
        p2AddDmaPredicate(P2_DMA_VIF1, p2PreviousFinishFuncDonePredicate, 0);
    }
    return packet->sequence;
}

void p2RegisterPredicateName(int (*predicate)(long long), const char *name) {
    int i = 0;
    while (i < 10 && p2PredicateNames[i].predicate != 0) {
        i += 1;
    }
    p2PredicateNames[i].predicate = predicate;
    p2PredicateNames[i].name = name;
}

int textureDeferredPredicate(long long sequence) {
    return p2DmaCompletedSequence[P2_DMA_VIF1] >= sequence;
}

int textureLoadedPredicate(long long sequence) {
    return p2DmaCompletedSequence[P2_DMA_GIF] >= sequence;
}

int p2DmaPacketQueued(int channel, p2DmaPacket *packet) {
    p2DmaPacket *active = p2DmaActivePacket[channel];
    int queued = 0;
    if (active != 0 && packet != 0 && p2DmaCurrentPacket[channel] != active && packet != active) {
        queued = 1;
    }
    return queued;
}

int p2DmaSequenceLastCompleted(int channel, long long sequence) {
    return sequence == p2DmaCompletedSequence[channel];
}

void p2SignalDmaWait(int unused) {
    struct SemaParam info;
    iReferSemaStatus(p2DmaWaitSema, &info);
    if (info.currentCount != info.maxCount) {
        iSignalSema(p2DmaWaitSema);
    }
}

long long p2GetVif1WaitSequence(void) {
    p2DmaPacket *packet = p2DmaCurrentPacket[P2_DMA_VIF1];
    long long sequence = packet->sequence;
    if (packet->cursor == packet->chain) {
        packet = p2DmaLastPacket[P2_DMA_VIF1];
        sequence = packet->sequence;
    }
    packet->signalWait = 1;
    return sequence;
}

void p2WaitDmaSequence(int channel, long long sequence) {
    int wait;
    long long *completed;
    long long start;
    long long end;

    DIntr();
    wait = 0;
    if (p2DmaCompletedSequence[channel] < sequence) {
        wait = 1;
        p2DmaWaitSequence[channel] = sequence;
    }
    EIntr();
    if (wait) {
        DIntr();
        p2DmaWatchFlags.busy |= 2;
        EIntr();
        p2FlushVif1Packet();
        completed = (long long *)((char *)p2DmaCompletedSequence + channel * 8);
        while (sequence > *completed) {
            p2ReadClock(&start);
            p2BlockedSema = p2DmaWaitSema;
            WaitSema(*(volatile int *)&p2DmaWaitSema);
            p2BlockedSema = -1;
            p2ReadClock(&end);
            p2DmaWaitTime += (int)(end - start);
        }
        DIntr();
        p2DmaWatchFlags.busy &= ~2;
        p2DmaWatchFlags.seen &= ~2;
        EIntr();
        p2DmaWaitSequence[channel] = 0;
    }
}

int p2DmaSequenceDone(int channel, long long sequence) {
    return p2DmaCompletedSequence[channel] >= sequence;
}

void p2ShutdownDmaChannels(void) {
    int channel;
    p2DmaPacket *packet;
    p2DmaPacket *head;
    p2DmaPacket **current;
    p2DmaPacket *keep;
    FlushCache(0);
    channel = 0;
    do {
        p2ResetDmaPacketCount(channel);
        p2DmaPacketCount[channel] = -1;
        p2DmaFreePackets[channel] = -1;
        current = &p2DmaCurrentPacket[channel];
        packet = *current;
        do {
            Memory_FreeToSelector(packet->memory, 22);
            packet->memory = 0;
            if (packet->predicates == 0 && channel == P2_DMA_GIF) p2FreeDmaPredicates(channel);
            packet = packet->next;
            head = *current;
        } while (packet != head);
        while (!head->blockHead) head = head->next;
        packet = head->next;
        keep = head;
        do {
            if (keep != 0 && keep->blockHead && !packet->blockHead) keep->next = packet->next;
            else if (keep != 0 && keep->blockHead && packet->blockHead) keep = packet;
            packet = packet->next;
        } while (packet != head);
        do {
            p2DmaPacket *block = packet;
            packet = packet->next;
            Memory_FreeToSelector(block, 22);
        } while (packet != head);
        *current = 0;
        p2DmaCompletedSequence[channel] = -1;
        p2DmaStartedSequence[channel] = -1;
        p2DmaWaitSequence[channel] = 0;
        p2DmaChannelIdle[channel] = 1;
        p2DmaActivePacket[channel] = 0;
        channel++;
    } while (channel <= P2_DMA_GIF);
}

static void p2WaitDmaCondition(void)
{
    asm {
    wait:
        nop
        nop
        nop
        nop
        nop
        bc0f    wait
        nop
    }
}
