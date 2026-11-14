void igResource_Create(int arg0) {
    igResource_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585978), (igMemoryPoolView *)arg0);
}

igMetaObject *igResource_GetOrCreateMetaObject(void) {
    if (g_igResource_metaObject[0] == 0) {
        g_igResource_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igResource_metaObject[0];
}

igMetaObject *igResource_GetMetaObject(void)
{
    igMetaObject *g = g_igResource_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igResource_EnsureRegistered();
    return g_igResource_metaObject[0];
}

int igResource_GetVTable(void) {
    igResource resource;
    int t;
    igObject_InitHeader((igObject *)&resource);
    resource._vtable = (int)&DAT_0052eb90[0];
    resource._imageDirectory = 0;
    resource._directoryList = 0;
    resource._relativeFilePath = 0;
    resource._absoluteFilePath = 0;
    resource._loadQueue = 0;
    resource._loadThread = 0;
    resource._alignmentStrings = 0;
    resource._alignmentValues = 0;
    resource._temporaryMemoryPool = 0;
    resource._dataMemoryPool = 0;
    resource._objectMemoryPool = 0;
    t = *(int *)((char *)&resource + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    resource._vtable = (int)&DAT_0052eb90[0];
    FUN_001509f0(&resource._objectMemoryPool, -1);
    FUN_001509f0(&resource._dataMemoryPool, -1);
    FUN_001509f0(&resource._temporaryMemoryPool, -1);
    ObjectRef_Destruct_00150eb0(&resource._alignmentValues, -1);
    FUN_001a0790(&resource._alignmentStrings, -1);
    FUN_001432d0(&resource._loadThread, -1);
    igSmartPointer_igQueue_Destruct((igQueue **)&resource._loadQueue, -1);
    StringRef_Destruct_00130720(&resource._absoluteFilePath, -1);
    StringRef_Destruct_00130720(&resource._relativeFilePath, -1);
    igSmartPointer_igDirectoryList_Destruct((void **)&resource._directoryList, -1);
    FUN_001d36d0(&resource._imageDirectory, -1);
    return t;
}

void **igSmartPointer_igDirectoryList_Destruct(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

igQueue **igSmartPointer_igQueue_Destruct(igQueue **arg0, short arg1) {
    if (arg0) {
        igQueue *t = *arg0;
        if (t) { t->_refCount -= 1; if ((t->_refCount & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void igResource_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igResource_Register);
}

void igResource_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igResource_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igResource_GetMetaObjectFunction,
        igResource_className,
        0x4C, /* instance size */
        igResource_GetVTable,
        &igResource_InitFields,
        0, /* extra callback item */
        g_igResource_callbackList /* callback list */
    );
}

void igResource_GetMetaObjectFunction(void) {
    igResource_GetMetaObject();
}

void igResource_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s1;

    temp_s1 = (void *)g_igResource_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, (igMetaField * (**)(void *))&g_igResource_ctorTable[0], 0x11);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igDirectory_GetOrCreateMetaObject();
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igDirectoryList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    ((igMetaField *)temp_s2_2)->_persistent = 0;
    igStringMetaField_SetDefaultText((int *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2))), 0);
    igStringMetaField_SetDefaultText((int *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3))), 0);
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igQueue_GetOrCreateMetaObject();
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igThread_GetOrCreateMetaObject();
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 7))), 1);
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 8)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)igStringObjList_GetOrCreateMetaObject();
    ((igMetaField *)temp_s2_5)->_persistent = 0;
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 9)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igMetaField *)temp_s2_6)->_persistent = 0;
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xA))), 1);
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xB)));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    temp_s2_8 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xC)));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    temp_s2_9 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xD)));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xE))), 1);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xF))), 0x20000);
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0x10))), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&g_igResource_fieldTable[0], (igMetaField ***)&DAT_004bf7e0[0], &DAT_004bf830[0], temp_s0);
}

