#include "dw4/reflected.h"
extern "C" {
void *FUN_002c9740(void *);
void *FUN_002c99b0(void *);
void List_Resize(...);
int igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
extern float DAT_0048da38[4];
extern float DAT_0048da40[4];
extern unsigned char GPR_00554988;
}
/* receiver class not established (no reflected class matches +44..+56); lists are typed by their creators FUN_002c9740 (igFloatList) and FUN_002c99b0 (igUnsignedCharList) */
struct Self { char pad[44]; igObject *f44; igFloatList *f48; igFloatList *f52; igUnsignedCharList *f56; };
struct Src { char pad[20]; int f20; };
#define REL3(p) { igObject *t = p; if (t) { t->_refCount = t->_refCount - 1; igObject *u = p; if (((unsigned long long)((long long)(int)u->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(u); } }
#define ASSIGN(field, src) { igObject *s0 = (src); if (s0) s0->_refCount = s0->_refCount + 1; igObject *old = (field); if (old) { old->_refCount = old->_refCount - 1; if (((unsigned long long)((long long)(int)old->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(old); } (field) = s0; }
extern "C" bool FUN_001d08d0(Self *arg0, int arg1) {
    igObject *volatile sp6C;
    igObject *volatile sp68;
    igObject *volatile sp64;
    bool r = false;
    int n;
    int i;
    int j;
    if (arg0->f48 == 0) {
        n = ((Src *)arg0->f44)->f20;
        sp6C = (igObject *)FUN_002c9740(igObject_GetAllocator(arg0));
        ASSIGN(*(igObject **)&arg0->f48, sp6C);
        REL3(sp6C);
        sp68 = (igObject *)FUN_002c9740(igObject_GetAllocator(arg0));
        ASSIGN(*(igObject **)&arg0->f52, sp68);
        REL3(sp68);
        sp64 = (igObject *)FUN_002c99b0(igObject_GetAllocator(arg0));
        ASSIGN(*(igObject **)&arg0->f56, sp64);
        REL3(sp64);
        { igFloatList *l = arg0->f48; if (n >= 0) { if (n <= l->_capacity) l->_count = n; else List_Resize(l, n, 4); } }
        { igFloatList *l = arg0->f52; if (n >= 0) { if (n <= l->_capacity) l->_count = n; else List_Resize(l, n, 4); } }
        { igUnsignedCharList *l = arg0->f56; if (n >= 0) { if (n <= l->_capacity) l->_count = n; else List_Resize(l, n, 1); } }
        for (i = 0; i < n; i++) {
            igFloatList *a = arg0->f48;
            int c = a->_count;
            if (c != 0 && i >= 0 && i < c) ((float *)a->_data)[i] = DAT_0048da38[0];
            igFloatList *b = arg0->f52;
            c = b->_count;
            if (c != 0 && i >= 0 && i < c) ((float *)b->_data)[i] = DAT_0048da40[0];
            igUnsignedCharList *d = arg0->f56;
            c = d->_count;
            if (c != 0 && i >= 0 && i < c) ((unsigned char *)d->_data)[i] = GPR_00554988;
        }
    }
    for (j = 0; j < arg1; j++) {
        if (((float *)arg0->f52->_data)[j] != ((float *)arg0->f48->_data)[j]) { r = true; break; }
    }
    return r;
}
