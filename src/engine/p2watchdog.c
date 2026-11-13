/* The watchdog thread. Code that waits for the hardware or another thread sets its bit in
 * p2DmaWatchFlags.busy and clears it when the wait ends; every four seconds the watchdog copies
 * busy into seen, and gives up if a bit it copied last time is still set. It also gives up when
 * p2WatchdogTicks, which the renderer resets each frame, reaches 60. */
#include "dw4/eekernel.h"
#include "dw4/p2dma.h"
#include "dw4/p2timer.h"

int printf(const char *format, ...);
void abort(void);
void exit(int status);
int p2GetVuProgramName(int program);
int p2IsVuProgramLoaded(int program);
void p2RunWatchdog(void *arg);

extern char _gp[];
extern int p2WatchdogThread;
extern int p2WatchdogDisabled;
extern char p2WatchdogStack[0x1000];
extern volatile int p2WatchdogTicks;
extern int p2FunctionTables[];
extern int p2FunctionTableSizes[3];
extern char newline[];

void p2StartWatchdog(void) {
    struct ThreadParam param = { 0, p2RunWatchdog, p2WatchdogStack, sizeof(p2WatchdogStack), _gp, 1 };
    int thread;
    int priority;

    thread = GetThreadId();
    priority = ChangeThreadPriority(thread, 2);
    if (priority > 2) {
        ChangeThreadPriority(thread, priority);
    }
    p2WatchdogThread = CreateThread(&param);
    _StartThread(p2WatchdogThread, 0);
}

/* Lists the VU programs of the three function tables with their names and whether each is loaded,
 * then the waits that timed out. */
void p2PrintWatchdogReport(void) {
    extern p2DmaWatch p2DmaWatchFlags;
    static char *watchNames[] = {
        "PacketBuffer", "DMAFinishSequence", "Swapbuffers", "FinishSequence", "TextureUnbind", "DMAVIF0",
        "DMAVIF1", "DMAGIF", "VSync", "VU0UcodeLoad", "VU0Lock", 0
    };
    int *handle0;
    int *handle1;
    int *handle2;
    int k;
    int name0;
    int name2;
    int i;
    int n;
    int j;
    int name1;
    int bit;

    n = 0;
    printf("Function table 0 (%d)\n", p2FunctionTableSizes[0]);
    for (i = 0; i < p2FunctionTableSizes[0]; i++, n++) {
        handle0 = &p2FunctionTables[n];
        name0 = p2GetVuProgramName(*handle0);
        printf("Handle %d (%d) : %s (%d)\n", n, *handle0, name0, p2IsVuProgramLoaded(*handle0));
    }
    printf("Function table 1 (%d)\n", p2FunctionTableSizes[1]);
    for (j = 0; j < p2FunctionTableSizes[1]; j++, n++) {
        handle1 = &p2FunctionTables[n];
        name1 = p2GetVuProgramName(*handle1);
        printf("Handle %d (%d) : %s (%d)\n", n, *handle1, name1, p2IsVuProgramLoaded(*handle1));
    }
    printf("Function table 2 (%d)\n", p2FunctionTableSizes[2]);
    for (k = 0; k < p2FunctionTableSizes[2]; k++, n++) {
        handle2 = &p2FunctionTables[n];
        name2 = p2GetVuProgramName(*handle2);
        printf("Handle %d (%d) : %s (%d)\n", n, *handle2, name2, p2IsVuProgramLoaded(*handle2));
    }
    printf("\tTimeouts: ");
    bit = 0;
    do {
        if (p2DmaWatchFlags.seen & (1u << bit)) {
            printf("%s ", watchNames[bit]);
        }
        bit++;
    } while (bit <= 9);
    printf(newline);
}

void p2RunWatchdog(void *arg) {
    /* other threads and the DMA handlers write these words while the thread runs */
    extern volatile p2DmaWatch p2DmaWatchFlags;

    printf("watchdog started\n");
    for (;;) {
        do {
            p2Sleep(4);
        } while (p2WatchdogDisabled != 0);
        if (p2DmaWatchFlags.seen != 0) {
            printf("\n *** Timeout 0x%x\n", p2DmaWatchFlags.seen);
            p2PrintWatchdogReport();
            abort();
        }
        p2DmaWatchFlags.seen = p2DmaWatchFlags.busy;
        if (++p2WatchdogTicks < 60) {
            continue;
        }
        printf("watchdog timer expired!\n");
        abort();
        exit(1);
    }
}
