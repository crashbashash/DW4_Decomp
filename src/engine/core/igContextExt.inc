igMetaObject *igContextExt_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igContextExt_EnsureRegistered();
    return g_igContextExt_metaObject[0];
}

void igContextExt_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igContextExt_Register);
}

void igContextExt_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igContextExt_metaObject),
        igContext_Register,
        igContext_GetPublishedMetaObject,
        igContextExt_GetMetaObjectFunction,
        igContextExt_className,
        0x14, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igContextExt_GetMetaObjectFunction(void) {
    igContextExt_GetMetaObject();
}

