/* 0x00293ca0 — FUN_00293ca0 (60 bytes). Maps a picture type: 1 -> 1, 2 -> 2, anything else -> 3. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

int FUN_00293ca0(unsigned int type) {
    int result;

    switch (type) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    default:
        result = 3;
        break;
    }
    return result;
}
