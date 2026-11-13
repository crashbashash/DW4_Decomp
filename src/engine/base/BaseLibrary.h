#ifndef DW4_BASE_LIBRARY_H
#define DW4_BASE_LIBRARY_H

#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/typecast.h"

extern unsigned char g_BaseLibrary_registered;
extern int DAT_0052bea0[4];
extern igMetaObject *g_igCompoundList_metaObject[4];
extern int DAT_0052c750[4];
extern char *g_objectSystem[4];
extern void *g_igDoubleMetaField_metaObject[4];
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igCompoundList_className[];
extern int DAT_00497b68[4];
extern int DAT_00497b78[4];
extern int DAT_00497b88[4];
extern int DAT_00497b98[4];
extern igMetaObject *g_igOptBase_metaObject[4];
extern igMetaObject *g_igOptInterface_metaObject[4];
extern int g_metadataAllocatorKey[4];
extern int DAT_0052be10[4];
extern char igInterface_GetPublishedMetaObject[];
extern char g_igOptInterface_callbackList[];
extern char igOptInterface_className[];
extern igMetaObject *g_igInterface_metaObject[4];
extern int DAT_00497bc0[4];
extern int DAT_00497bd0[4];
extern int DAT_00497be0[4];
extern int DAT_00497bf0[4];
extern int DAT_004e79b0[4];
extern igMetaObject *g_igOptConfiguration_metaObject[4];
extern int DAT_0052c610[4];
extern char igOptConfiguration_className[];
extern char igBase_GetPublishedMetaObject[];
extern char g_igOptBase_callbackList[];
extern char igOptBase_className[];
extern igMetaObject *g_igBase_metaObject[4];
extern int DAT_00497c10[4];
extern int DAT_00497c18[4];
extern int DAT_00497c20[4];
extern int DAT_00497c28[4];
extern igMetaObject *g_igMessageInterface_metaObject[4];
extern int DAT_0052bf30[4];
extern char g_igMessageInterface_callbackList[];
extern char igMessageInterface_className[];
extern int DAT_00497c38[4];
extern int DAT_00497c40[4];
extern int DAT_00497c48[4];
extern int DAT_00497c50[4];
extern igMetaObject *g_igMessageList_metaObject[4];
extern int DAT_0052c5a0[4];
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char g_igMessageList_callbackList[];
extern char igMessageList_className[];
extern igMetaObject *g_igMessageBase_metaObject[4];
extern int DAT_0052c6e0[4];
extern char igMessageBase_className[];
extern igMetaObject *g_igInterfaced_metaObject[4];
extern igMetaObject *g_igLogInterface_metaObject[4];
extern int DAT_0052bfa0[4];
extern char igLogInterface_className[];
extern int DAT_00497c60[4];
extern int DAT_00497c68[4];
extern int DAT_00497c70[4];
extern int DAT_00497c78[4];
extern igMetaObject *g_igLockInterface_metaObject[4];
extern int DAT_0052c010[4];
extern char g_igLockInterface_callbackList[];
extern char igLockInterface_className[];
extern int DAT_00497c90[4];
extern int DAT_00497ca0[4];
extern int DAT_00497cb0[4];
extern int DAT_00497cc0[4];
extern igMetaObject *g_igLockBase_metaObject[4];
extern char igInterfaced_GetPublishedMetaObject[];
extern char igLockBase_className[];
extern igMetaObject *g_igListenerInterface_metaObject[4];
extern int DAT_0052c080[4];
extern char g_igListenerInterface_callbackList[];
extern char igListenerInterface_className[];
extern int DAT_00497ce0[4];
extern int DAT_00497cf0[4];
extern int DAT_00497d00[4];
extern int DAT_00497d10[4];
extern igMetaObject *g_igListenerListList_metaObject[4];
extern int DAT_0052c530[4];
extern char g_igListenerListList_callbackList[];
extern char igListenerListList_className[];
extern igMetaObject *g_igListenerList_metaObject[4];
extern int DAT_0052c4c0[4];
extern char g_igListenerList_callbackList[];
extern char igListenerList_className[];
extern igMetaObject *g_igListenerBase_metaObject[4];
extern int DAT_0052c7b0[4];
extern char igListenerBase_className[];
extern igMetaObject *g_igIterator_metaObject[4];
extern char igIterator_className[];
extern igMetaObject *g_igIterateGraph_metaObject[4];
extern int DAT_0052c460[4];
extern char igIterator_GetPublishedMetaObject[];
extern char g_igIterateGraph_callbackList[];
extern char igIterateGraph_className[];
extern int DAT_00497d40[4];
extern int DAT_00497d50[4];
extern int DAT_00497d60[4];
extern int DAT_00497d70[4];
extern igMetaObject *g_igIterateField_metaObject[4];
extern int DAT_0052c400[4];
extern char g_igIterateField_callbackList[];
extern char igIterateField_className[];
extern int DAT_00497d88[4];
extern int DAT_00497d90[4];
extern int DAT_00497d98[4];
extern int DAT_00497da0[4];
extern igMetaObject *g_igIterateDerived_metaObject[4];
extern int DAT_0052c3a0[4];
extern char g_igIterateDerived_callbackList[];
extern char igIterateDerived_className[];
extern int DAT_00497db0[4];
extern int DAT_00497db8[4];
extern int DAT_00497dc0[4];
extern int DAT_00497dc8[4];
extern igMetaObject *g_igItemInterface_metaObject[4];
extern int DAT_0052c0f0[4];
extern char g_igItemInterface_callbackList[];
extern char igItemInterface_className[];
extern int DAT_00497df0[4];
extern int DAT_00497e10[4];
extern int DAT_00497e30[4];
extern int DAT_00497e50[4];
extern igMetaObject *g_igItemDataBaseList_metaObject[4];
extern int DAT_0052c340[4];
extern char igCompoundList_GetPublishedMetaObject[];
extern char igItemDataBaseList_className[];
extern int DAT_004e79a8[4];
extern int DAT_0056d9d0[4];
extern igMetaObject *g_igItemDataBaseField_metaObject[4];
extern int DAT_0052c240[4];
extern int DAT_00531740[4];
extern int g_igMetaField_vtable[4];
extern char igCompoundMetaField_GetPublishedMetaObject[];
extern char igCompoundMetaField_Register[];
extern char g_igItemDataBaseField_callbackList[];
extern char igItemDataBaseField_className[];
extern int DAT_0056d9e0[4];
extern int DAT_004e7ce8[4];
extern int DAT_004e7d70[4];
extern int DAT_004e7d80[4];
extern int g_stringPool[4];
extern igMetaObject *g_igItemBase_metaObject[4];
extern char igItemBase_className[];
extern char g_igInterfaced_callbackList[];
extern char igInterfaced_className[];
extern int DAT_00497e90[4];
extern int DAT_00497eb0[4];
extern int DAT_00497ed0[4];
extern int DAT_00497ef0[4];
extern int DAT_0052c670[4];
extern char igInterface_className[];
extern igMetaObject *g_igFileInfoList_metaObject[4];
extern int DAT_0052c1d0[4];
extern char g_igFileInfoList_callbackList[];
extern char igFileInfoList_className[];
extern igMetaObject *g_igFileInfo_metaObject[4];
extern int DAT_0052c170[4];
extern char igNamedObject_GetPublishedMetaObject[];
extern char igNamedObject_Register[];
extern char g_igFileInfo_callbackList[];
extern char igFileInfo_className[];
extern int DAT_00497f30[4];
extern int DAT_00497f40[4];
extern int DAT_00497f50[4];
extern int DAT_00497f60[4];
extern char igBase_className[];
extern int g_igTransform_metaObject[4];
extern igMetaObject *g_igInfo_metaObject[4];
extern int g_igSceneInfo_metaObject[4];
extern int g_igAnimationDatabase_metaObject[4];
extern int g_igMetaObject_metaObject[4];
extern int g_statusSucceeded[4];
extern char DAT_004e7ea8[16];
extern int g_igVec4ucMetaField_metaObject[4];
extern int g_igVec4fMetaField_metaObject[4];
extern int DAT_00560f60[4];
extern int DAT_00560f68[4];
extern int g_igVec3fMetaField_metaObject[4];
extern int DAT_00560f80[4];
extern int g_igVec2fMetaField_metaObject[4];
extern int DAT_00560f98[4];
extern int g_igMatrix44fMetaField_metaObject[4];
extern int DAT_00561010[4];
extern int g_igUnsignedShortMetaField_metaObject[4];
extern int g_igUnsignedLongMetaField_metaObject[4];
extern int g_igUnsignedIntMetaField_metaObject[4];
extern int g_igUnsignedCharMetaField_metaObject[4];
extern int g_igStringMetaField_metaObject[4];
extern int g_igShortMetaField_metaObject[4];
extern int g_igRawRefMetaField_metaObject[4];
extern int g_igObjectRefMetaField_metaObject[4];
extern int g_igMemoryRefMetaField_metaObject[4];
extern int g_igLongMetaField_metaObject[4];
extern int g_igIntMetaField_metaObject[4];
extern int g_igFloatMetaField_metaObject[4];
extern int g_igEnumMetaField_metaObject[4];
extern int g_igCharMetaField_metaObject[4];
extern int g_igBoolMetaField_metaObject[4];

extern "C" {
void igMetaObject_RunStaticInit(...);
int thunk_FUN_002ed460__002ff810(...);
int igObject_InitHeader(...);
int igMetaObject_RegisterClass(...);
int igUnsignedCharMetaField_GetDefaultDescriptor(...);
int igMetaObject_CreateFields(...);
void * igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igMetaObject_NameFields(...);
igMetaObject *igMetaObject_Create(...);
int Memory_GetAllocatorBySelector(...);
int FUN_0013a880(...);
int FUN_001d35d0(...);
void StringRef_Destruct_00130720(...);
int FUN_00100610(...);
int FUN_002c3440(...);
int FUN_002c8e50(...);
int igStringMetaField_SetDefaultText(...);
int FUN_002bb030(...);
int StringChunk_ReleaseHeader(...);
int FUN_002b9120(...);
int FUN_002c8810(...);
int FUN_002cb110(...);
int FUN_0014aa70(...);
int igObjectList_GetOrCreateMetaObject(...);
void *igMetaObject_CreateInstance(...);
int FUN_0019c8c0(...);
int igIntList_GetOrCreateMetaObject(...);
int FUN_002be610(...);
int FUN_002c86a0(...);
int FUN_002c8ca0(...);
int FUN_002fe480(...);
int ObjectPointerList_FindIndex(...);
int igMetaObject_FinalizeAndReplaceField(...);
void ** igMetaObject_FindFieldByName(...);
int igMetaField_Init(...);
void * FUN_002fc250(...);
int MetaRefList_AppendRetained(...);
int igMetaField_FinalizeDescriptor(...);
int FUN_002b9200(...);
int FUN_002c8f30(...);
int StringPool_Allocate(...);
int ObjectList_AppendRetained(...);
int StringPool_Construct(...);
void * StringPool_Intern(...);
int igMetaField_SetFieldName(...);
int igMetaObject_EnsureRegistered(...);
void * igObjectRefMetaField_Create(...);
int FUN_00131bc0(...);
int FUN_001d36d0(...);
int FUN_002c3820(...);
int FUN_002c7300(...);
int FUN_002f00c0(...);
int Gap__Core__igObject__vfunc_11(...);
int FUN_002295b0(...);
int FUN_0022a040(...);
int List_InsertWords(...);
int FUN_002fe300(...);
int igMetaObject_CountTree(...);
int List_Resize(...);
int igObject_IsKindOf(...);
int FUN_0022ad00(...);
int igMatrix44f_SetIdentity(...);
int FUN_001904f0(...);
int Matrix44_Copy(...);
igSmartPointer<igObject> FUN_002fd610(int);
int fflush(...);
int vprintf(...);
int FUN_0022b480(...);
int FUN_001d6340(...);
int Gap__Core__igObject__vfunc_09(...);
int FUN_0022c150(...);
int Gap__Core__igObject__vfunc_10(...);
int FUN_00190330(...);
int igStringMetaField_AssignRetainedToken(...);
int igObjectRefMetaField_Assign(...);
int FUN_00300e50(...);
int FUN_00300f50(...);
int Gap__Core__igObject__vfunc_02(...);
}

struct S {
    void *f0;
    char pad[28];
    void *f20;
    void *f24;
};
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
struct O { S_temp_a0 *m; };
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
                    igObject_Destroy(object);
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
                    igObject_Destroy(object);
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
            if ((q->refs & 0x7fffff) == 0) igObject_Destroy(q);
        }
    }
    void operator=(T *n) {
        T *q = p;
        if (q != 0) {
            q->refs = q->refs - 1;
            if ((q->refs & 0x7fffff) == 0) igObject_Destroy(q);
        }
        p = n;
    }
};
struct S_3 {
    igSmartPointer_2<Obj_9> a; igSmartPointer_2<Obj_9> b; igSmartPointer_2<Obj_9> c;
};
struct R_3 { int a, b, c, d; };
struct RecoveryString { void *p; ~RecoveryString() { if (p != 0) { int *t = (int *)((char *)p - 8); int v = *(int *)((char *)p - 4) - 1; *(int *)((char *)p - 4) = v; if (v == 0) StringChunk_ReleaseHeader(*t, t); } } };
class Obj_10 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual R_3 vf(RecoveryString *, int); };
struct L { char p[8]; int n; };
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
                StringChunk_ReleaseHeader(header[0], header);
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
            if (count == 0) { StringChunk_ReleaseHeader(*header, header); }
        }
    }
};
struct IteratorType {};
class ItemInterface { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void vX(const StringRef_2 &, int, int); };
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
            if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) igObject_Destroy(o);
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
class B_2 { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void put(char *); };
struct RecoveryString_2 {
    int *p;
    RecoveryString_2() : p(0) {}
    ~RecoveryString_2() {
        int *q = p;
        if (q != 0) {
            int *t = (int *)((char *)q - 8);
            int v = t[1] - 1;
            t[1] = v;
            if (v == 0) StringChunk_ReleaseHeader(*t, t);
        }
    }
};
struct List { char pad[8]; int count; int pad2; int **data; };
typedef struct Q { char pad[8]; int f8; } Q;
struct O_2 {
    char pad[8]; int f8;
    static inline O_2 *Cast(O_2 *p) {
        if (p != 0 && igObject_IsKindOf(p, g_igMatrix44fMetaField_metaObject[0]) != 0) {
            return p;
        }
        return 0;
    }
};
struct M { char pad[8]; int f8; };
struct S_a { char pad0[8]; int f8; };
struct K { 
  S_a *Cast(void *p) {
    if (p != 0 && igObject_IsKindOf(p, g_igDoubleMetaField_metaObject[0]) != 0) { return (S_a *)p; }
    return 0;
  }
};
typedef struct S_5 { char pad8[8]; int f8; int fC; int f10; } S_5;
typedef struct S_6 { char pad8[8]; int f8; int fC; unsigned int f10; } S_6;

extern "C" {
Rc_2 * FUN_002b9500(...);
int igStringObj_Set(Rc_2 *, char *);
void BaseLibrary_MarkRegistered(void);
void *FUN_00225790(struct S *arg0, short arg1);
igMetaObject *igCompoundList_GetMetaObject(void);
int igCompoundList_GetVTable(void);
void FUN_00225900(void);
void igCompoundList_Register(void);
void thunk_igCompoundList_GetMetaObject(void);
void igCompoundList_InitFields(void);
igMetaObject *FUN_00225a30(void);
igMetaObject *FUN_00225a40(void);
igMetaObject *igOptInterface_GetMetaObject(void);
int igOptInterface_GetVTable(void);
void **FUN_00225b90(void **arg0, long long arg1);
void FUN_00225c10(void);
void igOptInterface_Register(void);
void thunk_igOptInterface_GetMetaObject(void);
igMetaObject *FUN_00225cb0(void);
void igOptInterface_InitFields(void);
igMetaObject *FUN_00225dc0(void);
igMetaObject *igOptConfiguration_GetMetaObject(void);
int igOptConfiguration_GetVTable(void);
void FUN_00225ea0(void);
void igOptConfiguration_Register(void);
void thunk_igOptConfiguration_GetMetaObject(void);
igMetaObject *igOptBase_GetMetaObject(void);
void FUN_00225f80(void);
void igOptBase_Register(void);
void thunk_igOptBase_GetMetaObject(void);
igMetaObject *FUN_00226010(void);
void igOptBase_InitFields(void);
igMetaObject *FUN_002260d0(void);
igMetaObject *igMessageInterface_GetMetaObject(void);
int igMessageInterface_GetVTable(void);
void FUN_00226200(void);
void igMessageInterface_Register(void);
void thunk_igMessageInterface_GetMetaObject(void);
void igMessageInterface_InitFields(void);
igMetaObject *FUN_00226340(void);
igMetaObject *igMessageList_GetMetaObject(void);
int igMessageList_GetVTable(void);
void FUN_00226420(void);
void igMessageList_Register(void);
void thunk_igMessageList_GetMetaObject(void);
igMetaObject *igMessageBase_GetMetaObject(void);
int igMessageBase_GetVTable(void);
void FUN_00226540(void);
void igMessageBase_Register(void);
void thunk_igMessageBase_GetMetaObject(void);
igMetaObject *FUN_002265d0(void);
igMetaObject *FUN_002265e0(void);
igMetaObject *igLogInterface_GetMetaObject(void);
int igLogInterface_GetVTable(void);
void FUN_002266c0(void);
void igLogInterface_Register(void);
void thunk_igLogInterface_GetMetaObject(void);
void igLogInterface_InitFields(void);
igMetaObject *FUN_002267c0(void);
igMetaObject *igLockInterface_GetMetaObject(void);
int igLockInterface_GetVTable(void);
O *FUN_00226990(O *arg0, short arg1);
void FUN_00226a10(void);
void igLockInterface_Register(void);
void thunk_igLockInterface_GetMetaObject(void);
void igLockInterface_InitFields(void);
igMetaObject *igLockBase_GetMetaObject(void);
void FUN_00226be0(void);
void igLockBase_Register(void);
void thunk_igLockBase_GetMetaObject(void);
igMetaObject *FUN_00226c60(void);
igMetaObject *igListenerInterface_GetMetaObject(void);
int igListenerInterface_GetVTable(void);
struct T_2 **FUN_00226db0(struct T_2 **arg0, short arg1);
void FUN_00226e30(void);
void igListenerInterface_Register(void);
void thunk_igListenerInterface_GetMetaObject(void);
void igListenerInterface_InitFields(void);
igMetaObject *FUN_00226fd0(void);
igMetaObject *igListenerListList_GetMetaObject(void);
int igListenerListList_GetVTable(void);
void FUN_002270b0(void);
void igListenerListList_Register(void);
void thunk_igListenerListList_GetMetaObject(void);
igMetaObject *igListenerList_GetMetaObject(void);
int igListenerList_GetVTable(void);
void FUN_002271d0(void);
void igListenerList_Register(void);
void thunk_igListenerList_GetMetaObject(void);
igMetaObject *igListenerBase_GetMetaObject(void);
int igListenerBase_GetVTable(void);
void FUN_002272f0(void);
void igListenerBase_Register(void);
void thunk_igListenerBase_GetMetaObject(void);
igMetaObject *igIterator_GetMetaObject(void);
void FUN_002273d0(void);
void igIterator_Register(void);
void thunk_igIterator_GetMetaObject(void);
igMetaObject *FUN_00227450(void);
void FUN_00227460(int arg0);
igMetaObject *FUN_002274a0(void);
igMetaObject *igIterateGraph_GetMetaObject(void);
int igIterateGraph_GetVTable(void);
void FUN_00227620(void);
void igIterateGraph_Register(void);
void thunk_igIterateGraph_GetMetaObject(void);
void igIterateGraph_InitFields(void);
void FUN_00227780(int arg0);
igMetaObject *igIterateField_GetMetaObject(void);
int igIterateField_GetVTable(void);
void FUN_002278a0(void);
void igIterateField_Register(void);
void thunk_igIterateField_GetMetaObject(void);
void igIterateField_InitFields(void);
void *FUN_002279d0(int arg0);
igMetaObject *igIterateDerived_GetMetaObject(void);
int igIterateDerived_GetVTable(void);
void FUN_00227af0(void);
void igIterateDerived_Register(void);
void thunk_igIterateDerived_GetMetaObject(void);
void igIterateDerived_InitFields(void);
igMetaObject *FUN_00227c20(void);
igMetaObject *igItemInterface_GetMetaObject(void);
int igItemInterface_GetVTable(void);
void **FUN_00227d70(void **arg0, short arg1);
ObjectRefWord *FUN_00227df0(ObjectRefWord *self,int delete_storage);
void **FUN_00227e70(void **arg0, short arg1);
void FUN_00227ef0(void);
void igItemInterface_Register(void);
void thunk_igItemInterface_GetMetaObject(void);
void igItemInterface_InitFields(void);
void FUN_002280a0(void);
igMetaObject *FUN_002280b0(void);
igMetaObject *igItemDataBaseList_GetMetaObject(void);
int igItemDataBaseList_GetVTable(void);
void FUN_00228190(void);
void igItemDataBaseList_Register(void);
void thunk_igItemDataBaseList_GetMetaObject(void);
igMetaObject *FUN_00228220(void);
void igItemDataBaseList_InitFields(void);
igMetaObject *igItemDataBaseField_GetMetaObject(void);
int igItemDataBaseField_GetVTable(void);
void FUN_00228410(void);
void igItemDataBaseField_Register(void);
void thunk_igItemDataBaseField_GetMetaObject(void);
void FUN_002284a0(void);
int FUN_00228570(void);
int Gap__igItemDataBaseField__vfunc_25(void);
void Gap__igItemDataBaseField__vfunc_11(void *arg0);
void FUN_002285d0(int arg0);
igMetaObject *igItemBase_GetMetaObject(void);
void FUN_00228950(void);
void igItemBase_Register(void);
void thunk_igItemBase_GetMetaObject(void);
igMetaObject *igInterfaced_GetMetaObject(void);
void FUN_00228a20(void);
void igInterfaced_Register(void);
void thunk_igInterfaced_GetMetaObject(void);
void igInterfaced_InitFields(void);
igMetaObject *igInterface_GetMetaObject(void);
int igInterface_GetVTable(void);
void FUN_00228c60(void);
void igInterface_Register(void);
void thunk_igInterface_GetMetaObject(void);
igMetaObject *FUN_00228cf0(void);
igMetaObject *igFileInfoList_GetMetaObject(void);
int igFileInfoList_GetVTable(void);
void FUN_00228dd0(void);
void igFileInfoList_Register(void);
void thunk_igFileInfoList_GetMetaObject(void);
igMetaObject *FUN_00228e60(void);
igMetaObject *igFileInfo_GetMetaObject(void);
int igFileInfo_GetVTable(void);
ObjectRefWord *FUN_00228fc0(ObjectRefWord *self,int delete_storage);
struct R **FUN_00229040(struct R **arg0, short arg1);
void FUN_002290c0(void);
void igFileInfo_Register(void);
void thunk_igFileInfo_GetMetaObject(void);
void igFileInfo_InitFields(void);
int *FUN_00229260(int *p);
int *FUN_00229270(int *p);
igMetaObject *igBase_GetMetaObject(void);
void FUN_002292d0(void);
void igBase_Register(void);
void thunk_igBase_GetMetaObject(void);
void **FUN_00229350(void **arg0, short arg1);
void **FUN_002293d0(void **arg0, int arg1);
int Gap__igOptInterface__vfunc_29(void);
void **FUN_00229460(void **arg0, short arg1);
void Gap__igOptConfiguration__vfunc_23(void);
int igDataList_GetCount(int *p);
void FUN_00229500(void *arg0, int arg1, ...);
void FUN_00229570(void *arg0);
void FUN_00229580(igInterfaceView *self);
void FUN_002295a0(void *arg0);
int FUN_00229700(int a0, int a1);
S_2 *FUN_00229710(S_2 *arg0);
S_3 *FUN_002297f0(S_3 *s, short flag);
void FUN_00229980(void);
void Gap__igItemInterface__vfunc_13(igInterface *arg0);
R_3 Gap__igItemInterface__vfunc_28(Obj_10 *arg1, void *arg2, int arg3);
int FUN_00229e20(struct L *arg0, int *arg1);
int FUN_00229f70(int *arg0, int *arg1);
int FUN_00229f90(int *arg0, int *arg1);
void **FUN_00229fb0(void **arg0, void **arg1);
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
int FUN_0022ab90(int arg0, int arg1, int arg2);
int FUN_0022ac00(void *arg0);
int FUN_0022ac40(void);
int FUN_0022ac60(void *arg0);
int FUN_0022ac70(int arg0, int arg1);
void FUN_0022b0a0(int arg0, int *arg1);
void Gap__igListenerInterface__vfunc_13(igInterface *arg0);
int Gap__igListenerBase__vfunc_28(void);
int Gap__igListenerBase__vfunc_27(void);
int Gap__igLockInterface__vfunc_27(int self, int mode);
int Gap__igLogInterface__vfunc_24(void *d0, int arg1);
int Gap__igLogInterface__vfunc_27(void *arg0, int arg1, int arg2);
igMetaObject *Gap__Core__igInfo__vfunc_22(void);
void Gap__igMessageInterface__vfunc_13(igMessageInterface *self);
void FUN_0022b470(int arg0, int arg1);
void FUN_0022b610(void);
bool FUN_0022b820(int arg0, int arg1);
void FUN_0022b8a0(void **arg0, void *arg1);
bool FUN_0022b910(Own *arg0, V *arg1);
bool FUN_0022bac0(void *arg0, void *arg1);
void thunk_Gap__Core__igObject__vfunc_09__0022bbc0(void);
void Gap__igOptInterface__vfunc_13(void *arg0);
int Gap__Core__igMetaObject__vfunc_22(void);
void FUN_0022bc10(int *arg0, int arg1, int arg2, int arg3, int arg4);
int FUN_0022c7f0(A_2 *arg0, int arg1, B_2 *arg2, int arg3);
igMetaObject *Gap__igOptInterface__vfunc_22(void);
void Gap__igOptInterface__vfunc_27(void);
void Gap__igOptInterface__vfunc_28(void);
void Gap__igOptInterface__vfunc_30(void);
void Gap__igOptInterface__vfunc_31(void);
void Gap__igOptInterface__vfunc_32(int *arg0);
void Gap__igOptInterface__vfunc_12(void);
igMetaObject *FUN_0022ca10(void);
igMetaObject *Gap__igMessageInterface__vfunc_22(void);
igMetaObject *Gap__igLogInterface__vfunc_22(void);
igMetaObject *Gap__igLockInterface__vfunc_22(void);
igMetaObject *Gap__igListenerInterface__vfunc_22(void);
igMetaObject *Gap__igItemInterface__vfunc_22(void);
igMetaObject *Gap__igFileInfo__vfunc_22(void);
igMetaObject *Gap__igFileInfoList__vfunc_22(void);
void Gap__igListenerBase__vfunc_29(void);
igMetaObject *Gap__igCompoundList__vfunc_22(void);
igMetaObject *Gap__igItemDataBaseField__vfunc_22(void);
int Gap__igItemDataBaseField__vfunc_23(void);
igMetaObject *Gap__igItemDataBaseList__vfunc_22(void);
igMetaObject *Gap__igIterateDerived__vfunc_22(void);
igMetaObject *Gap__igIterateField__vfunc_22(void);
igMetaObject *Gap__igIterateGraph__vfunc_22(void);
igMetaObject *Gap__igListenerList__vfunc_22(void);
igMetaObject *Gap__igListenerListList__vfunc_22(void);
igMetaObject *Gap__igMessageList__vfunc_22(void);
igMetaObject *Gap__igOptConfiguration__vfunc_22(void);
igMetaObject *Gap__igInterface__vfunc_22(void);
igMetaObject *Gap__igMessageBase__vfunc_22(void);
igMetaObject *Gap__igListenerBase__vfunc_22(void);
int FUN_0022cb80(List *arg0, int **arg1);
igMetaObject *Gap__igMessageList__vfunc_24(void);
igMetaObject *Gap__igListenerListList__vfunc_24(void);
igMetaObject *Gap__igListenerList__vfunc_24(void);
igMetaObject *Gap__igFileInfoList__vfunc_24(void);
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
void Gap__igItemDataBaseList__vfunc_18(S_5 *arg0);
void Gap__igItemDataBaseList__vfunc_04(S_6 *arg0);
void **FUN_0022e3c0(struct Ref **self, short flag);
}

static inline Iterator *makeIterator(IteratorType) { return (Iterator *)FUN_002279d0(0); }
static inline int cnt_of(const L_2 *list) { return list->cnt; }
static inline Rc *createIterator() {
    Tag tag = Tag();
    return (Rc *)FUN_002279d0(0);
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
static inline void * cast0(void * o) { if (o != 0 && igObject_IsKindOf(o, g_igVec4ucMetaField_metaObject[0]) != 0) { return o; } return 0; }
static inline void * cast0_2(void * o) { if (o != 0 && igObject_IsKindOf(o, g_igUnsignedShortMetaField_metaObject[0]) != 0) { return o; } return 0; }
static inline void * cast0_3(void * o) { if (o != 0 && igObject_IsKindOf(o, g_igUnsignedIntMetaField_metaObject[0]) != 0) { return o; } return 0; }
static inline void * cast0_4(void * o) { if (o != 0 && igObject_IsKindOf(o, g_igStringMetaField_metaObject[0]) != 0) { return o; } return 0; }
static inline int *castToType(int *object) {
    if (object != 0 && igObject_IsKindOf(object, g_igShortMetaField_metaObject[0]) != 0) {
        return object;
    }
    return 0;
}
static inline void * cast0_5(void * o) { if (o != 0 && igObject_IsKindOf(o, g_igRawRefMetaField_metaObject[0]) != 0) { return o; } return 0; }
static inline void * cast0_6(void * o) { if (o != 0 && igObject_IsKindOf(o, g_igObjectRefMetaField_metaObject[0]) != 0) { return o; } return 0; }
static inline void * cast0_7(void * o) { if (o != 0 && igObject_IsKindOf(o, g_igMemoryRefMetaField_metaObject[0]) != 0) { return o; } return 0; }
static inline void * cast0_8(void * o) { if (o != 0 && igObject_IsKindOf(o, g_igFloatMetaField_metaObject[0]) != 0) { return o; } return 0; }
static inline void * cast0_9(void * o) { if (o != 0 && igObject_IsKindOf(o, g_igCharMetaField_metaObject[0]) != 0) { return o; } return 0; }
static inline void * cast0_10(void * o) { if (o != 0 && igObject_IsKindOf(o, g_igBoolMetaField_metaObject[0]) != 0) { return o; } return 0; }
static inline int f8_of(const S_6 *list) { return list->f8; }

#endif
