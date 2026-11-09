#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
igObject *beBaseInfoDataList_Create(int);
int Memory_GetAllocatorBySelector(...);
int beMessenger_SendNamed(...);
int beMessenger_SelectReceivers(...);
int beMessenger_AppendString(...);
int beMessenger_AppendVec3(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetObjectCount(...);
beBaseInfoRam *beMessenger_GetObject(...);
int igObject_GetAllocator(...);
int Matrix44_GetTranslation(...);
struct R { char p[16]; int f16; };
R *igProperty_FindByName(...);
extern int DAT_004cfc80[4];
extern int DAT_004cfca0[4];
extern int DAT_0051d3a0[4];
extern int DAT_0051d3a8[4];
extern int DAT_0051d3b8[4];
extern int DAT_0051d3c8[4];
extern int DAT_0051d3d8[4];
extern float DAT_004e1058[4];
extern float DAT_004e105c[4];
extern float DAT_004e1060[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
int FUN_00443900(beNDMWMdlPEBase *arg0, beBaseInfoRam *arg1, int arg2, int arg3, int arg4, int arg5);
}
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
struct V3 { float x, y, z; };
/* Owning stack reference to the freshly created property list; released on scope exit once the ram
 * holds its own reference (reference count in the low 23 bits of _refCount). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
int FUN_00443900(beNDMWMdlPEBase *arg0, beBaseInfoRam *arg1, int arg2, int arg3, int arg4, int arg5) {
    igObject *s0;
    R *r;
    beBaseInfoRam *o;
    V3 t, c1, c2, c3;
    if (arg1->_dataList == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(a));
        s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        Rel::go((igObject *)arg1->_dataList);
        arg1->_dataList = (int)s0;
    }
    r = igProperty_FindByName((void *)arg1->_dataList, DAT_00585be0[0], DAT_0051d3a0);
    Matrix44_GetTranslation(r->f16 + 32, &t);
    if (arg3 == -1) {
        beMessenger_SendNamed(arg0->_messenger, DAT_0051d3a8, arg2, -1, DAT_0051d3b8);
        if (beMessenger_GetObjectCount(arg0->_messenger) == 0) goto fail;
        {
            o = beMessenger_GetObject(arg0->_messenger, 0);
            beMessenger_SelectReceivers(arg0->_messenger, DAT_0051d3a8, arg2, o->_ramNo);
            beMessenger_AppendString(arg0->_messenger, DAT_004cfc80[arg4]);
            c1 = t;
            beMessenger_AppendVec3(arg0->_messenger, &c1);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051d3c8);
            return o->_ramNo;
        }
        goto fail;
    }
    if (arg5 != 0) {
        beMessenger_SendNamed(arg0->_messenger, DAT_0051d3a8, arg2, arg3, DAT_004cfca0[arg4]);
    }
    beMessenger_SelectReceivers(arg0->_messenger, DAT_0051d3a8, arg2, arg3);
    c2 = t;
    beMessenger_AppendVec3(arg0->_messenger, &c2);
    c3.x = DAT_004e1058[0];
    c3.y = DAT_004e105c[0];
    c3.z = DAT_004e1060[0];
    beMessenger_AppendVec3(arg0->_messenger, &c3);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_0051d3d8);
    return arg3;
fail:
    return -1;
}
