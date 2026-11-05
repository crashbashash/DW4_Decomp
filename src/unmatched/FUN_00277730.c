/* 0x00277730 — FUN_00277730 (52 bytes). Invokes the registered callback 0x004abb38, if any, with the two
   context words 0x004abb3c / 0x004abb40. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void (*DAT_004abb38)(int context, int user);
extern int DAT_004abb3c;
extern int DAT_004abb40;

void FUN_00277730(void) {
    if (DAT_004abb38 != 0) {
        DAT_004abb38(DAT_004abb3c, DAT_004abb40);
    }
}
