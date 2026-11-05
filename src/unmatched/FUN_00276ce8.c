/* 0x00276ce8 — FUN_00276ce8 (48 bytes). Sets the mode word DAT_004aba00 to 1 for mode 1 and to 0x8001 otherwise. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* matching construct: switch — retail tests mode 0 separately before mode 1, which an if/else does not emit. */
extern int DAT_004aba00;

void FUN_00276ce8(int mode) {
    switch (mode) {
    case 0:
        DAT_004aba00 = 0x8001;
        break;
    case 1:
        DAT_004aba00 = mode;
        break;
    default:
        DAT_004aba00 = 0x8001;
        break;
    }
}
