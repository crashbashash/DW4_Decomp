igMetaObject *g_igNonRefCountedAttrList_metaObject;

igMetaObject *FUN_0013ad40(void) {
    if (g_igNonRefCountedAttrList_metaObject == 0) {
        g_igNonRefCountedAttrList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igNonRefCountedAttrList_metaObject;
}

igMetaObject *igNonRefCountedAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedAttrList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013ae20();
    return g_igNonRefCountedAttrList_metaObject;
}

int igNonRefCountedAttrList_GetVTable(void) {
    struct Obj_13ade0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524490[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0013ae20(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedAttrList_Register);
}

static igMetaObjectCallback g_igNonRefCountedAttrList_callbackList[] = { FUN_0013b110, 0 };

void igNonRefCountedAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igNonRefCountedAttrList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedAttrList_GetMetaObject,
        "igNonRefCountedAttrList",
        0x14, /* instance size */
        igNonRefCountedAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedAttrList_callbackList /* callback list */
    );
}

void thunk_igNonRefCountedAttrList_GetMetaObject(void) {
    igNonRefCountedAttrList_GetMetaObject();
}

int FUN_0013aeb0(void) {
    return g_igNonRefCountedObjectList_metaObject[0];
}

