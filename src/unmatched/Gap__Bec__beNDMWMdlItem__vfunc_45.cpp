#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
igObject *beBaseInfoDataList_Create(int);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
struct ItemRecord { char p[20]; int f20; };
struct PropertyFolder { char p[12]; igObjectList *f12; };
struct PropertyByteArrayHolder { char p[12]; igUnsignedCharList *f12; };
struct PropertyRecord { char p[20]; beNDMWMdlItemInfoWork *q; };
PropertyRecord *igProperty_FindByName(...);
int FUN_00448050(...);
int beMessenger_AppendBool(...);
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetBoolCount(...);
int beMessenger_GetInt(...);
int beMessenger_GetObject(...);
int beMessenger_PopArgContext(...);
int beMessenger_PushArgContext(...);
int beMessenger_SelectGroup(...);
int beMessenger_SendGroup(...);
int beMessenger_SendNamed(...);
int ObjectList_AppendRetained(...);
PropertyFolder *igProperty_GetRecordFolder(...);
PropertyByteArrayHolder *igProperty_GetRecordArray(...);
extern int DAT_004e0858[16];
extern int DAT_0051cea8[16];
extern int DAT_0051cf58[16];
extern int DAT_0051cf60[16];
extern int DAT_0051cfc8[16];
extern int DAT_0051d0b8[16];
extern int DAT_0051d0c8[16];
extern int DAT_0051d0d8[16];
extern int DAT_0051d0e8[16];
extern int DAT_0051d0f8[16];
extern int DAT_00585be0[16];
extern int DAT_00587110[16];
extern unsigned char GPR_00554a74;
extern unsigned char GPR_00554c14;
}
/* matching construct: the inlined release of the previous data list is a static member so the compiler expands it as retail does */
struct ReleaseRefInline { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
class MdlItemVirtual { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42();  virtual void vX(beNDMWGameRamInfoRam *); char p[16]; };
/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void Gap__Bec__beNDMWMdlItem__vfunc_45(MdlItemVirtual *arg0, beNDMWGameRamInfoRam *arg1);
void Gap__Bec__beNDMWMdlItem__vfunc_45(MdlItemVirtual *arg0, beNDMWGameRamInfoRam *arg1) {
    beNDMWMdlItem *self = (beNDMWMdlItem *)arg0;
    igObject *s0;
    beNDMWMdlItemInfoWork *s5;
    int s2;
    bool s4;
    int s3;
    if (arg1->_dataList == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        ObjectRef ref(beBaseInfoDataList_Create(a));
        s0 = ref.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        ReleaseRefInline::go((igObject *)arg1->_dataList);
        arg1->_dataList = (int)s0;
    }
    s5 = igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], DAT_0051cf58)->q;
    if (beMessenger_GetBoolCount(self->_messenger) == 0 && s5->_isNamed != 0 && s5->_isDispName != 0) {
        s2 = beMessenger_GetInt(self->_messenger, 0);
        if (s2 == s5->_dispPlayerRamNo) {
            s4 = true;
            beMessenger_PushArgContext(self->_messenger);
            beMessenger_SelectGroup(self->_messenger, DAT_0051cf60);
            beMessenger_AppendInt(self->_messenger, s2);
            beMessenger_DispatchSelected(self->_messenger, DAT_0051d0b8);
            s3 = beMessenger_GetObject(self->_messenger, 0);
            unsigned t1 = s5->_kind - 3;
            switch (t1) {
            case 0:
            case 1:
            case 6:
                if (igProperty_GetRecordFolder(s3, DAT_0051d0c8)->f12->_count >= 36) {
                    s4 = false;
                }
                break;
            case 2:
            case 3:
            case 5: {
                igObjectList *l = igProperty_GetRecordFolder(s3, DAT_0051d0d8)->f12;
                if (((ItemRecord **)l->_data)[FUN_00448050(l, s5->_recNo)]->f20 >= 9) {
                    s4 = false;
                }
                break;
            }
            }
            if (s4) {
                igObjectList *a2 = igProperty_GetRecordFolder(s3, DAT_0051d0c8)->f12;
                unsigned t2 = s5->_kind - 3;
            switch (t2) {
                case 0:
                case 1:
                case 6:
                    ObjectList_AppendRetained(a2, s5->_itemObject);
                    break;
                case 2:
                case 3:
                case 5: {
                    igObjectList *l = igProperty_GetRecordFolder(s3, DAT_0051d0d8)->f12;
                    ItemRecord *it = ((ItemRecord **)l->_data)[FUN_00448050(l, s5->_recNo)];
                    int v = it->f20;
                    if (v != 9) {
                        it->f20 = v + 1;
                    }
                    break;
                }
                case 4: {
                    beMessenger_SendGroup(self->_messenger, DAT_0051cf60, DAT_0051d0e8);
                    int o = beMessenger_GetObject(self->_messenger, 0);
                    int idx = s5->_recNo;
                    igUnsignedCharList *ar = igProperty_GetRecordArray(o, DAT_0051d0f8)->f12;
                    int n = ar->_count;
                    if (n != 0 && idx >= 0 && idx < n) {
                        *(unsigned char *)(idx + (int)ar->_data) = GPR_00554a74;
                    }
                    break;
                }
                }
                int f8 = arg1->_ramNo;
                beNDMWGameRamInfo *info = (beNDMWGameRamInfo *)arg1->_parentInfo;
                int *name = info->_name ? (int *)info->_name : DAT_004e0858;
                beMessenger_SendNamed(self->_messenger, DAT_0051cea8, name, f8, DAT_0051cfc8);
                arg0->vX(arg1);
            }
            beMessenger_PopArgContext(self->_messenger);
            if (s4) {
                beMessenger_AppendBool(self->_messenger, 1);
            }
        }
    }
}
