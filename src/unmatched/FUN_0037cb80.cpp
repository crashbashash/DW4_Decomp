#include "dw4/reflected.h"
extern "C" {
int FUN_0037caf0(beCri *, beCriHandle *);
void FUN_0037cb80(beCri *arg0, long long arg1);
}

void FUN_0037cb80(beCri *arg0, long long arg1) {
    int var_s1;
    beCriHandle *temp_a1;

    temp_a1 = (beCriHandle *)arg0->_hdBGM;
    if (arg1 == temp_a1->_playID) {
        FUN_0037caf0(arg0, temp_a1);
        return;
    }
    temp_a1 = (beCriHandle *)arg0->_hdENV;
    if (arg1 == temp_a1->_playID) {
        FUN_0037caf0(arg0, temp_a1);
        return;
    }
    var_s1 = 0;
    if (0 < ((igObjectList *)arg0->_hdSEs)->_count) {
        do {
            temp_a1 = ((beCriHandle **)((igObjectList *)arg0->_hdSEs)->_data)[var_s1];
            if (arg1 == temp_a1->_playID) {
                FUN_0037caf0(arg0, temp_a1);
            }
            var_s1 += 1;
        } while (var_s1 < ((igObjectList *)arg0->_hdSEs)->_count);
    }
}
