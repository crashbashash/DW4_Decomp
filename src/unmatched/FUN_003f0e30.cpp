#include "dw4/reflected.h"
extern "C" {
int FUN_003ee690(int, int);

void FUN_003f0e30(beNDMWLoadSlotPlayer *arg0, int arg1) {
    int i;
    int k;
    beNDMWDegiDataList *l;

    l = (beNDMWDegiDataList *)arg0->_saveDataList;
    i = 0;
    if (0 < l->_count) {
        k = 0;
        do {
            FUN_003ee690(*(int *)(l->_data + k), arg1);
            l = (beNDMWDegiDataList *)arg0->_saveDataList;
            i += 1;
            arg1 += ((beNDMWDegiData *)*(int *)(l->_data + k))->_dataSize;
            k += 4;
        } while (i < l->_count);
    }
}
}
