typedef struct {
    char p0[24];
    long long pts;
    long long dts;
    char p1[44 - 40];
    int f2c;
    int f30;
    int f34;
    int f38;
    int f3c;
    int f40;
} Pic;
typedef struct {
    char p0[140];
    int has_rate;
    long long period;
    char p1[152 - 152];
    int base;
    char p2[160 - 156];
    long long rate;
    int frame;
    char p3[264 - 172];
    long long pending_pts;
    int pending_state;
} Dec;
void FUN_00107f00(Dec *d, Pic *pic, long long *pts, long long *dts, long long *flags) {
    if (d->has_rate && pic->pts < 0 && d->base >= 0) {
        int frame = d->frame;
        int rate = d->rate;
        int odd = rate & 1;
        int extra = odd & (d->period & 1) & (frame & 1);
        *pts = d->base + ((int)((d->period * rate) >> 1) + extra);
        if (odd & d->period) {
            d->frame = frame + 1;
        }
    } else {
        *pts = pic->pts;
    }
    if (d->pending_state == 2 && d->pending_pts >= 0) {
        *pts = d->pending_pts;
        d->pending_state = 0;
        d->pending_pts = -1;
    }
    *dts = pic->dts;
    *flags = (long long)pic->f34 << 8 | (long long)pic->f38 << 7 | (long long)pic->f3c << 6 | (long long)pic->f40 << 5 | (long long)pic->f30 << 3 | pic->f2c;
}
