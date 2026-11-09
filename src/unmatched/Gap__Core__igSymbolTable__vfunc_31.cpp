struct List { char pad[8]; int count; int capacity; int *data; };
class Table { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int vHash(int, int); virtual void d29(); virtual void vRehash(int);
 int pad1[7]; List *hash; };
static inline void setAt(List *l, int i, int v) { if (l->count != 0 && i >= 0 && i < l->count) { ((List *)l)->data[i] = v; } }
extern "C" int Gap__Core__igSymbolTable__vfunc_31(Table *self, int key, int key2, int value) {
    int probes = 0;
    int size = self->hash->count;
    int half = size / 2;
    int idx;
    List *l;

    if (size != 0) {
        idx = self->vHash(key, key2);
        l = self->hash;
        do {
            if (l->data[idx] == -1) {
                setAt(l, idx, value);
                goto done;
            }
            idx++;
            if (idx >= size) {
                idx = 0;
            }
            probes++;
        } while (probes < half);
        self->vRehash(size * 2);
        return 0;
    }
done:
    return 1;
}
