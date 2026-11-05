/* 0x002ee970 - igMemoryDictionary vfunc_32. Open-addressing remove; hidden-return R, find vcall at 132, success tail shared by goto; table base re-read through a volatile access; local order e, next, t. Alternate -O3. */
extern "C" {
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
}
struct R { int v; R(int x) { v = x; } };
class VT { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vFind(int); };
struct Ent { int key; int state; };
struct Tbl { int a0, a4; int cap; int a12; Ent *ents; };
struct Dict { int vt; int a4, a8; int cnt; Tbl *t; };
extern "C" {
R Gap__Core__igMemoryDictionary__vfunc_32(Dict *arg1, int arg2) {
    int i;
    int half;
    int idx;
    Ent *e;
    Ent *next;
    Tbl *t;

    i = 0;
    half = arg1->t->cap / 2;
    if (half != 0) {
        idx = ((VT *)arg1)->vFind(arg2);
        t = arg1->t;
        e = t->ents + idx;
        do {
            idx += 1;
            next = e + 1;
            if (idx >= half) {
                next = *(Ent *volatile *)&t->ents;
                idx = 0;
            }
            if (e->key == arg2) {
                e->key = 0;
                arg1->cnt = arg1->cnt - 1;
                if (next->state == -1) {
                    e->state = -1;
                } else {
                    e->state = -2;
                }
                goto ok;
            }
            if (e->state == -1) {
                return R(DAT_004fb418[0]);
            }
            i += 1;
            e = next;
        } while (i < half);
        return R(DAT_004fb418[0]);
    }
ok:
    return R(DAT_004fb410[0]);
}
}
