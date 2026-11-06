#include "dw4/reflected.h"

extern "C" {
int List_Reserve(void *, int, int);
int List_Resize(void *, int, int);
void *Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(void *, void *);
int ObjectList_FillRetained(void *, int);
int ObjectList_ResizeRetained(void *, int);
int StringChunk_ReleaseHeader(int, int *);
int StringList_Resize(void *, int);
int igNamedObject_SetName(void *, int);
void igObject_Destroy(igObject *);
void *igObject_GetAllocator(void *);
void *FUN_00364220(void *);
void *FUN_003644f0(void *);
void *FUN_003647c0(void *);
void *FUN_00364a90(void *);
void *FUN_00364d30(void *);
void *FUN_00365000(void *);
void *FUN_00365240(void *);
void *FUN_00365510(void *);
extern int DAT_00587108[4];
extern int DAT_004cf100[4];

extern unsigned char GPR_00554c14;
extern unsigned char GPR_005549e4;
void FUN_003f6620(void *arg0, void *arg1, void *arg2);
}

struct Entry { unsigned type; int count; int name; };

/* matching construct: one RAII holder per retail destructor copy. The cleanup table at 0x544e60 names eight release
 * copies (0x350b10 for the int node, the seven emitted behind this function for the others) and the string holder 0x130720. */
template <class T> struct DataRef {
    T *p;
    DataRef(T *o) : p(o) {}
    ~DataRef() { T *o = p; if (o) { --o->_refCount; if (!(o->_refCount & 0x7fffff)) igObject_Destroy((igObject *)o); } }
};
struct StringRef {
    int *p;
    StringRef(int *s) : p(s) {}
    ~StringRef() { int *cur = p; if (cur) { int *hd = cur - 2; int rc = cur[-1] - 1; cur[-1] = rc; if (rc == 0) StringChunk_ReleaseHeader(*hd, hd); } }
};

#define RELEASE_REF(T, q) { T *rr = (q); if (rr) { --rr->_refCount; if (!(rr->_refCount & 0x7fffff)) igObject_Destroy(rr); } }
#define ALLOC(var) { void *got = igObject_GetAllocator(arg0); if (GPR_00554c14) var = got; else var = Memory_GetAllocatorBySelector(DAT_00587108[0]); }
#define RESERVE(LT, h, SZ) { LT *l = (LT *)(h)->_data; if (!(e->count < l->_count)) List_Reserve(l, e->count, SZ); }
#define RESIZE(LT, h, SZ) { int n = e->count; LT *l = (LT *)(h)->_data; if (n >= 0) { if (n <= l->_capacity) l->_count = n; else List_Resize(l, n, SZ); } }

struct Fill {
    /* clear every slot of the string list to the empty token. matching construct: the empty-token holder is a temporary of the call statement (passed by const reference), which takes the lowest frame slot (retail slot 140) below the case holders; the loop counters stay the caller's variables so the register assignment matches */
    static inline void emptyStrings(beDataObjStringList *h5, const StringRef &str, int &n5, int **&d5, int &i5) {
        igStringRefList *l5 = (igStringRefList *)h5->_data;
        n5 = l5->_count;
        d5 = (int **)l5->_data;
        for (i5 = 0; i5 < n5; i5++) {
            int *cur = str.p;
            if (cur) ++cur[-1];
            int *old = *d5;
            if (old) { int *hd = old - 2; int rc = old[-1] - 1; old[-1] = rc; if (rc == 0) StringChunk_ReleaseHeader(*hd, hd); }
            *d5 = str.p;
            d5++;
        }
    }
};

void FUN_003f6620(void *arg0, void *arg1, void *arg2)
{
    igObjectList *out = (igObjectList *)arg1;
    int n1;
    int i1;
    int n5;
    int **d5;
    int i5;
    Entry *e = (Entry *)arg2;
    unsigned char done = 0;
    void *alloc;

    do {
        switch (e->type + 1) {
        case 1: {
            ALLOC(alloc)
            DataRef<beDataObjInt> s0((beDataObjInt *)FUN_00365510(alloc));
            igNamedObject_SetName(s0.p, e->name);
            ObjectList_AppendRetained(out, s0.p);
            break;
        }
        case 2: {
            ALLOC(alloc)
            DataRef<beDataObjIntList> s1((beDataObjIntList *)FUN_00365240(alloc));
            igNamedObject_SetName(s1.p, e->name);
            RESERVE(igIntList, s1.p, 4)
            RESIZE(igIntList, s1.p, 4)
            {
                igIntList *l1 = (igIntList *)s1.p->_data;
                n1 = l1->_count;
                int *d1 = (int *)l1->_data;
                for (i1 = 0; i1 < n1; i1++) d1[i1] = DAT_004cf100[0];
            }
            ObjectList_AppendRetained(out, s1.p);
            break;
        }
        case 3: {
            ALLOC(alloc)
            DataRef<beDataObjBool> s2((beDataObjBool *)FUN_00365000(alloc));
            igNamedObject_SetName(s2.p, e->name);
            ObjectList_AppendRetained(out, s2.p);
            break;
        }
        case 4: {
            ALLOC(alloc)
            DataRef<beDataObjBoolList> s3((beDataObjBoolList *)FUN_00364d30(alloc));
            igNamedObject_SetName(s3.p, e->name);
            RESERVE(igBoolList, s3.p, 1)
            RESIZE(igBoolList, s3.p, 1)
            {
                igBoolList *l3 = (igBoolList *)s3.p->_data;
                int n3 = l3->_count;
                unsigned char *d3 = (unsigned char *)l3->_data;
                for (int i3 = 0; i3 < n3; i3++) d3[i3] = GPR_005549e4;
            }
            ObjectList_AppendRetained(out, s3.p);
            break;
        }
        case 5: {
            ALLOC(alloc)
            DataRef<beDataObjString> s4((beDataObjString *)FUN_00364a90(alloc));
            igNamedObject_SetName(s4.p, e->name);
            ObjectList_AppendRetained(out, s4.p);
            break;
        }
        case 6: {
            ALLOC(alloc)
            DataRef<beDataObjStringList> s5((beDataObjStringList *)FUN_003647c0(alloc));
            igNamedObject_SetName(s5.p, e->name);
            RESERVE(igStringRefList, s5.p, 4)
            StringList_Resize((void *)s5.p->_data, e->count);
            Fill::emptyStrings(s5.p, StringRef(0), n5, d5, i5);
            ObjectList_AppendRetained(out, s5.p);
            break;
        }
        case 7: {
            ALLOC(alloc)
            DataRef<beDataObjObjectList> s6((beDataObjObjectList *)FUN_003644f0(alloc));
            igNamedObject_SetName(s6.p, e->name);
            RESERVE(igObjectList, s6.p, 4)
            ObjectList_ResizeRetained((void *)s6.p->_data, e->count);
            ObjectList_FillRetained((void *)s6.p->_data, 0);
            ObjectList_AppendRetained(out, s6.p);
            break;
        }
        case 8: {
            ALLOC(alloc)
            DataRef<beDataObjFloatList> s7((beDataObjFloatList *)FUN_00364220(alloc));
            igNamedObject_SetName(s7.p, e->name);
            RESERVE(igFloatList, s7.p, 4)
            RESIZE(igFloatList, s7.p, 4)
            {
                igFloatList *l7 = (igFloatList *)s7.p->_data;
                int n7 = l7->_count;
                float *d7 = (float *)l7->_data;
                for (int i7 = 0; i7 < n7; i7++) d7[i7] = *(float *)&DAT_004cf100[2];
            }
            ObjectList_AppendRetained(out, s7.p);
            break;
        }
        case 0:
            done = 1;
            break;
        }
        e++;
    } while (done == 0);
    {
        int n = out->_count;
        if (!(n < ((volatile igObjectList *)out)->_count)) List_Reserve(out, n, 4);
    }
}
