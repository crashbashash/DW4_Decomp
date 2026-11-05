/* 0x00260a40 — FUN_00260a40 (28 bytes). Calls FUN_0010b918 with base and the address of the last byte of a length-byte span starting at base. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0010b918(char *start, char *last);

void FUN_00260a40(char *base, int length) {
    FUN_0010b918(base, base + length - 1);
}
