/* 0x002b38b0 — FUN_002b38b0 (20 bytes). Installs the callback and its argument in DAT_004bec30 (invoked by FUN_002b3b38). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

/* DAT_004bec30: a callback, the argument it is called with, and a call counter. */
struct CallbackSlot {
    void (*fn)();
    int arg;
    int count;
};

extern struct CallbackSlot DAT_004bec30;

void FUN_002b38b0(void (*fn)(), int arg) {
    DAT_004bec30.fn = fn;
    DAT_004bec30.arg = arg;
}
