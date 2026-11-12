int FUN_00194dd0(void) {
    if (DAT_005611d0[0] == 0) {
        DAT_005611d0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005611d0[0];
}

igMetaObject *igTransformSource_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformSource_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00194e70();
    return g_igTransformSource_metaObject[0];
}

void FUN_00194e70(void)
{
    igMetaObject_RunStaticInit(igTransformSource_Register);
}

void igTransformSource_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igTransformSource_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igTransformSource_GetMetaObject,
        igTransformSource_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTransformSource_GetMetaObject(void) {
    igTransformSource_GetMetaObject();
}

