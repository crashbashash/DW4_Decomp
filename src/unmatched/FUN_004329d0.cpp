/* Per player slot 0..3 query the messenger and gather values and lists. The per-player weapon-
 * number list is held in an RP (owning reference) whose destructor the exception table names
 * (retail body 0x00150eb0.json duplicate __dt__2RPFv). Register-id notes: the byte-offset
 * induction variable shares the function-level `idx` (the first append's index web, then the
 * offset web), which gives it a later node id than the stack reload of the new list pointer. */
#include "dw4/reflected.h"
extern "C" {
extern int beMessenger_SendGroup(...);
extern int beMessenger_SelectGroup(...);
extern int beMessenger_AppendInt(...);
extern int beMessenger_DispatchSelected(...);
extern int List_Resize(...);
extern int ObjectList_AppendRetained(...);
extern int igObject_Destroy(...);
extern int FUN_002caa70(...);
extern void *Memory_GetAllocatorBySelector(...);
extern void *igObject_GetAllocator(...);
/* property-record views: igProperty_* return records of no reflected class, so these stay local (hypothesis) */
struct Item { int p[3]; int f12; };
struct Rec { int p[3]; igObjectList *f12; };
struct RecB { int p[3]; unsigned char f12; };
struct RecI { int p[3]; int f12; };
extern void *beMessenger_GetObject(...);
extern RecI *igProperty_GetRecord(...);
extern RecB *igProperty_GetRecordByte(...);
extern Rec *igProperty_GetRecordFolder(...);
extern int DAT_0051b398[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b810[4];
extern int DAT_0051b870[4];
extern int DAT_0051bac0[4];
extern int DAT_0051bc40[4];
extern int DAT_0051bc48[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void FUN_004329d0(beNDMWShopCtrlDigilabo *self);
}
/* Owning stack reference to the new weapon-number list: constructed from the freshly created list and released on
 * scope exit (reference count in the low 23 bits of _refCount).  The out-of-line copy the exception table names is
 * the retail body 0x00150eb0 (config/SLUS-20836/unit-objects.json, duplicate __dt__2RPFv). */
class RP {
public:
    igIntList *p;
    RP(igIntList *o) : p(o) {}
    ~RP() { igIntList *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
void FUN_004329d0(beNDMWShopCtrlDigilabo *self) {
    void *obj;
    RecB *rb;
    int i;
    int val;
    igObjectList *fold;
    void *alloc;
    int j;
    Item *it;
    int idx;

    beMessenger_SendGroup(self->_messenger, &DAT_0051b398[0], &DAT_0051b810[0]);
    igProperty_GetRecord(beMessenger_GetObject(self->_messenger, 0), &DAT_0051bc40[0]);
    i = 0;
    do {
        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
        beMessenger_AppendInt(self->_messenger, i);
        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
        obj = beMessenger_GetObject(self->_messenger, 0);
        rb = igProperty_GetRecordByte(obj, &DAT_0051b870[0]);
        if (rb->f12 != 0) {
            {
                igIntList *l = (igIntList *)self->_playerNoList;
                idx = l->_count;
                if (idx < l->_capacity) {
                    l->_count = *(volatile int *)&l->_count + 1;
                } else {
                    List_Resize(l, idx + 1, 4);
                }
                ((int *)l->_data)[idx] = i;
            }
            {
                int idx2;
                igIntList *l;
                val = igProperty_GetRecord(obj, &DAT_0051bac0[0])->f12;
                l = (igIntList *)self->_digimonNoList;
                idx2 = l->_count;
                if (idx2 < l->_capacity) {
                    l->_count = *(volatile int *)&l->_count + 1;
                } else {
                    List_Resize(l, idx2 + 1, 4);
                }
                ((int *)l->_data)[idx2] = val;
            }
            fold = igProperty_GetRecordFolder(obj, &DAT_0051bc48[0])->f12;
            alloc = igObject_GetAllocator(self);
            alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
            RP lst((igIntList *)FUN_002caa70(alloc));
            j = 0;
            if (0 < fold->_count) {
                idx = 0;
                do {
                    it = *(Item **)&((char *)fold->_data)[idx];
                    if (it != 0) {
                        int idx3;
                        igIntList *l = lst.p;
                        val = it->f12;
                        idx3 = l->_count;
                        if (idx3 < l->_capacity) {
                            l->_count = *(volatile int *)&l->_count + 1;
                        } else {
                            List_Resize(l, idx3 + 1, 4);
                        }
                        ((int *)l->_data)[idx3] = val;
                    }
                    j += 1;
                    idx += 4;
                } while (j < fold->_count);
            }
            ObjectList_AppendRetained(self->_wpuNoListList, lst.p);
        }
        i += 1;
    } while (i < 4);
}
