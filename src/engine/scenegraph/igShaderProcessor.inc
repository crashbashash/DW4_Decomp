int FUN_00198b60(int arg0) {
    FUN_00198c30();
    return igMetaObject_CreateInstance(*(int *)0x5614F8, arg0);
}

igMetaObject *igShaderProcessor_GetMetaObject(void)
{
    igMetaObject *g = g_igShaderProcessor_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00198c30();
    return g_igShaderProcessor_metaObject[0];
}

int igShaderProcessor_GetVTable(void) {
    struct Obj_198bf0 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00528720[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00198c30(void)
{
    igMetaObject_RunStaticInit(igShaderProcessor_Register);
}

void igShaderProcessor_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igShaderProcessor_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igShaderProcessor_GetMetaObject,
        igShaderProcessor_className,
        8, /* instance size */
        igShaderProcessor_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igShaderProcessor_GetMetaObject(void) {
    igShaderProcessor_GetMetaObject();
}

