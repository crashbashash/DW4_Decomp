igMetaObject *FUN_002cb340(void) {
    if (g_igContextExtList_metaObject[0] == 0) {
        g_igContextExtList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    }
    return g_igContextExtList_metaObject[0];
}

igMetaObject *igContextExtList_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExtList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cb420();
    return g_igContextExtList_metaObject[0];
}

int igContextExtList_GetVTable(void) {
    struct Obj_2cb3e0 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00531980[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002cb420(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igContextExtList_Register);
}

void igContextExtList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igContextExtList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igContextExtList_GetMetaObject,
        igContextExtList_className,
        0x14, /* instance size */
        igContextExtList_GetVTable,
        0,
        0, /* extra callback item */
        g_igContextExtList_callbackList /* callback list */
    );
}

void thunk_igContextExtList_GetMetaObject(void) {
    igContextExtList_GetMetaObject();
}

