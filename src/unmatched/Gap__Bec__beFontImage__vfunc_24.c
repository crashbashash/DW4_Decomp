#include "dw4/reflected.h"
int FUN_00453830();

float Gap__Bec__beFontImage__vfunc_24(beFontImage *arg0) {
    int temp_v0;
    igCharMetricsList *metrics;
    temp_v0 = FUN_00453830();
    if (temp_v0 < 0) {
        return 0.0f;
    }
    metrics = (igCharMetricsList *)arg0->_charMetricsList;
    return *(float *)((char *)((metrics->_data + (temp_v0 * 0x28))) + 4);
}
