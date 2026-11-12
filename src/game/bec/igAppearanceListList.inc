igMetaObject *FUN_0033fd70(void) {
    if (g_igAppearanceListList_metaObject[0] == 0) {
        g_igAppearanceListList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igAppearanceListList_metaObject[0];
}

igMetaObject *FUN_0033fdc0(void) {
    igMetaObject *g = g_igAppearanceListList_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_0033fe50();
done:
    return g_igAppearanceListList_metaObject[0];
}

int igAppearanceListList_GetVTable(void) {
    Obj_33fe10 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00539b40[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0033fe50(void)
{
    igMetaObject_RunStaticInit(igAppearanceListList_Register);
}

void *igAppearanceListList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAppearanceListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igAppearanceListList_GetMetaObject,
        igAppearanceListList_className,
        0x14, /* instance size */
        igAppearanceListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAppearanceListList_callbackList /* callback list */
    );
}

void igAppearanceListList_GetMetaObject(void)
{
    FUN_0033fdc0();
}

igMetaObject *FUN_0033ff00(void) {
    if (g_igModelViewMatrixBoneSelectList_metaObject_00587aa0[0] == 0) {
        g_igModelViewMatrixBoneSelectList_metaObject_00587aa0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igModelViewMatrixBoneSelectList_metaObject_00587aa0[0];
}

