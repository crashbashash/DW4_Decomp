typedef struct S { char pad0[10]; unsigned char f10; unsigned char f11; char pad12; unsigned char f13; unsigned char f14; char pad15; char *f16; char pad20[16]; unsigned char f36; char pad37[7]; short f44; short pad46; short f48; short pad50; short pad52; short f54; } S;
void FUN_001fdeb0(S *o, int arg1, float *a2, float *a3, float *a4) {
    int a7;
    float * t;
    int a6;
    int t4;
    int v1;
    int a1;
    int q;
    int r;
    char * p;
    a7 = o->f48;
    p = o->f16;
    a6 = o->f11;
    t4 = o->f10;
    v1 = o->f36;
    q = arg1 / a7;
    p += 0xC;
    r = arg1 % a7;
    t4 = ((a6 < t4) ? t4 : a6) & 0xFF;
    a1 = o->f13;
    t4 = (a1 < t4) ? t4 : a1;
    a1 = o->f14;
    t4 = (a1 < t4) ? t4 : a1;
    p += q * o->f44;
    p += o->f54;
    p += v1 * (r * t4) * 4;
    t = (float *)p;
    if (v1 == 1) {
        switch (t4) {
        case 3: a4[0] = 2.0f * t[2];
        case 2: a3[0] = 2.0f * t[1];
        case 1: a2[0] = 2.0f * t[0];
        }
    } else if (v1 == 2) {
        switch (t4) {
        case 3: a4[0] = 2.0f * t[4]; a4[1] = 2.0f * t[5];
        case 2: a3[0] = 2.0f * t[2]; a3[1] = 2.0f * t[3];
        case 1: a2[0] = 2.0f * t[0]; a2[1] = 2.0f * t[1];
        }
    } else {
        if (v1 >= 3) {
            switch (t4) {
            case 3: a4[0] = 2.0f * *(float *)((char *)t + v1 * 8); a4[1] = 2.0f * *(float *)((char *)t + v1 * 8 + 4);
            case 2: a3[0] = 2.0f * *(float *)((char *)t + v1 * 4); a3[1] = 2.0f * *(float *)((char *)t + v1 * 4 + 4);
            case 1: a2[0] = 2.0f * t[0]; a2[1] = 2.0f * t[1];
            }
        }
    }
}
