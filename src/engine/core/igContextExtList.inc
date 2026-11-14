igMetaObject *igContextExtList_GetOrCreateMetaObject(void) {
    if (g_igContextExtList_metaObject[0] == 0) {
        g_igContextExtList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igContextExtList_metaObject[0];
}

igMetaObject *igContextExtList_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExtList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igContextExtList_EnsureRegistered();
    return g_igContextExtList_metaObject[0];
}

int igContextExtList_GetVTable(void) {
    igContextExtList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00531980[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igContextExtList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igContextExtList_Register);
}

void igContextExtList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igContextExtList_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
        igContextExtList_GetMetaObjectFunction,
        igContextExtList_className,
        0x14,
        igContextExtList_GetVTable,
        0,
        0,
        (igMetaObjectCallback *)g_igContextExtList_callbackList
    );
}

void igContextExtList_GetMetaObjectFunction(void) {
    igContextExtList_GetMetaObject();
}

