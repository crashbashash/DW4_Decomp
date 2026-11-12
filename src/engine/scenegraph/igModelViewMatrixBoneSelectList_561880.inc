igMetaObject *igModelViewMatrixBoneSelectList_561880_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixBoneSelectList_metaObject_00561880[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019d360();
    return g_igModelViewMatrixBoneSelectList_metaObject_00561880[0];
}

int igModelViewMatrixBoneSelectList_561880_GetVTable(void) {
    union U u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052aab0[0];
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}

void FUN_0019d360(void)
{
    igMetaObject_RunStaticInit(igModelViewMatrixBoneSelectList_561880_Register);
}

void igModelViewMatrixBoneSelectList_561880_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igModelViewMatrixBoneSelectList_metaObject_00561880),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igModelViewMatrixBoneSelectList_561880_GetMetaObject,
        igModelViewMatrixBoneSelectList_className,
        0x14, /* instance size */
        igModelViewMatrixBoneSelectList_561880_GetVTable,
        0,
        0, /* extra callback item */
        g_igModelViewMatrixBoneSelectList_561880_callbackList /* callback list */
    );
}

void thunk_igModelViewMatrixBoneSelectList_561880_GetMetaObject(void) {
    igModelViewMatrixBoneSelectList_561880_GetMetaObject();
}

