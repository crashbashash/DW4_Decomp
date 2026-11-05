/* 0x002753d8 — FUN_002753d8 (48 bytes). Error report: invokes the registered error callback 0x004ab5dc, if
   any, with its context word 0x004ab5e0, the message and the caller's first argument.
   Same shape as FUN_002739b8 for a second library's callback slot. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void (*DAT_004ab5dc)(int context, const char *message, int detail);
extern int DAT_004ab5e0;

void FUN_002753d8(int detail, const char *message) {
    if (DAT_004ab5dc != 0) {
        DAT_004ab5dc(DAT_004ab5e0, message, detail);
    }
}
