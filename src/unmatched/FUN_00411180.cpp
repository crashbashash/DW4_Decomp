/* FUN_00411180 - swap of two kind slots in the power-socket list (equip status window) */
#include "dw4/reflected.h"
extern "C" {
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
int beMessenger_SelectGroup(...);
int beMessenger_SelectReceivers(...);
void igObject_Destroy(void *);
extern int DAT_00519ba0[4];
extern int DAT_00519c10[4];
extern int DAT_00519c18[4];
extern int DAT_00519c40[4];
extern int DAT_00519cb8[4];
}
#define SEL(d) beMessenger_SelectGroup(p->_messenger, d)
#define API(d) beMessenger_AppendInt(p->_messenger, d)
#define DSP(d) beMessenger_DispatchSelected(p->_messenger, d)
/* Owning stack reference to one of the two swapped socket items, taken from the list slot and
 * released on scope exit (reference count in the low 23 bits of _refCount).  The out-of-line copy
 * the exception table names is the retail body 0x003c1520 (config/SLUS-20836/unit-objects.json, duplicate
 * __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igObject *volatile p; /* matching construct: volatile member keeps every use a reload from the frame slot (register colouring) */
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
#define SLOT(IX, V_) { igObject *v = (V_); int r = (IX); beNDMWItemBaseList *l = (beNDMWItemBaseList *)p->_powerSocket; igObject *old; if (v != 0) { v->_refCount = v->_refCount + 1; } old = ((igObject **)l->_data)[r]; if (old != 0) { --old->_refCount; if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old); } if (l->_count != 0 && r >= 0 && r < l->_count) { ((igObject **)l->_data)[r] = v; } }
extern "C" void FUN_00411180(beNDMWStatusCtrlBaseEquip *p)
{
    igObject *t;
    /* both items are retained for the duration of the swap */
    ObjectRef kindItem((igObject *)((int *)((beNDMWItemBaseList *)p->_powerSocket)->_data)[p->_kindListPos]);
    t = kindItem.p; if (t != 0) { t->_refCount = t->_refCount + 1; }
    ObjectRef retItem((igObject *)((int *)((beNDMWItemBaseList *)p->_powerSocket)->_data)[p->_retCode]);
    t = retItem.p; if (t != 0) { t->_refCount = t->_refCount + 1; }
    if (p->_kindListPos == p->_retCode || ((p->_kindListPos == 0 || p->_retCode == 0) && (kindItem.p == 0 || retItem.p == 0))) {
        SEL(DAT_00519c10); API(p->_playerNo); DSP(DAT_00519c18);
    } else {
        SLOT(p->_kindListPos, retItem.p);
        SLOT(p->_retCode, kindItem.p);
        beMessenger_SelectReceivers(p->_messenger, DAT_00519ba0, 0, 0); API(p->_playerNo); DSP(DAT_00519c40);
        SEL(DAT_00519c10); API(p->_playerNo); DSP(DAT_00519cb8);
        SLOT(p->_kindListPos, kindItem.p);
        SLOT(p->_retCode, retItem.p);
        beMessenger_SelectReceivers(p->_messenger, DAT_00519ba0, 0, 0); API(p->_playerNo); DSP(DAT_00519c40);
    }
}
