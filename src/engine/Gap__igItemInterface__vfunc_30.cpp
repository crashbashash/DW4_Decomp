#include "dw4/igSmartPointer.h"

typedef struct Iterator : public igObject { } Iterator;
extern "C" {
Iterator *FUN_002279d0(int);
int FUN_0022a8d0(Iterator *, int);
int FUN_0022a950(Iterator *);
int FUN_0022a9b0(Iterator *);
int StringChunk_ReleaseHeader(int, int *);
}
struct StringRef {
    int *p;
    StringRef(const StringRef &other) : p(other.p) { if (p != 0) { p[-1] = p[-1] + 1; } }
    ~StringRef() {
        if (p != 0) {
            int *header = p - 2;
            int count = p[-1] - 1;
            p[-1] = count;
            if (count == 0) { StringChunk_ReleaseHeader(*header, header); }
        }
    }
};

struct IteratorType {};
static inline Iterator *makeIterator(IteratorType) { return FUN_002279d0(0); }
class ItemInterface { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void vX(const StringRef &, int, int); };
extern "C" void Gap__igItemInterface__vfunc_30(ItemInterface *self, const StringRef &name, int a2, int a3) {
    igSmartPointer<Iterator> it(makeIterator(IteratorType()));
    FUN_0022a8d0(it.p, a2);
    for (;;) {
        int v = FUN_0022a950(it.p);
        if (((v != 0) ^ 1) != 0) break;
        { StringRef copy(name); self->vX(copy, v, a3); }
        FUN_0022a9b0(it.p);
    }
}
