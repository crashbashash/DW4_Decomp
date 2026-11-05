/* 0x0029a948 — FUN_0029a948 (68 bytes). In mode 1 (FUN_002648e8) returns FUN_0029aa98(arg), otherwise 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002648e8(void);
extern int FUN_0029aa98(void *arg);

int FUN_0029a948(void *arg) {
    int result = 0;

    if (FUN_002648e8() == 1) {
        result = FUN_0029aa98(arg);
    }
    return result;
}
