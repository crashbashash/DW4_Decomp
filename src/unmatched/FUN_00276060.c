/* 0x00276060 — FUN_00276060 (48 bytes). Returns the low 32 bits of the 64-bit value from FUN_00275fd8.
   Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern long long FUN_00275fd8(void);

int FUN_00276060(void) {
    return (int)(FUN_00275fd8() & 0xFFFFFFFF);
}
