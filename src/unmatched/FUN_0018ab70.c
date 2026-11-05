#include "dw4/reflected.h"
typedef struct V3 { float x, y, z; } V3;
void FUN_0018ab70(igAABox *arg0, unsigned int arg1, V3 *arg2) {
    float c, b, a;
    switch (arg1) {
    case 7:
        arg2->x = *(float *)&arg0->_min[0];
        arg2->y = *(float *)&arg0->_min[1];
        arg2->z = *(float *)&arg0->_min[2];
        break;
    case 6:
        c = ((float *)&arg0->_max)[2];
        b = *(float *)&arg0->_min[1];
        a = *(float *)&arg0->_min[0];
        arg2->x = a;
        arg2->y = b;
        arg2->z = c;
        break;
    case 5:
        c = *(float *)&arg0->_min[2];
        b = ((float *)&arg0->_max)[1];
        a = *(float *)&arg0->_min[0];
        arg2->x = a;
        arg2->y = b;
        arg2->z = c;
        break;
    case 4:
        c = ((float *)&arg0->_max)[2];
        b = ((float *)&arg0->_max)[1];
        a = *(float *)&arg0->_min[0];
        arg2->x = a;
        arg2->y = b;
        arg2->z = c;
        break;
    case 3:
        c = *(float *)&arg0->_min[2];
        b = *(float *)&arg0->_min[1];
        a = ((float *)&arg0->_max)[0];
        arg2->x = a;
        arg2->y = b;
        arg2->z = c;
        break;
    case 2:
        c = ((float *)&arg0->_max)[2];
        b = *(float *)&arg0->_min[1];
        a = ((float *)&arg0->_max)[0];
        arg2->x = a;
        arg2->y = b;
        arg2->z = c;
        break;
    case 1:
        c = *(float *)&arg0->_min[2];
        b = ((float *)&arg0->_max)[1];
        a = ((float *)&arg0->_max)[0];
        arg2->x = a;
        arg2->y = b;
        arg2->z = c;
        break;
    case 0:
        arg2->x = ((float *)&arg0->_max)[0];
        arg2->y = ((float *)&arg0->_max)[1];
        arg2->z = ((float *)&arg0->_max)[2];
        break;
    }
}
