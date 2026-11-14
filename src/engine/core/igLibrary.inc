igMetaObject *igLibrary_GetMetaObject(void)
{
    igMetaObject *g = g_igLibrary_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igLibrary_EnsureRegistered();
    return g_igLibrary_metaObject[0];
}

void igLibrary_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLibrary_Register);
}

void igLibrary_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,
        g_igLibrary_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igLibrary_GetMetaObjectFunction,
        igLibrary_className,
        0xC,
        0,
        igLibrary_InitFields,
        0,
        0
    );
}

void igLibrary_GetMetaObjectFunction(void) {
    igLibrary_GetMetaObject();
}

void igLibrary_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_igLibrary_metaObject[0];
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, (igMetaField * (**)(void *))&g_igLibrary_ctorTable[0], 1);
    igMetaObject_NameFields(meta, (const char **)&g_igLibrary_fieldTable[0], (igMetaField ***)&g_igLibrary_fieldDescriptors[0], &g_igLibrary_fieldOffsets[0], base);
}

