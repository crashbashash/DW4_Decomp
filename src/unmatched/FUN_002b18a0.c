/* 0x002b18a0 — FUN_002b18a0 (48 bytes). Calls FUN_002b18f0 and then decrements the word at +4 of DAT_00585690. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b18f0();

struct Counter5690 {
    int f0;
    int f4;                               /* decremented here */
};

extern struct Counter5690 DAT_00585690;

void FUN_002b18a0(void) {
    FUN_002b18f0();
    DAT_00585690.f4--;
}
