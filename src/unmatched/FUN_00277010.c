/* 0x00277010 — FUN_00277010 (36 bytes). Forwards its two arguments to FUN_00277038 with zero for the next
   two and 0xFFFFF as the fifth. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_00277038(int a, int b, int c, int d, int limit);

void FUN_00277010(int a, int b) {
    FUN_00277038(a, b, 0, 0, 0xFFFFF);
}
