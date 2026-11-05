/* 0x001b89b0 — FUN_001b89b0. hand-matched: the real argument is the second (m2c
 * dropped the leading one); verified by tools/verify.py. */
#include "dw4/reflected.h"
int List_RemoveWordAt();

void FUN_001b89b0(void *arg0, igCommonTraversal *arg1) {
    igDataList *temp_a0;
    igDataList *temp_a0_2;
    igDataList *temp_a0_3;

    temp_a0 = (igDataList *)arg1->_boneMatrixPaletteList;
    List_RemoveWordAt(temp_a0, temp_a0->_count - 1);
    temp_a0_2 = (igDataList *)arg1->_blendMatrixPaletteList;
    List_RemoveWordAt(temp_a0_2, temp_a0_2->_count - 1);
    temp_a0_3 = (igDataList *)arg1->_blendMatrixPaletteLengths;
    List_RemoveWordAt(temp_a0_3, temp_a0_3->_count - 1);
}
