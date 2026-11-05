/* MDLisSeqName (0x003742e0, 304 bytes).
 *
 * Answer whether the first model-control info ram's sequence code name equals the given string.
 * When the ram has no data list yet, create one (pooled allocator unless the global selector flag
 * is clear), retain it into the ram and release the creating reference on scope exit. */
#include "dw4/reflected.h"
extern "C" {
igObject *beBaseInfoDataList_Create(...);
int Memory_GetAllocatorBySelector(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
beModelCtrlInfoRamData *igProperty_FindByName(...);
int igStrCmp(const char *, const char *);
extern beBaseInfoRam *DAT_0058a1e0[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern int DAT_0050dd40[4];
extern unsigned char GPR_00554c14;
int MDLisSeqName(char *arg0);
}
/* Owning stack reference to the freshly created data list: constructed from the object and released
 * on scope exit (reference count in the low 23 bits of _refCount).  The out-of-line copy the
 * exception table names is the retail body 0x0033e9c0 (config/SLUS-20836/unit-objects.json, duplicate
 * __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    /* matching construct: accessor read — reading the member through `this` (not `ref.p`) keeps the
     * ram pointer in s0 and the new list in s1 as retail; a direct member read swaps them. */
    igObject *get() const { return p; }
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
int MDLisSeqName(char *arg0) {
    beBaseInfoRam *h = DAT_0058a1e0[0];
    if (h->_dataList == 0) {
        int al;
        igObject *o;
        al = igObject_GetAllocator(h);
        al = GPR_00554c14 != 0 ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        ObjectRef ref(beBaseInfoDataList_Create(al));
        igObject *s0 = ref.get();
        if (s0 != 0) {
            s0->_refCount = s0->_refCount + 1;
        }
        o = (igObject *)h->_dataList;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        h->_dataList = (int)s0;
    }
    beModelCtrlInfoRamData *p = igProperty_FindByName(h->_dataList, DAT_00585be0[0], &DAT_0050dd40[0]);
    return igStrCmp((const char *)((beModelCtrlInfoWork *)p->_work)->_seqCodeName, arg0) == 0;
}
