struct LocationHashWords { int vt; int rc; int count; int cap; int *data; };
class LocationHashTable { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual int slot(int); virtual void p29(); virtual void rehash(int);
  char q4[16]; LocationHashWords *table; };
extern "C" int Gap__Core__igLocationTable__vfunc_31(LocationHashTable *self, int key, int value) {
    int probes = 0;
    int size = self->table->count;
    int limit = size / 2;
    int i;
    LocationHashWords *t;
    int *data;
    if (size != 0) {
        i = self->slot(key);
        t = self->table;
        data = t->data;
        do {
            if (data[i] == -1) {
                int n = t->count;
                if (n != 0 && i >= 0 && n > i) { ((volatile LocationHashWords *)t)->data[i] = value; }
                goto done;
            }
            i++;
            if (i >= size) { i = 0; }
            probes++;
        } while (probes < limit);
        self->rehash(size * 2);
        return 0;
    }
done:
    return 1;
}
