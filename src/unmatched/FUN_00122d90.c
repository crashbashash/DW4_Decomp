/* fdlibm atanf(x). */
#include "dw4/ieee_words.h"

extern float FUN_00123210(float); /* fabsf */

static const float atanhi[] = {
    4.6364760399e-01F,
    7.8539812565e-01F,
    9.8279368877e-01F,
    1.5707962513e+00F,
};

static const float atanlo[] = {
    5.0121582440e-09F,
    3.7748947079e-08F,
    3.4473217170e-08F,
    7.5497894159e-08F,
};

static const float aT[] = {
    3.3333334327e-01F,
    -2.0000000298e-01F,
    1.4285714924e-01F,
    -1.1111110449e-01F,
    9.0908870101e-02F,
    -7.6918758452e-02F,
    6.6610731184e-02F,
    -5.8335702866e-02F,
    4.9768779427e-02F,
    -3.6531571299e-02F,
    1.6285819933e-02F,
};

static const float one = 1.0F, huge = 1.0e30F;

float FUN_00122d90(float x)
{
    float w, s1, s2, z;
    int ix, hx, id;

    GET_FLOAT_WORD(hx, x);
    ix = hx & 0x7fffffff;
    if (ix >= 0x50800000) {
        if (hx > 0)
            return atanhi[3] + atanlo[3];
        else
            return -atanhi[3] - atanlo[3];
    }
    if (ix < 0x3ee00000) {
        if (ix < 0x31000000) {
            if (huge + x > one)
                return x;
        }
        id = -1;
    } else {
        x = FUN_00123210(x);
        if (ix < 0x3f980000) {
            if (ix < 0x3f300000) {
                id = 0;
                x = ((float)2.0 * x - one) / ((float)2.0 + x);
            } else {
                id = 1;
                x = (x - one) / (x + one);
            }
        } else {
            if (ix < 0x401c0000) {
                id = 2;
                x = (x - (float)1.5) / (one + (float)1.5 * x);
            } else {
                id = 3;
                x = -(float)1.0 / x;
            }
        }
    }
    z = x * x;
    w = z * z;
    s1 = z * (aT[0] + w * (aT[2] + w * (aT[4] + w * (aT[6] + w * (aT[8] + w * aT[10])))));
    s2 = w * (aT[1] + w * (aT[3] + w * (aT[5] + w * (aT[7] + w * aT[9]))));
    if (id < 0)
        return x - x * (s1 + s2);
    else {
        z = atanhi[id] - ((x * (s1 + s2) - atanlo[id]) - x);
        return (hx < 0) ? -z : z;
    }
}
