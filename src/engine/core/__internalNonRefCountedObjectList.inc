void **FUN_002c29c0(int arg0) {
    void **var_s0;

    if (*g_objectSystem[0] != 0) {
        FUN_002c2bb0();
        var_s0 = (void **)(((void **)igMetaObject_CreateInstance((CreateMeta *)g___internalNonRefCountedObjectList_metaObject[0], (MemoryPool *)arg0)));
    } else {
        var_s0 = (void **)(((void **)igObject_AllocateRawStorage(0x10, 0, (igMemoryPoolView *)arg0)));
        if (var_s0 != 0) {
            var_s0 = (void **)(((void **)ObjectPointerList_Construct((__internalNonRefCountedObjectList *)var_s0, 1)));
        }
        ((igObjectDispatchView *)(var_s0))->vfunc_09();
        ((igObjectDispatchView *)(var_s0))->userConstruct((int)(0));
    }
    return var_s0;
}

int FUN_002c2a60(int arg0, int arg1) {
    int temp_v0;

    if (*g_objectSystem[0] != 0) {
        FUN_002c2bb0();
        return igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    temp_v0 = ((int)igObject_AllocateRawStorageDefault(0x10, 0));
    if (temp_v0 != 0) {
        temp_v0 = ((int)ObjectPointerList_CopyConstruct((__internalNonRefCountedObjectList *)temp_v0, (__internalNonRefCountedObjectList *)arg0));
    }
    return temp_v0;
}

igMetaObject *FUN_002c2ae0(void) {
    if (g___internalNonRefCountedObjectList_metaObject[0] == 0) {
        g___internalNonRefCountedObjectList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g___internalNonRefCountedObjectList_metaObject[0];
}

igMetaObject *__internalNonRefCountedObjectList_GetMetaObject(void)
{
    igMetaObject *g = g___internalNonRefCountedObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c2bb0();
    return g___internalNonRefCountedObjectList_metaObject[0];
}

int __internalNonRefCountedObjectList_GetVTable(void) {
    int o[4];

    ObjectPointerList_Init((PointerList *)o);
    return *(int *)((char *)o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002c2bb0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())__internalNonRefCountedObjectList_Register);
}

void __internalNonRefCountedObjectList_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g___internalNonRefCountedObjectList_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk___internalNonRefCountedObjectList_GetMetaObject,
        __internalNonRefCountedObjectList_className,
        0x10, /* instance size */
        __internalNonRefCountedObjectList_GetVTable,
        &__internalNonRefCountedObjectList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk___internalNonRefCountedObjectList_GetMetaObject(void) {
    __internalNonRefCountedObjectList_GetMetaObject();
}

void __internalNonRefCountedObjectList_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g___internalNonRefCountedObjectList_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g___internalNonRefCountedObjectList_ctorTable[0], 2);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igObjectRefMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)temp_s1)->_memSize = 0x40;
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    ((igMemoryRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g___internalNonRefCountedObjectList_fieldTable[0], (igMetaField ***)&DAT_004c05d0[0], &DAT_004c05d8[0], temp_s2);
}

