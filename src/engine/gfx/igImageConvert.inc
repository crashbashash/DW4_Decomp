igMetaObject *g_igImageConvert_metaObject;

int igImageConvert_Create(int arg0) {
    igImageConvert_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_igImageConvert_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igImageConvert_GetMetaObject(void)
{
    igMetaObject *g = g_igImageConvert_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igImageConvert_EnsureRegistered();
    return g_igImageConvert_metaObject;
}

void igImageConvert_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igImageConvert_Register);
}

CallbackArray *igImageConvert_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igImageConvert_metaObject,
        igImageUtils_Register,
        igImageUtils_GetPublishedMetaObject,
        igImageConvert_GetMetaObjectFunction,
        "igImageConvert",
        8, /* instance size */
        0,
        igImageConvert_SetAbstractProxy_0014dc40, /* post-init hook */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igImageConvert_GetMetaObjectFunction(void) {
    igImageConvert_GetMetaObject();
}

