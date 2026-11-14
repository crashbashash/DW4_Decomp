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
        1,
        g_igContextExt_metaObject,
        (igMetaObjectRegisterFunction)igContext_Register,
        (igMetaObjectGetFunction)igContext_GetPublishedMetaObject,
        igContextExt_GetMetaObjectFunction,
        igContextExt_className,
        0x14,
        0,
        0,
        0,
        0
    );
}

void igContextExt_GetMetaObjectFunction(void) {
    igContextExt_GetMetaObject();
}

