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
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];

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

extern "C" int FUN_002fd610(Instance **out, int meta) {
    igSmartPointer<Instance> created((Instance *)igMetaObject_CreateInstanceDefault((void *)meta), kRetainReference);
    release(created.p);
    *out = created.p;
    retain(*out);
    return 0;
}

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
extern "C" CreatedRef FUN_002fd6e0(int meta, int pool) {
    CreatedRef created((igObject *)igMetaObject_CreateInstance((CreateMeta *)meta, (MemoryPool *)pool));
    releaseObject(created.get());
    return created;
}

/* Construct a metaobject: base header, igMetaObject vtable, no name or pool
 * name, and an empty field list. */
extern "C" void *igMetaObject_Construct(igMetaObject *meta){
    igObject_ConstructHeader(meta);
    meta->_vtable=(int)g_igMetaObject_vtable;
    meta->_name=0;
    meta->_poolName=0;
    if(meta)igMetaObject_Init(meta);
    meta->_metaFields=InternalObjectList_Create(0);
    return meta;
}

/* Reset a freshly constructed metaobject to its defaults, then intern the empty string as the
 * pool name, creating the shared string pool on first use. No previous lists are released. */
extern "C" igMetaObject *igMetaObject_Init(igMetaObject *meta){
    int pool,oldName,refCount;int *oldHeader;void *emptyToken;
    igObject_InitHeader(meta);meta->_vtable=(int)g_igMetaObject_vtable;
    meta->_name=0;
    meta->_poolName=0;
    meta->_metaFields=0;
    meta->_instances=0;
    meta->_children=0;
    meta->_parent=0;
    meta->_abstractProxy=0;
    meta->_writeProxy=0;
    meta->_templateObject=0;
    meta->_volatile=0;
    meta->_persistent=1;
    meta->_abstractState=0;
    meta->_majorVersion=1;
    meta->_minorVersion=0;
    meta->_index=0;
    meta->_id=0;
    meta->_metaFields=0;
    meta->_runTimeSize=0;
    meta->_instanceCount=0;
    meta->_validity=0;
    meta->_sizeofSize=-1;
    meta->_setupFunction=0;
    meta->_cleanupFunction=0;
    meta->_getMetaObjectFunction=0;
    meta->_requiredAlignment=4;
    meta->_vTablePointer=0;
    if(g_stringPool[0]==0){
        pool=FUN_002eb010(16);if(pool)pool=StringPool_Construct(pool);
        g_stringPool[0]=pool;
    }
    emptyToken=(void *)StringPool_Intern(g_stringPool[0],0);
    /* Drop the old pool-name token: owner chunk at -8, reference count at -4. */
    oldName=meta->_poolName;
    if(oldName){oldHeader=(int *)(oldName-8);refCount=*(int *)(oldName-4)-1;*(int *)(oldName-4)=refCount;
        if(!refCount)StringChunk_ReleaseHeader(*oldHeader,oldHeader);
    }
    meta->_poolName=(int)emptyToken;return meta;
}

/* Copy-construct: base header copy, vtable stamp and cleared names; the other
 * metadata members are not copied here. */
extern "C" void *igMetaObject_CopyConstruct(igMetaObject *meta,void *source){
    igObject_CopyConstructHeader(meta,source);
    meta->_vtable=(int)g_igMetaObject_vtable;
    meta->_name=0;
    meta->_poolName=0;
    return meta;
}

/* Drop the field list and then the child list: decrement the reference count
 * and destroy the list once its 23 low count bits reach zero.  The member cells
 * are left untouched. */
extern "C" void igMetaObject_ReleaseLists(igMetaObject *meta){
    igObject *list=(igObject *)meta->_metaFields;
    if(list){
        --list->_refCount;
        if(!(list->_refCount&0x7fffff))igObject_Destroy(list);
    }
    list=(igObject *)meta->_children;
    if(list){
        --list->_refCount;
        if(!(list->_refCount&0x7fffff))igObject_Destroy(list);
    }
}

extern "C" void *igMetaObject_CreateInstanceDefault(void *meta){return (void *)igMetaObject_CreateInstance((CreateMeta *)meta,Memory_GetDefaultAllocator());}

extern "C" int igMetaObject_CreateInstance(CreateMeta *arg0, MemoryPool *arg1) {
    int temp_s1;
    int temp_s1_2;
    char *temp_a0;
    MemoryPool *var_s2;
    MemoryPool *var_v0;
    CreateMeta *(*temp_v0)();

    var_s2 = arg1;
    temp_v0 = arg0->f60;
    if (temp_v0 != 0) {
        return igMetaObject_CreateInstance(temp_v0(), var_s2);
    }
    if (arg0->f26 == 1) {
        return 0;
    }
    if (var_s2 == 0) {
        temp_a0 = arg0->f96;
        if ((temp_a0 != 0) && (*temp_a0 != 0)) {
            var_s2 = Memory_GetAllocatorByName(temp_a0);
            if (var_s2 == 0) {
                var_v0 = Memory_GetDefaultAllocator();
                goto block_10;
            }
        } else {
            var_v0 = Memory_GetDefaultAllocator();
block_10:
            var_s2 = var_v0;
        }
    }
    temp_s1_2 = arg0->f32;
    temp_s1 = var_s2->vX(temp_s1_2 + arg0->f72);
    temp_s1 = temp_s1 + temp_s1_2;
    if (temp_s1 != 0) {
        igObject_Construct(temp_s1, arg0);
    }
    return temp_s1;
}

extern "C" int igMetaObject_CreateInstanceWithPool(PooledMeta *arg0, MemoryPool *arg1) {
    int temp_s1;
    int temp_s1_2;
    char *temp_a0;
    MemoryPool *var_s2;
    MemoryPool *var_v0;
    PooledMeta *(*temp_v0)();

    var_s2 = arg1;
    if (((arg0->f36 & 4) != 0) == 0) {
        return 0;
    }
    temp_v0 = arg0->f60;
    if (temp_v0 != 0) {
        return igMetaObject_CreateInstanceWithPool(temp_v0(), var_s2);
    }
    if (arg0->f26 == 1) {
        return 0;
    }
    if (var_s2 == 0) {
        temp_a0 = arg0->f96;
        if ((temp_a0 != 0) && (*temp_a0 != 0)) {
            var_s2 = Memory_GetAllocatorByName(temp_a0);
            if (var_s2 == 0) {
                var_v0 = Memory_GetDefaultAllocator();
                goto block_10;
            }
        } else {
            var_v0 = Memory_GetDefaultAllocator();
block_10:
            var_s2 = var_v0;
        }
    }
    temp_s1_2 = arg0->f32;
    temp_s1 = var_s2->vX(temp_s1_2 + arg0->f72);
    temp_s1 = temp_s1 + temp_s1_2;
    if (temp_s1 != 0) {
        igObject_ConstructPooled(temp_s1, arg0);
    }
    return temp_s1;
}

extern "C" void igMetaObject_AppendField(igMetaObject *meta, igMetaField *field);

extern "C" void igMetaObject_InheritFromBase(igMetaObject *meta,igMetaObject *parent){
    if(parent!=0){
        if(parent->_children==0)parent->_children=(int)FUN_002c29c0(Memory_GetAllocatorBySelector(*(int *)0x587040));
        ObjectPointerList_Append((void *)parent->_children,meta);
        meta->_parent=(int)parent;
        meta->_vTablePointer=parent->_vTablePointer;
        meta->_requiredAlignment=((igMetaObject *)meta->_parent)->_requiredAlignment;
        meta->_runTimeSize=((igMetaObject *)meta->_parent)->_runTimeSize;
        meta->_sizeofSize=((igMetaObject *)meta->_parent)->_sizeofSize;
        int count=((FieldPointerStorage *)parent->_metaFields)->count;
        for(int i=0;i<count;i++)igMetaObject_AppendField(meta,(igMetaField *)igMetaObject_GetFieldAt(parent,i));
    }
}

extern "C" int igMetaObject_CountInstances(MetaTreeNode *arg0, int arg1) {
    int s2 = arg0->f44;
    MetaTreeList *l;
    int s1;
    int s0;
    if (arg1 != 0) {
        l = arg0->f52;
        if (l != 0) {
            s0 = l->n;
            for (s1 = 0; s1 < s0; s1++) {
                s2 += igMetaObject_CountInstances(arg0->f52->arr[s1], 1);
            }
        }
    }
    return s2;
}

/* Give a metaobject its (interned) class name. The shared string pool is created on first use even
 * for a null name; the new name is interned first, then the previous name token is released. */
extern "C" void igMetaObject_SetName(igMetaObject *meta, int name) {
    int pool, internedName, oldName, refCount;
    int *oldHeader;

    if (g_stringPool[0] == 0) {
        pool = FUN_002eb010(16);
        if (pool) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    internedName = StringPool_Intern(g_stringPool[0], name);
    oldName = meta->_name;
    if (oldName) {
        oldHeader = (int *)(oldName - 8);
        refCount = *(int *)(oldName - 4) - 1;
        *(int *)(oldName - 4) = refCount;
        if (!refCount) {
            StringChunk_ReleaseHeader(*oldHeader, oldHeader);
        }
    }
    meta->_name = internedName;
}

extern "C" void igMetaObject_AppendField(igMetaObject *meta, igMetaField *field)
{
    MetaRefList_AppendRetained((void *)meta->_metaFields, field);
}

extern "C" void igMetaObject_FinalizeAndAppendField(void *meta,void *field){
    igMetaField_FinalizeDescriptor(field);igMetaObject_AppendField((igMetaObject *)meta,(igMetaField *)field);
}

extern "C" void igMetaObject_FinalizeAndReplaceField(igMetaObject *meta,int index,igMetaField *field){
    igMetaField_FinalizeDescriptor(field);
    InternalObjectList_SetAtRetained((void *)meta->_metaFields,index,field);
}

extern "C" int FUN_002fdef0(int a0, int a1)
{
    return a1;
}

/* The item array is read at +8 of the field list object. */
extern "C" int igMetaObject_GetFieldAt(igMetaObject *self, int index) {
    return *(int *)(*(int *)((char *)(self->_metaFields) + 8) + (index * 4));
}

extern "C" void *igMetaObject_FindFieldByName(igMetaObject *meta, const char *name) {
    return ObjectPointerList_FindByStringField((void *)meta->_metaFields, g_fieldNameMember[0], name);
}

extern "C" void igMetaObject_CreateFields(igMetaObject *meta,FieldFactory *factories,int count){
    int i;
    igMetaField *field;
    for(i=0;i<count;i++){
        field=factories[i](Memory_GetAllocatorBySelector(*(int *)0x587040));
        igMetaObject_AppendField(meta,field);
        --((RefHeader *)field)->refs;
        if(!(((RefHeader *)field)->refs&0x7fffff))igObject_Destroy(field);
    }
}

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

extern "C" void igMetaObject_FinalizeFieldLayout(LayoutMeta *arg0) {
    int off;
    int minAlign;
    unsigned short sz;
    int i;
    LayoutField *f;
    int count;
    int nneg;
    int end;
    unsigned short maxAlign;
    int maxEnd;
    bool flag;
    count = igMetaObject_GetFieldCount((igMetaObject *)arg0);
    off = 0;
    maxEnd = 0;
    minAlign = 4;
    nneg = 0;
    maxAlign = 4;
    for (i = 0; i < count; i++) {
        f = (LayoutField *)igMetaObject_GetFieldAt((igMetaObject *)arg0, i);
        sz = f->vX();
        if (maxAlign < sz) maxAlign = sz;
        if (f->neg != 0) {
            nneg++;
            off = ~(sz - 1) & (off - f->sz);
            f->off = off;
        } else {
            flag = 0;
            if (arg0->parent == 0 || igMetaObject_GetFieldCount((igMetaObject *)arg0->parent) <= i) {
                flag = 1;
            } else if ((LayoutField *)igMetaObject_GetFieldAt((igMetaObject *)arg0->parent, i) != f) {
                flag = 1;
            }
            if (flag) {
                f->idx = i - nneg;
                f->owner = arg0;
            }
            minAlign = (sz < minAlign) ? minAlign : sz;
        }
        end = f->off; end += f->sz;
        if (maxEnd < end) maxEnd = end;
    }
    arg0->w88 = maxAlign;
    if (arg0->w72 != -1) arg0->w32 = -(off & ~(minAlign - 1));
    arg0->w36 |= 4;
    FUN_002d3150(g_objectSystem[0], arg0);
}

extern "C" int FUN_002fe290(AncestorMeta *arg0, AncestorMeta *arg1) {
    while (arg0 != 0) {
        if (arg1 == arg0) {
            return 1;
        }
        arg0 = arg0->f56;
    }
    return 0;
}

extern "C" int igMetaObject_GetChildCount(igMetaObject *arg0) {
    void *temp_v0;

    temp_v0 = (void *)(arg0->_children);
    if (temp_v0 == 0) {
        return 0;
    }
    return *(int *)((char *)(temp_v0) + 12);
}

/* The item array is read at +8 of the child list object. */
extern "C" int igMetaObject_GetChildAt(igMetaObject *self, int index) {
    return *(int *)(*(int *)((char *)(self->_children) + 8) + (index * 4));
}

extern "C" void *FUN_002fe300(igMetaObject *arg0, int arg1) {
    int cnt;
    int acc;
    int i;
    int v;
    igMetaObject *k;
    if (arg1 == 0) {
        return arg0;
    }
    if (arg0->_children == 0) {
        return 0;
    }
    cnt = *(int *)(arg0->_children + 12);
    acc = 1;
    for (i = 0; i < cnt; i++) {
        k = ((igMetaObject **)*(int *)(arg0->_children + 8))[i];
        v = igMetaObject_CountTree((MetaTreeNode *)k);
        v += acc;
        if (arg1 < v) {
            return FUN_002fe300(k, arg1 - acc);
        }
        acc = v;
    }
    return 0;
}

extern "C" int igMetaObject_CountTree(MetaTreeNode *arg0) {
    MetaTreeList *l = arg0->f52;
    int s2;
    int s1;
    int s0;
    if (l == 0) return 1;
    s1 = l->n;
    s2 = 1;
    for (s0 = 0; s0 < s1; s0++) {
        s2 += igMetaObject_CountTree(arg0->f52->arr[s0]);
    }
    return s2;
}

extern "C" int igObjectSystem_FindMetaByNameDefault(const char *name){return igObjectSystem_FindMetaByName(g_objectSystem[0],name);}

/* Read from the field list's `_capacity` slot (+12), not `_count` (+8). */
extern "C" int igMetaObject_GetFieldCount(igMetaObject *self) {
    return ((igMetaFieldList *)self->_metaFields)->_capacity;
}

extern "C" void FUN_002fe480(int arg0) {
    FUN_002d30c0(g_objectSystem[0], arg0);
}

extern "C" void FUN_002fe490(int arg0) {
    FUN_002d30d0(g_objectSystem[0], arg0);
}

extern "C" void igMetaObject_AddField(igMetaObject *arg0, void *arg1) {
    int flags;
    int idx;
    char *m;
    int n;
    int i;

    flags = arg0->_validity;
    arg0->_validity = flags & ~4;
    *(char *)((char *)(arg1) + 37) = 1;
    *(int *)((char *)(arg1) + 24) = (int)(arg0);
    igMetaField_FinalizeDescriptor(arg1);
    idx = MetaRefList_AppendRetained((void *)arg0->_metaFields, arg1);
    n = igMetaObject_CountTree((MetaTreeNode *)arg0);
    for (i = 1; i < n; i++) {
        m = (char *)FUN_002fe300(arg0, i);
        *(int *)(m + 36) = *(int *)(m + 36) & ~4;
        InternalObjectList_InsertRetained(*(int *)(m + 40), idx, arg1);
    }
}

extern "C" void FUN_002fe5a0(int arg0);

extern "C" void FUN_002fe570(igMetaObject *arg0, void *arg1) {
    igMetaObject_AddField(arg0, arg1);
    FUN_002fe5a0((int)arg0);
}

extern "C" void FUN_002fe5a0(int arg0) {
    int temp_s1;
    int var_s0;
    temp_s1 = igMetaObject_CountTree((MetaTreeNode *)arg0);
    for (var_s0 = 0; var_s0 < temp_s1; var_s0++) {
        igMetaObject_FinalizeFieldLayout((LayoutMeta *)FUN_002fe300((igMetaObject *)arg0, var_s0));
    }
}

extern "C" int FUN_002fe600(igTDataList<ChainMeta *> *list, ChainMeta *object) {
    int i = list->find(object);
    if (i != -1) {
        return i;
    }
    int n = list->count();
    while (i == -1 && object != 0) {
        ChainRef retained(object);
        List_InsertWords(list, n, 1, &retained);
        object = object->parent;
        i = list->find(object);
    }
    return list->_count - 1;
}

extern "C" int FUN_002fe730(int arg0) {
    int n = 0;
    int i;

    for (i = 0; i < igMetaObject_GetFieldCount((igMetaObject *)arg0); i++) {
        if (*(unsigned char *)((char *)(igMetaObject_GetFieldAt((igMetaObject *)arg0, i)) + 37) == 0) {
            n += 1;
        }
    }
    return n;
}

/* Search the object system's registry; when absent (-1) append the metaobject and search again,
 * since appending can replace the registry. */
extern "C" void igMetaObject_AssignTypeId(igMetaObject *meta){
    meta->_index=ObjectPointerList_FindIndex(((ObjectSystemRecord *)g_objectSystem[0])->metaRegistry,meta);
    if(meta->_index==-1){
        igObjectSystem_AppendMetaObject(g_objectSystem[0],meta);
        meta->_index=ObjectPointerList_FindIndex(((ObjectSystemRecord *)g_objectSystem[0])->metaRegistry,meta);
    }
}

extern "C" void FUN_002fe810(int *out, PoolNameMeta *s, MemoryPool *a) {
    if (s->buf == 0) { *out = DAT_004fb418[0]; return; }
    if (s->f26 != 0) { *out = DAT_004fb418[0]; return; }
    if (a == 0) a = Memory_GetDefaultAllocator();
    int *p; int *base = s->buf;
    p = base;
    while (!*p) p++;
    while (*p != 0) p++;
    int n = (char *)p - (char *)base;
    int *nb = (int *)a->vX(n);
    if (nb == 0) { *out = DAT_004fb418[0]; return; }
    memcpy(nb, s->buf, n);
    s->buf = nb;
    *out = DAT_004fb410[0];
}

extern "C" int igMetaObject_GetPoolName(int *p)
{
    return *(int *)((char *)p + 96);
}

extern "C" void igMetaObject_RunStaticInit(StaticInitCallbacks *(*initialize)()){
    StaticInitCallbacks *list=initialize();
    int count; int i;
    if(list){count=list->count;for(i=0;i<count;i++)list->functions[i]();igArray_Destruct(list,1);}
}
