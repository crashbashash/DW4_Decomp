/* 0x00260bf8 — FUN_00260bf8 (40 bytes). Returns the number of 2048-byte sectors needed to hold a byte count (division rounded up). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00260bf8(int bytes) {
    return bytes / 2048 + (bytes % 2048 > 0);
}
