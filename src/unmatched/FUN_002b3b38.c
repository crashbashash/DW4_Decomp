/* Counts the call in DAT_004bec30 and, when a callback is installed (FUN_002b38b0), calls it with
 * its argument and `value`. */

/* DAT_004bec30: a callback, the argument it is called with, and a call counter. */
struct CallbackSlot {
    void (*fn)();
    int arg;
    int count;
};

extern struct CallbackSlot DAT_004bec30;

void FUN_002b3b38(int unused0, int unused1, int value) {
    /* Both callback words are read before the counter is bumped, as in retail. */
    struct CallbackSlot *slot = &DAT_004bec30;
    void (*fn)() = slot->fn;
    int arg = slot->arg;

    slot->count++;
    if (fn != 0) {
        fn(arg, value);
    }
}
