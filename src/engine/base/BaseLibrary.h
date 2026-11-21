#ifndef DW4_BASE_LIBRARY_H
#define DW4_BASE_LIBRARY_H

#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/support/typecast.h"
#include "dw4/core/igTDataList.h"
#include "dw4/core/igMetaObject.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igObjectSystem.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igResult.h"
#include "dw4/core/StringPool.h"
#include "dw4/core/igMetaField.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObjectList.h"
#include "dw4/core/igDataLists.h"
#include "dw4/core/igStringObj.h"
#include "dw4/core/igMemory.h"
#include "dw4/core/igBoolList.h"
#include "dw4/core/igBoolMetaField.h"
#include "dw4/core/igCharMetaField.h"
#include "dw4/core/igCompoundMetaField.h"
#include "dw4/core/igDirectory.h"
#include "dw4/core/igDoubleMetaField.h"
#include "dw4/core/igEnumMetaField.h"
#include "dw4/core/igFloatMetaField.h"
#include "dw4/core/igIGBFile.h"
#include "dw4/core/igInfo.h"
#include "dw4/core/igInfoList.h"
#include "dw4/core/igIntList.h"
#include "dw4/core/igIntMetaField.h"
#include "dw4/core/igLongMetaField.h"
#include "dw4/maths/igMatrix44fMetaField.h"
#include "dw4/core/igMemoryRefMetaField.h"
#include "dw4/core/igMetaObjectList.h"
#include "dw4/core/igMetaObjectListList.h"
#include "dw4/core/igObjectListList.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igRawRefMetaField.h"
#include "dw4/core/igRegistry.h"
#include "dw4/core/igShortMetaField.h"
#include "dw4/core/igStringMetaField.h"
#include "dw4/core/igStringRefList.h"
#include "dw4/core/igStringRefListList.h"
#include "dw4/core/igUnsignedCharMetaField.h"
#include "dw4/core/igUnsignedIntMetaField.h"
#include "dw4/core/igUnsignedLongMetaField.h"
#include "dw4/core/igUnsignedShortMetaField.h"
#include "dw4/maths/igVec2fMetaField.h"
#include "dw4/maths/igVec3fMetaField.h"
#include "dw4/maths/igVec4fMetaField.h"
#include "dw4/maths/igVec4ucMetaField.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/maths/igMatrix44d.h"
#include "dw4/scenegraph/igTransform.h"
#include "dw4/scenegraph/igSceneInfo.h"
#include "dw4/scenegraph/igAnimationDatabase.h"
#include "dw4/scenegraph/igSegment.h"
#include "dw4/support/ClassRegistration.h"
#include <stdio.h>
#include "dw4/support/emptyString.h"
#include "dw4/core/igStringRef.h"
#include "dw4/core/internalNonRefCountedObjectList.h"
#include "dw4/support/list-services.h"
#include "dw4/base/igOptBase.h"
#include "dw4/scenegraph/igNonRefCountedNodeList.h"
#include "dw4/base/igIterateGraph.h"

typedef void (*igMetaObjectCallback)();

extern int DAT_0052bea0[4];
extern igMetaObject *g_igCompoundList_metaObject;
extern int g_igCompoundList_vtable[4];
extern igMetaObject *g_igOptBase_metaObject;
extern igMetaObject *g_igOptInterface_metaObject;
extern int g_igOptInterface_vtable[4];
extern igMetaObject *g_igInterface_metaObject;
extern igMetaObject *g_igOptConfiguration_metaObject;
extern int g_igOptConfiguration_vtable[4];
extern igMetaObject *g_igBase_metaObject;
extern igMetaObject *g_igMessageInterface_metaObject;
extern int g_igMessageInterface_vtable[4];
extern igMetaObject *g_igMessageList_metaObject;
extern int g_igMessageList_vtable[4];
extern igMetaObject *g_igMessageBase_metaObject;
extern int g_igMessageBase_vtable[4];
extern igMetaObject *g_igInterfaced_metaObject;
extern igMetaObject *g_igLogInterface_metaObject;
extern int g_igLogInterface_vtable[4];
extern igMetaObject *g_igLockInterface_metaObject;
extern int g_igLockInterface_vtable[4];
extern igMetaObject *g_igLockBase_metaObject;
extern igMetaObject *g_igListenerInterface_metaObject;
extern int g_igListenerInterface_vtable[4];
extern igMetaObject *g_igListenerListList_metaObject;
extern int g_igListenerListList_vtable[4];
extern igMetaObject *g_igListenerList_metaObject;
extern int g_igListenerList_vtable[4];
extern igMetaObject *g_igListenerBase_metaObject;
extern int g_igListenerBase_vtable[4];
extern igMetaObject *g_igIterator_metaObject;
extern igMetaObject *g_igIterateGraph_metaObject;
extern int g_igIterateGraph_vtable[4];
extern igMetaObject *g_igIterateField_metaObject;
extern int g_igIterateField_vtable[4];
extern igMetaObject *g_igIterateDerived_metaObject;
extern int g_igIterateDerived_vtable[4];
extern igMetaObject *g_igItemInterface_metaObject;
extern int g_igItemInterface_vtable[4];
extern igMetaObject *g_igItemDataBaseList_metaObject;
extern int g_igItemDataBaseList_vtable[4];
extern igMetaObject *g_igItemDataBaseField_metaObject;
extern int g_igItemDataBaseField_vtable[4];
extern igMetaObject *g_igItemBase_metaObject;
extern int g_igInterface_vtable[4];
extern igMetaObject *g_igFileInfoList_metaObject;
extern int g_igFileInfoList_vtable[4];
extern igMetaObject *g_igFileInfo_metaObject;
extern int g_igFileInfo_vtable[4];
extern int DAT_00560f60[4];
extern int DAT_00560f68[4];
extern int DAT_00560f80[4];
extern int DAT_00560f98[4];
extern int DAT_00561010[4];

extern "C" {

int FUN_002fdef0(int, int);
struct GraphIterator;
int FUN_0022ad00(struct GraphIterator *it);
}

#include "dw4/base/igOptBase.h"
#include "dw4/attrs/igObjectList.h"
struct Obj { int *vt; char pad[28]; };
struct Obj_2 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
struct Obj_3 { int *vt; char pad[4]; };
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct W { int *vt; int f[11]; };
typedef struct { int *vt; int pad[7]; } Obj_4;
union U_2 { int vt; int w[12]; void *p[12]; char b[48]; };
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U_3 { int vt; char b[48]; };
struct S_temp_a0 { char pad4[4]; int f4; };
struct Obj_5 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
struct T_2 { int w0; int refs; };
struct T_3 { int word0; int references; };
struct Obj_6 {
    int *vt; char p4[8]; T_3 *m12; T_3 *m16; char tail[12]; 
    inline void rel12() {
        T_3 **self = &m12;
        if (self) {
            T_3 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy((igObject *)object);
            }
        }
    }
    inline void rel16() {
        T_3 **self = &m16;
        if (self) {
            T_3 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy((igObject *)object);
            }
        }
    }
};
union U_4 { int vt; char b[16]; };
struct F { int *vt; int pad[1]; int *ref; int pad2[1]; };
struct Obj_7 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
struct S_obj { char pad4[4]; int f4; char pad8[20]; int f28; char pad32[24]; int f56; int f60; };
union U_5 { int vt; char b[64]; };
struct Obj_8 { int *vt; int w[7]; };
struct R { int vt; unsigned int rc; };
class DW4VC_108 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, char *); };
class igInterfaceView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void vfunc_22();
    unsigned int _refCount;
    char _pad8[20];
    igInterfaceView *_logInterface;
};
typedef struct R_2 { int w0; int refs; } R_2;
typedef struct S_2 { R_2 *a; R_2 *b; R_2 *c; } S_2;
struct Obj_9 { int w0; unsigned refs; };
template <class T> struct igSmartPointer_2 {
    T *p;
    ~igSmartPointer_2() {
        T *q = p;
        if (q != 0) {
            q->refs = q->refs - 1;
            if ((q->refs & 0x7fffff) == 0) igObject_Destroy((igObject *)q);
        }
    }
    void operator=(T *n) {
        T *q = p;
        if (q != 0) {
            q->refs = q->refs - 1;
            if ((q->refs & 0x7fffff) == 0) igObject_Destroy((igObject *)q);
        }
        p = n;
    }
};
struct S_3 {
    igSmartPointer_2<Obj_9> a; igSmartPointer_2<Obj_9> b; igSmartPointer_2<Obj_9> c;
};
struct R_3 { int a, b, c, d; };
struct RecoveryString {
    void *p;
    RecoveryString() {}
    RecoveryString(void *token) : p(token) {}
    ~RecoveryString() { if (p != 0) { int *t = (int *)((char *)p - 8); int v = *(int *)((char *)p - 4) - 1; *(int *)((char *)p - 4) = v; if (v == 0) StringChunk_ReleaseHeader((StringChunk *)*t, (StringTokenHeader *)t); } }
};
class Obj_10 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual R_3 vf(RecoveryString *, int); };
struct L { char p[8]; int n; };
struct UIntList { char pad[8]; int count; int cap; unsigned int *data; };
struct IntList { char pad[8]; int count; int cap; int *data; };
struct IntListList { char pad[8]; int count; int cap; IntList **data; };
struct NameTableList { char pad[8]; int count; int cap; L **data; };
struct ItemRegistry { char pad[36]; UIntList *kinds; IntListList *items; NameTableList *names; int typeCount; };
extern "C" void FUN_002299c0(ItemRegistry *self);
struct InterfaceItem : public igObject { };
struct StringRef {
    char *s;
    StringRef(const StringRef &other) : s(other.s) {
        if (s != 0) {
            *(int *)(s - 4) = *(int *)(s - 4) + 1;
        }
    }
    ~StringRef() {
        if (s != 0) {
            int *header = (int *)(s - 8);
            if (--header[1] == 0) {
                StringChunk_ReleaseHeader((StringChunk *)header[0], (StringTokenHeader *)header);
            }
        }
    }
};
typedef struct Iterator : public igObject { } Iterator;
struct StringRef_2 {
    int *p;
    StringRef_2(const StringRef_2 &other) : p(other.p) { if (p != 0) { p[-1] = p[-1] + 1; } }
    ~StringRef_2() {
        if (p != 0) {
            int *header = p - 2;
            int count = p[-1] - 1;
            p[-1] = count;
            if (count == 0) { StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header); }
        }
    }
};
struct IteratorType {};
class ItemInterface { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void vX(const StringRef_2 &, int, int); virtual void vfunc_28(const StringRef_2 &, int, int); };
/* An igItemBase instance as FUN_002299c0 queries it: slot 29 the item kind, slots 30 and 31 two
 * flags, slot 32 the item name. */
class igItemBaseDispatchView : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual int vfunc_29(); virtual unsigned char vfunc_30(); virtual unsigned char vfunc_31(); virtual StringRef_2 vfunc_32(); };
typedef struct S1 { char pad4[4]; int f4; } S1;
typedef struct S0 { char pad8[8]; int f8; int fC; } S0;
struct S22 { int a0, a1, b, c; };
struct S22a9d0 { char pad[12]; int f; };
struct A { char pad[8]; int *arr; int cnt; };
struct B { char pad[8]; int p; int idx; };
struct S_4 { char pad[12]; int x; };
typedef struct { char pad[8]; int cnt; int cap; int *data; } L_2;
typedef struct { char pad[12]; L_2 *l12; L_2 *l16; } T_4;
struct TransformObjectList { char pad[8]; int n; int pad2; int **data; };
struct Rc : public igObject { };
class Lock : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int tryLock(int); };
struct LockRef {
    Lock *p;
    LockRef() {}
    void attach(Lock *lock) {
        p = lock;
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
    }
    ~LockRef() {
        Lock *lock = get();
        if (lock != 0) {
            lock->_refCount = lock->_refCount - 1;
            if ((lock->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(lock);
            }
        }
    }
    Lock *get() const { return p; }
};
struct Tag { };
class DW4VC_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int); };
struct T_5 : public igObject { };
struct Item { char p[12]; T_5 *held; };
struct Lst { char p[8]; int count; char q[4]; Item **data; };
struct Own { char p[28]; Lst *f28; };
class V {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25();
    virtual bool v26(igSmartPointer<T_5> &);
    virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();
    virtual int v31(T_5 *);
};
struct RT { int word0; int references;
    static void rel(RT *o) {
        if (o) {
            --o->references;
            if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) igObject_Destroy((igObject *)o);
        }
    }
};
class C132 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(RT *); };
class C112 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual bool vX(RT **); };
struct Arg0 { char pad[20]; RT *ref; };
struct Rc_2 : public igObject { int f8; };
struct Ent { char pad[12]; char *name; };
struct Lst_2 { char pad[8]; Ent **arr; unsigned int count; };
struct Obj_11 { char pad[40]; Lst_2 *lst; };
class A_2 { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual Obj_11 *getObj(); };
class B_2 { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void put(const char *format, ...); };
extern "C" int FUN_0022c150(igRegistry *registry, B_2 *log, igStringObj *key, int section, igMetaField *field, void *object);
struct RecoveryString_2 {
    int *p;
    RecoveryString_2() : p(0) {}
    ~RecoveryString_2() {
        int *q = p;
        if (q != 0) {
            int *t = (int *)((char *)q - 8);
            int v = t[1] - 1;
            t[1] = v;
            if (v == 0) StringChunk_ReleaseHeader((StringChunk *)*t, (StringTokenHeader *)t);
        }
    }
};
struct List { char pad[8]; int count; int pad2; int **data; };
typedef struct Q { char pad[8]; int f8; } Q;
struct O_2 {
    char pad[8]; int f8;
    static inline O_2 *Cast(O_2 *p) {
        if (p != 0 && ((Gap::Core::igObject *)p)->isOfType(g_igMatrix44fMetaField_metaObject) != 0) {
            return p;
        }
        return 0;
    }
};
struct M { char pad[8]; int f8; };
struct S_a { char pad0[8]; int f8; };
struct K { 
  S_a *Cast(void *p) {
    if (p != 0 && ((Gap::Core::igObject *)p)->isOfType(g_igDoubleMetaField_metaObject) != 0) { return (S_a *)p; }
    return 0;
  }
};
typedef struct S_5 { char pad8[8]; int f8; int fC; int f10; } S_5;
typedef struct S_6 { char pad8[8]; int f8; int fC; unsigned int f10; } S_6;

extern "C" {
void BaseLibrary_MarkRegistered(void);
igMetaObject *igCompoundList_GetMetaObject(void);
int igCompoundList_GetVTable(void);
void FUN_00225900(void);
CallbackArray *igCompoundList_Register(void);
void igCompoundList_GetMetaObjectFunction(void);
void igCompoundList_InitFields(void);
igMetaObject *FUN_00225a30(void);
igMetaObject *igOptInterface_GetOrCreateMetaObject(void);
igMetaObject *igOptInterface_GetMetaObject(void);
int igOptInterface_GetVTable(void);
void **FUN_00225b90(void **arg0, long long arg1);
void FUN_00225c10(void);
CallbackArray *igOptInterface_Register(void);
void igOptInterface_GetMetaObjectFunction(void);
igMetaObject *igInterface_GetPublishedMetaObject(void);
void igOptInterface_InitFields(void);
igMetaObject *igOptConfiguration_GetOrCreateMetaObject(void);
igMetaObject *igOptConfiguration_GetMetaObject(void);
int igOptConfiguration_GetVTable(void);
void FUN_00225ea0(void);
CallbackArray *igOptConfiguration_Register(void);
void igOptConfiguration_GetMetaObjectFunction(void);
igMetaObject *igOptBase_GetMetaObject(void);
void FUN_00225f80(void);
void igOptBase_GetMetaObjectFunction(void);
igMetaObject *igBase_GetPublishedMetaObject(void);
void igOptBase_InitFields(void);
igMetaObject *igMessageInterface_GetOrCreateMetaObject(void);
igMetaObject *igMessageInterface_GetMetaObject(void);
int igMessageInterface_GetVTable(void);
void FUN_00226200(void);
CallbackArray *igMessageInterface_Register(void);
void igMessageInterface_GetMetaObjectFunction(void);
void igMessageInterface_InitFields(void);
igMetaObject *igMessageList_GetOrCreateMetaObject(void);
igMetaObject *igMessageList_GetMetaObject(void);
int igMessageList_GetVTable(void);
void FUN_00226420(void);
CallbackArray *igMessageList_Register(void);
void igMessageList_GetMetaObjectFunction(void);
igMetaObject *igMessageBase_GetMetaObject(void);
int igMessageBase_GetVTable(void);
void FUN_00226540(void);
CallbackArray *igMessageBase_Register(void);
void igMessageBase_GetMetaObjectFunction(void);
igMetaObject *igInterfaced_GetPublishedMetaObject(void);
igMetaObject *igLogInterface_GetOrCreateMetaObject(void);
igMetaObject *igLogInterface_GetMetaObject(void);
int igLogInterface_GetVTable(void);
void FUN_002266c0(void);
CallbackArray *igLogInterface_Register(void);
void igLogInterface_GetMetaObjectFunction(void);
void igLogInterface_InitFields(void);
igMetaObject *igLockInterface_GetOrCreateMetaObject(void);
igMetaObject *igLockInterface_GetMetaObject(void);
int igLockInterface_GetVTable(void);
void FUN_00226a10(void);
CallbackArray *igLockInterface_Register(void);
void igLockInterface_GetMetaObjectFunction(void);
void igLockInterface_InitFields(void);
igMetaObject *igLockBase_GetMetaObject(void);
void FUN_00226be0(void);
CallbackArray *igLockBase_Register(void);
void igLockBase_GetMetaObjectFunction(void);
igMetaObject *igListenerInterface_GetOrCreateMetaObject(void);
igMetaObject *igListenerInterface_GetMetaObject(void);
int igListenerInterface_GetVTable(void);
struct T_2 **FUN_00226db0(struct T_2 **arg0, short arg1);
void FUN_00226e30(void);
CallbackArray *igListenerInterface_Register(void);
void igListenerInterface_GetMetaObjectFunction(void);
void igListenerInterface_InitFields(void);
igMetaObject *igListenerListList_GetOrCreateMetaObject(void);
igMetaObject *igListenerListList_GetMetaObject(void);
int igListenerListList_GetVTable(void);
void FUN_002270b0(void);
CallbackArray *igListenerListList_Register(void);
void igListenerListList_GetMetaObjectFunction(void);
igMetaObject *igListenerList_GetMetaObject(void);
int igListenerList_GetVTable(void);
void FUN_002271d0(void);
CallbackArray *igListenerList_Register(void);
void igListenerList_GetMetaObjectFunction(void);
igMetaObject *igListenerBase_GetMetaObject(void);
int igListenerBase_GetVTable(void);
void FUN_002272f0(void);
CallbackArray *igListenerBase_Register(void);
void igListenerBase_GetMetaObjectFunction(void);
igMetaObject *igIterator_GetMetaObject(void);
void FUN_002273d0(void);
CallbackArray *igIterator_Register(void);
void igIterator_GetMetaObjectFunction(void);
igMetaObject *igIterator_GetPublishedMetaObject(void);
igMetaObject *igIterateGraph_GetOrCreateMetaObject(void);
igMetaObject *igIterateGraph_GetMetaObject(void);
int igIterateGraph_GetVTable(void);
void igIterateGraph_EnsureRegistered(void);
CallbackArray *igIterateGraph_Register(void);
void igIterateGraph_GetMetaObjectFunction(void);
void igIterateGraph_InitFields(void);
void *igIterateField_Create(int arg0);
igMetaObject *igIterateField_GetMetaObject(void);
int igIterateField_GetVTable(void);
void FUN_002278a0(void);
CallbackArray *igIterateField_Register(void);
void igIterateField_GetMetaObjectFunction(void);
void igIterateField_InitFields(void);
void *igIterateDerived_Create(int arg0);
igMetaObject *igIterateDerived_GetMetaObject(void);
int igIterateDerived_GetVTable(void);
void FUN_00227af0(void);
CallbackArray *igIterateDerived_Register(void);
void igIterateDerived_GetMetaObjectFunction(void);
void igIterateDerived_InitFields(void);
igMetaObject *igItemInterface_GetOrCreateMetaObject(void);
igMetaObject *igItemInterface_GetMetaObject(void);
int igItemInterface_GetVTable(void);
void **FUN_00227d70(void **arg0, short arg1);
ObjectRefWord *FUN_00227df0(ObjectRefWord *self,int delete_storage);
void FUN_00227ef0(void);
CallbackArray *igItemInterface_Register(void);
void igItemInterface_GetMetaObjectFunction(void);
void igItemInterface_InitFields(void);
void FUN_002280a0(void);
igMetaObject *igItemDataBaseList_GetOrCreateMetaObject(void);
igMetaObject *igItemDataBaseList_GetMetaObject(void);
int igItemDataBaseList_GetVTable(void);
void FUN_00228190(void);
CallbackArray *igItemDataBaseList_Register(void);
void igItemDataBaseList_GetMetaObjectFunction(void);
igMetaObject *igCompoundList_GetPublishedMetaObject(void);
void igItemDataBaseList_InitFields(void);
igMetaObject *igItemDataBaseField_GetMetaObject(void);
int igItemDataBaseField_GetVTable(void);
void FUN_00228410(void);
CallbackArray *igItemDataBaseField_Register(void);
void igItemDataBaseField_GetMetaObjectFunction(void);
void FUN_002284a0(void);
int FUN_00228570(void);
int Gap__igItemDataBaseField__vfunc_25(void);
void igItemDataBaseField_InitDefaults(igItemDataBaseField *self);
void FUN_002285d0(int arg0);
igMetaObject *igItemBase_GetMetaObject(void);
void FUN_00228950(void);
CallbackArray *igItemBase_Register(void);
void igItemBase_GetMetaObjectFunction(void);
igMetaObject *igInterfaced_GetMetaObject(void);
void FUN_00228a20(void);
CallbackArray *igInterfaced_Register(void);
void igInterfaced_GetMetaObjectFunction(void);
void igInterfaced_InitFields(void);
igMetaObject *igInterface_GetMetaObject(void);
int igInterface_GetVTable(void);
void FUN_00228c60(void);
CallbackArray *igInterface_Register(void);
void igInterface_GetMetaObjectFunction(void);
igMetaObject *igFileInfoList_GetOrCreateMetaObject(void);
igMetaObject *igFileInfoList_GetMetaObject(void);
int igFileInfoList_GetVTable(void);
void FUN_00228dd0(void);
CallbackArray *igFileInfoList_Register(void);
void igFileInfoList_GetMetaObjectFunction(void);
igMetaObject *igFileInfo_GetOrCreateMetaObject(void);
igMetaObject *igFileInfo_GetMetaObject(void);
int igFileInfo_GetVTable(void);
ObjectRefWord *FUN_00228fc0(ObjectRefWord *self,int delete_storage);
struct R **FUN_00229040(struct R **arg0, short arg1);
void FUN_002290c0(void);
CallbackArray *igFileInfo_Register(void);
void igFileInfo_GetMetaObjectFunction(void);
void igFileInfo_InitFields(void);
int *FUN_00229260(int *p);
igMetaObject *igBase_GetMetaObject(void);
void FUN_002292d0(void);
CallbackArray *igBase_Register(void);
void igBase_GetMetaObjectFunction(void);
int Gap__igOptInterface__vfunc_29(void);
void **FUN_00229460(void **arg0, short arg1);
void Gap__igOptConfiguration__vfunc_23(void);
void FUN_00229500(void *arg0, int arg1, ...);
void FUN_00229570(void *arg0);
void FUN_00229580(igInterfaceView *self);
void FUN_002295a0(void *arg0);
int FUN_00229700(int a0, int a1);
S_2 *FUN_00229710(S_2 *arg0);
S_3 *FUN_002297f0(S_3 *s, short flag);
void FUN_00229980(void);
void igItemInterface_resetFields(igInterface *arg0, int flags);
R_3 Gap__igItemInterface__vfunc_28(Obj_10 *arg1, void *arg2, int arg3);
int FUN_00229e20(struct L *arg0, int *arg1);
int FUN_00229f70(int *arg0, int *arg1);
int FUN_00229f90(int *arg0, int *arg1);
int FUN_0022a030(int *p);
igSmartPointer<InterfaceItem> Gap__igItemInterface__vfunc_27(int self, const StringRef &name, int kind);
int FUN_0022a740(int arg0, void **arg1);
void Gap__igItemInterface__vfunc_30(ItemInterface *self, const StringRef_2 &name, int a2, int a3);
void FUN_0022a8d0(S0 *arg0, S1 *arg1);
int FUN_0022a950(struct S22 *arg0);
int FUN_0022a9b0(struct S22a9d0 *arg0);
int FUN_0022a9d0(struct S22a9d0 *arg0);
void FUN_0022a9e0(S0 *arg0, S1 *arg1);
int FUN_0022aa60(struct B *arg0);
void FUN_0022aab0(struct S_4 *arg0);
int FUN_0022aac0(T_4 *arg0, int arg1);
int FUN_0022ac40(void *it);
int FUN_0022ac60(void *arg0);
void igListenerInterface_resetFields(igInterface *arg0, int flags);
int Gap__igListenerBase__vfunc_28(void);
int Gap__igListenerBase__vfunc_27(void);
int Gap__igLockInterface__vfunc_27(int self, int mode);
int Gap__igLogInterface__vfunc_24(void *d0, FILE *stream);
int Gap__igLogInterface__vfunc_27(igLogInterface *self, const char *format, va_list args);
igMetaObject *igInfo_GetMeta(void);
void igMessageInterface_resetFields(igMessageInterface *self, int flags);
void FUN_0022b470(int arg0, int arg1);
void FUN_0022b610(B_2 *log, int root);
bool FUN_0022b820(int arg0, int arg1);
void FUN_0022b8a0(void **arg0, void *arg1);
bool FUN_0022b910(Own *arg0, V *arg1);
bool FUN_0022bac0(void *arg0, void *arg1);
void thunk_igObject_InitDefaults__0022bbc0(igObject *self);
void igOptInterface_resetFields(igOptInterface *self, int flags);
igMetaObject *igMetaObject_GetMeta(void);
void FUN_0022bc10(int *arg0, int arg1, int arg2, int arg3, int arg4);
int FUN_0022c7f0(A_2 *arg0, int arg1, B_2 *arg2, int arg3);
igMetaObject *igOptInterface_GetMeta(void);
void Gap__igOptInterface__vfunc_27(void);
void Gap__igOptInterface__vfunc_28(void);
void Gap__igOptInterface__vfunc_30(void);
void Gap__igOptInterface__vfunc_31(void);
void Gap__igOptInterface__vfunc_32(int *arg0);
void igOptInterface_ReleaseDefaults(igObject *self);
igMetaObject *FUN_0022ca10(void);
igMetaObject *igMessageInterface_GetMeta(void);
igMetaObject *igLogInterface_GetMeta(void);
igMetaObject *igLockInterface_GetMeta(void);
igMetaObject *igListenerInterface_GetMeta(void);
igMetaObject *igItemInterface_GetMeta(void);
igMetaObject *igFileInfo_GetMeta(void);
igMetaObject *igFileInfoList_GetMeta(void);
void Gap__igListenerBase__vfunc_29(void);
igMetaObject *igCompoundList_GetMeta(void);
igMetaObject *igItemDataBaseField_GetMeta(void);
int igItemDataBaseField_GetDescriptor(void);
igMetaObject *igItemDataBaseList_GetMeta(void);
igMetaObject *igIterateDerived_GetMeta(void);
igMetaObject *igIterateField_GetMeta(void);
igMetaObject *igIterateGraph_GetMeta(void);
igMetaObject *igListenerList_GetMeta(void);
igMetaObject *igListenerListList_GetMeta(void);
igMetaObject *igMessageList_GetMeta(void);
igMetaObject *igOptConfiguration_GetMeta(void);
igMetaObject *igInterface_GetMeta(void);
igMetaObject *igMessageBase_GetMeta(void);
igMetaObject *igListenerBase_GetMeta(void);
int FUN_0022cb80(List *arg0, int **arg1);
igMetaObject *igMessageList_GetElementMeta(void);
igMetaObject *igListenerListList_GetElementMeta(void);
igMetaObject *igListenerList_GetElementMeta(void);
igMetaObject *igFileInfoList_GetElementMeta(void);
int FUN_0022cdb0(void *arg0, int arg1, void *arg2, int arg3, int arg4);
int FUN_0022ce90(char *arg0, int arg1, char *arg2, int arg3, int arg4);
int FUN_0022cf70(Q *arg0, int arg1, Q *arg2, int arg3, int arg4);
int FUN_0022d050(Q *arg0, int arg1, Q *arg2, int arg3, int arg4);
int FUN_0022d120(Q *arg0, int arg1, Q *arg2, int arg3, int arg4);
int FUN_0022d1f0(igMetaField *arg0, int arg1, igMetaField *arg2, int arg3, int arg4);
int FUN_0022d2c0(char *arg0, int arg1, char *arg2, int arg3, int arg4);
int FUN_0022d390(Q *arg0, int arg1, Q *arg2, int arg3, int arg4);
int FUN_0022d460(O_2 *arg0, int arg1, O_2 *arg2, int arg3, int arg4);
int FUN_0022d520(void *arg0, int arg1, void *arg2, int arg3, int arg4);
int FUN_0022d5e0(void *arg0, int arg1, void *arg2, int arg3, int arg4);
int FUN_0022d6a0(Q *arg0, int arg1, Q *arg2, int arg3, int arg4);
int FUN_0022d760(void *arg0, int arg1, void *arg2, int arg3, int arg4);
int FUN_0022d820(void *arg0, int arg1, void *arg2, int arg3, int arg4);
int FUN_0022d8e0(struct M *arg0, int arg1, int arg2, int arg3, int arg4);
int FUN_0022d9e0(int *arg0, int arg1, int *arg2, int arg3, int arg4);
int FUN_0022daa0(void *arg0, int arg1, void *arg2, int arg3, int arg4);
int FUN_0022db60(struct M *arg0, int arg1, int arg2, int arg3, int arg4);
int FUN_0022dc20(void *arg0, int arg1, void *arg2, int arg3, int arg4);
int FUN_0022dce0(char *arg0, int arg1, char *arg2, int arg3, int arg4);
int FUN_0022dda0(Q *arg0, int arg1, Q *arg2, int arg3, int arg4);
int FUN_0022de60(void *arg0, char *arg1, void *arg2, char *arg3, int arg4);
int FUN_0022df20(void *arg0, int arg1, void *arg2, int arg3, int arg4);
int FUN_0022dfe0(void *arg0, int arg1, void *arg2, int arg3, int arg4);
int FUN_0022e0a0(void *arg0, int arg1, void *arg2, int arg3, int arg4);
int FUN_0022e160(struct M *arg0, int arg1, struct M *arg2, int arg3, int arg4);
void igItemDataBaseList_TrimCapacity(S_5 *arg0);
void igItemDataBaseList_destructFields(S_6 *arg0);
}

static inline Iterator *makeIterator(IteratorType) { return (Iterator *)igIterateDerived_Create(0); }
static inline int cnt_of(const L_2 *list) { return list->cnt; }
static inline Rc *createIterator() {
    Tag tag = Tag();
    return (Rc *)igIterateDerived_Create(0);
}
static inline void storeHeld(Lst *list, int index, const igSmartPointer<T_5> &value) {
    T_5 *held = value.p;
    Item *it = list->data[index];
    T_5 *old;
    if (held) ++held->_refCount;
    old = it->held;
    if (old) {
        --old->_refCount;
        if ((old->_refCount & 0x7FFFFF) == 0)
            igObject_Destroy(old);
    }
    it->held = held;
}
static inline void * cast0(void * o) { if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(Gap::Math::igVec4ucMetaField::getClassMeta()) != 0) { return o; } return 0; }
static inline void * cast0_2(void * o) { if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(Gap::Core::igUnsignedShortMetaField::getClassMeta()) != 0) { return o; } return 0; }
static inline void * cast0_3(void * o) { if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(Gap::Core::igUnsignedIntMetaField::getClassMeta()) != 0) { return o; } return 0; }
static inline void * cast0_4(void * o) { if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(Gap::Core::igStringMetaField::getClassMeta()) != 0) { return o; } return 0; }
static inline int *castToType(int *object) {
    if (object != 0 && ((Gap::Core::igObject *)object)->isOfType(Gap::Core::igShortMetaField::getClassMeta()) != 0) {
        return object;
    }
    return 0;
}
static inline void * cast0_5(void * o) { if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(Gap::Core::igRawRefMetaField::getClassMeta()) != 0) { return o; } return 0; }
static inline void * cast0_6(void * o) { if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(Gap::Core::igObjectRefMetaField::getClassMeta()) != 0) { return o; } return 0; }
static inline void * cast0_7(void * o) { if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(Gap::Core::igMemoryRefMetaField::getClassMeta()) != 0) { return o; } return 0; }
static inline void * cast0_8(void * o) { if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(Gap::Core::igFloatMetaField::getClassMeta()) != 0) { return o; } return 0; }
static inline void * cast0_9(void * o) { if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(Gap::Core::igCharMetaField::getClassMeta()) != 0) { return o; } return 0; }
static inline void * cast0_10(void * o) { if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(Gap::Core::igBoolMetaField::getClassMeta()) != 0) { return o; } return 0; }
static inline int f8_of(const S_6 *list) { return list->f8; }

#endif
