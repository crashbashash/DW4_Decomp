/* Clamps a scrolling offset: two scaled sample values (negative 210 times a float helper result
 * and times the span float) have their sign bit cleared through a byte bit-field union, are
 * converted to int and biased, and the offset field is zeroed when the order flips; the member is
 * re-read volatile (retail reloads it after each stack store); alternate compiler -O3,p. */
typedef union U { float f; struct { unsigned char p0, p1, p2; unsigned char lo : 7; unsigned char sign : 1; } b; } U;
typedef struct A { char p0[8]; int w8; int w12; float f16; float f20; float f24; } A;
extern "C" {
float FUN_003a7810(A *);
int FUN_003a7890(A *arg0, int arg1);
}
int FUN_003a7890(A *arg0, int arg1) {
    float f21 = arg0->f20;
    float f20 = arg0->f24;
    U ua, ub;
    int v0, v1;
    ua.f = -210.0f * FUN_003a7810(arg0);
    ua.b.sign = 0;
    v0 = arg1 + ((int)ua.f - 210 + *(volatile int *)&arg0->w12);
    ub.f = -210.0f * f20;
    ub.b.sign = 0;
    v1 = arg1 + ((int)ub.f - 210 + *(volatile int *)&arg0->w12);
    if (!(f21 <= f20)) {
        if (v0 <= v1) {
            arg0->w8 = 0;
            if (f20 == 0.0f) {
                return -999;
            }
        }
    } else {
        if (v0 >= v1) {
            arg0->w8 = 0;
        }
    }
    return v0;
}
