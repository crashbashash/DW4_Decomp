#include "dw4/reflected.h"

void FUN_0018b730(igAABox *box, igAABox *other) {
    if (!(box->_min[0] <= other->_min[0])) box->_min[0] = other->_min[0];
    if (!(box->_min[1] <= other->_min[1])) box->_min[1] = other->_min[1];
    if (!(box->_min[2] <= other->_min[2])) box->_min[2] = other->_min[2];
    if (box->_max[0] < other->_max[0]) box->_max[0] = other->_max[0];
    if (box->_max[1] < other->_max[1]) box->_max[1] = other->_max[1];
    if (box->_max[2] < other->_max[2]) box->_max[2] = other->_max[2];
}
