#include "dw4/reflected.h"
static inline int countOf(const igObjectList *l) { return l->_count; }
extern "C" {
void igObject_Destroy(beUnicodeObj *);
struct W { char pad[12]; igObjectList *f12; };
int FUN_003f9570(beNDMWGameRam *);
int FUN_00236f80(int, int);
int FUN_00382eb0(beUnicodeObj **, int, int);
int beUnicodeObj_AllocateBuffer(beUnicodeObj *, int);
beUnicodeObj *FUN_003614f0(int);
int igObject_GetAllocator(beNDMWGameRam *);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(igObjectList *, beUnicodeObj *);
W *igProperty_GetRecordFolder(int, char *);
extern char DAT_00518828[];
extern int DAT_00587108[4];
extern int DAT_00589678[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the new name text; released on scope exit, after the name list has
 * retained it (reference count in the low 23 bits of _refCount). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void FUN_003f96e0(beNDMWGameRam *arg0, int arg1, void *arg2, int *arg3) {
    int s0;
    int al;
    igObjectList *l;
    int n, n2, i, j;
    unsigned short *src;
    unsigned short *base;
    int k;
    unsigned short *dst;
    igObject *p;
    FUN_003f9570(arg0);
    s0 = ((int *)(((igObjectList *)arg0->_playerDataListList)->_data))[arg1];
    al = igObject_GetAllocator(arg0);
    al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(DAT_00587108[0]);
    igSmartPointer<beUnicodeObj> rb(FUN_003614f0(al));
    beUnicodeObj_AllocateBuffer(rb.p, 8);
    {
        /* The looked-up name is an out-parameter the lookup retains; it is released by hand rather
         * than by a destructor. */
        beUnicodeObj *ra;
        int sel = *arg3;
        int table = FUN_00236f80(arg0->_insight, DAT_00589678[0]);
        FUN_00382eb0(&ra, table, sel);
        k = 0;
        src = (unsigned short *)ra->_buffer;
        base = (unsigned short *)rb.p->_buffer;
        dst = base;
        for (;;) {
            *dst = *src;
            if (*src == 0) break;
            k++; src++; dst++;
            if (k >= 8) break;
        }
        for (; k < 8; k++) base[k] = 0;
        {
            beUnicodeObj *o;
            if ((o = ra) != 0) {
                --o->_refCount;
                if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
            }
        }
    }
    l = igProperty_GetRecordFolder(s0, DAT_00518828)->f12;
    if (countOf(l) != 0) {
        n = l->_count;
        for (i = 0; i < n; i++) {
            p = ((igObject **)l->_data)[i];
            if (p != 0) {
                p->_refCount = p->_refCount - 1;
                if ((p->_refCount & 0x7FFFFF) == 0) igObject_Destroy((beUnicodeObj *)p);
            }
        }
        n2 = l->_count;
        for (j = 0; j < n2; j++) ((igObject **)l->_data)[j] = 0;
        l->_count = 0;
    }
    ObjectList_AppendRetained(l, rb.p);
}
