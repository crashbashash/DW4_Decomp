/* 0x002628a0 — FUN_002628a0 (24 bytes). Returns the address 16 bytes into entry index of the pointer table DAT_0049a228. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern char *DAT_0049a228[];

char *FUN_002628a0(int index) {
    return DAT_0049a228[index] + 16;
}
