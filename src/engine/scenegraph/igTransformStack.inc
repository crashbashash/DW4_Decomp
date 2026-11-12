int FUN_00195fe0(void) {
    if (DAT_005612a8[0] == 0) {
        DAT_005612a8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005612a8[0];
}

igMetaObject *igTransformStack_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformStack_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001960c0();
    return g_igTransformStack_metaObject[0];
}

int igTransformStack_GetVTable(void) {
    struct Obj_196080 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052b690[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001960c0(void)
{
    igMetaObject_RunStaticInit(igTransformStack_Register);
}

void igTransformStack_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igTransformStack_metaObject),
        igNonRefCountedObjectStack_Register,
        igNonRefCountedObjectStack_GetPublishedMetaObject,
        thunk_igTransformStack_GetMetaObject,
        igTransformStack_className,
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

