#include "dw4/p2dma.h"

enum {
    P2_POOL_DMA_PREDICATE = 7,
    P2_POOL_DMA_COMPLETION = 8
};

typedef struct p2PredicateName {
    int (*predicate)(long long arg);
    const char *name;
} p2PredicateName;

struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};

int FUN_00113f20();
int FUN_00113f78();
int FUN_00204240();
int FUN_00204100(int);
int FUN_00208120(void);
int FUN_00330770();
void FUN_0020d270(long long *);
int FlushCache(int);
int iReferSemaStatus();
int iSignalSema();
int WaitSema(int);

void p2StartDmaPacket(int channel);

extern p2DmaPacket *p2DmaCurrentPacket[P2_DMA_CHANNEL_COUNT];
extern p2DmaPacket *p2DmaLastPacket[P2_DMA_CHANNEL_COUNT];
extern p2DmaPacket *p2DmaActivePacket[P2_DMA_CHANNEL_COUNT];
extern long long p2DmaStartedSequence[P2_DMA_CHANNEL_COUNT];
extern long long p2DmaCompletedSequence[P2_DMA_CHANNEL_COUNT];
extern long long p2DmaWaitSequence[P2_DMA_CHANNEL_COUNT];
extern char p2DmaChannelIdle[P2_DMA_CHANNEL_COUNT];
extern int p2DmaPacketCount[P2_DMA_CHANNEL_COUNT];
extern int p2DmaFreePackets[P2_DMA_CHANNEL_COUNT];
extern p2DmaPredicate *p2DmaPredicatePool;
extern p2DmaCompletion *p2DmaCompletionPool;
extern p2PredicateName p2PredicateNames[10];
extern int p2PreviousFinishFuncDone;
extern char p2StoreImagePending;
extern int p2DmaWaitSema;
extern int p2BlockedSema;
extern int p2DmaWaitTime;
extern volatile p2DmaWatch p2DmaWatchFlags;

void p2AddDmaPredicate(int channel, int (*predicate)(long long), long long arg) {
    p2DmaPacket *packet = p2DmaCurrentPacket[channel];
    p2DmaPredicate *node;
    unsigned int status;
    if (p2DmaPredicatePool == 0) {
        FUN_00204240(P2_POOL_DMA_PREDICATE, &p2DmaPredicatePool);
    }
    __asm__ volatile("mfc0 %0, $12\n\tsrl $6, %0, 16\n\tand %0, %0, $6" : "=r"(status) : : "$6");
    if (status & 1) {
        FUN_00113f20();
        node = p2DmaPredicatePool;
        p2DmaPredicatePool = node->next;
        FUN_00113f78();
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
    FUN_00204240(P2_POOL_DMA_COMPLETION, &p2DmaCompletionPool);
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
        FUN_00204240(P2_POOL_DMA_COMPLETION, &p2DmaCompletionPool, i);
    }
}

void p2AddDmaCompletion(int channel, void (*func)(void *), void *arg) {
    p2DmaPacket *packet = p2DmaCurrentPacket[channel];
    p2DmaCompletion *node;
    unsigned int status;
    if (p2DmaCompletionPool == 0) {
        FUN_00204240(P2_POOL_DMA_COMPLETION, &p2DmaCompletionPool);
    }
    __asm__ volatile("mfc0 %0, $12\n\tsrl $6, %0, 16\n\tand %0, %0, $6" : "=r"(status) : : "$6");
    if (status & 1) {
        FUN_00113f20();
        node = p2DmaCompletionPool;
        p2DmaCompletionPool = node->next;
        FUN_00113f78();
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

static inline int p2HasFinishPredicate(const p2DmaPacket *packet) {
    return packet->finishPredicate;
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

void p2SignalDmaWait(void) {
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

    FUN_00113f20();
    wait = 0;
    if (p2DmaCompletedSequence[channel] < sequence) {
        wait = 1;
        p2DmaWaitSequence[channel] = sequence;
    }
    FUN_00113f78();
    if (wait) {
        FUN_00113f20();
        p2DmaWatchFlags.busy |= 2;
        FUN_00113f78();
        FUN_00208120();
        completed = (long long *)((char *)p2DmaCompletedSequence + channel * 8);
        while (sequence > *completed) {
            FUN_0020d270(&start);
            p2BlockedSema = *(volatile int *)&p2DmaWaitSema;
            WaitSema(*(volatile int *)&p2DmaWaitSema);
            p2BlockedSema = -1;
            FUN_0020d270(&end);
            p2DmaWaitTime += (int)(end - start);
        }
        FUN_00113f20();
        p2DmaWatchFlags.busy &= ~2;
        p2DmaWatchFlags.seen &= ~2;
        FUN_00113f78();
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
        FUN_00204100(channel);
        p2DmaPacketCount[channel] = -1;
        p2DmaFreePackets[channel] = -1;
        current = &p2DmaCurrentPacket[channel];
        packet = *current;
        do {
            FUN_00330770(packet->memory, 22);
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
            FUN_00330770(block, 22);
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

static asm void p2WaitDmaCondition(void)
{
wait:
    nop
    nop
    nop
    nop
    nop
    bc0f    wait
    nop
    jr      ra
    nop
}
