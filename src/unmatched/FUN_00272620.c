/* 0x00272620 — FUN_00272620 (84 bytes). Stores a sign-extended byte into the volatile control word
   0x004a92cc, mirrors it into 0x004a92fc, and prints "SRD: Enable HostLock" (FUN_0010d108, a printf-style logger) when the value is 1.
   Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_0010d108(const char *format);
extern volatile int DAT_004a92cc;
extern int DAT_004a92fc;
extern const char s_SRD_Enable_HostLock_004efe48[];

void FUN_00272620(int value) {
    DAT_004a92cc = (char)value;
    DAT_004a92fc = DAT_004a92cc;
    if (value == 1) {
        FUN_0010d108(s_SRD_Enable_HostLock_004efe48);
    }
}
