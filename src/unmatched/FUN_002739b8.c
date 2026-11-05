/* 0x002739b8 — FUN_002739b8 (48 bytes). Error report: invokes the registered error callback 0x004aa744, if
   any, with its context word 0x004aa748, the message and the caller's first argument. Callers pass
   messages such as "E0092912:handl is null." (0x004f0348). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void (*DAT_004aa744)(int context, const char *message, int detail);
extern int DAT_004aa748;

void FUN_002739b8(int detail, const char *message) {
    if (DAT_004aa744 != 0) {
        DAT_004aa744(DAT_004aa748, message, detail);
    }
}
