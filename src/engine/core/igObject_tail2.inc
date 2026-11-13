struct ObjectHeader *igObject_InitHeader(struct ObjectHeader *p) {
    p->vt = &g_igObject_vtable[0];
    p->refs = 1;
    p->flag = 0;
    p->b7 = 0;
    return p;
}

CopyHeader *igObject_CopyConstructHeader(CopyHeader *arg0, CopyHeader *arg1) {
    arg0->vt = (int)&g_igObject_vtable[0];
    if (arg0 != 0) {
        igObject_InitHeader((ObjectHeader *)arg0);
    }
    arg0->hi = arg1->hi;
    if (*g_objectSystem[0] != 0) {
        arg0->b7 = ((char)igAllocator_EncodeIndex((AllocatorLookupView *)(Memory_FindOwningAllocator((int)(igObject_GetAllocationBase(arg0))))));
    }
    return arg0;
}

igObject *igObject_ConstructHeader(igObject *self) {
    void **owner;

    self->_vtable = (int)(&g_igObject_vtable[0]);
    if (self != 0) {
        igObject_InitHeader((ObjectHeader *)self);
    }
    if (*g_objectSystem[0] != 0) {
        owner = (void **)(Memory_FindOwningAllocator((int)(igObject_GetAllocationBase(self))));
        if (owner != 0) {
            *(unsigned char *)((char *)(self) + 7) = ((DW4VC_364_0 *)(owner))->vX();
        } else {
            *(unsigned char *)((char *)(self) + 7) = 0;
        }
    } else {
        *(unsigned char *)((char *)(self) + 7) = 0;
    }
    return self;
}

/* Shared default virtual slots that almost every class inherits, so most are empty or return a
 * constant. The slot number is the only name evidence, so the bodies are documented by what they
 * do. The `__<addr>` names are distinct bodies resolved to the same slot. */
int Gap__Core__igObject__vfunc_00__002ff0a0(int extra0)
{
}

/* Slot 1 default: empty. */
void Gap__Core__igObject__constructFields(int extra0, int extra1)
{
}

/* Slot 2 default: empty. */
void Gap__Core__igObject__destructFields(int extra0)
{
}

/* Slot 3 default: empty. */
void Gap__Core__igObject__vfunc_03(void)
{
}

/* Slot 7 default: empty. */
void Gap__Core__igObject__userConstruct(void)
{
}

void Gap__Core__igObject__userDestruct(void)
{
}

/* Slot 4 default: empty. */
void Gap__Core__igObject__vfunc_04(void)
{
}

/* Slot 5 default: always 1. */
int Gap__Core__igObject__vfunc_05(void)
{
    return 1;
}

/* Slot 6 default: always 1. */
int Gap__Core__igObject__vfunc_06(void)
{
    return 1;
}

/* Slot 11 default: empty. */
void Gap__Core__igObject__resetFields(int extra0, int extra1)
{
}

/* Slot 9 default: empty. */
void Gap__Core__igObject__vfunc_09(int extra0)
{
}

/* Slot 10 default: empty. */
void Gap__Core__igObject__vfunc_10(int extra0)
{
}

/* Slot 12 default: empty. */
void Gap__Core__igObject__vfunc_12(void)
{
}

/* Slot 13 default: empty. */
void Gap__Core__igObject__vfunc_13(void)
{
}

/* Slot 15 default: empty. */
void Gap__Core__igObject__vfunc_15(void)
{
}

/* Slot 14 default: empty. */
void Gap__Core__igObject__vfunc_14(void)
{
}

/* Slot 16 default: empty. */
void Gap__Core__igObject__vfunc_16(int extra0)
{
}

/* Slot 17 default: empty. */
void Gap__Core__igObject__vfunc_17(void)
{
}

/* Slot 18 default: empty. */
void Gap__Core__igObject__vfunc_18(void)
{
}

void igObject_Construct(ConstructedObject *arg0, char *arg1) {
    Alloc_2fef20 *a;
    Lst_2fef20 *l;
    *(int *)((char *)arg0 + *(int *)((char *)g_objectSystem[0] + 916)) = *(int *)(arg1 + 92);
    arg0->u.w4 = 0;
    arg0->u.b.cnt = 1;
    arg0->u.c.hi = 0;
    a = (Alloc_2fef20 *)Memory_FindOwningAllocator((int)(igObject_GetAllocationBase(arg0)));
    if (a != 0) {
        arg0->u.c.id = a->vA();
    } else {
        arg0->u.c.id = 0;
    }
    igObject_ZeroFields((void **)arg0);
    igObject_ConstructFields((void **)arg0);
    igObject_ResetUnconstructedFields((void **)arg0);
    arg0->v11();
    arg0->v9(0);
    l = arg0->v22();
    if (l != 0) {
        l->cnt = l->cnt + 1;
        if (l->list != 0) {
            ObjectPointerList_Append((PointerList *)l->list, (int)arg0);
        }
    }
}

void igObject_ConstructPooled(PooledHeader *arg0, char *arg1) {
    G_2fef20 *g;

    *(int *)((char *)arg0 + *(int *)((char *)(g_objectSystem[0]) + 916)) = *(int *)(arg1 + 92);
    arg0->refs = 1;
    arg0->flag = 0 & 1;
    g = (G_2fef20 *)Memory_FindOwningAllocator((int)(igObject_GetAllocationBase(arg0)));
    if (g != 0) {
        arg0->rest = g->vX();
    } else {
        arg0->rest = 0;
    }
    igObject_ZeroFields((void **)arg0);
}

void igObject_RegisterInstance(void **arg0, void *arg1) {
    int temp_a0;
    void *temp_v0;

    if ((arg1 != 0) && (*(int *)((char *)(arg1) + 60) != 0)) {
        ((DW4VC_80_0 *)(arg0))->vX();
    }
    ((DW4VC_12_1 *)(arg0))->vX((int)(0));
    ((DW4VC_52_1 *)(arg0))->vX((int)(0));
    ((DW4VC_36_1 *)(arg0))->vX((int)(1));
    temp_v0 = (void *)(((DW4VC_88_0 *)(arg0))->vX());
    if (temp_v0 != 0) {
        *(int *)((char *)(temp_v0) + 44) = (int)((int) (*(int *)((char *)(temp_v0) + 44) + 1));
        temp_a0 = *(int *)((char *)(temp_v0) + 48);
        if (temp_a0 != 0) {
            ObjectPointerList_Append((PointerList *)temp_a0, (int)arg0);
        }
    }
}

/* Class-registration "extra callbacks" factory for igObject (passed to igMetaObject_RegisterClass
 * by igObject_Register): allocate a 12-byte callback array from the metadata allocator selector
 * and construct it empty. Returns the array, or 0 when the allocation fails. */
int igObject_CreateEmptyInitCallbacks(void) {
    int callbacks;

    callbacks = ((int)Memory_AllocateBufferDirect(0xC, (igMemoryPool_2ed1c0 *)((igMemoryPool *)(((void **)Memory_GetAllocatorBySelector(g_memoryContextMetaData))))));
    if (callbacks != 0) {
        callbacks = ((int)igArray_Construct((CallbackArray *)callbacks));
    }
    return callbacks;
}

void *igObject_GetNoParentMetaObject(void){return 0;}

int igObject_GetVTable(void) {
    int o[2];

    igObject_InitHeader((ObjectHeader *)o);
    return *(int *)((char *)o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igObject_EnsureRegistered(void){igMetaObject_RunStaticInit((StaticInitCallbacks *(*)())igObject_Register);}

void *igObject_Register(void) {
    return ((void *)igMetaObject_RegisterClass(
        0, /* abstract */
        g_igObject_metaObject,
        igObject_CreateEmptyInitCallbacks,
        igObject_GetNoParentMetaObject,
        igObject_GetMetaObject,
        igObject_className,
        8, /* instance size */
        igObject_GetVTable,
        &igObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    ));
}

void *igObject_GetMetaObject(void){return (void *)g_igObject_metaObject[0];}

void igObject_InitFields(void) {
    void *sp2C;
    void *sp28;
    int *temp_a1;
    int *temp_a1_2;
    int temp_v0_2;
    int temp_v0_4;
    int var_v0_2;
    int var_v0_4;
    igUnsignedIntMetaField *temp_v0;
    igUnsignedIntMetaField *temp_v0_3;
    void *var_v0;
    void *var_v0_3;

    temp_v0 = ((igUnsignedIntMetaField *)igUnsignedIntMetaField_Create((int)(((void **)Memory_GetAllocatorBySelector(g_memoryContextMetaData)))));
    temp_v0->_offset = 4;
    temp_v0->_externalEnumStorage = (int)(&DAT_005871a0[0]);
    if (&text_refCount[0] == 0) {
        var_v0 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_2 = ((int)StringPool_Allocate(0x10));
            if (var_v0_2 != 0) {
                var_v0_2 = ((int)StringPool_Construct((S_2eadf0 *)var_v0_2));
            }
            g_stringPool[0] = var_v0_2;
        }
        var_v0 = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)&text_refCount[0])));
    }
    sp2C = (void *)(var_v0);
    igMetaField_SetFieldName((igMetaField *)temp_v0, &sp2C);
    if (sp2C != 0) {
        temp_a1 = (int *)((char *)sp2C - 8);
        temp_v0_2 = *(int *)((char *)(sp2C) - 4) - 1;
        *(int *)((char *)(sp2C) - 4) = temp_v0_2;
        if (temp_v0_2 == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
        }
    }
    temp_v0->_persistent = 0;
    temp_v0->_resetMethod = 3;
    igMetaObject_FinalizeAndAppendField(g_igObject_metaObject[0], temp_v0);
    temp_v0->_refCount = (int)temp_v0->_refCount - 1;
    if (((unsigned long long)((long long)(int)temp_v0->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0);
    }
    temp_v0_3 = ((igUnsignedIntMetaField *)igUnsignedIntMetaField_Create((int)(((void **)Memory_GetAllocatorBySelector(g_memoryContextMetaData)))));
    temp_v0_3->_offset = 4;
    temp_v0_3->_externalEnumStorage = (int)(&DAT_005871a8[0]);
    if (&text_memPoolIndex[0] == 0) {
        var_v0_3 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_4 = ((int)StringPool_Allocate(0x10));
            if (var_v0_4 != 0) {
                var_v0_4 = ((int)StringPool_Construct((S_2eadf0 *)var_v0_4));
            }
            g_stringPool[0] = var_v0_4;
        }
        var_v0_3 = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)&text_memPoolIndex[0])));
    }
    sp28 = (void *)(var_v0_3);
    igMetaField_SetFieldName((igMetaField *)temp_v0_3, &sp28);
    if (sp28 != 0) {
        temp_a1_2 = (int *)((char *)sp28 - 8);
        temp_v0_4 = *(int *)((char *)(sp28) - 4) - 1;
        *(int *)((char *)(sp28) - 4) = temp_v0_4;
        if (temp_v0_4 == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1_2), (int)temp_a1_2);
        }
    }
    temp_v0_3->_persistent = 0;
    temp_v0_3->_resetMethod = 3;
    igMetaObject_FinalizeAndAppendField(g_igObject_metaObject[0], temp_v0_3);
    temp_v0_3->_refCount = (int)temp_v0_3->_refCount - 1;
    if (((unsigned long long)((long long)(int)temp_v0_3->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_3);
    }
}

char *igObject_AllocateRawStorage(int size, int prefix_size, void **requested_allocator) {
    int total_size;
    void **allocator;

    allocator = requested_allocator;
    total_size = size + prefix_size;
    if (allocator == 0) {
        allocator = (void **)Memory_GetAllocatorBySelector(g_memoryContextBootstrap);
    }
    if (allocator == 0) {
        /* no allocator at all: the prefix is not added on this path (retail behaviour) */
        return ((char *)malloc(total_size));
    }
    return ((DW4VC_216_2 *)allocator)->vX(total_size) + prefix_size;
}

void *igObject_AllocateRawStorageDefault(int size,int prefix){return igObject_AllocateRawStorage(size,prefix,0);}

int thunk_FUN_002ed460__002ff810(int extra0)
{
    return Memory_FreeBuffer((void *)extra0);
}

void igObject_Destroy(void *input){
    igObjectDispatchView *object;
    igMetaObject *type;
    void *instances;
    if(g_objectSystem[0]){
        unsigned char mode=*g_objectSystem[0];
        /* matching construct: hand search — the copy is taken after the mode load; taken at the top of the function it moves into the null-system branch's delay slot */
        object=(igObjectDispatchView *)input;
        if(!mode){
            object->slot_08();object->slot_10();object->slot_00();
            Memory_FreeBuffer(object);return;
        }
        type=object->slot_20();
        type->_instanceCount=(int)((unsigned)type->_instanceCount-1);
        instances=(void *)type->_instances;
        if(instances)ObjectPointerList_EraseAt((PointerList *)instances, ObjectPointerList_FindIndex((char *)instances, (int)object));
        object->slot_16();object->slot_08();object->slot_10();
        igObject_DestructFieldValues((int *)object);igObject_ClearFieldValues((int *)object);
        Memory_FreeBuffer(igObject_GetAllocationBase(object));
    }
}

static inline int isValid(igMetaObject *m) { return (m->_validity & 4) != 0; }

void igObject_ZeroFields(void **arg0) {
    igMetaObject *temp_v0;
    int var_s3;
    void **temp_a0;
    void *temp_s1;
    int temp_s0;

    temp_v0 = (igMetaObject *)(((DW4VC_88_0 *)(arg0))->vX());
    if (((temp_v0 != 0) && isValid(temp_v0)) || (*(unsigned char *)((char *)(g_objectSystem[0]) + 20) == 0) || (*(unsigned char *)((char *)(g_objectSystem[0]) + 0) != 0)) {
        temp_s1 = (void *)(temp_v0->_metaFields);
        var_s3 = *(int *)((char *)(g_igObject_metaObject[0]->_metaFields) + 12);
        temp_s0 = *(int *)((char *)(temp_s1) + 12);
        for (; var_s3 < temp_s0; var_s3++) {
            temp_a0 = (void **)(*(int *)(*(int *)((char *)(temp_s1) + 8) + (var_s3 * 4)));
            ((DW4VC_132_1 *)(temp_a0))->vX((int)(arg0));
        }
    }
}

void igObject_ConstructFields(void **arg0) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the declaration order of the locals sets their stack slot and register assignment */
    char *meta;
    void **o;
    int n;
    int i;

    meta = (char *)(*(int *)((char *)(((DW4VC_88_0 *)(arg0))->vX()) + 40));
    i = *(int *)((char *)(*(int *)((char *)(g_igObject_metaObject[0]) + 40)) + 12);
    n = *(int *)(meta + 12);
    while (i < n) {
        o = (void **)(*(int *)(*(int *)(meta + 8) + (i * 4)));
        ((DW4VC_124_1 *)(o))->vX((int)(arg0));
        i++;
    }
    ((DW4VC_12_1 *)(arg0))->vX((int)(1));
}

void igObject_ResetFields(void **arg0) {
    /* matching construct: variant search — decl order [2, 1, 0]; the declaration order of the locals sets their stack slot and register assignment */
    List_2fef20 *temp_s2;
    int temp_s1;
    int var_s0;

    temp_s2 = ((V88_2fef20 *)arg0)->vX()->f40;
    var_s0 = ((ResetMeta *)g_igObject_metaObject[0])->f40->count;
    temp_s1 = temp_s2->count;
    while (var_s0 < temp_s1) {
        igMetaField_Reset((igMetaField *)temp_s2->data[var_s0], (void *)arg0);
        var_s0++;
    }
    ((V52 *)arg0)->vX(1);
}

void igObject_ResetUnconstructedFields(void **arg0) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the declaration order of the locals sets their stack slot and register assignment */
    char *meta;
    void **o;
    int n;
    int i;

    meta = (char *)(*(int *)((char *)(((DW4VC_88_0 *)(arg0))->vX()) + 40));
    i = *(int *)((char *)(*(int *)((char *)(g_igObject_metaObject[0]) + 40)) + 12);
    n = *(int *)(meta + 12);
    while (i < n) {
        o = (void **)(*(int *)(*(int *)(meta + 8) + (i * 4)));
        if (((DW4VC_240_0 *)(o))->vX() == 0) {
            igMetaField_Reset((igMetaField *)o, (void *)arg0);
        }
        i++;
    }
    ((DW4VC_52_1 *)(arg0))->vX((int)(1));
}

void igObject_DestructFieldValues(int *arg0) {
    DestructFieldList *q;
    int i;
    int n;

    ((DestructSelf *)arg0)->vX();
    q = (DestructFieldList *)((int *)((MetaSource *)arg0)->vX())[10];
    i = ((DestructFieldList *)((int *)g_igObject_metaObject[0])[10])->count;
    n = q->count;
    for (; i < n; i++) {
        q->data[i]->vX(arg0);
    }
}

void igObject_ClearFieldValues(int *arg0) {
    ClearFieldList *q;
    int i;
    int n;

    q = (ClearFieldList *)((int *)((MetaSource *)arg0)->vX())[10];
    i = ((ClearFieldList *)((int *)g_igObject_metaObject[0])[10])->count;
    n = q->count;
    for (; i < n; i++) {
        q->data[i]->vX(arg0);
    }
}

int igObject_GetSerializedSize(SizeObject *arg0) {
    SizeMeta *m0 = arg0->GetMeta();
    SizeMeta *m;
    int size, i, n;
    SizeMeta *(*fp)();
    fp = m0->f40;
    if (fp != 0) { m = fp(); } else { m = m0; }
    if (m->b19 == 0) return 0;
    size = 8;
    i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]);
    n = igMetaObject_GetFieldCount((igMetaObject *)m);
    for (; i < n; i++) { size += ((SizeField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)m, i)))->GetSize(arg0); }
    return size;
}

int igObject_WritePersistentFields(O_2fef20 * arg0, int * arg1, int arg2, void * r3, void * r4) {
    int arg3 = (int)r3;
    int arg4 = (int)r4;
    WriteMeta *m;
    int id;
    int i;
    FI *f;

    m = arg0->v88();
    if (m->persistent == 0) {
        return 0;
    }
    arg0->v56();
    id = 0;
    m = (m->getter != 0) ? (WriteMeta *)m->getter() : m;
    if (arg3 != 0) {
        id = FUN_002fe600((igTDataList<ChainMeta *> *)arg3, (ChainMeta *)m);
    }
    arg3 = igMetaObject_GetFieldCount((igMetaObject *)m);
    i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]);
    arg1[0] = id;
    id = i;
    arg1[1] = igObject_GetSerializedSize((SizeObject *)arg0);
    if (arg4 != 0) {
        ((SwapDescriptor *)igIntMetaField_GetDefaultDescriptor())->Swap(arg1, 2);
    }
    arg1 += 2;
    for (; id < arg3; id++) {
        f = (FI *)igMetaObject_GetFieldAt((igMetaObject *)m, id);
        if (f->f38 == 1 && f->f37 == 0) {
            arg1 = (int *)((char *)arg1 + igMetaField_WritePersistentValue((igMetaField *)f, (void *)arg0, (void *)arg1, (void *)arg2, arg4));
        }
    }
    return igObject_GetSerializedSize((SizeObject *)arg0);
}

int FUN_002fff90(ReadObject *arg0, Dat_2fef20 *arg1, int arg2, int arg3, int arg4) {
    igMetaObject *m;
    char *s2;
    int s1;
    int cnt;
    int s6, s7;
    igMetaField *f;
    m = arg0->v20();
    if (m->_persistent == 0) return 0;
    if (arg4 != 0) {
        ((SwapDescriptor *)igIntMetaField_GetDefaultDescriptor())->Swap(arg1, 3);
    }
    s2 = (char *)arg1 + 12;
    s1 = igMetaObject_GetFieldCount(g_igObject_metaObject[0]);
    cnt = igMetaObject_GetFieldCount((igMetaObject *)m);
    s6 = 0;
    s7 = 0;
    for (; s1 < cnt; s1++) {
        f = (igMetaField *)igMetaObject_GetFieldAt(m, s1);
        if (f->_isRunTime != 0) {
            s6 += 1;
            ((ReadField *)f)->v29(arg0);
            if (igObject_IsKindOf(f, (igMetaObject *)g_igRefMetaField_metaObject[0]) == 0 || *(unsigned char *)((char *)f + 52) == 0) igMetaField_Reset(f, arg0);
        } else if (s7 >= arg1->f8) {
            ((ReadField *)f)->v29(arg0);
            if (igObject_IsKindOf(f, (igMetaObject *)g_igRefMetaField_metaObject[0]) == 0 || *(unsigned char *)((char *)f + 52) == 0) igMetaField_Reset(f, arg0);
        } else {
            if (arg4 != 0) ((SwapDescriptor *)igShortMetaField_GetDefaultDescriptor())->Swap(s2, 2);
            if (s1 < *(short *)s2 + s6) {
                ((ReadField *)f)->v29(arg0);
                if (igObject_IsKindOf(f, (igMetaObject *)g_igRefMetaField_metaObject[0]) == 0 || *(unsigned char *)((char *)f + 52) == 0) igMetaField_Reset(f, arg0);
                if (arg4 != 0) ((SwapDescriptor *)igShortMetaField_GetDefaultDescriptor())->Swap(s2, 2);
            } else {
                s7 += 1;
                s2 += FUN_002fc740((PersistentSizeView *)f, (int)arg0, (int)s2, arg2, arg4);
            }
        }
    }
    {
        int r = arg1->f4;
        if (arg4 != 0) ((SwapDescriptor *)igIntMetaField_GetDefaultDescriptor())->Swap(arg1, 3);
        arg0->v14();
        return r;
    }
}

void FUN_00300490(void **arg0, int arg1, int arg2) {
    void **temp_a0;
    void *temp_s3;
    int temp_v0;
    unsigned int temp_s1;
    unsigned int var_s0;

    temp_s3 = (void *)(((DW4VC_88_meta *)(arg0))->vX()->_metaFields);
    FUN_00304430(DAT_004faf60, arg2, arg0, ((DW4VC_88_meta *)(arg0))->vX()->_name);
    FUN_00304680();
    if (arg1 != 0) {
        temp_v0 = igObject_AllocateStorage((int)arg0, (strlen(arg2) + 2) * 4);
        sprintf(temp_v0, &DAT_004faf78[0], arg2);
        ((DW4VC_72_0 *)(arg0))->vX();
        temp_s1 = *(int *)((char *)(temp_s3) + 12);
        var_s0 = *(int *)((char *)(g_igObject_metaObject[0]->_metaFields) + 12);
        FUN_00304430(DAT_004faf80, arg2);
        FUN_00304680();
        for (; var_s0 < temp_s1; var_s0++) {
            int *base = *(int **)((char *)(temp_s3) + 8);
            temp_a0 = (void **)base[var_s0];
            { int d = arg1 - 1; ((DW4VC_164_3 *)(temp_a0))->vX((int)(arg0), d, (int)(temp_v0)); }
        }
        FUN_00304430(DAT_004faf88, arg2);
        FUN_00304680();
        FUN_00300f50((int)arg0, temp_v0);
    }
}

void igObject_VisitFields(VisitorObjectView *object,Visitor callback,void *context){
    FieldVector *fields;
    int count;
    int i;
    VisitorFieldView *field;
    if(callback(object,0,context)==1)return;
    object->Prepare();
    fields=(FieldVector *)object->Meta()->_metaFields;
    count=fields->count;
    for(i=igMetaObject_GetFieldCount((igMetaObject *)g_igObject_metaObject[0]);i<count;++i){
        field=fields->data[i];
        if(callback(object,field,context)!=1)field->Visit(object,callback,context);
    }
}

void FUN_00300c00(int arg0, int arg1, int arg2) {
    switch (arg2) {
    case 1:
        FUN_003006a0((void **)arg0, (void **)arg1);
        break;
    case 0:
        FUN_00300770((ShallowObject *)arg0, arg1);
        break;
    case 2:
        FUN_00300600((void **)arg0, arg1);
        break;
    }
}

/* Generic clone of any object. Asks the source for its metaobject through vtable slot 20 (the
 * GetMetaObject slot), creates an instance of that class on the source's own allocator and copies
 * the contents across. `copyMode` is passed to the contents copy unchanged (the copy dispatches on
 * 0, 1 and 2). */
int igObject_CloneViaMetadata(void **source, int copyMode) {
    int metaObject;
    int copy;

    metaObject = ((DW4VC_88_0 *)(source))->vX();
    copy = igMetaObject_CreateInstance((CreateMeta *)metaObject, (MemoryPool *)(igObject_GetAllocator((int)source)));
    FUN_00300c00(copy, (int)source, copyMode);
    return copy;
}

int igObject_IsKindOf(void *object, igMetaObject *kind) {
    igMetaObject *meta = (igMetaObject *)((KindVC *)object)->vX((int)kind);
    while (meta != 0) {
        if (meta == kind) return 1;
        meta = (igMetaObject *)meta->_parent;
    }
    return 0;
}

void *igObject_GetAllocationBase(void *self) {
    return (char *)self - ((MetadataDispatchView *)self)->GetMetadata()->_runTimeSize;
}

/* Object storage dispatch: every helper re-selects the allocator from the object header
 * (igObject_GetAllocator) and calls one slot of that allocator's vtable, forwarding its arguments
 * unchanged. */
int igObject_AllocateStorage(int object, int size) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->allocate_storage(size);
}

int FUN_00300db0(int object, int size, int alignment) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_220(size, alignment);
}

int FUN_00300e00(int object, int size, int option) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_224(size, option);
}

int FUN_00300e50(int object, int storage, int size) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_232(storage, size);
}

int FUN_00300ea0(int object, int storage, int size, int alignment) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_236(storage, size, alignment);
}

/* A null storage pointer returns without touching the allocator */
void igObject_FreeStorage(int object, int storage) {
    if (storage != 0) {
        Allocator *allocator = igObject_GetAllocator(object);
        allocator->free_storage(storage);
    }
}

/* Same instruction body as igObject_FreeStorage. */
void FUN_00300f50(int object, int storage) {
    if (storage != 0) {
        Allocator *allocator = igObject_GetAllocator(object);
        allocator->free_storage(storage);
    }
}

/* Copy a C string into storage owned by `self`: allocate strlen + 1 bytes with the igObject
 * storage allocator (vtable slot 216, igObject_AllocateStorage), strcpy into it and return the
 * copy. */
int igObject_DuplicateString(int self, int string) {
    int copy;

    copy = igObject_AllocateStorage(self, strlen(string) + 1);
    strcpy(copy, string);
    return copy;
}

Allocator *igObject_GetAllocator(int a0) {
    return ((Allocator *)igAllocator_ResolveEncodedIndex(*(unsigned char *)((char *)a0 + 7)));
}

igSmartPointer<ClonedObject> FUN_00301010(CloneSource *arg1, int arg2) {
    igSmartPointer<ClonedObject> created(arg1->v84(arg2), kRetainReference);
    created.release();
    return created;
}

