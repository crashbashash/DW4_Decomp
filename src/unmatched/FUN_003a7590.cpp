extern "C" {
extern float DAT_004c8fc0[];
extern float DAT_004c90b0[];
}

typedef struct Ramp {
    char pad0[8];
    int mode;
    int base;
    float cur;
    float from;
    float to;
    float step;
} Ramp;

typedef union FBits { float f; struct { unsigned m : 31; unsigned s : 1; } b; } FBits;

extern "C" {
int FUN_003a7590(Ramp *self, int add, float from, float to, float div);
}
int FUN_003a7590(Ramp *self, int add, float from, float to, float div) {
    FBits u;
    int lo, hi, i, j, lo2, hi2, m, k;
    self->mode = 3;
    self->from = from;
    self->to = to;
    if (from < to) {
        lo = -1; hi = -1;
        for (i = 0; i < 60; i++) {
            if (from <= DAT_004c8fc0[i]) { lo = i; break; }
        }
        for (j = 59; j > -1; j--) {
            if (to >= DAT_004c8fc0[j]) { hi = j; break; }
        }
        self->cur = (float)lo;
        self->step = (float)(hi - lo) / div;
        u.f = -210.0f * DAT_004c8fc0[(int)self->cur];
        u.b.s = 0;
        return add + ((int)u.f - 210 + self->base);
    }
    lo2 = -1; hi2 = -1;
    for (m = 0; m < 60; m++) {
        if (from >= DAT_004c90b0[m]) { lo2 = m; break; }
    }
    for (k = 59; k > -1; k--) {
        if (to <= DAT_004c90b0[k]) { hi2 = k; break; }
    }
    self->cur = (float)lo2;
    self->step = (float)(hi2 - lo2) / div;
    u.f = -210.0f * DAT_004c90b0[(int)self->cur];
    u.b.s = 0;
    return add + ((int)u.f - 210 + self->base);
}
