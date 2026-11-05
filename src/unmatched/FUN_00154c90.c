/* 0x00154c90 - FUN_00154c90. Copies the header fields of arg1 into arg0 (releasing the old buffer at +20 first through FUN_00300f50, which keeps arg0 in a0), optionally cloning the buffer; the size is read volatile first so it is loaded before the buffer pointer; alternate compiler -O3. */
#include "dw4/reflected.h"
int memcpy(int, int, int);
int FUN_00300db0(igClut *, int, int);
int FUN_00300f50(igClut *, int);

void FUN_00154c90(igClut *arg0, igClut *arg1, int arg2) {
    int temp_a1;
    int sz;

    if (arg0 != arg1) {
        temp_a1 = arg0->_pData;
        if (temp_a1 != 0) {
            FUN_00300f50(arg0, temp_a1);
            arg0->_pData = 0;
        }
        arg0->_fmt = arg1->_fmt;
        arg0->_numEntries = arg1->_numEntries;
        arg0->_stride = arg1->_stride;
        arg0->_clutSize = arg1->_clutSize;
        arg0->_isAlphaScaled = arg1->_isAlphaScaled;
        if (arg2 != 0) {
            arg0->_pData = FUN_00300db0(arg0, arg0->_clutSize, 0x80);
            sz = *(volatile int *)&arg0->_clutSize;
            memcpy(arg0->_pData, arg1->_pData, sz);
        }
    }
}
