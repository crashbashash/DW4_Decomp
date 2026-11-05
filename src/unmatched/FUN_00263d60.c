/* 0x00263d60 — FUN_00263d60 (40 bytes). Calls FUN_00263c78 with the values of DAT_0049da2c and DAT_0049d9a8. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* DAT_0049da2c is read through a full address (lui/addiu/lw 0): it is volatile. */
extern volatile int DAT_0049da2c;
extern int DAT_0049d9a8;
void FUN_00263c78(int a, int b);

void FUN_00263d60(void) {
    FUN_00263c78(DAT_0049da2c, DAT_0049d9a8);
}
