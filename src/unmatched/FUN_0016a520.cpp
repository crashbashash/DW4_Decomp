extern "C" int FUN_001e8d10(int,int,int,int);
typedef struct R { int x; int y; } R;
typedef struct L { char pad[16]; R *rects; } L;
typedef struct O {
    char p0[104]; int f68; char p1[760]; L *l364; int idx;
    char p2[40]; int e394; int e398; int e39c; int e3a0;
    char p3[304]; int e4d4; int e4d8; int e4dc; int e4e0;
} O;
#define MIN(a,b) ((a) < (b) ? (a) : (b))
struct H {
static inline int clampLen(int lim, int diff) {
    if (MIN(lim, diff) > 1) return MIN(lim, diff);
    return 1;
}
static inline int clampLow(int lim, int diff) {
    if (MIN(lim, diff) > 0) return MIN(lim, diff);
    return 0;
}
};
extern "C" void FUN_0016a520(O *o) {
    R *r = (R *)((char *)o->l364->rects + o->idx * 0x30);
    if (r != 0) {
        if (o->f68 == 0) {
            int a = o->e398; int hi_y = r->y; int c = o->e3a0;
            c = H::clampLen(c, hi_y - a);
            { int lo_x = o->e394; int hi_x = r->x; int w = o->e39c;
              w = H::clampLen(w, hi_x - lo_x);
              a = H::clampLow(a, hi_y);
              lo_x = H::clampLow(lo_x, hi_x);
              FUN_001e8d10(lo_x, a, w, c); }
        } else {
            int a = o->e4d8; int hi_y = r->y; int c = o->e4e0;
            c = H::clampLen(c, hi_y - a);
            { int lo_x = o->e4d4; int hi_x = r->x; int w = o->e4dc;
              w = H::clampLen(w, hi_x - lo_x);
              a = H::clampLow(a, hi_y);
              lo_x = H::clampLow(lo_x, hi_x);
              FUN_001e8d10(lo_x, a, w, c); }
        }
    }
}
