/* 0x00399940 - beModelCtrlSCEffect vfunc 21: asks the gene model for its ram number, then dispatches the effect
 * request (owner name, sequence, lock target, offset, rotation, position lock) to the selected receivers. The ram
 * object's data list is created on first use and held in an ObjectRef whose destructor the exception table names. */
#include "dw4/reflected.h"
extern "C" {
struct PropertyEntry { char pad[20]; struct PropertyValueObj *f20; };
struct PropertyValueObj { char pad[220]; int *f220; int f224; };
struct Vec3f { float x, y, z; };
igObject *beBaseInfoDataList_Create(int);
int Memory_GetAllocatorBySelector(int);
int beMessenger_AppendBool(int, unsigned char);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, ...); /* string argument is a name pointer or a 4-byte arena handle (_seqName) */
int beMessenger_AppendVec3(int, Vec3f *);
int beMessenger_DispatchSelected(int, int *);
beBaseInfoRam *beMessenger_GetObject(int, int); /* hypothesis: the receiver objects are the matched beBaseInfoRam entries of beMessengerWork._findRamList */
int beMessenger_GetObjectCount(int);
int beMessenger_SelectReceivers(int, int *, int, int);
int beMessenger_SendNamed(int, int *, int, int, int *);
void igObject_Destroy(igObject *);
int igObject_GetAllocator(beBaseInfoRam *);
PropertyEntry *igProperty_FindByName(int, int, int *);
extern int DAT_004e0858[4];
extern int DAT_0050f410[4];
extern int DAT_0050f468[4];
extern int DAT_0050f478[4];
extern int DAT_0050f488[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the freshly created data list: constructed from the object and released on scope
 * exit (reference count in the low 23 bits of _refCount).  The out-of-line copy the exception table names is the
 * retail body 0x0033e9c0 (config/SLUS-20836/unit-objects.json, duplicate __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" int Gap__Bec__beModelCtrlSCEffect__vfunc_21(beModelCtrlSCEffect *arg0, beBaseInfoRam *arg1) {
    beBaseInfo *s2;
    beBaseInfoManager *s1;
    int *v;
    int *str;
    PropertyValueObj *s0;
    Vec3f sp70;
    Vec3f sp60;
    s1 = (beBaseInfoManager *)arg1->_parentManager;
    s2 = (beBaseInfo *)arg1->_parentInfo;
    beMessenger_SendNamed(s1->_messenger, &DAT_0050f468[0], arg0->_modelName, -1, &DAT_0050f478[0]);
    if (beMessenger_GetObjectCount(s1->_messenger) != 0) {
    arg0->_geneRamNo = beMessenger_GetObject(s1->_messenger, 0)->_ramNo;
    beMessenger_SelectReceivers(s1->_messenger, &DAT_0050f468[0], arg0->_modelName, arg0->_geneRamNo);
    beMessenger_AppendInt(s1->_messenger, arg1->_ramNo);
    v = (int *)s2->_name;
    if (v != 0) str = v; else str = &DAT_004e0858[0];
    beMessenger_AppendString(s1->_messenger, str);
    beMessenger_AppendString(s1->_messenger, arg0->_seqName);
    if (arg1->_dataList == 0) {
        int a = igObject_GetAllocator(arg1);
        ObjectRef created(beBaseInfoDataList_Create(GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0])));
        igObject *t = created.p;
        if (t != 0) t->_refCount = t->_refCount + 1;
        igObject *old = (igObject *)arg1->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
        }
        arg1->_dataList = (int)t;
    }
    s0 = igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_0050f410[0])->f20;
    if (s0->f220 == 0) {
        v = (int *)s2->_name;
        if (v != 0) str = v; else str = &DAT_004e0858[0];
        beMessenger_AppendString(s1->_messenger, str);
        beMessenger_AppendInt(s1->_messenger, arg1->_ramNo);
    } else {
        beMessenger_AppendString(s1->_messenger, s0->f220);
        beMessenger_AppendInt(s1->_messenger, s0->f224);
    }
    sp70.x = ((float *)arg0->_offset)[0];
    sp70.y = ((float *)arg0->_offset)[1];
    sp70.z = ((float *)arg0->_offset)[2];
    beMessenger_AppendVec3(s1->_messenger, &sp70);
    sp60.x = ((float *)arg0->_rotation)[0];
    sp60.y = ((float *)arg0->_rotation)[1];
    sp60.z = ((float *)arg0->_rotation)[2];
    beMessenger_AppendVec3(s1->_messenger, &sp60);
    beMessenger_AppendBool(s1->_messenger, arg0->_isPositionLock);
    beMessenger_DispatchSelected(s1->_messenger, &DAT_0050f488[0]);
    } else {
        return 0;
    }
    return arg0->_isSeqDead != 0;
}
