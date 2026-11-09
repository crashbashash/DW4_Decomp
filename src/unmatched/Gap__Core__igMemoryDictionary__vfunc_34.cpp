#include "dw4/igSmartPointer.h"

extern "C" {
extern char DAT_004c2158[];
void *FUN_002ca260(int);
int List_Reserve(...);
int List_Resize(...);
int igObject_GetAllocator(void *);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
}
struct R { int v; };
class VT { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual R vIns(int, int); };
struct Tbl : public igObject { int size; int cap; int *data; };

struct Dict { int vt; int a4; int f8; int f12; Tbl *t; int f20; };
extern "C" int Gap__Core__igMemoryDictionary__vfunc_34(int *result, Dict *dict, int capacity) {
    igSmartPointer<Tbl> previous(dict->t, kRetainReference);
    int count = previous.get()->size;
    int *entry = previous.get()->data;
    int allocator;
    Tbl *table;
    int words;
    int i;
    dict->f8 = capacity;
    dict->f20 = 0;
    allocator = igObject_GetAllocator(dict);
    table = dict->t;
    if (table != 0) {
        table->_refCount = table->_refCount - 1;
        if ((table->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(table);
        }
    }
    dict->t = (Tbl *)FUN_002ca260(allocator);
    words = dict->f8 * 2;
    if (words >= dict->t->size) {
        List_Reserve(dict->t, words, 4);
    }
    table = dict->t;
    if (table->data == 0) {
        *result = DAT_004fb418[0];
        return 0;
    }
    words = dict->f8 * 2;
    if (words >= 0) {
        if (words <= table->cap) {
            table->size = words;
        } else {
            List_Resize(table, words, 4);
        }
    }
    table = dict->t;
    int size = table->size;
    int *data = table->data;
    for (int slot = 0; slot < size; slot++) {
        data[slot] = *(int *)DAT_004c2158;
    }
    dict->f12 = 0;
    for (i = 0; i < count; i += 2, entry += 2) {
        if (entry[0] != 0) {
            ((VT *)dict)->vIns(entry[0], entry[1]);
        }
    }
    *result = DAT_004fb410[0];
    return 0;
}
