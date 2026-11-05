typedef struct { char p0[8]; unsigned char n; char p9[7]; char *base; char p14[24]; short s44; short p46; short s48; short s50; } O;
void FUN_001fd5a0(O *o, int idx, float *a2, float *a3, float *a4) {
    char *p = o->base;
    short d = o->s48;
    float *t;
    int q = idx / d;
    int r = idx % d;
    int s = o->s44;
    p += 12;
    p += q * s;
    p += o->s50;
    p += r * o->n * 12;
    t = (float *)p;
    switch (o->n) {
    case 3:
        t[6] = a4[0]; t[7] = a4[1]; t[8] = a4[2];
    case 2:
        t[3] = a3[0]; t[4] = a3[1]; t[5] = a3[2];
    case 1:
        t[0] = a2[0]; t[1] = a2[1]; t[2] = a2[2];
    default:
        break;
    }
}
