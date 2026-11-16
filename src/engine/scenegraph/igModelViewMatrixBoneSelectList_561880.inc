igMetaObject *igModelViewMatrixBoneSelectList_561880_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixBoneSelectList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igModelViewMatrixBoneSelectList_561880_EnsureRegistered();
    return g_igModelViewMatrixBoneSelectList_metaObject;
}

int igModelViewMatrixBoneSelectList_561880_GetVTable(void) {
    union U u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052aab0[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void igModelViewMatrixBoneSelectList_561880_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igModelViewMatrixBoneSelectList_561880_Register);
}

static igMetaObjectCallback g_igModelViewMatrixBoneSelectList_callbackList[] = { igModelViewMatrixBoneSelect_EnsureRegistered, 0 };

void igModelViewMatrixBoneSelectList_561880_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igModelViewMatrixBoneSelectList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igModelViewMatrixBoneSelectList_561880_GetMetaObject,
        "igModelViewMatrixBoneSelectList",
        0x14, /* instance size */
        igModelViewMatrixBoneSelectList_561880_GetVTable,
        0,
        0, /* extra callback item */
        g_igModelViewMatrixBoneSelectList_callbackList /* callback list */
    );
}

void thunk_igModelViewMatrixBoneSelectList_561880_GetMetaObject(void) {
    igModelViewMatrixBoneSelectList_561880_GetMetaObject();
}

