class Tgt { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void v80(void *);  };
struct Sub { char pad[60]; int w60; };
struct Elem { char pad[24]; Tgt *t; Sub *s; };
struct Coll { char pad[8]; unsigned n; char pad2[44]; unsigned char done; };
extern int DAT_00585b70[4];
extern "C" {
Elem *FUN_002d7e90(Coll *, unsigned);
int igObject_IsKindOf(Elem *, int);
void FUN_002d8f20(Coll *arg0);
}
void FUN_002d8f20(Coll *arg0) {
    unsigned n;
    unsigned i;
    Elem *e;
    if (arg0->done != 1) {
        n = arg0->n;
        i = 0;
        while (i < n) {
            e = FUN_002d7e90(arg0, i);
            if (e != 0 && igObject_IsKindOf(e, DAT_00585b70[0]) != 0) {
                if (e->s != 0 && e->s->w60 != 0) {
                    e->t->v80(e->s);
                }
            }
            i++;
        }
        arg0->done = 1;
    }
}
