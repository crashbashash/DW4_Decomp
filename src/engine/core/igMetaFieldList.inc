void * igMetaFieldList_Create(int arg0) {
    igMetaFieldList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5867C0), (igMemoryPoolView *)arg0));
}

igMetaObject *igMetaFieldList_GetOrCreateMetaObject(void) {
    if (g_igMetaFieldList_metaObject[0] == 0) {
        g_igMetaFieldList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igMetaFieldList_metaObject[0];
}

igMetaObject *igMetaFieldList_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaFieldList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMetaFieldList_EnsureRegistered();
    return g_igMetaFieldList_metaObject[0];
}

int igMetaFieldList_GetVTable(void) {
    igMetaFieldList obj;

    igObject_InitHeader((igObject *)&obj);
    obj._vtable = (int)&DAT_005320a0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igMetaFieldList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMetaFieldList_Register);
}

void igMetaFieldList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMetaFieldList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igMetaFieldList_GetMetaObjectFunction,
        igMetaFieldList_className,
        0x14, /* instance size */
        igMetaFieldList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMetaFieldList_callbackList /* callback list */
    );
}

void igMetaFieldList_GetMetaObjectFunction(void) {
    igMetaFieldList_GetMetaObject();
}

