#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
igObject *beBaseInfoDataList_Create(int);
int Memory_GetAllocatorBySelector(...);
int beMessenger_SendGroup(...);
int beMessenger_GetMatrixCount(...);
int beMessenger_GetMatrix(...);
int igObject_GetAllocator(...);
int Matrix44_GetTranslation(...);
int Matrix44_SetTranslation(...);
struct PropertyRecord { char p[16]; int f16; };
PropertyRecord *igProperty_FindByName(...);
extern int DAT_0051dba8[4];
extern int DAT_0051dbb0[4];
extern int DAT_0051dbb8[4];
extern float DAT_004e1058[4];
extern float DAT_004e105c[4];
extern float DAT_004e1060[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct Vec3Float { float x, y, z; };
struct RamInfoArg { char p0[40]; igObject *m40; };
extern "C" void Gap__Bec__beNDMWMdlMapBase__vfunc_46(beNDMWMdlMapBase *arg0, RamInfoArg *arg1);
void Gap__Bec__beNDMWMdlMapBase__vfunc_46(beNDMWMdlMapBase *arg0, RamInfoArg *arg1) {
    PropertyRecord *r;
    int m[16];
    Vec3Float sum;
    Vec3Float t;
    int n, i;
    float *py = &sum.y;
    float *pz = &sum.z;
    sum.x = DAT_004e1058[0];
    *py = DAT_004e105c[0];
    *pz = DAT_004e1060[0];
    beMessenger_SendGroup(arg0->_messenger, DAT_0051dbb0, DAT_0051dbb8);
    if (beMessenger_GetMatrixCount(arg0->_messenger) != 0) {
        n = beMessenger_GetMatrixCount(arg0->_messenger);
        for (i = 0; i < n; i++) {
            {
                beMessenger_GetMatrix(m, arg0->_messenger, i);
                Matrix44_GetTranslation(m, &t);
                sum.x += t.x;
                *py += t.y;
                *pz += t.z;
            }
        }
        switch (n) {
        case 0: break;
        case 1: break;
        case 2: sum.x /= 2.0f; *pz /= 2.0f; break;
        case 3: sum.x /= 3.0f; *pz /= 3.0f; break;
        case 4: sum.x /= 4.0f; *pz /= 4.0f; break;
        }
        sum.x = -sum.x;
        *py = 0.0f;
        *pz = -*pz;
    }
    if (arg1->m40 == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(a));
        igObject *s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        igObject *old = arg1->m40;
        if (old != 0) {
            --old->_refCount;
            if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
        }
        arg1->m40 = s0;
    }
    r = igProperty_FindByName(arg1->m40, DAT_00585be0[0], DAT_0051dba8);
    Matrix44_SetTranslation(r->f16 + 32, &sum);
}
