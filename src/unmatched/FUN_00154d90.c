#include "dw4/reflected.h"

unsigned char FUN_00154d90(igClut *clut)
{
    unsigned int i;
    unsigned char *entry;
    unsigned char scaled = 0;

    if (clut->_fmt == 7) {
        entry = (unsigned char *)clut->_pData;
        for (i = 0; i < clut->_numEntries; i++) {
            entry[3] = (entry[3] >> 1) + (entry[3] & 1);
            entry += 4;
        }
        scaled = 1;
    } else if (clut->_fmt != 5) {
        return 0;
    }
    return scaled;
}
