/* 0x002ae608 — FUN_002ae608 (60 bytes). Returns 1 after reporting error 0xFF000222 for the handle when FUN_002ae648(handle) fails, else 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a0bb8();
int FUN_002ae648();

int FUN_002ae608(int handle) {
    if (FUN_002ae648(handle) != 0) {
        FUN_002a0bb8(handle, 0xFF000222);
        return 1;
    }
    return 0;
}
