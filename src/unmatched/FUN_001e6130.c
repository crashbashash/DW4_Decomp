#include "dw4/reflected.h"

void FUN_001e5fe0(igQuaternionfList *list, short *quantized, float minimum, float range);

static inline void extend(float value, float *minimum, float *maximum) {
    if (value < *minimum) {
        *minimum = value;
    } else if (!(value <= *maximum)) {
        *maximum = value;
    }
}

void FUN_001e6130(igQuaternionfList *list, short *quantized, float *minimum, float *range) {
    int i;
    int count;
    float maximum;
    const float *q;
    float y;
    float z;
    float w;
    float x;

    count = list->_count;
    maximum = *minimum = *(float *)list->_data;
    for (i = 0; i < count; i++) {
        q = (float *)list->_data + i * 4;
        x = q[0];
        y = q[1];
        z = q[2];
        w = q[3];
        extend(x, minimum, &maximum);
        extend(y, minimum, &maximum);
        extend(z, minimum, &maximum);
        extend(w, minimum, &maximum);
    }
    *range = maximum - *minimum;
    FUN_001e5fe0(list, quantized, *minimum, *range);
}
