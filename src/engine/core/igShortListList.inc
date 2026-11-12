void FUN_002c9bd0(int arg0) {
    FUN_002c9cf0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586828), (MemoryPool *)arg0);
}

igMetaObject *FUN_002c9c10(void) {
    if (g_igShortListList_metaObject[0] == 0) {
        g_igShortListList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    }
    return g_igShortListList_metaObject[0];
}

igMetaObject *igShortListList_GetMetaObject(void)
{
    igMetaObject *g = g_igShortListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c9cf0();
    return g_igShortListList_metaObject[0];
}

int igShortListList_GetVTable(void) {
    struct Obj_2c9cb0 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00531d50[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002c9cf0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igShortListList_Register);
}

void igShortListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igShortListList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igShortListList_GetMetaObject,
        igShortListList_className,
        0x14, /* instance size */
        igShortListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igShortListList_callbackList /* callback list */
    );
}

void thunk_igShortListList_GetMetaObject(void) {
    igShortListList_GetMetaObject();
}

