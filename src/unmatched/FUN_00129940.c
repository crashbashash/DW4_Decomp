/* Allocates the reent signal-handler table on first use and sets every entry to the default
 * handler; returns -1 when allocation fails. */
typedef void (*SignalHandler)(int);

typedef struct Reent {
    int errorNumber;
    char f4[464];
    SignalHandler *signalHandlers; /* 32 entries */
} Reent;

#define SIGNAL_COUNT 32
#define SIGNAL_DEFAULT ((SignalHandler)0)
#define SIGNAL_IGNORE ((SignalHandler)1)
#define SIGNAL_ERROR ((SignalHandler)-1)

void *FUN_00126600(Reent *reent, unsigned int size);

int FUN_00129940(Reent *reent) {
    int i;

    if (reent->signalHandlers == 0) {
        reent->signalHandlers = FUN_00126600(reent, sizeof(SignalHandler) * SIGNAL_COUNT);
        if (reent->signalHandlers == 0) {
            return -1;
        }
        for (i = 0; i < SIGNAL_COUNT; i++) {
            reent->signalHandlers[i] = SIGNAL_DEFAULT;
        }
    }
    return 0;
}
