#include "dw4/reflected.h"
/* Receivers (data/class-hierarchy.tsv, include/dw4/reflected.h; offset and width agree):
 *   tree  -> beMatCtrlSearchList (igObjectList): _count +8, _data +16 = beMatCtrlSearch *[]
 *   node  -> beMatCtrlSearch: _minX +8, _maxX +12, _matNO +16, _memberList +24 = child list
 *   cells -> beMatCtrlDataList: _count +8, _data +16 = beMatCtrlData *[]; cell->_chkBox +12 = box
 *   flags -> igIntList: _count +8, _data +16 = int[]
 * Arena references are 4-byte handles in the reflected fields; the casts below widen them to
 * the pointers the code dereferences. */
struct B;
struct V;
extern "C" {
int FUN_0018b630(struct B *arg0, struct V *arg1);
void FUN_0038b080(int arg0, igIntList *flags, beMatCtrlSearchList *tree, int bit, float *pos, beMatCtrlDataList *cells);
}
void FUN_0038b080(int arg0, igIntList *flags, beMatCtrlSearchList *tree, int bit, float *pos, beMatCtrlDataList *cells) {
    int n = tree->_count;
    int i;
    if (n != 0) {
        for (i = 0; i < n; i++) {
            float p = *pos;
            beMatCtrlSearch *b = ((beMatCtrlSearch **)tree->_data)[i];
            if (b->_minX <= p && !(b->_maxX < p)) {
                int slot = b->_matNO;
                if (slot != -1) {
                    if (FUN_0018b630((struct B *)((beMatCtrlData **)cells->_data)[slot]->_chkBox, (struct V *)pos) == 2) {
                        int *arr = (int *)flags->_data;
                        int v = arr[slot];
                        int fc = flags->_count;
                        v |= (1 << bit);
                        if (fc != 0 && slot >= 0 && slot < fc) arr[slot] = v;
                    }
                }
                FUN_0038b080(arg0, flags, (beMatCtrlSearchList *)((beMatCtrlSearch **)tree->_data)[i]->_memberList, bit, pos, cells);
            }
        }
    }
}
