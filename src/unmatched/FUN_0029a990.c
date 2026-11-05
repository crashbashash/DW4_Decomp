/* 0x0029a990 — FUN_0029a990 (128 bytes). Runs a server pass (FUN_0029ac78) for the caller: in mode 1 (FUN_002648e8) only when FUN_0029aa78 also reports 1, otherwise after FUN_0029aa98; returns the pass result or 0 when skipped. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002648e8(void);
extern int FUN_0029aa78(void *arg);
extern void FUN_0029aa98(void *arg);
extern int FUN_0029ac78(void *arg);

int FUN_0029a990(void *arg) {
    int result = 0;
    int mode = FUN_002648e8();

    if (mode == 1) {
        if (FUN_0029aa78(arg) == mode) {
            result = FUN_0029ac78(arg);
        }
    } else {
        FUN_0029aa98(arg);
        result = FUN_0029ac78(arg);
    }
    return result;
}
