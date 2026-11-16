igMetaObject *igModelViewMatrixBoneSelectListSg_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixBoneSelectListSg_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igModelViewMatrixBoneSelectListSg_EnsureRegistered();
    return g_igModelViewMatrixBoneSelectListSg_metaObject;
}

int igModelViewMatrixBoneSelectListSg_GetVTable(void) {
    union U u;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&DAT_0052aab0[0];
    return *(int *)&u.b[*(int *)((char *)g_objectSystem + 916)];
}

void igModelViewMatrixBoneSelectListSg_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igModelViewMatrixBoneSelectListSg_Register);
}

static igMetaObjectCallback g_igModelViewMatrixBoneSelectListSg_callbackList[] = { igModelViewMatrixBoneSelect_EnsureRegistered, 0 };

CallbackArray *igModelViewMatrixBoneSelectListSg_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igModelViewMatrixBoneSelectListSg_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igModelViewMatrixBoneSelectListSg_GetMetaObject,
        "igModelViewMatrixBoneSelectList",
        0x14, /* instance size */
        igModelViewMatrixBoneSelectListSg_GetVTable,
        0,
        0, /* extra callback item */
        g_igModelViewMatrixBoneSelectListSg_callbackList /* callback list */
    );
}

void thunk_igModelViewMatrixBoneSelectListSg_GetMetaObject(void) {
    igModelViewMatrixBoneSelectListSg_GetMetaObject();
}

