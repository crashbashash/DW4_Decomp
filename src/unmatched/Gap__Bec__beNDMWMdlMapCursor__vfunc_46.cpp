#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
igObject *beBaseInfoDataList_Create(int);
int Memory_GetAllocatorBySelector(...);
int beMessenger_SendGroup(...);
int beMessenger_SendNamed(...);
int beMessenger_SendRam(...);
int beMessenger_GetMatrixCount(...);
int beMessenger_GetMatrix(...);
int igObject_GetAllocator(...);
int Matrix44_GetTranslation(...);
int Matrix44_SetTranslation(...);
struct PropertyEntry { char p[16]; int f16; };
PropertyEntry *igProperty_FindByName(...);
extern int DAT_0051dc38[4];
extern int DAT_0051dc80[4];
extern int DAT_0051dc88[4];
extern int DAT_0051dc98[4];
extern int DAT_0051dca8[4];
extern int DAT_0051dcb8[4];
extern int DAT_004cfed0[4];
extern int DAT_004e0858[4];
extern float DAT_004e1058[4];
extern float DAT_004e105c[4];
extern float DAT_004e1060[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* matching construct: inline release helper reproduces the retail inlined release of the previous data list */
struct RefRelease { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
struct Vec3f { float x, y, z; };
/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void Gap__Bec__beNDMWMdlMapCursor__vfunc_46(beNDMWMdlMapCursor *arg0, beBaseInfoRam *arg1);
void Gap__Bec__beNDMWMdlMapCursor__vfunc_46(beNDMWMdlMapCursor *arg0, beBaseInfoRam *arg1) {
    igObject *s0;
    PropertyEntry *r;
    int m1[16];
    int m2[16];
    Vec3f sum;
    Vec3f t;
    bool s2;
    bool s1;
    float *py = &sum.y;
    float *pz = &sum.z;
    s2 = false;
    sum.x = DAT_004e1058[0];
    *py = DAT_004e105c[0];
    *pz = DAT_004e1060[0];
    s1 = false;
    beMessenger_SendRam(arg0->_messenger, DAT_0051dc80, arg1->_ramNo, DAT_0051dc88);
    if (beMessenger_GetMatrixCount(arg0->_messenger) != 0) {
        beMessenger_GetMatrix(m1, arg0->_messenger, 0);
        Matrix44_GetTranslation(m1, &sum);
        s2 = true;
    }
    switch (arg1->_st0) {
    case 0:
        if (s2) {
            int a2 = ((beBaseInfo *)arg1->_parentInfo)->_name;
            int a3 = arg1->_ramNo;
            a2 = a2 ? a2 : (int)DAT_004e0858;
            beMessenger_SendNamed(arg0->_messenger, DAT_0051dc98, a2, a3, DAT_004cfed0[a3]);
            s1 = true;
            arg1->_st0 = 1;
            arg1->_st3 = 0;
            arg1->_st2 = 0;
            arg1->_st1 = 0;
        }
        break;
    case 1:
        if (!(s2 & 0xFF)) {
            int a2 = ((beBaseInfo *)arg1->_parentInfo)->_name;
            int a3 = arg1->_ramNo;
            a2 = a2 ? a2 : (int)DAT_004e0858;
            beMessenger_SendNamed(arg0->_messenger, DAT_0051dc98, a2, a3, DAT_0051dca8);
            arg1->_st0 = 0;
            arg1->_st3 = 0;
            arg1->_st2 = 0;
            arg1->_st1 = 0;
        }
        s1 = true;
        break;
    }
    if (s1) {
        beMessenger_SendGroup(arg0->_messenger, DAT_0051dcb8, DAT_0051dc88);
        if (beMessenger_GetMatrixCount(arg0->_messenger) != 0) {
            beMessenger_GetMatrix(m2, arg0->_messenger, 0);
            Matrix44_GetTranslation(m2, &t);
            sum.x += t.x;
            *py += t.y;
            *pz += t.z;
            if (arg1->_dataList == 0) {
                int alloc = igObject_GetAllocator(arg1);
                int a;
                if (GPR_00554c14 != 0) {
                    a = alloc;
                } else {
                    a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
                }
                igSmartPointer<igObject> ref(beBaseInfoDataList_Create(a));
                s0 = ref.p;
                if (s0 != 0) {
                    s0->_refCount++;
                }
                RefRelease::go((igObject *)arg1->_dataList);
                arg1->_dataList = (int)s0;
            }
            r = igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], DAT_0051dc38);
            *py = 0.0f;
            Matrix44_SetTranslation(r->f16 + 32, &sum);
        }
    }
}
