extern float sqrtf(float);
extern int DAT_00562c70[];
extern int DAT_00569330[4];
extern int DAT_0056af00[4];
extern unsigned char DAT_0056af30[];
extern int DAT_0056af40[];
extern int DAT_0056af9c[4];
extern int DAT_0056b5f8[4];
extern float DAT_0056afd0[];
extern char GPR_00554bc4;

void FUN_001fb470(float *out) {
    int sel;
    float *M;
    float zero;
    float *o;
    int i;
    float *L;
    sel = (((unsigned int)DAT_00562c70[DAT_00569330[0]]) >> 21) & 1;
    zero = 0.0f;
    M = DAT_0056afd0;
    if (GPR_00554bc4 != 0 && sel == 0) DAT_0056b5f8[0] = 1;
    for (i = 0; i < 4; i++) {
        L = (float *)DAT_0056af40[DAT_0056af30[i]];
        o = out + i;
        if (L != 0 && i < DAT_0056af00[0]) {
            if (GPR_00554bc4 != 0 && sel != 0) {
                float x = L[24], y = L[25], z = L[26];
                float a = x * M[0] + y * M[1] + z * M[2];
                float b = x * M[4] + y * M[5] + z * M[6];
                float c = x * M[8] + y * M[9] + z * M[10];
                float n = 1.0f / sqrtf(a * a + b * b + c * c);
                o[0] = a * n;
                o[4] = b * n;
                o[8] = c * n;
                if (DAT_0056af9c[0] != 0) {
                    float a2, b2, c2, s, m;
                    z = z + 1.0f;
                    a2 = x * M[0] + y * M[1] + z * M[2];
                    b2 = x * M[4] + y * M[5] + z * M[6];
                    c2 = x * M[8] + y * M[9] + z * M[10];
                    s = a2 * a2 + b2 * b2 + c2 * c2;
                                        if (s != zero) m = 1.0f / sqrtf(s); else m = zero;
                    o[12] = a2 * m;
                    o[16] = b2 * m;
                    o[20] = c2 * m;
                }
            } else {
                o[0] = L[24];
                o[4] = L[25];
                o[8] = L[26];
                if (DAT_0056af9c[0] != 0) {
                    o[12] = L[24];
                    o[16] = L[25];
                    o[20] = 1.0f + L[26];
                }
            }
        } else {
            o[0] = 0.0f;
            o[4] = 0.0f;
            o[8] = 0.0f;
            if (DAT_0056af9c[0] != 0) {
                o[12] = 0.0f;
                o[16] = 0.0f;
                o[20] = 0.0f;
            }
        }
    }
}
