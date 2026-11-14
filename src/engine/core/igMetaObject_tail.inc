static inline void retain(Instance *object) {
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
}

static inline void release_2fd610(Instance *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}

int FUN_002fd610(Instance **out, int meta) {
    igSmartPointer<Instance> created((Instance *)igMetaObject_CreateInstanceDefault((void *)meta), kRetainReference);
    release_2fd610(created.p);
    *out = created.p;
    retain(*out);
    return 0;
}

/* The new instance arrives with one reference; the holder takes its own and drops that one. */
CreatedRef FUN_002fd6e0(int meta, int pool) {
    CreatedRef created((igObject *)igMetaObject_CreateInstance((igMetaObject *)meta, (igMemoryPoolView *)pool));
    releaseObject_2fd610(created.get());
    return created;
}

/* Construct a metaobject: base header, igMetaObject vtable, no name or pool
 * name, and an empty field list. */
void *igMetaObject_Construct(igMetaObject *meta, int extra1){
    igObject_ConstructHeader((igObject *)meta);
    meta->_vtable=(int)g_igMetaObject_vtable;
    meta->_name=0;
    meta->_poolName=0;
    if(meta)igMetaObject_Init(meta);
    meta->_metaFields=((int)InternalObjectList_Create(0));
    return meta;
}

/* Reset a freshly constructed metaobject to its defaults, then intern the empty string as the
 * pool name, creating the shared string pool on first use. No previous lists are released. */
igMetaObject *igMetaObject_Init(igMetaObject *meta){
    int pool,oldName,refCount;int *oldHeader;void *emptyToken;
    igObject_InitHeader((igObject *)meta);meta->_vtable=(int)g_igMetaObject_vtable;
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
        pool=((int)StringPool_Allocate(16));if(pool)pool=((int)StringPool_Construct((StringPool *)pool));
        g_stringPool[0]=pool;
    }
    emptyToken=(void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)0);
    /* Drop the old pool-name token: owner chunk at -8, reference count at -4. */
    oldName=meta->_poolName;
    if(oldName){oldHeader=(int *)(oldName-8);refCount=*(int *)(oldName-4)-1;*(int *)(oldName-4)=refCount;
        if(!refCount)StringChunk_ReleaseHeader((StringChunkOwnerView *)(*oldHeader), (int)oldHeader);
    }
    meta->_poolName=(int)emptyToken;return meta;
}

/* Copy-construct: base header copy, vtable stamp and cleared names; the other
 * metadata members are not copied here. */
void *igMetaObject_CopyConstruct(igMetaObject *meta,void *source){
    igObject_CopyConstructHeader((igObject *)meta, (igObject *)source);
    meta->_vtable=(int)g_igMetaObject_vtable;
    meta->_name=0;
    meta->_poolName=0;
    return meta;
}

/* Drop the field list and then the child list: decrement the reference count
 * and destroy the list once its 23 low count bits reach zero.  The member cells
 * are left untouched. */
void igMetaObject_ReleaseLists(igMetaObject *meta){
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

void *igMetaObject_CreateInstanceDefault(void *meta){return (void *)igMetaObject_CreateInstance((igMetaObject *)meta,((igMemoryPoolView *)Memory_GetDefaultAllocator()));}

int igMetaObject_CreateInstance(igMetaObject *arg0, igMemoryPoolView *arg1) {
    int temp_s1;
    int temp_s1_2;
    char *temp_a0;
    igMemoryPoolView *var_s2;
    igMemoryPoolView *var_v0;
    igMetaObject *(*temp_v0)();

    var_s2 = arg1;
    temp_v0 = (igMetaObject *(*)())arg0->_abstractProxy;
    if (temp_v0 != 0) {
        return igMetaObject_CreateInstance(temp_v0(), var_s2);
    }
    if (arg0->_abstractState == 1) {
        return 0;
    }
    if (var_s2 == 0) {
        temp_a0 = (char *)arg0->_poolName;
        if ((temp_a0 != 0) && (*temp_a0 != 0)) {
            var_s2 = ((igMemoryPoolView *)Memory_GetAllocatorByName((int)temp_a0));
            if (var_s2 == 0) {
                var_v0 = ((igMemoryPoolView *)Memory_GetDefaultAllocator());
                goto block_10;
            }
        } else {
            var_v0 = ((igMemoryPoolView *)Memory_GetDefaultAllocator());
block_10:
            var_s2 = var_v0;
        }
    }
    temp_s1_2 = arg0->_runTimeSize;
    temp_s1 = (int)var_s2->Allocate(temp_s1_2 + arg0->_sizeofSize);
    temp_s1 = temp_s1 + temp_s1_2;
    if (temp_s1 != 0) {
        igObject_Construct((igObjectDispatchView *)temp_s1, (char *)arg0);
    }
    return temp_s1;
}

int igMetaObject_CreateInstanceWithPool(igMetaObject *arg0, igMemoryPoolView *arg1) {
    int temp_s1;
    int temp_s1_2;
    char *temp_a0;
    igMemoryPoolView *var_s2;
    igMemoryPoolView *var_v0;
    igMetaObject *(*temp_v0)();

    var_s2 = arg1;
    if (((arg0->_validity & 4) != 0) == 0) {
        return 0;
    }
    temp_v0 = (igMetaObject *(*)())arg0->_abstractProxy;
    if (temp_v0 != 0) {
        return igMetaObject_CreateInstanceWithPool(temp_v0(), var_s2);
    }
    if (arg0->_abstractState == 1) {
        return 0;
    }
    if (var_s2 == 0) {
        temp_a0 = (char *)arg0->_poolName;
        if ((temp_a0 != 0) && (*temp_a0 != 0)) {
            var_s2 = ((igMemoryPoolView *)Memory_GetAllocatorByName((int)temp_a0));
            if (var_s2 == 0) {
                var_v0 = ((igMemoryPoolView *)Memory_GetDefaultAllocator());
                goto block_10;
            }
        } else {
            var_v0 = ((igMemoryPoolView *)Memory_GetDefaultAllocator());
block_10:
            var_s2 = var_v0;
        }
    }
    temp_s1_2 = arg0->_runTimeSize;
    temp_s1 = (int)var_s2->Allocate(temp_s1_2 + arg0->_sizeofSize);
    temp_s1 = temp_s1 + temp_s1_2;
    if (temp_s1 != 0) {
        igObject_ConstructPooled((igObject *)temp_s1, (char *)arg0);
    }
    return temp_s1;
}

void igMetaObject_InheritFromBase(igMetaObject *meta,igMetaObject *parent){
    if(parent!=0){
        if(parent->_children==0)parent->_children=(int)FUN_002c29c0((int)(Memory_GetAllocatorBySelector(*(int *)0x587040)));
        ObjectPointerList_Append((__internalNonRefCountedObjectList *)((void *)parent->_children), (int)meta);
        meta->_parent=(int)parent;
        meta->_vTablePointer=parent->_vTablePointer;
        meta->_requiredAlignment=((igMetaObject *)meta->_parent)->_requiredAlignment;
        meta->_runTimeSize=((igMetaObject *)meta->_parent)->_runTimeSize;
        meta->_sizeofSize=((igMetaObject *)meta->_parent)->_sizeofSize;
        int count=((__internalObjectList *)parent->_metaFields)->_count;
        for(int i=0;i<count;i++)igMetaObject_AppendField(meta,(igMetaField *)igMetaObject_GetFieldAt(parent,i));
    }
}

int igMetaObject_CountInstances(igMetaObject *arg0, int arg1) {
    int s2 = arg0->_instanceCount;
    __internalObjectList *l;
    int s1;
    int s0;
    if (arg1 != 0) {
        l = (__internalObjectList *)arg0->_children;
        if (l != 0) {
            s0 = l->_count;
            for (s1 = 0; s1 < s0; s1++) {
                s2 += igMetaObject_CountInstances(((igMetaObject **)((__internalObjectList *)arg0->_children)->_data)[s1], 1);
            }
        }
    }
    return s2;
}

/* Give a metaobject its (interned) class name. The shared string pool is created on first use even
 * for a null name; the new name is interned first, then the previous name token is released. */
void igMetaObject_SetName(igMetaObject *meta, int name) {
    int pool, internedName, oldName, refCount;
    int *oldHeader;

    if (g_stringPool[0] == 0) {
        pool = ((int)StringPool_Allocate(16));
        if (pool) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool[0] = pool;
    }
    internedName = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)name);
    oldName = meta->_name;
    if (oldName) {
        oldHeader = (int *)(oldName - 8);
        refCount = *(int *)(oldName - 4) - 1;
        *(int *)(oldName - 4) = refCount;
        if (!refCount) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*oldHeader), (int)oldHeader);
        }
    }
    meta->_name = internedName;
}

void igMetaObject_AppendField(igMetaObject *meta, igMetaField *field)
{
    MetaRefList_AppendRetained((__internalObjectList *)((void *)meta->_metaFields), (igObject *)field);
}

void igMetaObject_FinalizeAndAppendField(void *meta,void *field){
    igMetaField_FinalizeDescriptor((igMetaField *)field);igMetaObject_AppendField((igMetaObject *)meta,(igMetaField *)field);
}

void igMetaObject_FinalizeAndReplaceField(igMetaObject *meta,int index,igMetaField *field){
    igMetaField_FinalizeDescriptor((igMetaField *)field);
    InternalObjectList_SetAtRetained((__internalObjectList *)((void *)meta->_metaFields), index, (igObject *)field);
}

int FUN_002fdef0(int a0, int a1)
{
    return a1;
}

/* The item array is read at +8 of the field list object. */
int igMetaObject_GetFieldAt(igMetaObject *self, int index) {
    return *(int *)(*(int *)((char *)(self->_metaFields) + 8) + (index * 4));
}

void *igMetaObject_FindFieldByName(igMetaObject *meta, const char *name) {
    return ObjectPointerList_FindByStringField((__internalNonRefCountedObjectList *)((void *)meta->_metaFields), g_fieldNameMember[0], name);
}

void igMetaObject_CreateFields(igMetaObject *meta,FieldFactory *factories,int count){
    int i;
    igMetaField *field;
    for(i=0;i<count;i++){
        field=factories[i](Memory_GetAllocatorBySelector(*(int *)0x587040));
        igMetaObject_AppendField(meta,field);
        --field->_refCount;
        if(!(field->_refCount&0x7fffff))igObject_Destroy(field);
    }
}

void igMetaObject_NameFields(igMetaObject *meta,const char **names,igMetaField ***handles,int *offsets,int start){
    int count;
    int row;
    igMetaField *field;
    count=igMetaObject_GetFieldCount(meta);
    row=0;
    for(;start<count;start++,row++){
        field=((igMetaField **)((__internalObjectList *)meta->_metaFields)->_data)[start];
        igMetaField_Configure(field,names[row],handles[row],offsets[row],meta);
        igMetaField_FinalizeDescriptor(field);
    }
}

void igMetaObject_FinalizeFieldLayout(igMetaObject *arg0) {
    int off;
    int minAlign;
    unsigned short sz;
    int i;
    igMetaFieldView *f;
    int count;
    int nneg;
    int end;
    unsigned short maxAlign;
    int maxEnd;
    bool flag;
    count = igMetaObject_GetFieldCount(arg0);
    off = 0;
    maxEnd = 0;
    minAlign = 4;
    nneg = 0;
    maxAlign = 4;
    for (i = 0; i < count; i++) {
        f = (igMetaFieldView *)igMetaObject_GetFieldAt(arg0, i);
        sz = f->vfunc_27();
        if (maxAlign < sz) maxAlign = sz;
        if (f->_isRunTime != 0) {
            nneg++;
            off = ~(sz - 1) & (off - f->_size);
            f->_offset = off;
        } else {
            flag = 0;
            if (arg0->_parent == 0 || igMetaObject_GetFieldCount((igMetaObject *)arg0->_parent) <= i) {
                flag = 1;
            } else if ((igMetaFieldView *)igMetaObject_GetFieldAt((igMetaObject *)arg0->_parent, i) != f) {
                flag = 1;
            }
            if (flag) {
                f->_internalIndex = i - nneg;
                f->_parentMetaObject = (int)arg0;
            }
            minAlign = (sz < minAlign) ? minAlign : sz;
        }
        end = f->_offset; end += f->_size;
        if (maxEnd < end) maxEnd = end;
    }
    arg0->_requiredAlignment = maxAlign;
    if (arg0->_sizeofSize != -1) arg0->_runTimeSize = -(off & ~(minAlign - 1));
    arg0->_validity |= 4;
    FUN_002d3150((int *)(((void * *)g_objectSystem)[0]), (int)arg0);
}

int FUN_002fe290(igMetaObject *arg0, igMetaObject *arg1) {
    while (arg0 != 0) {
        if (arg1 == arg0) {
            return 1;
        }
        arg0 = (igMetaObject *)arg0->_parent;
    }
    return 0;
}

int igMetaObject_GetChildCount(igMetaObject *arg0) {
    void *temp_v0;

    temp_v0 = (void *)(arg0->_children);
    if (temp_v0 == 0) {
        return 0;
    }
    return *(int *)((char *)(temp_v0) + 12);
}

/* The item array is read at +8 of the child list object. */
int igMetaObject_GetChildAt(igMetaObject *self, int index) {
    return *(int *)(*(int *)((char *)(self->_children) + 8) + (index * 4));
}

void *FUN_002fe300(igMetaObject *arg0, int arg1) {
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
        v = igMetaObject_CountTree((igMetaObject *)k);
        v += acc;
        if (arg1 < v) {
            return FUN_002fe300(k, arg1 - acc);
        }
        acc = v;
    }
    return 0;
}

int igMetaObject_CountTree(igMetaObject *arg0) {
    __internalObjectList *l = (__internalObjectList *)arg0->_children;
    int s2;
    int s1;
    int s0;
    if (l == 0) return 1;
    s1 = l->_count;
    s2 = 1;
    for (s0 = 0; s0 < s1; s0++) {
        s2 += igMetaObject_CountTree(((igMetaObject **)((__internalObjectList *)arg0->_children)->_data)[s0]);
    }
    return s2;
}

int igObjectSystem_FindMetaByNameDefault(const char *name){return igObjectSystem_FindMetaByName((ObjectSystemView *)(((void * *)g_objectSystem)[0]), name);}

/* Read from the field list's `_capacity` slot (+12), not `_count` (+8). */
int igMetaObject_GetFieldCount(igMetaObject *self) {
    return ((igMetaFieldList *)self->_metaFields)->_capacity;
}

void FUN_002fe480(int arg0) {
    FUN_002d30c0((int *)(((void * *)g_objectSystem)[0]), arg0);
}

void FUN_002fe490(int arg0) {
    FUN_002d30d0((ObjectSystemView *)(((void * *)g_objectSystem)[0]), (int (*)(int))arg0);
}

void igMetaObject_AddField(igMetaObject *arg0, void *arg1) {
    int flags;
    int idx;
    char *m;
    int n;
    int i;

    flags = arg0->_validity;
    arg0->_validity = flags & ~4;
    *(char *)((char *)(arg1) + 37) = 1;
    *(int *)((char *)(arg1) + 24) = (int)(arg0);
    igMetaField_FinalizeDescriptor((igMetaField *)arg1);
    idx = MetaRefList_AppendRetained((__internalObjectList *)((void *)arg0->_metaFields), (igObject *)arg1);
    n = igMetaObject_CountTree((igMetaObject *)arg0);
    for (i = 1; i < n; i++) {
        m = (char *)FUN_002fe300(arg0, i);
        *(int *)(m + 36) = *(int *)(m + 36) & ~4;
        InternalObjectList_InsertRetained((__internalObjectList *)(*(int *)(m + 40)), idx, (igObject *)arg1);
    }
}

void FUN_002fe570(igMetaObject *arg0, void *arg1) {
    igMetaObject_AddField(arg0, arg1);
    FUN_002fe5a0((int)arg0);
}

void FUN_002fe5a0(int arg0) {
    int temp_s1;
    int var_s0;
    temp_s1 = igMetaObject_CountTree((igMetaObject *)arg0);
    for (var_s0 = 0; var_s0 < temp_s1; var_s0++) {
        igMetaObject_FinalizeFieldLayout((igMetaObject *)FUN_002fe300((igMetaObject *)arg0, var_s0));
    }
}

int FUN_002fe600(igTDataList<igMetaObject *> *list, igMetaObject *object) {
    int i = list->find(object);
    if (i != -1) {
        return i;
    }
    int n = list->count();
    while (i == -1 && object != 0) {
        ChainRef retained(object);
        List_InsertWords((igDataList *)list, n, 1, &retained);
        object = (igMetaObject *)object->_parent;
        i = list->find(object);
    }
    return list->_count - 1;
}

int FUN_002fe730(int arg0) {
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
void igMetaObject_AssignTypeId(igMetaObject *meta){
    meta->_index=ObjectPointerList_FindIndex((char *)(((ObjectSystemView *)((void * *)g_objectSystem)[0])->metaRegistry), (int)meta);
    if(meta->_index==-1){
        igObjectSystem_AppendMetaObject(((void * *)g_objectSystem)[0],meta);
        meta->_index=ObjectPointerList_FindIndex((char *)(((ObjectSystemView *)((void * *)g_objectSystem)[0])->metaRegistry), (int)meta);
    }
}

void FUN_002fe810(int *out, igMetaObject *s, igMemoryPoolView *a) {
    if (s->_vTablePointer == 0) { *out = g_resultFailure.v; return; }
    if (s->_abstractState != 0) { *out = g_resultFailure.v; return; }
    if (a == 0) a = ((igMemoryPoolView *)Memory_GetDefaultAllocator());
    int *p; int *base = (int *)s->_vTablePointer;
    p = base;
    while (!*p) p++;
    while (*p != 0) p++;
    int n = (char *)p - (char *)base;
    int *nb = (int *)a->Allocate(n);
    if (nb == 0) { *out = g_resultFailure.v; return; }
    memcpy(nb, (int *)s->_vTablePointer, n);
    s->_vTablePointer = (int)nb;
    *out = g_resultSuccess.v;
}

int igMetaObject_GetPoolName(int *p)
{
    return *(int *)((char *)p + 96);
}

void igMetaObject_RunStaticInit(StaticInitCallbacks *(*initialize)()){
    StaticInitCallbacks *list=initialize();
    int count; int i;
    if(list){count=list->count;for(i=0;i<count;i++)list->functions[i]();igArray_Destruct((CallbackArray *)list, 1);}
}

