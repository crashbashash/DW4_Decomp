igMetaObject *g_igMetaFieldList_metaObject;

void * igMetaFieldList_Create(int pool) {
    igMetaFieldList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igMetaFieldList_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igMetaFieldList_GetOrCreateMetaObject(void) {
    if (g_igMetaFieldList_metaObject == 0) {
        g_igMetaFieldList_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igMetaFieldList_metaObject;
}

igMetaObject *igMetaFieldList_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaFieldList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMetaFieldList_EnsureRegistered();
    return g_igMetaFieldList_metaObject;
}

int igMetaFieldList_GetVTable(void) {
    igMetaFieldList obj;

    igObject_InitHeader((igObject *)&obj);
    obj._vtable = (int)&g_igMetaFieldList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igMetaFieldList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMetaFieldList_Register);
}

static igMetaObjectCallback g_igMetaFieldList_callbackList[] = { igMetaField_EnsureRegistered, 0 };

void igMetaFieldList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igMetaFieldList_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
        igMetaFieldList_GetMetaObjectFunction,
        "igMetaFieldList",
        0x14,
        igMetaFieldList_GetVTable,
        0,
        0,
        g_igMetaFieldList_callbackList
    );
}

void igMetaFieldList_GetMetaObjectFunction(void) {
    igMetaFieldList_GetMetaObject();
}

