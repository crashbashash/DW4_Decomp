/* Gap::Core::igObject::vfunc_38 (0x00391b40, 420 bytes): beModelCtrl per-instance hook.
 *
 * Make sure the ram has a data list (create one on demand, pooled allocator unless the global
 * selector flag is clear), then dispatch on which named property the parent info carries:
 * FUN_00390f80 when the first property's node is armed, FUN_003915a0 for the second property. */
#include "dw4/reflected.h"
/* Minimal view of the property node: only the word at +8 is tested here. */
struct NodeView { int _vtable; unsigned int _refCount; int f8; };
extern "C" {
igObject *beBaseInfoDataList_Create(int);
int FUN_00390f80(int, beBaseInfo *, beBaseInfoRam *, int, beModelCtrlInfoRamData *);
int FUN_003915a0(int, beBaseInfo *, beBaseInfoRam *, int, beModelCtrlInfoRamData *);
int Memory_GetAllocatorBySelector(int);
int igObject_Destroy(igObject *);
int igObject_GetAllocator(beBaseInfoRam *);
beModelCtrlInfoRamData *igProperty_FindByName(int, int, int *);
extern int DAT_0050ef60[4];
extern int DAT_0050efd8[4];
extern int DAT_0050efe0[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void Gap__Core__igObject__vfunc_38(int arg0, beBaseInfoRam *arg1);
}
/* Owning stack reference to the freshly created data list: constructed from the object and released
 * on scope exit (reference count in the low 23 bits of _refCount).  The out-of-line copy the
 * exception table names is the retail body 0x0033e9c0 (config/SLUS-20836/unit-objects.json, duplicate
 * __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
void Gap__Core__igObject__vfunc_38(int arg0, beBaseInfoRam *arg1) {
    beBaseInfo *info;
    int work;
    beModelCtrlInfoRamData *prop;
    int allocator;
    igObject *list;
    igObject *old;
    info = (beBaseInfo *)arg1->_parentInfo;
    if (arg1->_dataList == 0) {
        allocator = igObject_GetAllocator(arg1);
        allocator = (GPR_00554c14 != 0) ? allocator : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        ObjectRef ref(beBaseInfoDataList_Create(allocator));
        list = ref.p;
        if (list != 0) {
            list->_refCount = list->_refCount + 1;
        }
        old = (igObject *)arg1->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        arg1->_dataList = (int)list;
    }
    work = igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_0050ef60[0])->_work;
    prop = igProperty_FindByName(info->_dataList, DAT_00585be0[0], &DAT_0050efd8[0]);
    if (prop != 0) {
        if (((NodeView *)prop->_node)->f8 != 0) {
            FUN_00390f80(arg0, info, arg1, work, prop);
        }
    } else {
        prop = igProperty_FindByName(info->_dataList, DAT_00585be0[0], &DAT_0050efe0[0]);
        if (prop != 0) {
            FUN_003915a0(arg0, info, arg1, work, prop);
        }
    }
}
