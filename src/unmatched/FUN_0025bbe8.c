/* 0x0025bbe8 — FUN_0025bbe8 (36 bytes). Calls the hook in D_00498a54. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void (*D_00498a54)(void);

void FUN_0025bbe8(void) {
    D_00498a54();
}
