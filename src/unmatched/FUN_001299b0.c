/* 0x001299b0 — FUN_001299b0 (128 bytes). Installs a handler for a signal in the reent table and returns the previous one; sets EINVAL and returns SIG_ERR for an out-of-range signal (newlib _signal_r shape; name is a hypothesis). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
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

int FUN_00129940(Reent *reent);

SignalHandler FUN_001299b0(Reent *reent, int signal, SignalHandler handler) {
    SignalHandler previous;

    if (signal < 0 || signal >= SIGNAL_COUNT) {
        reent->errorNumber = 22; /* EINVAL */
        return SIGNAL_ERROR;
    }
    if (reent->signalHandlers == 0 && FUN_00129940(reent) != 0) {
        return SIGNAL_ERROR;
    }
    previous = reent->signalHandlers[signal];
    reent->signalHandlers[signal] = handler;
    return previous;
}
