/* 0x00293ce0 — FUN_00293ce0 (104 bytes). mwl_convPtypeFromSFD (named by its diagnostic string): passes picture types 1..4 through; anything else is reported as "Invalid Ptype" and treated as 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0029a320(const char *message);

extern char DAT_004f3150[]; /* "mwl_convPtypeFromSFD : Invalid Ptype" */

int FUN_00293ce0(unsigned int type) {
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
    case 4:
        result = 4;
        break;
    default:
        FUN_0029a320(DAT_004f3150);
        result = 1;
        break;
    }
    return result;
}
