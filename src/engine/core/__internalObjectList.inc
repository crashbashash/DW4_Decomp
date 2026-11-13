void **InternalObjectList_Create(int allocator) {
    void **list;

    if (*g_objectSystem[0] != 0) {
        __internalObjectList_EnsureRegistered();
        list = (void **)(((void **)igMetaObject_CreateInstance((CreateMeta *)(((int *)g___internalObjectList_metaObject)[0]), (MemoryPool *)allocator)));
    } else {
        list = (void **)(((void **)igObject_AllocateRawStorage(0x10, 0, (void **)allocator)));
        if (list != 0) {
            list = (void **)(((void **)InternalObjectList_Construct((PointerList *)list, 1)));
        }
        ((DW4VC_44_0 *)(list))->vX();
        ((DW4VC_36_1 *)(list))->vX((int)(0));
    }
    return list;
}

int FUN_002c2710(int arg0, int arg1) {
    int temp_v0;

    if (*g_objectSystem[0] != 0) {
        __internalObjectList_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    temp_v0 = ((int)igObject_AllocateRawStorageDefault(0x10, 0));
    if (temp_v0 != 0) {
        temp_v0 = ((int)InternalObjectList_CopyConstruct((PointerList *)temp_v0, (PointerList *)arg0));
    }
    return temp_v0;
}

igMetaObject *FUN_002c2790(void) {
    if (g___internalObjectList_metaObject[0] == 0) {
        g___internalObjectList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData)));
    }
    return g___internalObjectList_metaObject[0];
}

igMetaObject *__internalObjectList_GetMetaObject(void)
{
    igMetaObject *g = g___internalObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        __internalObjectList_EnsureRegistered();
    return g___internalObjectList_metaObject[0];
}

int __internalObjectList_GetVTable(void) {
    int o[4];
    InternalObjectList_Init((PointerList *)o);
    return *(int *)((char *)o + *(int *)((char *)((int * *)g_objectSystem)[0] + 916));
}

void __internalObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())__internalObjectList_Register);
}

void __internalObjectList_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g___internalObjectList_metaObject),
        __internalNonRefCountedObjectList_Register,
        __internalNonRefCountedObjectList_GetPublishedMetaObject_002c28f0,
        thunk___internalObjectList_GetMetaObject,
        __internalObjectList_className,
        0x10, /* instance size */
        __internalObjectList_GetVTable,
        &__internalObjectList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk___internalObjectList_GetMetaObject(void) {
    __internalObjectList_GetMetaObject();
}

igMetaObject *FUN_002c28f0(void) {
    return g___internalNonRefCountedObjectList_metaObject[0];
}

void __internalObjectList_InitFields(void) {
    void **temp_v0;
    int temp_s1;
    void *temp_s0;
    T_2c2900 *temp_v0_2;

    temp_s0 = (void *)(((void * *)g___internalObjectList_metaObject)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s0, data)));
    temp_s1 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s0) + 40)), (int)temp_v0);
    temp_v0_2 = (T_2c2900 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(char *)((char *)(temp_v0_2) + 66) = 1;
    temp_v0_2->f28 = (int)(&DAT_005860d8[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s0, temp_s1, (igMetaField *)temp_v0_2);
    temp_v0_2->references = temp_v0_2->references - 1;
    if ((temp_v0_2->references & 0x7fffff) == 0) {
        igObject_Destroy(temp_v0_2);
    }
}

