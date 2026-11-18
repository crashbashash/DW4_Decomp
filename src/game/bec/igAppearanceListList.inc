igMetaObject *g_igAppearanceListList_metaObject;

igMetaObject *igAppearanceListList_GetOrCreateMetaObject(void) {
    if (g_igAppearanceListList_metaObject == 0) {
        g_igAppearanceListList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAppearanceListList_metaObject;
}

igMetaObject *igAppearanceListList_GetMetaObject(void) {
    igMetaObject *g = g_igAppearanceListList_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    igAppearanceListList_EnsureRegistered();
done:
    return g_igAppearanceListList_metaObject;
}

int igAppearanceListList_GetVTable(void) {
    igAppearanceListList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_igAppearanceListList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igAppearanceListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAppearanceListList_Register);
}

static igMetaObjectCallback g_igAppearanceListList_callbackList[] = { igAppearanceList_EnsureRegistered, 0 };

CallbackArray *igAppearanceListList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAppearanceListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igAppearanceListList_GetMetaObjectFunction,
        "igAppearanceListList",
        0x14, /* instance size */
        igAppearanceListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAppearanceListList_callbackList /* callback list */
    );
}

void igAppearanceListList_GetMetaObjectFunction(void)
{
    igAppearanceListList_GetMetaObject();
}

igMetaObject *g_igModelViewMatrixBoneSelectListBec_metaObject;

igMetaObject *igModelViewMatrixBoneSelectListBec_GetOrCreateMetaObject(void) {
    if (g_igModelViewMatrixBoneSelectListBec_metaObject == 0) {
        g_igModelViewMatrixBoneSelectListBec_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igModelViewMatrixBoneSelectListBec_metaObject;
}

