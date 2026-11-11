void FUN_002d1a00(S_2d1a00 *self) {
    void *m;
    P_2d1a00 *p;
    L_2d1a00 *l;
    unsigned int n;
    int b;
    self->f20 = 1;
    FUN_0032ae70();
    self->f916 = 0;
    if (((P_2d1a00 * *)DAT_00586fd0)[0] == 0) {
        m = FUN_002f87f0(0x19F4);
        if (m != 0) m = ((P_2d1a00 *)igMemoryPoolContextInfo_Construct((igMemoryPoolContextInfo *)m));
        ((P_2d1a00 * *)DAT_00586fd0)[0] = (P_2d1a00 *)m;
    }
    ((P_2d1a00 * *)DAT_00586fd0)[0]->v40();
    self->f24 = ((L_2d1a00 *)InternalObjectList_Create(((int)Memory_GetAllocatorBySelector(DAT_00587018[0]))));
    l = self->f24;
    if (l->f8 == 0) n = 0; else n = Memory_GetBufferSize((void *)l->f8) >> 2;
    if ((int)n < 0x401) ObjectPointerList_EnsureIndex((List_2ea4f0 *)l, 0x400);
    self->f36 = ((L_2d1a00 *)InternalObjectList_Create(((int)Memory_GetAllocatorBySelector(DAT_00587018[0]))));
    b = ((int)Memory_AllocateDefaultBuffer((unsigned int)12));
    if (b != 0) b = ((int)igArray_Construct((CallbackArray *)b));
    self->f40 = b;
    b = ((int)Memory_AllocateDefaultBuffer((unsigned int)12));
    if (b != 0) b = ((int)igArray_Construct((CallbackArray *)b));
    self->f44 = b;
    igMetaObject_EnsureRegistered();
    self->f0 = 1;
    self->f4 = self->f24->f12;
    self->f8 = ((L_2d1a00 * *)DAT_00587188)[0]->f12;
    FUN_002bf190();
    FUN_002ce3c0();
    FUN_002cdcf0();
    igAliasMemoryPool_EnsureRegistered();
    FUN_002cd7c0();
    FUN_002c1190();
    FUN_002caf80();
    FUN_002cadc0();
    igIntList_EnsureRegistered();
    FUN_002ca9d0();
    FUN_002ca530();
    FUN_002ca380();
    FUN_002b8f90();
    FUN_002b87c0();
    FUN_002cc960();
    FUN_002cc710();
    FUN_002d04a0();
    FUN_002c20f0();
    FUN_002c59e0();
    FUN_002c4710();
    FUN_002c1b10();
    igUnsignedCharMetaField_EnsureRegistered();
    ((int *)DAT_00585a68)[0] = igRawRefMetaField_GetDefaultDescriptor();
    ((P_2d1a00 * *)DAT_00586fd0)[0]->v41();
}

int FUN_002d1c20(int *p)
{
    return *(int *)((char *)p + 920);
}

int FUN_002d1c30(int *p)
{
    return *(int *)((char *)p + 924);
}

void FUN_002d1c40(Obj_2d1c40 *arg0) {
    igString env;
    char *text = (char *)getenv(DAT_004f9460);
    text = ((char *)StringPool_Intern((StringPool *)(Pool::get()), (const char *)text));
    env.adopt(text);
    arg0->m920.assign(env);
    text = ((char *)StringPool_Intern((StringPool *)(Pool::get()), (const char *)DAT_004f9468));
    arg0->m924.adopt(text);
    text = ((char *)StringPool_Intern((StringPool *)(Pool::get()), (const char *)DAT_004f9470));
    arg0->m924.adopt(text);
}

int FUN_002d2790(void) {
    return DAT_00585fc8[0];
}

void FUN_002d27a0(S_2d27a0 *arg0) {
    void **temp_a0;

    arg0->b = 1;
    temp_a0 = arg0->p;
    if (temp_a0 != 0) {
        ((DW4VC_184_0 *)(temp_a0))->vX();
        FUN_002dcc60((FileRequest *)arg0->p, (int)&DAT_004f9578[0]);
    }
}

void FUN_002d2de0(S_2d2de0 *arg0) {
    if (arg0->f84 != 0) {
        arg0->f84->vX();
        FUN_002dcc60((FileRequest *)arg0->f84, (int)(&DAT_004f9580[0]));
    }
    if (arg0->f117 != 0 && ((V224 * *)DAT_00586fd0)[0] != 0) {
        ((V224 * *)DAT_00586fd0)[0]->vX();
    }
}

void FUN_002d2e60(S_2d2e60 *arg0) {
    int i;
    int v;
    Obj_2d2e60 *o;
    o = arg0->f36;
    o->refs = o->refs - 1;
    if ((o->refs & 0x7fffff) == 0) igObject_Destroy(o);
    arg0->f36 = 0;
    FUN_002e3280(0);
    igArray_Destruct((CallbackArray *)arg0->f44, 1);
    if (DAT_00586fd0[0] != 0) {
        DAT_00586fd0[0]->v45();
    }
    InternalObjectList_SetCount((PointerList *)DAT_00587188[0], arg0->f8);
    for (i = arg0->f12 - 1; i >= arg0->f4; i--) {
        InternalObjectList_SetAtRetained((PointerList *)arg0->f24, i, (RefHeader *)0);
    }
    arg0->f0 = 0;
    o = DAT_00587188[0];
    o->refs = o->refs - 1;
    if ((o->refs & 0x7fffff) == 0) igObject_Destroy(o);
    o = arg0->f24;
    o->refs = o->refs - 1;
    if ((o->refs & 0x7fffff) == 0) igObject_Destroy(o);
    o = arg0->f112;
    if (o != 0) {
        o->refs = o->refs - 1;
        if ((o->refs & 0x7fffff) == 0) igObject_Destroy(o);
    }
    if (DAT_00586f20[0] == 0) {
        v = ((int)FUN_002eb010(16));
        if (v != 0) v = ((int)StringPool_Construct((S_2eadf0 *)v));
        DAT_00586f20[0] = v;
    }
    StringPool_Destroy((int *)DAT_00586f20[0], 1);
    arg0->f20 = 0;
    if (DAT_00586fd0[0] != 0) {
        DAT_00586fd0[0]->v42();
        if (DAT_00586fd0[0] != 0) {
            DAT_00586fd0[0]->v65(1);
        }
        DAT_00586fd0[0] = 0;
    }
    FUN_0032aea0();
}

/* Register a metaobject in the object system's registry, retaining it. */
void igObjectSystem_AppendMetaObject(void *system,igMetaObject *meta){
    MetaRefList_AppendRetained((PointerList *)((void *)((ObjectSystemRecord *)system)->metaRegistry), (RefHeader *)meta);
}

int igObjectSystem_FindMetaByName(ObjectSystemView *objectSystem, const char *className) {
    if (objectSystem->active != 0) {
        return (int)ObjectPointerList_FindByStringField((FieldPointerList *)objectSystem->metaRegistry, g_igMetaObjectNameField[0], className);
    }
    return 0;
}

int FUN_002d30b0(int *p, int extra1)
{
    return MetaRefList_AppendRetained((PointerList *)(*(int *)((char *)p + 36)), (RefHeader *)extra1);
}

int FUN_002d30c0(int *p, int extra1)
{
    return igArray_Append((CallbackArray *)(*(int *)((char *)p + 40)), extra1);
}

void FUN_002d30d0(struct S24 *arg0, int (*arg1)(int)) {
    int i;

    for (i = 0; i < arg0->f24->count; i++) {
        arg1(arg0->f24->data[i]);
    }
    igArray_Append((CallbackArray *)arg0->f44, (int)arg1);
}

void FUN_002d3150(int *arg0, int arg1) {
    int n = *(int *)(arg0[11] + 4);
    int i = 0;
    while (i < n) {
        ((void (*)(int))(*(int **)arg0[11])[i])(arg1);
        i++;
    }
}

void FUN_002d31d0(struct N *arg0, char *arg1) {
    if (arg1 != 0) {
        strncpy(arg0->name, arg1, 0x7F);
        arg0->name[127] = 0;
    } else {
        arg0->name[0] = 0;
    }
    if ((arg1 != 0) && (*arg1 != 0)) {
        DAT_004c1eb8[0] = arg0->name;
    }
}

void FUN_002d3240(S_2d3240 *arg0, char *arg1) {
    if (arg1 != 0) {
        strncpy(arg0->f272, arg1, 0x7F);
        arg0->f399 = 0;
    } else {
        arg0->f272[0] = 0;
    }
    if ((arg1 != 0) && (*arg1 != 0)) {
        DAT_004c1ec0[0] = (void *)arg0->f272;
    }
}

void FUN_002d32b0(struct O_2d32b0 *arg0, char *arg1) {
    if (arg1 != 0) {
        strncpy(arg0->buf, arg1, 0x7F);
        arg0->buf[127] = 0;
    } else {
        arg0->buf[0] = 0;
    }
    if ((arg1 != 0) && (*arg1 != 0)) {
        DAT_004c1ec8[0] = arg0->buf;
    }
}

void FUN_002d3320(char *arg0, char *arg1) {
    if ((arg1 != 0) && (*arg1 != 0)) {
        strncpy(arg0 + 528, arg1, 0x7F);
        arg0[655] = 0;
        return;
    }
    arg0[528] = 0;
}

void FUN_002d3370(char *a, char *b) {
    if (b != 0 && *b != 0) {
        strncpy(a + 656, b, 127);
        a[783] = 0;
        return;
    }
    a[656] = 0;
}

void FUN_002d33c0(void *arg0, int arg1) {
    if (arg1 != 0) {
        strncpy((char *)arg0 + 0x310, arg1, 0x7F);
        *((char *)arg0 + 911) = 0;
        return;
    }
    *((char *)arg0 + 784) = 0;
}

CallbackArray *igArray_Construct(CallbackArray *array){array->data=0;array->capacity=0;array->count=0;return array;}

/* Free the data buffer, and the array object itself when `deleteFlag` is positive. */
CallbackArray *igArray_Destruct(CallbackArray *array,short deleteFlag){
    if(array){if(array->data)Memory_FreeBuffer(array->data);if(deleteFlag>0)FUN_002ed5c0(array);}
    return array;
}

/* Grow only when count equals capacity, then store `item` at the end. */
int igArray_Append(CallbackArray *array,int item){
    int capacity=array->capacity;
    if(array->count==capacity){
        if(capacity==0)array->capacity=4;
        else array->capacity*=((capacity*3)/2);
        if(array->data==0)array->data=(int *)(Memory_AllocateBufferDirect((unsigned int)(array->capacity*4), (igMemoryPool_2ed1c0 *)(((ObjectSystemRecord_2d3400 * *)g_objectSystem)[0]->allocator)));
        else array->data=(int *)(Memory_ReallocateBuffer(array->data, (unsigned int)(array->capacity*4)));
    }
    array->data[array->count++]=item;
}

int thunk_malloc(int extra0)
{
    return malloc();
}

int thunk_free(int extra0)
{
    return free();
}

