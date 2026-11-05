/* 0x00293c70 — FUN_00293c70 (44 bytes). Forwards to FUN_002916f8 with the third argument converted from seconds to milliseconds (* 1000). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_002916f8(int a, int b, int ms);

void FUN_00293c70(int a, int b, int seconds) {
    FUN_002916f8(a, b, seconds * 1000);
}
