igMetaObject *FUN_002c95d0(void) {
    if (g_igFloatListList_metaObject[0] == 0) {
        g_igFloatListList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    }
    return g_igFloatListList_metaObject[0];
}

igMetaObject *igFloatListList_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c96b0();
    return g_igFloatListList_metaObject[0];
}

int igFloatListList_GetVTable(void) {
    struct Obj_2c9670 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00531e80[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002c96b0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igFloatListList_Register);
}

void igFloatListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igFloatListList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igFloatListList_GetMetaObject,
        igFloatListList_className,
        0x14, /* instance size */
        igFloatListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igFloatListList_callbackList /* callback list */
    );
}

void thunk_igFloatListList_GetMetaObject(void) {
    igFloatListList_GetMetaObject();
}

