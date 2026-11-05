/* 0x00263d88 — FUN_00263d88 (40 bytes). Calls FUN_00263c78 with the values of DAT_0049da30 and DAT_0049d9ac. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* DAT_0049da30 is read through a full address (lui/addiu/lw 0): it is volatile. */
extern volatile int DAT_0049da30;
extern int DAT_0049d9ac;
void FUN_00263c78(int a, int b);

void FUN_00263d88(void) {
    FUN_00263c78(DAT_0049da30, DAT_0049d9ac);
}
