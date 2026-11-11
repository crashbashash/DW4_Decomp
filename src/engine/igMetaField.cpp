#include "dw4/igSmartPointer.h"

struct X : public igObject { char pad2[16]; int f24; };
struct FieldNameView { char pad12[12]; char *f12; };
struct MetaObjectNameView { char pad28[28]; char *f28; };
struct MetaObjectListView { char pad8[8]; MetaObjectNameView **data; int n; };
struct MetaObjectRegistryView { char pad24[24]; MetaObjectListView *f24; };

extern "C" {
int memcpy(...);
int strlen(...);
int strcat(...);
int strcpy(...);
int strcmp(...);
int strncmp(...);
char *strstr(...);
int sprintf(...);
int FUN_002eb010(...);
int StringPool_Construct(...);
char *StringPool_Intern(...);
void StringChunk_ReleaseHeader(int, int *);
char *igObject_AllocateStorage(void *, int);
void *igObject_ConstructHeader(void *);
void *igObject_InitHeader(void *);
void *igObject_CopyConstructHeader(void *, void *);
void igObject_FreeStorage(...);
int Gap__Core__igObject__vfunc_00__002ff0a0(...);
int InternalObjectList_Create(int);
int Memory_GetAllocatorBySelector(int);
int Memory_GetBufferSize(void *);
void *FUN_00300e00(igMetaField *,unsigned short,int);
igMetaField *igMetaField_Init(igMetaField *);
void igMetaField_SetFieldName(igMetaField *, void **);
void igMetaField_EnsureDefaultStorage(igMetaField *);
extern int g_igMetaField_vtable[4];
extern int g_stringPool[4];
extern int DAT_00587040[4];
extern int DAT_00587188[4];
extern int g_igMetaFieldInfo_metaObject_00587190[4];
int FUN_00300f50(void *, void *);
void FUN_00304430(void *, const char *, int, char *);
void FUN_00304680(void);
int Gap__Core__igObject__vfunc_14(...);
int FUN_002e2d30(...);
int igObject_IsKindOf(...);
int ObjectPointerList_FindIndex(...);
FieldNameView *igMetaObject_GetFieldAt(MetaObjectNameView *, int);
int igMetaObject_GetFieldCount(MetaObjectNameView *);
extern int DAT_004f95a0[4];
extern int DAT_004faf00[4];
extern char GPR_00554c28;
extern char *DAT_004c22b8[4];
extern char *DAT_004c22c0[4];
extern MetaObjectRegistryView *DAT_00586dc8[4];
extern int DAT_00585cc8[4];
}

extern "C" void *igMetaField_Construct(igMetaField *self) {
    igObject_ConstructHeader(self);
    self->_vtable = (int)g_igMetaField_vtable;
    self->_fieldName = 0;
    if (self) {
        igMetaField_Init(self);
    }
    return self;
}

/* igMetaField_Init: reset a freshly constructed field descriptor to its defaults. Every member
 * starts cleared, the type index is -1, and the descriptor is persistent. The name slot is then
 * given the interned empty token: the shared string pool is created on first use, the previous
 * name token (none for a fresh object) has its reference count dropped, and the pool's token
 * replaces it. */
extern "C" igMetaField *igMetaField_Init(igMetaField *field){
    int pool;
    void *emptyToken;
    int oldName,refCount;
    int *oldHeader;
    igObject_InitHeader(field);
    field->_vtable=(int)g_igMetaField_vtable;
    field->_fieldName=0;
    field->_offset=0;
    field->_isRunTime=0;
    field->_typeIndex=-1;
    field->_internalIndex=0;
    field->_size=0;
    field->_default=0;
    field->_externalEnumStorage=0;
    if(g_stringPool[0]==0){
        pool=FUN_002eb010(16);
        if(pool)pool=StringPool_Construct(pool);
        g_stringPool[0]=pool;
    }
    emptyToken=StringPool_Intern(g_stringPool[0],0);
    /* Interned strings carry a header in front of the characters: owner chunk at -8, reference
     * count at -4. */
    oldName=field->_fieldName;
    if(oldName){
        oldHeader=(int *)(oldName-8);
        refCount=*(int *)(oldName-4)-1;
        *(int *)(oldName-4)=refCount;
        if(!refCount)StringChunk_ReleaseHeader(*oldHeader,oldHeader);
    }
    field->_fieldName=(int)emptyToken;
    field->_parentMetaObject=0;
    field->_invarianceFunction=0;
    field->_resetMethod=0;
    field->_shallowCopyMethod=0;
    field->_deepCopyMethod=0;
    field->_constructCopyMethod=0;
    field->_isAlikeExactlyMethod=0;
    /* Method selector codes: the three comparison kinds default to 0, 1 and 2. */
    field->_isAlikeDeepMethod=1;
    field->_isAlikeShallowMethod=2;
    field->_persistent=1;
    return field;
}

extern "C" igMetaField *igMetaField_CopyConstruct(igMetaField *dest, igMetaField *source) {
    int name;
    int refCount;
    int *nameHeader;

    igObject_CopyConstructHeader(dest, source);
    dest->_vtable = (int)g_igMetaField_vtable;
    dest->_fieldName = 0;
    dest->_offset = source->_offset;
    dest->_isRunTime = source->_isRunTime;
    dest->_typeIndex = source->_typeIndex;
    dest->_size = source->_size;
    dest->_internalIndex = source->_internalIndex;
    dest->_externalEnumStorage = source->_externalEnumStorage;

    name = source->_fieldName;
    if (name) {
        ++*(int *)(name - 4);
    }
    name = dest->_fieldName;
    if (name) {
        nameHeader = (int *)(name - 8);
        refCount = *(int *)(name - 4) - 1;
        *(int *)(name - 4) = refCount;
        if (!refCount) {
            StringChunk_ReleaseHeader(*nameHeader, nameHeader);
        }
    }
    dest->_fieldName = source->_fieldName;

    dest->_parentMetaObject = source->_parentMetaObject;
    dest->_invarianceFunction = source->_invarianceFunction;
    dest->_resetMethod = source->_resetMethod;
    dest->_shallowCopyMethod = source->_shallowCopyMethod;
    dest->_deepCopyMethod = source->_deepCopyMethod;
    dest->_constructCopyMethod = source->_constructCopyMethod;
    dest->_isAlikeExactlyMethod = source->_isAlikeExactlyMethod;
    dest->_isAlikeDeepMethod = source->_isAlikeDeepMethod;
    dest->_isAlikeShallowMethod = source->_isAlikeShallowMethod;
    dest->_persistent = source->_persistent;

    dest->_default = (int)igObject_AllocateStorage(dest, dest->_size);
    memcpy((void *)dest->_default, (void *)source->_default, dest->_size);
    return dest;
}

extern "C" void igMetaField_Destruct(igMetaField *arg0) {
    int temp_a1;

    temp_a1 = arg0->_default;
    if (temp_a1 != 0) {
        igObject_FreeStorage(arg0, temp_a1);
    }
    Gap__Core__igObject__vfunc_00__002ff0a0(arg0);
}

extern "C" int FUN_002fc250(void) {
    if (DAT_00587188[0] == 0) {
        DAT_00587188[0] = InternalObjectList_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00587188[0];
}

/* igMetaField slot +0x6c: a constant leaf returning -1. The receiver is not touched,
 * hence no parameters. */
extern "C" int FUN_002fc2a0(void) {
    return -1;
}

extern "C" int igMetaField_GetSize(void) {
    return 0;
}

/* Interned strings are reference counted in place: the count sits at (string - 4) and the owning
 * StringChunk header at (string - 8); dropping the last reference hands the header back with
 * StringChunk_ReleaseHeader. */
extern "C" void igMetaField_Configure(igMetaField *self, int fieldName, int externalEnumStorage, int offset, int parentMetaObject) {
    void *internedName;
    int *chunkHeader;
    int refCount;
    int pool;
    void *name;

    if (fieldName == 0) {
        name = 0;
    } else {
        if (g_stringPool[0] == 0) {
            pool = FUN_002eb010(0x10);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        name = StringPool_Intern(g_stringPool[0], fieldName);
    }
    internedName = name;
    igMetaField_SetFieldName(self, &internedName);
    if (internedName != 0) {
        chunkHeader = (int *)((char *)internedName - 8);
        refCount = *(int *)((char *)internedName - 4) - 1;
        *(int *)((char *)internedName - 4) = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader(*chunkHeader, chunkHeader);
        }
    }
    self->_externalEnumStorage = externalEnumStorage;
    self->_offset = offset;
    self->_parentMetaObject = parentMetaObject;
    igMetaField_EnsureDefaultStorage(self);
}

class FieldSizeDispatchView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int GetTypeSize(); };

extern "C" void igMetaField_EnsureDefaultStorage(igMetaField *field){
    field->_size=(unsigned short)((FieldSizeDispatchView *)field)->GetTypeSize();
    if(field->_default==0)field->_default=(int)FUN_00300e00(field,field->_size,1);
    else {
        int size=field->_size;
        if(Memory_GetBufferSize((void *)field->_default)<size){
            igObject_FreeStorage(field,(void *)field->_default);
            field->_default=(int)FUN_00300e00(field,field->_size,1);
        }
    }
}

extern "C" void igMetaField_SetDefault(igMetaField *self, int defaultValue) {
    igMetaField_EnsureDefaultStorage(self);
    if (defaultValue != 0) {
        memcpy(self->_default, defaultValue, (int)self->_size);
    }
}

extern "C" void igMetaField_SetFieldName(igMetaField *self, void **newName) {
    int *chunkHeader;
    int refCount;
    void *incoming;
    void *previous;

    /* Retain the new name before releasing the old one. */
    incoming = *newName;
    if (incoming != 0) {
        *(int *)((char *)incoming - 4) += 1;
    }
    previous = (void *)self->_fieldName;
    if (previous != 0) {
        chunkHeader = (int *)((char *)previous - 8);
        refCount = *(int *)((char *)previous - 4) - 1;
        *(int *)((char *)previous - 4) = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader(*chunkHeader, chunkHeader);
        }
    }
    self->_fieldName = (int)*newName;
}

class FieldResetDispatchView {public: virtual void reserved0(); virtual void reserved1(); virtual void reserved2(); virtual void reserved3(); virtual void reserved4(); virtual void reserved5(); virtual void reserved6(); virtual void reserved7(); virtual void reserved8(); virtual void reserved9(); virtual void reserved10(); virtual void reserved11(); virtual void reserved12(); virtual void reserved13(); virtual void reserved14(); virtual void reserved15(); virtual void reserved16(); virtual void reserved17(); virtual void reserved18(); virtual void reserved19(); virtual void reserved20(); virtual void reserved21(); virtual void reserved22(); virtual void reserved23(); virtual void reserved24(); virtual void reserved25(); virtual void Reset0(void *); virtual void Reset3(void *); virtual void Reset2(void *);};
extern "C" void igMetaField_Reset(igMetaField *field,void *object){
    switch(field->_resetMethod){
    case 0: ((FieldResetDispatchView *)field)->Reset0(object); break;
    case 3: ((FieldResetDispatchView *)field)->Reset3(object); break;
    case 2: ((FieldResetDispatchView *)field)->Reset2(object); break;
    }
}

struct DefaultCopyField { int a, b; int off; int c[2]; unsigned short sz; short d; int e[2]; int def; };
extern "C" void igMetaField_SetToDefault(DefaultCopyField *arg0, int arg1) {
    memcpy(arg1 + arg0->off, arg0->def, arg0->sz);
}

struct DefaultValueField { int pad0[2]; int f8; int pad1[2]; unsigned short f20; short pad2; int pad3[2]; int f32; };
extern "C" void igMetaField_CopyDefaultToValue(DefaultValueField *arg0, int arg1) {
    memcpy(arg1 + arg0->f8, arg0->f32, arg0->f20);
}

/* igMetaField reset hook, base implementation: an empty function, so a reset request leaves the
 * value alone. */
extern "C" void igMetaField_IgnoreReset(void) {
}

struct igMetaObj { char pad[18]; short id; };
class TypeIndexView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual igMetaObj *vX();
    char pad[12];
    short typeIndex;
};
extern "C" short igMetaField_GetTypeIndex(TypeIndexView *arg0) {
    if (arg0->typeIndex == -1) {
        arg0->typeIndex = arg0->vX()->id;
    }
    return arg0->typeIndex;
}

/* Class-handle getter: returns the cached metaobject pointer in the global, the same global the
 * field constructor reads for a field's `_typeIndex`. */
extern "C" int FUN_002fc620(void) {
    return g_igMetaFieldInfo_metaObject_00587190[0];
}

class FieldBuildDispatchView { public: virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3(); virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7(); virtual void r8(); virtual void r9(); virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15(); virtual void r16(); virtual void r17(); virtual void r18(); virtual void r19(); virtual void r20(); virtual void *TypeInfo(); virtual void r96(); virtual int TypeSize(); virtual void r104(); virtual void r108(); virtual void r112(); virtual void r116(); virtual void r120(); virtual void r124(); virtual void r128(); virtual void r132(); virtual void r136(); virtual void SetDefault(void *); };

extern "C" void igMetaField_FinalizeDescriptor(igMetaField *field){
    void *type=((FieldBuildDispatchView *)field)->TypeInfo();
    if(type!=0)field->_typeIndex=*(short *)((char *)type+18);
    else field->_typeIndex=-1;
    field->_size=(unsigned short)((FieldBuildDispatchView *)field)->TypeSize();
    ((FieldBuildDispatchView *)field)->SetDefault(0);
    if(field->_externalEnumStorage!=0)*(int *)field->_externalEnumStorage=(int)field;
}

/* Rounds size up to a multiple of the field's alignment: (size + a - 1) & ~(a - 1). Reusing the
 * mask local for its complement (m = ~m) orders the temporaries so the nor lands in v0 and the sum
 * in v1. */
struct AlignmentView {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual int v25();
};
extern "C" int igMetaField_AlignSize(void *p, int size)
{
    int m = ((AlignmentView *)p)->v25() - 1;
    int s = size + m;
    m = ~m;
    return m & s;
}

class FieldWriteDispatchView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual int Write(void *,void *,void *,long long); };
extern "C" int igMetaField_WritePersistentValue(igMetaField *field,void *object,void *output,void *context,long long swap){
    if(field->_persistent==0)return 0;
    return (((FieldWriteDispatchView *)field)->Write((char *)object+field->_offset,output,context,swap)+3)&~3;
}

/* The class lists its virtual methods first so the vptr stays at offset 0 and the data words
 * follow at +4/+8. */
struct PersistentSizeView { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48();  virtual int v49(int, int); int pad; int f; };
extern "C" int FUN_002fc740(PersistentSizeView *p, int a1, int a2) {
    int r = p->v49(a1 + p->f, a2 + 4) + 4;
    return (r + 3) & -4;
}

class ReadSizeView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual int vX(int); };
extern "C" int FUN_002fc780(void *arg0, int arg1) {
    return (((ReadSizeView *)((int *)((char *)(arg0) + 0)))->vX((int)(arg1 + *(int *)((char *)(arg0) + 8))) + 3) & ~3;
}

class RawReadView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void vX(int, int); char pad4[16]; unsigned short f20; };
extern "C" unsigned short igMetaField_ReadRawFieldMem(RawReadView *arg0, int arg1, int arg2, int arg3, int arg4) {
    memcpy(arg1, arg2, arg0->f20);
    if (arg4 != 0) {
        arg0->vX(arg1, 1);
    }
    return arg0->f20;
}

class RawWriteView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void vX(int, int); };
extern "C" unsigned short igMetaField_WriteRawFieldMem(unsigned short *arg0, int arg1, int arg2, int arg3, int arg4) {
    memcpy(arg2, arg1, arg0[10]);
    if (arg4 != 0) {
        ((RawWriteView *)arg0)->vX(arg2, 1);
    }
    return arg0[10];
}

extern "C" int FUN_002fc8a0(igMetaField *arg0) {
    if (arg0->_persistent == 0 || arg0->_isRunTime != 0) {
        return 0;
    }
    return (arg0->_size + 3) & ~3;
}

class CopyDispatchView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33();
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
};

extern "C" void igMetaField_CopyByTechnique(CopyDispatchView *arg0, int arg1, int arg2, int arg3) {
    switch (arg3) {
    case 0:
        arg0->v0();
        break;
    case 1:
        arg0->v1();
        break;
    case 2:
        arg0->v2();
        break;
    case 3:
        arg0->v3();
        break;
    case 4:
        arg0->v4();
        break;
    }
}

extern "C" void igMetaField_ShallowCopy(int a0, int a1, int a2, int a3) {
    igMetaField_CopyByTechnique((CopyDispatchView *)a0, a1, a2, *(char *)((char *)a0 + 39));
}

extern "C" void igMetaField_DeepCopy(int a0, int a1, int a2, int a3) {
    igMetaField_CopyByTechnique((CopyDispatchView *)a0, a1, a2, *(char *)((char *)a0 + 40));
}

extern "C" void igMetaField_ConstructCopy(int a0, int a1, int a2, int a3) {
    igMetaField_CopyByTechnique((CopyDispatchView *)a0, a1, a2, *(char *)((char *)a0 + 41));
}

extern "C" void FUN_002fc9d0(void *arg0, int arg1, int arg2) {
    memcpy(arg1 + *(int *)((char *)(arg0) + 8), arg2 + *(int *)((char *)(arg0) + 8), *(unsigned short *)((char *)(arg0) + 20));
}

extern "C" void FUN_002fc9f0(igMetaField *arg0, int arg1, int arg2) {
    memcpy(arg1 + arg0->_offset, arg2 + arg0->_offset, arg0->_size);
}

extern "C" void FUN_002fca10(void *arg0, int arg1, int arg2) {
    memcpy(arg1 + *(int *)((char *)(arg0) + 8), arg2 + *(int *)((char *)(arg0) + 8), *(unsigned short *)((char *)(arg0) + 20));
}

extern "C" void FUN_002fca30(igMetaField *field, void *object) {
    igMetaField_Reset(field, object);
}

extern "C" void FUN_002fca40(void) {

}

class TypeSizeView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(); };
extern "C" int FUN_002fca50(void **arg0) {
    return ((TypeSizeView *)(arg0))->vX() & 0xFFFF;
}

struct igString {
    char *p;
    igString(char *text) : p(text) {}
    igString(const igString &other) : p(other.p) {
        char *o = p;
        if (o != 0) {
            *(int *)(o - 4) = *(int *)(o - 4) + 1;
        }
    }
    ~igString() {
        char *s = p;
        if (s != 0) {
            int *header = (int *)(s - 8);
            int count = *(int *)(s - 4) - 1;
            *(int *)(s - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader(*header, header);
            }
        }
    }
    void assign(const igString &other) {
        char *o = other.p;
        char *s;
        if (o != 0) {
            *(int *)(o - 4) = *(int *)(o - 4) + 1;
        }
        s = p;
        if (s != 0) {
            int *header = (int *)(s - 8);
            int count = *(int *)(s - 4) - 1;
            *(int *)(s - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader(*header, header);
            }
        }
        p = other.p;
    }
};
class StringJoinView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int v104(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual igString v228(int, int); };
struct InternedStrings {
    static inline int get() {
        if (g_stringPool[0] == 0) {
            int pool = FUN_002eb010(16);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        return g_stringPool[0];
    }
};
extern "C" igString FUN_002fca80(StringJoinView *arg1, int arg2, int arg3, int arg4)
{
    int i;
    igString *list;
    int total;
    int cnt;
    char *buf;
    char *p;

    list = (igString *)igObject_AllocateStorage(arg1, arg3 * 4);
    total = 0;
    cnt = 0;
    for (i = 0; i < arg3; i++) {
        igString part = arg1->v228(arg2, arg4);
        if (part.p != 0) {
            list[cnt++].assign(part);
            total += strlen(part.p);
            arg2 += arg1->v104();
        }
    }
    buf = igObject_AllocateStorage(arg1, total + 1);
    p = buf;
    for (i = 0; i < cnt; i++) {
        p += sprintf(p, DAT_004f95a0, list[i].p);
    }
    *p = 0;
    igString result(buf == 0 ? (char *)0 : StringPool_Intern(InternedStrings::get(), buf));
    FUN_00300f50(arg1, list);
    FUN_00300f50(arg1, buf);
    return result;
}

class ElementWriteView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vB(); virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19(); virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23(); virtual void e24(); virtual void e25(); virtual void e26(); virtual void e27(); virtual void e28(); virtual int vC(int, int, int); };
extern "C" int FUN_002fcce0(ElementWriteView *arg0, int arg1, int arg2, int arg3, int arg4) {
    int r;
    int s2 = arg1;
    int s1 = arg2;
    int i = 0;
    for (; i < arg3; i++) {
        r = arg0->vC(s1, s2, arg4);
        if (r != 0) {
            s2 = r + s2;
            s1 += arg0->vB();
        } else {
            return 0;
        }
    }
    return s2 - arg1;
}

class FieldValueView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual int vX(int); };
extern "C" int FUN_002fcdb0(igMetaField *arg0, int arg1) {
    int temp_a1 = arg1 + arg0->_offset;
    if (temp_a1 != 0) { return ((FieldValueView *)(((char *)(arg0) + 0)))->vX(temp_a1); }
    return 0;
}

class igResult {
public:
    int v;
    igResult(const igResult &o) : v(o.v) {}
};
class igMetaFieldResultView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54();
    virtual igResult vfunc_55(void *value);
    unsigned int _refCount;
    int _offset;
};

extern "C" igResult FUN_002fcdf0(igMetaFieldResultView *self, char *object)
{
    return self->vfunc_55(object + self->_offset);
}

extern "C" void FUN_002fce10(int arg0, int arg1, int arg2) {
    strlen(arg2);
}

extern "C" void FUN_002fce20(int *arg0, void *arg1) {
    int temp_s0;
    int var_v0;
    int var_v1;

    temp_s0 = *(int *)((char *)(arg1) + 12);
    if (temp_s0 == 0) {
        var_v1 = 0;
    } else {
        if (g_stringPool[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            g_stringPool[0] = var_v0;
        }
        var_v1 = (int)StringPool_Intern(g_stringPool[0], temp_s0);
    }
    *arg0 = var_v1;
}

extern "C" int igMetaField_Write(igMetaField *arg0) {
    return -(arg0->_persistent == 0);
}

class IsAlikeExactlyView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual int vX(); };
class IsAlikeDeepView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual int vX(); };
class IsAlikeShallowView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual int vX(); };
class IsAlikeSlot46View { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual int vX(); };
extern "C" int igMetaField_IsAlikeByTechnique(void **arg0, int arg1, int arg2, int arg3) {
    switch (arg3) {
    case 0:
        return ((IsAlikeExactlyView *)(arg0))->vX();
    case 1:
        return ((IsAlikeDeepView *)(arg0))->vX();
    case 2:
        return ((IsAlikeShallowView *)(arg0))->vX();
    case 3:
        return ((IsAlikeSlot46View *)(arg0))->vX();
    default:
        return 0;
    }
}

extern "C" int igMetaField_IsAlikeExactly(int a0, int a1, int a2, int a3) {
    return igMetaField_IsAlikeByTechnique((void **)a0, a1, a2, *(char *)((char *)a0 + 42));
}

extern "C" void igMetaField_IsAlikeDeep(int a0, int a1, int a2, int a3) {
    igMetaField_IsAlikeByTechnique((void **)a0, a1, a2, *(char *)((char *)a0 + 43));
}

extern "C" void igMetaField_IsAlikeShallow(int a0, int a1, int a2, int a3) {
    igMetaField_IsAlikeByTechnique((void **)a0, a1, a2, *(char *)((char *)a0 + 44));
}

struct ByteCompareField { char pad[8]; int base; char pad2[8]; unsigned short n; };
extern "C" int FUN_002fcf90(ByteCompareField *arg0, unsigned char *arg1, unsigned char *arg2) {
    unsigned char *p1;
    unsigned char *p2;
    int n;
    int i;
    int b;
    b = arg0->base;
    n = arg0->n;
    p1 = arg1 + b;
    p2 = arg2 + b;
    for (i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return 0;
        }
    }
    return 1;
}

class igMetaFieldSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42();
    virtual bool vfunc_43(const void *left, const void *right);
};

extern "C" bool FUN_002fcfe0(igMetaFieldSlots *self, const void *left, const void *right)
{
    return self->vfunc_43(left, right);
}

extern "C" bool FUN_002fcff0(igMetaFieldSlots *self, const void *left, const void *right)
{
    return self->vfunc_43(left, right);
}

extern "C" int FUN_002fd000(void) {
    return 1;
}

extern "C" unsigned char FUN_002fd010(int a0, int a1, int a2, int a3) {
    return (igMetaField_IsAlikeExactly(a0, a1, a2, a3) != 0) ^ 1;
}

/* igMetaField slot +0xa8 (ReleaseElements), base implementation: a plain field owns no elements to
 * release. The memory-ref classes override it. */
extern "C" void igMetaField_ReleaseElements(void) {
}

extern "C" void igMetaField_ConstructValue(void)
{
}

extern "C" void igMetaField_DestructValue(void)
{
}

/* igMetaField slot +0x84 (ZeroValue), base implementation: nothing to zero. igRefMetaField
 * overrides it to clear the reference slot at `instance + _offset`. */
extern "C" void igMetaField_ZeroValue(void) {
}

/* igMetaField slot +0x88 (ClearValue), base implementation: nothing to clear. igRefMetaField
 * overrides it for its reference slot. */
extern "C" void igMetaField_ClearValue(void) {
}

struct PrintString { char *p; PrintString() {} };
struct PrintView {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
    virtual PrintString vX(int, int);
};
struct PrintField { int vt; int pad; int f8; int fc; };
extern "C" void igMetaField_Print(void *arg0, int arg1, int arg2, const char *arg3) {
    PrintString s = ((PrintView *)arg0)->vX(arg1 + ((PrintField *)arg0)->f8, 0);
    if (arg3 == 0) arg3 = &GPR_00554c28;
    FUN_00304430(&DAT_004faf00[0], arg3, ((PrintField *)arg0)->fc, s.p);
    FUN_00304680();
    if (s.p != 0) {
        int *h = (int *)(s.p - 8);
        int c = *(int *)(s.p - 4) - 1;
        *(int *)(s.p - 4) = c;
        if (c == 0) StringChunk_ReleaseHeader(*h, h);
    }
}

struct CopyInField { int p[2]; int a; int q[2]; unsigned short h; };
extern "C" void FUN_002fd130(CopyInField *arg0, int arg1, int arg2) {
    memcpy(arg1 + arg0->a, arg2, arg0->h);
}

class igMetaFieldAssignView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void vfunc_22(void *object, const void *value);
    unsigned int _refCount;
    int _offset;
};

extern "C" void FUN_002fd150(igMetaFieldAssignView *self, void *object, igMetaFieldAssignView *field, char *source)
{
    self->vfunc_22(object, source + field->_offset);
}

struct SwapBytesField { char p[20]; unsigned short size; };
extern "C" void igMetaField_SwapBytes(SwapBytesField *arg0, unsigned char *arg1, int arg2) {
    int size = arg0->size;
    int i;
    int j;
    int half;
    int lo;
    int last;
    unsigned char *a;
    unsigned char *b;
    unsigned char t;
    if (size != 1) {
        for (i = 0, half = size >> 1; i < arg2; i++) {
            lo = i * size;
            last = (i + 1) * size - 1;
            for (j = 0; j < half; j++) {
                a = arg1 + (j + lo);
                b = arg1 + (last - j);
                t = *a;
                *a = *b;
                *b = t;
            }
        }
    }
}

class igMetaFieldSwapView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49();
    virtual void SwapBytes(void *value, int count);
    unsigned int _refCount;
    int _offset;
};

extern "C" void igMetaField_SwapValue(igMetaFieldSwapView *self, char *object)
{
    self->SwapBytes(object + self->_offset, 1);
}

extern "C" void FUN_002fd200(int arg0) {
    Gap__Core__igObject__vfunc_14();
    igMetaField_EnsureDefaultStorage((igMetaField *)arg0);
}

/* igMetaField slot +0xf0 (IsConstruct): whether the field's value is built by the field itself.
 * The base returns 0, so the generic object initialiser constructs a plain field's value;
 * igRefMetaField returns its declared `_construct` (+0x34) instead. */
extern "C" int igMetaField_IsConstruct(void) {
    return 0;
}

class MangledNameAllocatorView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };
extern "C" int igMetaField_GetMangledName(igMetaField *arg0, void **arg1) {
    int temp_s0;
    int temp_s2;
    int temp_s2_2;
    int temp_s2_3;
    int temp_s3;
    int var_s2;
    int var_v0;

    var_s2 = 0;
    if (arg0 != 0) {
        var_v0 = 0;
        if (arg1 != 0) {
            temp_s0 = arg0->_fieldName;
            temp_s3 = *(int *)((char *)(arg0->_parentMetaObject) + 28);
            temp_s2 = strlen(DAT_004c22b8[0]);
            temp_s2_2 = temp_s2 + strlen(temp_s0);
            temp_s2_3 = strlen(DAT_004c22c0[0]);
            temp_s2_3 = temp_s2_3 + temp_s2_2;
            var_s2 = strlen(temp_s3);
            var_s2 = ((MangledNameAllocatorView *)(arg1))->vX((int)(var_s2 + temp_s2_3 + 1));
            strcpy(var_s2, DAT_004c22b8[0]);
            strcat(var_s2, temp_s3);
            strcat(var_s2, DAT_004c22c0[0]);
            strcat(var_s2, temp_s0);
            goto block_3;
        }
    } else {
block_3:
        var_v0 = var_s2;
    }
    return var_v0;
}

class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int v96(int); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); };
class VB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void v264(int); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual void d206(); virtual void d207(); virtual void d208(); virtual void d209(); virtual void d210(); virtual void d211(); virtual void d212(); virtual void d213(); virtual void d214(); virtual void d215(); virtual void d216(); virtual void d217(); virtual void d218(); virtual void d219(); virtual void d220(); virtual void d221(); virtual void d222(); virtual void d223(); virtual void d224(); virtual void d225(); virtual void d226(); virtual void d227(); virtual void d228(); virtual void d229(); virtual void d230(); virtual void d231(); virtual void d232(); virtual void d233(); virtual void d234(); virtual void d235(); virtual void d236(); virtual void d237(); virtual void d238(); virtual void d239(); virtual void d240(); virtual void d241(); virtual void d242(); virtual void d243(); virtual void d244(); virtual void d245(); virtual void d246(); virtual void d247(); virtual void d248(); virtual void d249(); virtual void d250(); virtual void d251(); virtual void d252(); virtual void d253(); virtual void d254(); virtual void d255(); virtual void d256(); virtual void d257(); virtual void d258(); virtual void d259(); virtual void d260(); virtual void d261(); virtual void d262(); virtual void d263(); virtual void d264(); };
extern "C" VB *Memory_GetDefaultAllocator(...);

static inline X *cast0(X *o) { if (o != 0 && igObject_IsKindOf(o, DAT_00585cc8[0]) != 0) { return o; } return 0; }
extern "C" int Gap__Core__igMetaFieldInfo__vfunc_23(VA *arg0, int arg1, void *arg2) {
    int result = 0;
    igSmartPointer<X> held((X *)arg2, kRetainReference);
    X *field = cast0(held.get());
    VB *allocator = Memory_GetDefaultAllocator();
    if (field != 0) {
        int name = igMetaField_GetMangledName((igMetaField *)field, (void **)allocator);
        if (ObjectPointerList_FindIndex(DAT_00586dc8[0]->f24, field->f24) != -1 || arg0->v96(name) != 0) {
            result = FUN_002e2d30(arg1, arg0, name, arg2) & 0xFF;
        }
        allocator->v264(name);
    }
    return result;
}

extern "C" FieldNameView *igMetaField_FindByName(int arg0, char *arg1) {
    FieldNameView *found; char *q; char *s8; int n; int i; int j; int fc; MetaObjectNameView *o; MetaObjectListView *list; char *nm; FieldNameView *f;
    found = 0;
    if (strncmp(arg1, DAT_004c22b8[0], strlen(DAT_004c22b8[0])) == 0) {
        arg1 = arg1 + strlen(DAT_004c22b8[0]);
        q = strstr(arg1, DAT_004c22c0[0]);
        if (q != 0) {
            s8 = q + strlen(DAT_004c22c0[0]);
            i = 0;
            list = DAT_00586dc8[0]->f24;
            n = list->n;
            goto test;
body:
            o = 0;
            if (i < list->n) { o = list->data[i]; }
            nm = o->f28;
            if (strncmp(nm, arg1, strlen(nm)) == 0) {
                fc = igMetaObject_GetFieldCount(o);
                j = 0;
                goto t2;
b2:
                f = igMetaObject_GetFieldAt(o, j);
                if (strcmp(f->f12, s8) == 0) {
                    found = f;
                    goto next;
                }
                j++;
t2:
                if (j < fc) goto b2;
            }
next:
            i++;
test:
            if (i < n) goto body;
        }
    }
    return found;
}
