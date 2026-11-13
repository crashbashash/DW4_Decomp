igMetaObject *igLibrary_GetMetaObject(void)
{
    igMetaObject *g = g_igLibrary_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c2570();
    return g_igLibrary_metaObject[0];
}

void FUN_002c2570(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLibrary_Register);
}

void igLibrary_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igLibrary_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igLibrary_GetMetaObject,
        igLibrary_className,
        0xC, /* instance size */
        0,
        &igLibrary_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igLibrary_GetMetaObject(void) {
    igLibrary_GetMetaObject();
}

void igLibrary_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igLibrary_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igLibrary_ctorTable[0], 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igLibrary_fieldTable[0], (igMetaField ***)&DAT_004c05b0[0], &DAT_004c05b8[0], temp_s1);
}

