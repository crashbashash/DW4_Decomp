void *igMetaField_Construct(igMetaField *self) {
    igObject_ConstructHeader((igObject *)self);
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
igMetaField *igMetaField_Init(igMetaField *field){
    int pool;
    void *emptyToken;
    int oldName,refCount;
    int *oldHeader;
    igObject_InitHeader((struct ObjectHeader *)field);
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
        pool=((int)StringPool_Allocate(16));
        if(pool)pool=((int)StringPool_Construct((S_2eadf0 *)pool));
        g_stringPool[0]=pool;
    }
    emptyToken=((char *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)0));
    /* Interned strings carry a header in front of the characters: owner chunk at -8, reference
     * count at -4. */
    oldName=field->_fieldName;
    if(oldName){
        oldHeader=(int *)(oldName-8);
        refCount=*(int *)(oldName-4)-1;
        *(int *)(oldName-4)=refCount;
        if(!refCount)StringChunk_ReleaseHeader((StringChunkOwnerView *)(*oldHeader), (int)oldHeader);
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

igMetaField *igMetaField_CopyConstruct(igMetaField *dest, igMetaField *source) {
    int name;
    int refCount;
    int *nameHeader;

    igObject_CopyConstructHeader((CopyHeader *)dest, (CopyHeader *)source);
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
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*nameHeader), (int)nameHeader);
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

    dest->_default = (int)((char *)igObject_AllocateStorage((int)dest, dest->_size));
    memcpy((void *)dest->_default, (void *)source->_default, dest->_size);
    return dest;
}

void igMetaField_Destruct(igMetaField *arg0) {
    int temp_a1;

    temp_a1 = arg0->_default;
    if (temp_a1 != 0) {
        igObject_FreeStorage((int)arg0, temp_a1);
    }
    Gap__Core__igObject__vfunc_00__002ff0a0((int)arg0);
}

int FUN_002fc250(void) {
    if (((int *)DAT_00587188)[0] == 0) {
        ((int *)DAT_00587188)[0] = ((int)InternalObjectList_Create(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData))));
    }
    return ((int *)DAT_00587188)[0];
}

/* igMetaField slot +0x6c: a constant leaf returning -1. The receiver is not touched,
 * hence no parameters. */
int FUN_002fc2a0(void) {
    return -1;
}

int igMetaField_GetSize(void) {
    return 0;
}

/* Interned strings are reference counted in place: the count sits at (string - 4) and the owning
 * StringChunk header at (string - 8); dropping the last reference hands the header back with
 * StringChunk_ReleaseHeader. */
void igMetaField_Configure(igMetaField *self, int fieldName, int externalEnumStorage, int offset, int parentMetaObject) {
    void *internedName;
    int *chunkHeader;
    int refCount;
    int pool;
    void *name;

    if (fieldName == 0) {
        name = 0;
    } else {
        if (g_stringPool[0] == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((S_2eadf0 *)pool));
            }
            g_stringPool[0] = pool;
        }
        name = ((char *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)fieldName));
    }
    internedName = name;
    igMetaField_SetFieldName(self, &internedName);
    if (internedName != 0) {
        chunkHeader = (int *)((char *)internedName - 8);
        refCount = *(int *)((char *)internedName - 4) - 1;
        *(int *)((char *)internedName - 4) = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*chunkHeader), (int)chunkHeader);
        }
    }
    self->_externalEnumStorage = externalEnumStorage;
    self->_offset = offset;
    self->_parentMetaObject = parentMetaObject;
    igMetaField_EnsureDefaultStorage(self);
}

void igMetaField_EnsureDefaultStorage(igMetaField *field){
    field->_size=(unsigned short)((FieldSizeDispatchView *)field)->GetTypeSize();
    if(field->_default==0)field->_default=(int)FUN_00300e00((int)field, (int)field->_size, 1);
    else {
        int size=field->_size;
        if(((int)Memory_GetBufferSize((void *)field->_default))<size){
            igObject_FreeStorage((int)field, (int)((void *)field->_default));
            field->_default=(int)FUN_00300e00((int)field, (int)field->_size, 1);
        }
    }
}

void igMetaField_SetDefault(igMetaField *self, int defaultValue) {
    igMetaField_EnsureDefaultStorage(self);
    if (defaultValue != 0) {
        memcpy(self->_default, defaultValue, (int)self->_size);
    }
}

void igMetaField_SetFieldName(igMetaField *self, void **newName) {
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
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*chunkHeader), (int)chunkHeader);
        }
    }
    self->_fieldName = (int)*newName;
}

void igMetaField_Reset(igMetaField *field,void *object){
    switch(field->_resetMethod){
    case 0: ((FieldResetDispatchView *)field)->Reset0(object); break;
    case 3: ((FieldResetDispatchView *)field)->Reset3(object); break;
    case 2: ((FieldResetDispatchView *)field)->Reset2(object); break;
    }
}

void igMetaField_SetToDefault(DefaultCopyField *arg0, int arg1) {
    memcpy(arg1 + arg0->off, arg0->def, arg0->sz);
}

void igMetaField_CopyDefaultToValue(DefaultValueField *arg0, int arg1) {
    memcpy(arg1 + arg0->f8, arg0->f32, arg0->f20);
}

/* igMetaField reset hook, base implementation: an empty function, so a reset request leaves the
 * value alone. */
void igMetaField_IgnoreReset(void) {
}

short igMetaField_GetTypeIndex(TypeIndexView *arg0) {
    if (arg0->typeIndex == -1) {
        arg0->typeIndex = arg0->vX()->id;
    }
    return arg0->typeIndex;
}

/* Class-handle getter: returns the cached metaobject pointer in the global, the same global the
 * field constructor reads for a field's `_typeIndex`. */
int FUN_002fc620(void) {
    return g_igMetaFieldInfo_metaObject_00587190[0];
}

void igMetaField_FinalizeDescriptor(igMetaField *field){
    void *type=((FieldBuildDispatchView *)field)->TypeInfo();
    if(type!=0)field->_typeIndex=*(short *)((char *)type+18);
    else field->_typeIndex=-1;
    field->_size=(unsigned short)((FieldBuildDispatchView *)field)->TypeSize();
    ((FieldBuildDispatchView *)field)->SetDefault(0);
    if(field->_externalEnumStorage!=0)*(int *)field->_externalEnumStorage=(int)field;
}

int igMetaField_AlignSize(void *p, int size)
{
    int m = ((AlignmentView *)p)->v25() - 1;
    int s = size + m;
    m = ~m;
    return m & s;
}

int igMetaField_WritePersistentValue(igMetaField *field,void *object,void *output,void *context,int swap){
    if(field->_persistent==0)return 0;
    return (((FieldWriteDispatchView *)field)->Write((char *)object+field->_offset,output,context,swap)+3)&~3;
}

int FUN_002fc740(PersistentSizeView *p, int a1, int a2, int extra3, int extra4) {
    int r = p->v49(a1 + p->f, a2 + 4) + 4;
    return (r + 3) & -4;
}

int FUN_002fc780(void *arg0, int arg1, int extra2, int extra3, int extra4) {
    return (((ReadSizeView *)((int *)((char *)(arg0) + 0)))->vX((int)(arg1 + *(int *)((char *)(arg0) + 8))) + 3) & ~3;
}

unsigned short igMetaField_ReadRawFieldMem(RawReadView *arg0, int arg1, int arg2, int arg3, int arg4) {
    memcpy(arg1, arg2, arg0->f20);
    if (arg4 != 0) {
        arg0->vX(arg1, 1);
    }
    return arg0->f20;
}

unsigned short igMetaField_WriteRawFieldMem(unsigned short *arg0, int arg1, int arg2, int arg3, int arg4) {
    memcpy(arg2, arg1, arg0[10]);
    if (arg4 != 0) {
        ((RawWriteView *)arg0)->vX(arg2, 1);
    }
    return arg0[10];
}

int FUN_002fc8a0(igMetaField *arg0) {
    if (arg0->_persistent == 0 || arg0->_isRunTime != 0) {
        return 0;
    }
    return (arg0->_size + 3) & ~3;
}

void igMetaField_CopyByTechnique(CopyDispatchView *arg0, int arg1, int arg2, int arg3) {
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

void igMetaField_ShallowCopy(int a0, int a1, int a2, int a3) {
    igMetaField_CopyByTechnique((CopyDispatchView *)a0, a1, a2, *(char *)((char *)a0 + 39));
}

void igMetaField_DeepCopy(int a0, int a1, int a2, int a3) {
    igMetaField_CopyByTechnique((CopyDispatchView *)a0, a1, a2, *(char *)((char *)a0 + 40));
}

void igMetaField_ConstructCopy(int a0, int a1, int a2, int a3) {
    igMetaField_CopyByTechnique((CopyDispatchView *)a0, a1, a2, *(char *)((char *)a0 + 41));
}

void FUN_002fc9d0(void *arg0, int arg1, int arg2) {
    memcpy(arg1 + *(int *)((char *)(arg0) + 8), arg2 + *(int *)((char *)(arg0) + 8), *(unsigned short *)((char *)(arg0) + 20));
}

void FUN_002fc9f0(igMetaField *arg0, int arg1, int arg2) {
    memcpy(arg1 + arg0->_offset, arg2 + arg0->_offset, arg0->_size);
}

void FUN_002fca10(void *arg0, int arg1, int arg2) {
    memcpy(arg1 + *(int *)((char *)(arg0) + 8), arg2 + *(int *)((char *)(arg0) + 8), *(unsigned short *)((char *)(arg0) + 20));
}

void FUN_002fca30(igMetaField *field, void *object) {
    igMetaField_Reset(field, object);
}

void FUN_002fca40(void) {

}

int FUN_002fca50(void **arg0) {
    return ((TypeSizeView *)(arg0))->vX() & 0xFFFF;
}

igString_2fbf90 FUN_002fca80(StringJoinView *arg1, int arg2, int arg3, int arg4)
{
    int i;
    igString_2fbf90 *list;
    int total;
    int cnt;
    char *buf;
    char *p;

    list = (igString_2fbf90 *)((char *)igObject_AllocateStorage((int)arg1, arg3 * 4));
    total = 0;
    cnt = 0;
    for (i = 0; i < arg3; i++) {
        igString_2fbf90 part = arg1->v228(arg2, arg4);
        if (part.p != 0) {
            list[cnt++].assign(part);
            total += strlen(part.p);
            arg2 += arg1->v104();
        }
    }
    buf = ((char *)igObject_AllocateStorage((int)arg1, total + 1));
    p = buf;
    for (i = 0; i < cnt; i++) {
        p += sprintf(p, DAT_004f95a0, list[i].p);
    }
    *p = 0;
    igString_2fbf90 result(buf == 0 ? (char *)0 : ((char *)StringPool_Intern((StringPool *)(InternedStrings::get()), (const char *)buf)));
    FUN_00300f50((int)arg1, (int)list);
    FUN_00300f50((int)arg1, (int)buf);
    return result;
}

int FUN_002fcce0(ElementWriteView *arg0, int arg1, int arg2, int arg3, int arg4) {
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

int FUN_002fcdb0(igMetaField *arg0, int arg1) {
    int temp_a1 = arg1 + arg0->_offset;
    if (temp_a1 != 0) { return ((FieldValueView *)(((char *)(arg0) + 0)))->vX(temp_a1); }
    return 0;
}

igResult FUN_002fcdf0(igMetaFieldResultView *self, char *object)
{
    return self->vfunc_55(object + self->_offset);
}

void FUN_002fce10(int arg0, int arg1, int arg2) {
    strlen(arg2);
}

void FUN_002fce20(int *arg0, void *arg1) {
    int temp_s0;
    int var_v0;
    int var_v1;

    temp_s0 = *(int *)((char *)(arg1) + 12);
    if (temp_s0 == 0) {
        var_v1 = 0;
    } else {
        if (g_stringPool[0] == 0) {
            var_v0 = ((int)StringPool_Allocate(0x10));
            if (var_v0 != 0) {
                var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
            }
            g_stringPool[0] = var_v0;
        }
        var_v1 = (int)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)temp_s0);
    }
    *arg0 = var_v1;
}

int igMetaField_Write(igMetaField *arg0) {
    return -(arg0->_persistent == 0);
}

int igMetaField_IsAlikeByTechnique(void **arg0, int arg1, int arg2, int arg3) {
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

int igMetaField_IsAlikeExactly(int a0, int a1, int a2, int a3) {
    return igMetaField_IsAlikeByTechnique((void **)a0, a1, a2, *(char *)((char *)a0 + 42));
}

int igMetaField_IsAlikeDeep(int a0, int a1, int a2, int a3) {
    return igMetaField_IsAlikeByTechnique((void **)a0, a1, a2, *(char *)((char *)a0 + 43));
}

int igMetaField_IsAlikeShallow(int a0, int a1, int a2, int a3) {
    return igMetaField_IsAlikeByTechnique((void **)a0, a1, a2, *(char *)((char *)a0 + 44));
}

int FUN_002fcf90(ByteCompareField *arg0, unsigned char *arg1, unsigned char *arg2) {
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

bool FUN_002fcfe0(igMetaFieldSlots *self, const void *left, const void *right)
{
    return self->vfunc_43(left, right);
}

bool FUN_002fcff0(igMetaFieldSlots *self, const void *left, const void *right)
{
    return self->vfunc_43(left, right);
}

int FUN_002fd000(void) {
    return 1;
}

unsigned char FUN_002fd010(int a0, int a1, int a2, int a3) {
    return (igMetaField_IsAlikeExactly(a0, a1, a2, a3) != 0) ^ 1;
}

/* igMetaField slot +0xa8 (ReleaseElements), base implementation: a plain field owns no elements to
 * release. The memory-ref classes override it. */
void igMetaField_ReleaseElements(void) {
}

void igMetaField_ConstructValue(void)
{
}

void igMetaField_DestructValue(void)
{
}

/* igMetaField slot +0x84 (ZeroValue), base implementation: nothing to zero. igRefMetaField
 * overrides it to clear the reference slot at `instance + _offset`. */
void igMetaField_ZeroValue(void) {
}

/* igMetaField slot +0x88 (ClearValue), base implementation: nothing to clear. igRefMetaField
 * overrides it for its reference slot. */
void igMetaField_ClearValue(void) {
}

void igMetaField_Print(void *arg0, int arg1, int arg2, const char *arg3) {
    PrintString s = ((PrintView *)arg0)->vX(arg1 + ((PrintField *)arg0)->f8, 0);
    if (arg3 == 0) arg3 = &GPR_00554c28;
    FUN_00304430(DAT_004faf00, arg3, ((PrintField *)arg0)->fc, s.p);
    FUN_00304680();
    if (s.p != 0) {
        int *h = (int *)(s.p - 8);
        int c = *(int *)(s.p - 4) - 1;
        *(int *)(s.p - 4) = c;
        if (c == 0) StringChunk_ReleaseHeader((StringChunkOwnerView *)(*h), (int)h);
    }
}

void FUN_002fd130(CopyInField *arg0, int arg1, int arg2) {
    memcpy(arg1 + arg0->a, arg2, arg0->h);
}

void FUN_002fd150(igMetaFieldAssignView *self, void *object, igMetaFieldAssignView *field, char *source)
{
    self->vfunc_22(object, source + field->_offset);
}

void igMetaField_SwapBytes(SwapBytesField *arg0, unsigned char *arg1, int arg2) {
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

void igMetaField_SwapValue(igMetaFieldSwapView *self, char *object)
{
    self->SwapBytes(object + self->_offset, 1);
}

void FUN_002fd200(int arg0) {
    Gap__Core__igObject__vfunc_14();
    igMetaField_EnsureDefaultStorage((igMetaField *)arg0);
}

/* igMetaField slot +0xf0 (IsConstruct): whether the field's value is built by the field itself.
 * The base returns 0, so the generic object initialiser constructs a plain field's value;
 * igRefMetaField returns its declared `_construct` (+0x34) instead. */
int igMetaField_IsConstruct(void) {
    return 0;
}

int igMetaField_GetMangledName(igMetaField *arg0, void **arg1) {
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

static inline X_2fbf90 *cast0(X_2fbf90 *o) { if (o != 0 && igObject_IsKindOf((void *)o, (igMetaObject *)g_igMetaField_metaObject[0]) != 0) { return o; } return 0; }

