typedef unsigned int __ULong;
struct _Bigint { struct _Bigint *_next; int _k, _maxwds, _sign, _wds; __ULong _x[1]; };
union double_union { double d; __ULong i[2]; };
int FUN_001276f0();
#define d0 d.i[1]
#define d1 d.i[0]
double FUN_00127f98(struct _Bigint *a, int *e) {
    __ULong *xa, *xa0, w, y, z;
    int k;
    union double_union d;
    xa0 = a->_x;
    xa = xa0 + a->_wds;
    y = *--xa;
    k = FUN_001276f0(y);
    *e = 32 - k;
    if (k < 11) {
        d0 = 0x3ff00000 | y >> (11 - k);
        w = xa > xa0 ? *--xa : 0;
        d1 = y << ((32 - 11) + k) | w >> (11 - k);
        goto ret_d;
    }
    z = xa > xa0 ? *--xa : 0;
    if (k -= 11) {
        d0 = 0x3ff00000 | y << k | z >> (32 - k);
        y = xa > xa0 ? *--xa : 0;
        d1 = z << k | y >> (32 - k);
    } else {
        d0 = 0x3ff00000 | y;
        d1 = z;
    }
ret_d:
    return d.d;
}
