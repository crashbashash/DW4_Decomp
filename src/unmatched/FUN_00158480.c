/* 0x00158480 - FUN_00158480. Resolves the mode id at +44 (from the table lookup when negative), flags +80 for the ids 13,14,15,16,34, then fills the object fields from two out-parameter helpers; the case labels are written 34,13,14,15 because the compare chain comes out in reverse; alternate compiler -O3. */
#include "dw4/reflected.h"
int FUN_00159320();
int FUN_00159a80();
int FUN_00159f00();
int FUN_0015a270();

void FUN_00158480(igImage *arg0) {
    unsigned int sp5C;
    int sp58;
    int sp54;
    int sp50;
    int sp4C;
    int sp48;
    int sp44;
    int sp40;
    int sp3C;
    int sp38;
    int temp_s1;
    int temp_v1;
    unsigned int temp_a0;

    if (FUN_0015a270(arg0->_pfmt) == 0) {
        if (arg0->_pfmt < 0) {
            temp_a0 = arg0->_pz;
            if ((temp_a0 != 0) && (temp_a0 < 5U)) {
                arg0->_pfmt = FUN_00159f00(temp_a0);
            }
        }
        temp_v1 = arg0->_pfmt;
        switch (temp_v1) {
        case 34:
        case 13:
        case 14:
        case 15:
        case 16:
            arg0->_compressed = 1;
            break;
        }
        temp_s1 = arg0->_pfmt;
        FUN_00159320(arg0, temp_s1, arg0->_px, arg0->_py, &sp58, &sp5C, &sp54);
        arg0->_imageSize = sp58;
        arg0->_bytesPerRow = sp54;
        FUN_00159a80(temp_s1, &sp50, &sp4C, &sp48, &sp44, &sp40, &sp3C, &sp38);
        arg0->_bitsInt = sp50;
        arg0->_bitsIdx = sp4C;
        arg0->_bitsRed = sp48;
        arg0->_bitsGrn = sp44;
        arg0->_bitsBlu = sp40;
        arg0->_bitsAlpha = sp3C;
        arg0->_bitsDepth = sp38;
        arg0->_pz = sp5C;
    }
}
