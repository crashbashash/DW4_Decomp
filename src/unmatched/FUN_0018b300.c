#include "dw4/reflected.h"

enum { kOutside, kInside };

int FUN_0018c920(void *other, igAABox *box);

int FUN_0018b300(igAABox *box, void *other) {
    unsigned char inside;
    if (!(box->_min[0] <= box->_max[0])) {
        return kOutside;
    }
    inside = FUN_0018c920(other, box);
    return inside ? kInside : kOutside;
}
