class L { public: int pad0, pad1; int count; int pad3; int *items; };
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual unsigned char v29(int, int, float); };
class OL { public: int pad0, pad1; int count; int pad3; Obj **items; };
class Holder { public: int pad0, pad1; L *list; };
class OHolder { public: int pad0, pad1; OL *list; };
class ED2 { public: int p0, p1, p2; OHolder *o; Holder *h; };
struct F { static int IndexOf(L *l, int n, int k) { for (int i = 0; i < n; i++) { if (l->items[i] == k) return i; } return -1; } };
extern "C" void Gap__Core__igEventDispatcher__vfunc_38(ED2 *self, int a1, int key, int a3, float f) {
    L *l = self->h->list;
    volatile int vk = key;
    int cnt = l->count;
    int kk = vk;
    int idx = F::IndexOf(l, cnt, kk);

    int n = self->o->list->count;
    for (int i = 0; i < n; i++) {
        unsigned char r = self->o->list->items[i]->v29(idx, a3, f);
        if (r) break;
    }
}
