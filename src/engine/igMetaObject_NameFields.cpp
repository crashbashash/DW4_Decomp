#include "dw4/igSmartPointer.h"
#include "dw4/igTDataList.h"

struct Instance : public igObject { };
struct MetaTreeNode;
struct MetaTreeList { char p[8]; MetaTreeNode **arr; int n; };
struct MetaTreeNode { char p[44]; int f44; char q[4]; MetaTreeList *f52; };
struct FieldPointerStorage { int prefix[2]; igMetaField **data; int count; };
struct RefHeader { int vtable; unsigned refs; };
typedef igMetaField *(*FieldFactory)(void *);
struct StaticInitCallbacks { void (**functions)(); int count; };

class MemoryPool { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };

struct CreateMeta { char p[26]; unsigned char f26; char q[5]; int f32; char r[24]; CreateMeta *(*f60)(); char s[8]; int f72; char t[20]; char *f96; };
struct PooledMeta { char p[26]; unsigned char f26; char q[5]; int f32; int f36; char r[20]; PooledMeta *(*f60)(); char s[8]; int f72; char t[20]; char *f96; };
class LayoutField { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(); char p0[4]; int off; char p1[6]; short idx; unsigned short sz; char p2[2]; void *owner; char p3[9]; unsigned char neg; };
struct LayoutMeta {
    char p0[32]; int w32; int w36; char p1[16]; LayoutMeta *parent; char p2[12]; int w72; char p3[12]; unsigned short w88;
};
struct AncestorMeta { char p[56]; AncestorMeta *f56; };
struct ChainMeta { char p[4]; int refs; char p8[48]; ChainMeta *parent; };
struct ChainRef { ChainMeta *p; ChainRef(ChainMeta *o) : p(o) { if (p != 0) { p->refs = p->refs + 1; } } };
struct ObjectSystemRecord { char unknown0[24]; int metaRegistry; };
struct PoolNameMeta { char pad[26]; unsigned char f26; char pad2[65]; int *buf; };

extern "C" {
void *igObject_ConstructHeader(void *);
void *igObject_CopyConstructHeader(void *, void *);
void *igObject_InitHeader(void *);
int igObject_Construct(...);
int igObject_ConstructPooled(...);
int InternalObjectList_Create(int);
int InternalObjectList_InsertRetained(...);
void InternalObjectList_SetAtRetained(void *, int, igMetaField *);
int ObjectPointerList_FindIndex(int, igMetaObject *);
void ObjectPointerList_Append(void *, void *);
void *ObjectPointerList_FindByStringField(void *list, igMetaField *stringMember, const char *name);
int MetaRefList_AppendRetained(void *, void *);
void igObjectSystem_AppendMetaObject(void *, igMetaObject *);
int igObjectSystem_FindMetaByName(void *objectSystem, const char *name);
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int StringChunk_ReleaseHeader(int, void *);
MemoryPool *Memory_GetAllocatorByName(...);
MemoryPool *Memory_GetDefaultAllocator(...);
void *Memory_GetAllocatorBySelector(int);
void *FUN_002c29c0(void *);
void igMetaField_FinalizeDescriptor(void *);
void igMetaField_Configure(igMetaField *, const char *, igMetaField **, int, igMetaObject *);
int FUN_002d3150(...);
int FUN_002d30c0(...);
int FUN_002d30d0(...);
void List_InsertWords(void *, int, int, ...);
void igArray_Destruct(StaticInitCallbacks *, short);
void memcpy(...);
extern int g_igMetaObject_vtable[4];
extern int g_stringPool[4];
extern void *g_objectSystem[4];
extern igMetaField *g_fieldNameMember[4];
extern int g_statusSucceeded[4];
extern int g_allocatorFailureStatus[4];

void *igMetaObject_CreateInstanceDefault(void *meta);
int igMetaObject_CreateInstance(CreateMeta *arg0, MemoryPool *arg1);
igMetaObject *igMetaObject_Init(igMetaObject *);
int igMetaObject_GetFieldAt(igMetaObject *self, int index);
int igMetaObject_GetFieldCount(igMetaObject *self);
int igMetaObject_CountTree(MetaTreeNode *arg0);
}

static inline void retain(Instance *object) {
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
}
static inline void release(Instance *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}

extern "C" int FUN_002fd610(Instance **out, int meta);

static inline void releaseObject(igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) igObject_Destroy(object);
    }
}
struct CreatedRef {
    igObject *p;
    CreatedRef(igObject *object) : p(object) {
        if (p != 0) p->_refCount = p->_refCount + 1;
    }
    CreatedRef(const CreatedRef &other) : p(other.p) {
        if (p != 0) p->_refCount = p->_refCount + 1;
    }
    ~CreatedRef() { releaseObject(p); }
    igObject *get() const { return p; }
};
/* The new instance arrives with one reference; the holder takes its own and drops that one. */
extern "C" CreatedRef FUN_002fd6e0(int meta, int pool);

/* Construct a metaobject: base header, igMetaObject vtable, no name or pool
 * name, and an empty field list. */
extern "C" void *igMetaObject_Construct(igMetaObject *meta);

/* Reset a freshly constructed metaobject to its defaults, then intern the empty string as the
 * pool name, creating the shared string pool on first use. No previous lists are released. */
extern "C" igMetaObject *igMetaObject_Init(igMetaObject *meta);

/* Copy-construct: base header copy, vtable stamp and cleared names; the other
 * metadata members are not copied here. */
extern "C" void *igMetaObject_CopyConstruct(igMetaObject *meta,void *source);

/* Drop the field list and then the child list: decrement the reference count
 * and destroy the list once its 23 low count bits reach zero.  The member cells
 * are left untouched. */
extern "C" void igMetaObject_ReleaseLists(igMetaObject *meta);

extern "C" void *igMetaObject_CreateInstanceDefault(void *meta);

extern "C" int igMetaObject_CreateInstance(CreateMeta *arg0, MemoryPool *arg1);

extern "C" int igMetaObject_CreateInstanceWithPool(PooledMeta *arg0, MemoryPool *arg1);

extern "C" void igMetaObject_AppendField(igMetaObject *meta, igMetaField *field);

extern "C" void igMetaObject_InheritFromBase(igMetaObject *meta,igMetaObject *parent);

extern "C" int igMetaObject_CountInstances(MetaTreeNode *arg0, int arg1);

/* Give a metaobject its (interned) class name. The shared string pool is created on first use even
 * for a null name; the new name is interned first, then the previous name token is released. */
extern "C" void igMetaObject_SetName(igMetaObject *meta, int name);

extern "C" void igMetaObject_AppendField(igMetaObject *meta, igMetaField *field);

extern "C" void igMetaObject_FinalizeAndAppendField(void *meta,void *field);

extern "C" void igMetaObject_FinalizeAndReplaceField(igMetaObject *meta,int index,igMetaField *field);

extern "C" int FUN_002fdef0(int a0, int a1);

/* The item array is read at +8 of the field list object. */
extern "C" int igMetaObject_GetFieldAt(igMetaObject *self, int index);

extern "C" void *igMetaObject_FindFieldByName(igMetaObject *meta, const char *name);

extern "C" void igMetaObject_CreateFields(igMetaObject *meta,FieldFactory *factories,int count);

extern "C" void igMetaObject_NameFields(igMetaObject *meta,const char **names,igMetaField ***handles,int *offsets,int start){
    int count;
    int row;
    igMetaField *field;
    count=igMetaObject_GetFieldCount(meta);
    row=0;
    for(;start<count;start++,row++){
        field=((FieldPointerStorage *)meta->_metaFields)->data[start];
        igMetaField_Configure(field,names[row],handles[row],offsets[row],meta);
        igMetaField_FinalizeDescriptor(field);
    }
}

extern "C" void igMetaObject_FinalizeFieldLayout(LayoutMeta *arg0);

extern "C" int FUN_002fe290(AncestorMeta *arg0, AncestorMeta *arg1);

extern "C" int igMetaObject_GetChildCount(igMetaObject *arg0);

/* The item array is read at +8 of the child list object. */
extern "C" int igMetaObject_GetChildAt(igMetaObject *self, int index);

extern "C" void *FUN_002fe300(igMetaObject *arg0, int arg1);

extern "C" int igMetaObject_CountTree(MetaTreeNode *arg0);

extern "C" int igObjectSystem_FindMetaByNameDefault(const char *name);

/* Read from the field list's `_capacity` slot (+12), not `_count` (+8). */
extern "C" int igMetaObject_GetFieldCount(igMetaObject *self);

extern "C" void FUN_002fe480(int arg0);

extern "C" void FUN_002fe490(int arg0);

extern "C" void igMetaObject_AddField(igMetaObject *arg0, void *arg1);

extern "C" void FUN_002fe5a0(int arg0);

extern "C" void FUN_002fe570(igMetaObject *arg0, void *arg1);

extern "C" void FUN_002fe5a0(int arg0);

extern "C" int FUN_002fe600(igTDataList<ChainMeta *> *list, ChainMeta *object);

extern "C" int FUN_002fe730(int arg0);

/* Search the object system's registry; when absent (-1) append the metaobject and search again,
 * since appending can replace the registry. */
extern "C" void igMetaObject_AssignTypeId(igMetaObject *meta);

extern "C" void FUN_002fe810(int *out, PoolNameMeta *s, MemoryPool *a);

extern "C" int igMetaObject_GetPoolName(int *p);

extern "C" void igMetaObject_RunStaticInit(StaticInitCallbacks *(*initialize)());
