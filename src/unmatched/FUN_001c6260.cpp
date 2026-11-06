extern "C" {
int FUN_001c6260(void *arg0);
}
class Elem { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
struct List { int pad0[2]; unsigned int count; int pad1; Elem **data; };
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(); char pad[24]; List *list; };
int FUN_001c6260(void *arg0) {
    Obj *self = (Obj *)arg0;
    unsigned int n;
    unsigned int i;
    if (self->vX() > 1) {
        return 0;
    }
    n = 0;
    if (self->list != 0) {
        n = self->list->count;
    }
    for (i = 0; i < n; i++) {
        if (self->list->data[i]->vX() == 0) {
            return 0;
        }
    }
    return 1;
}
