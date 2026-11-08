typedef struct { short v[4]; } Ent;
int FUN_002830d0();
void FUN_002846c0(int mode, int lo, int hi, Ent *t) {
    int max;
    int i;
    short y;
    short b1, b2, r0, r1;
    float c;
    float scale;
    int range;
    Ent *tb;
    Ent *tr;

    max = FUN_002830d0();
    i = 0;
    tb = t + 256;
    tr = t + 512;
    for (; i < 256; i++) {
        y = (int)((float)(i - 16) * 74.49599456787109375f + 0.5f);
        c = (float)(i - 128);
        b2 = (int)(c * 129.0879974365234375f + 0.5f);
        b1 = (int)(c * -25.0879993438720703125f + 0.5f);
        r1 = (int)(c * -52.0319976806640625f + 0.5f);
        r0 = (int)(c * 102.1439971923828125f + 0.5f);
        t[i].v[2] = y;
        t[i].v[1] = y;
        t[i].v[0] = y;
        tb[i].v[2] = b2;
        tb[i].v[1] = b1;
        tb[i].v[0] = 0;
        tb[i].v[3] = 0;
        tr[i].v[1] = r1;
        tr[i].v[0] = r0;
        tr[i].v[2] = 0;
        tr[i].v[3] = 0;
    }
    range = hi - lo;
    scale = (float)max / (float)range;
    if (mode == 1) {
        for (i = 0; i < 256; i++) {
            if (i < lo) {
                t[i].v[3] = max << 6;
            } else if (hi < i) {
                t[i].v[3] = 0;
            } else {
                t[i].v[3] = (int)((float)(range - (i - lo)) * scale) << 6;
            }
        }
    } else {
        for (i = 0; i < 256; i++) {
            if (i < lo) {
                t[i].v[3] = 0;
            } else if (hi < i) {
                t[i].v[3] = max << 6;
            } else {
                t[i].v[3] = (int)((float)(i - lo) * scale) << 6;
            }
        }
    }
}
