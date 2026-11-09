extern "C" {
extern int DAT_004c2300;
int FUN_0030da10(...);
int List_Reserve(...);
int List_Resize(...);
}
struct Entry { int name; int a; int b; int path; };
struct List { char pad[8]; int count; int capacity; void *data; };
class Table { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
 virtual int vX(int, int, int);
 int pad1; int pad2; unsigned int bucketSize; unsigned int start; unsigned int end; unsigned int buckets; List *entries; List *hash; };
static inline void reserve(List *l, int n) { if (n >= l->count) { List_Reserve(l, n, 4); } }
static inline void setCount(List *l, int n) { if (n >= 0) { if (n <= l->capacity) { l->count = n; } else { List_Resize(l, n, 4); } } }
extern "C" void Gap__Core__igSymbolTable__vfunc_32(Table *self, int n) {
    List *l;
    int count;
    int *data;
    int i;
    Entry *begin;
    Entry *end;
    Entry *e;

    FUN_0030da10(self, n);
    reserve(self->hash, n);
    setCount(self->hash, n);
    l = self->hash;
    count = l->count;
    data = (int *)l->data;
    for (i = 0; i < count; i++) {
        data[i] = DAT_004c2300;
    }
    if (self->bucketSize != 0) {
        self->buckets = (self->end - self->start) / self->bucketSize;
        if ((self->end - self->start) % self->bucketSize != 0) {
            self->buckets = self->buckets + 1;
        }
    } else {
        self->buckets = 1;
    }
    l = self->entries;
    begin = (Entry *)l->data;
    end = begin + l->count / 4;
    for (e = begin; e < end; e++) {
        int bb = *(unsigned int *)&e->b; if (self->vX(e->a, bb, e - begin) == 0) {
            break;
        }
    }
}
