/* 0x002b19c8 — FUN_002b19c8 (40 bytes). True unless the word at *value is -1, 0 or 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

int FUN_002b19c8(int *value) {
    switch (*value) {
    case -1:
    case 0:
    case 1:
        return 0;
    }
    return 1;
}
