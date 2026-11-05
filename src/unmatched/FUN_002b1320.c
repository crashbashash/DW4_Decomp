/* 0x002b1320 — FUN_002b1320 (36 bytes). Resets an item by calling FUN_002b1348(item, 0, 0, 0, 0). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b1348();

void FUN_002b1320(void *item) {
    FUN_002b1348(item, 0, 0, 0, 0);
}
