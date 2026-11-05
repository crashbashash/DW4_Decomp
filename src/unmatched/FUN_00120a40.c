/* FUN_00120a40 -- fdlibm __kernel_tan(x, y, iy): tangent of x + y on |x| <= pi/4 by a degree-27 odd
 * polynomial (T[0..12]); for |x| >= 0.6744 the argument is folded around pi/4 and the result is
 * recovered with tan(pi/4 - x) identities. iy == -1 returns -1/tan (the cotangent branch). */
#include "dw4/ieee_words.h"

extern double FUN_00122538(double); /* fabs */

static const double T[] = {
    3.33333333333334091986e-01,
    1.33333333333201242699e-01,
    5.39682539762260521377e-02,
    2.18694882948595424599e-02,
    8.86323982359930005737e-03,
    3.59207910759131235356e-03,
    1.45620945432529025516e-03,
    5.88041240820264096874e-04,
    2.46463134818469906812e-04,
    7.81794442939557092300e-05,
    7.14072491382608190305e-05,
    -1.85586374855275456654e-05,
    2.59073051863633712884e-05
};
#define one 1.00000000000000000000e+00
#define pio4 7.85398163397448278999e-01
#define pio4lo 3.06161699786838301793e-17

double FUN_00120a40(double x, double y, int iy)
{
    double z, r, v, w, s;
    int ix, hx;
    unsigned lx;

    GET_HIGH_WORD(hx, x);
    ix = hx & 0x7fffffff;
    if (ix < 0x3e300000) {
        if ((int)x == 0) {
            GET_LOW_WORD(lx, x);
            if (((ix | lx) | (iy + 1)) == 0)
                return one / FUN_00122538(x);
            else {
                if (iy != 1)
                    return -one / x;
                else
                    return x;
            }
        }
    }
    if (ix >= 0x3FE59428) {
        if (hx < 0) {
            x = -x;
            y = -y;
        }
        z = pio4 - x;
        w = pio4lo - y;
        x = z + w;
        y = 0.0;
    }
    z = x * x;
    w = z * z;
    r = T[1] + w * (T[3] + w * (T[5] + w * (T[7] + w * (T[9] + w * T[11]))));
    v = z * (T[2] + w * (T[4] + w * (T[6] + w * (T[8] + w * (T[10] + w * T[12])))));
    s = z * x;
    r = y + z * (s * (r + v) + y);
    r += T[0] * s;
    w = x + r;
    if (ix >= 0x3FE59428) {
        v = (double)iy;
        return (double)(1 - ((hx >> 30) & 2)) * (v - 2.0 * (x - (w * w / (w + v) - r)));
    }
    if (iy == 1)
        return w;
    else {
        double a, t;
        z = w;
        SET_LOW_WORD(z, 0);
        v = r - (z - x);
        t = a = -1.0 / w;
        SET_LOW_WORD(t, 0);
        s = 1.0 + t * z;
        return t + a * (s + t * v);
    }
}
