igMetaObject *g_igTransformStack_metaObject;

igMetaObject *FUN_00195fe0(void) {
    if (g_igTransformStack_metaObject == 0) {
        g_igTransformStack_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igTransformStack_metaObject;
}

igMetaObject *igTransformStack_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformStack_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001960c0();
    return g_igTransformStack_metaObject;
}

int igTransformStack_GetVTable(void) {
    struct Obj_196080 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igTransformStack_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001960c0(void)
{
    igMetaObject_RunStaticInit(igTransformStack_Register);
}

static igMetaObjectCallback g_igTransformStack_callbackList[] = { igTransform_EnsureRegistered, 0 };

void igTransformStack_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTransformStack_metaObject,
        igNonRefCountedObjectStack_Register,
        igNonRefCountedObjectStack_GetPublishedMetaObject,
        thunk_igTransformStack_GetMetaObject,
        "igTransformStack",
        0x14, /* instance size */
        igTransformStack_GetVTable,
        0,
        0, /* extra callback item */
        g_igTransformStack_callbackList /* callback list */
    );
}

void thunk_igTransformStack_GetMetaObject(void) {
    igTransformStack_GetMetaObject();
}

