/* 0x00265308 — FUN_00265308 (36 bytes). Sets the flag DAT_0049d9dc and calls FUN_00264350. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* The store materialises the full address (lui/addiu/sw 0): the flag is volatile. */
extern volatile int DAT_0049d9dc;
void FUN_00264350(void);

void FUN_00265308(void) {
    DAT_0049d9dc = 1;
    FUN_00264350();
}
