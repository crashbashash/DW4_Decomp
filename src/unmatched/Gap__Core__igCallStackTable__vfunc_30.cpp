struct CallStackIndexList { int vt; int rc; int count; int capacity; int *data; };
struct CallStackIndexCells { int vt; int rc; int count; int capacity; unsigned int *data; };
class CallStackTableHashView { public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual int Hash(int *key);
    virtual void s28();
    virtual void Rehash(int size);
    int rc; int pad8; int pad12; CallStackIndexList *words; CallStackIndexList *index;
};
extern "C" int Gap__Core__igCallStackTable__vfunc_30(CallStackTableHashView *self, int *key, int value);
static inline void setAt(CallStackIndexCells *l, int i, int v) {
    if (l->count != 0 && i >= 0 && i < l->count) {
        l->data[i] = v;
    }
}
int Gap__Core__igCallStackTable__vfunc_30(CallStackTableHashView *self, int *key, int value) {
    int tries = 0;
    int n = self->index->count;
    int half = n / 2;
    int h;
    CallStackIndexList *index;
    if (n != 0) {
        h = self->Hash(key);
        index = self->index;
        do {
            if (index->data[h] == -1) {
                setAt((CallStackIndexCells *)index, h, value);
                goto ok;
            }
            h++;
            if (h >= n) {
                h = 0;
            }
            tries++;
        } while (tries < half);
        self->Rehash(n * 2);
        return 0;
    }
ok:
    return 1;
}
