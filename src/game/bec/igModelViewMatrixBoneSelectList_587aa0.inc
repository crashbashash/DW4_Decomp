igMetaObject *igModelViewMatrixBoneSelectListBec_GetMetaObject(void) {
    if (g_igModelViewMatrixBoneSelectListBec_metaObject == 0 || !isValid(g_igModelViewMatrixBoneSelectListBec_metaObject)) igModelViewMatrixBoneSelectListBec_EnsureRegistered();
    return g_igModelViewMatrixBoneSelectListBec_metaObject;
}

int igModelViewMatrixBoneSelectListBec_GetVTable(void) {
    igModelViewMatrixBoneSelectList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_igModelViewMatrixBoneSelectListBec_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igModelViewMatrixBoneSelectListBec_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igModelViewMatrixBoneSelectListBec_Register);
}

static igMetaObjectCallback g_igModelViewMatrixBoneSelectListBec_callbackList[] = { igModelViewMatrixBoneSelect_EnsureRegistered, 0 };

CallbackArray *igModelViewMatrixBoneSelectListBec_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igModelViewMatrixBoneSelectListBec_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igModelViewMatrixBoneSelectListBec_GetMetaObjectFunction,
        "igModelViewMatrixBoneSelectList",
        0x14, /* instance size */
        igModelViewMatrixBoneSelectListBec_GetVTable,
        0,
        0, /* extra callback item */
        g_igModelViewMatrixBoneSelectListBec_callbackList /* callback list */
    );
}

void igModelViewMatrixBoneSelectListBec_GetMetaObjectFunction(void)
{
    igModelViewMatrixBoneSelectListBec_GetMetaObject();
}

