int FUN_00133950(void) {
    if (DAT_0055ee90[0] == 0) {
        DAT_0055ee90[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055ee90[0];
}

igMetaObject *igShadeModelAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igShadeModelAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00133a30();
    return g_igShadeModelAttr_metaObject[0];
}

int igShadeModelAttr_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00522ec0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00133a30(void)
{
    igMetaObject_RunStaticInit(igShadeModelAttr_Register);
}

void igShadeModelAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igShadeModelAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igShadeModelAttr_GetMetaObject,
        igShadeModelAttr_className,
        0x10, /* instance size */
        igShadeModelAttr_GetVTable,
        &igShadeModelAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igShadeModelAttr_GetMetaObject(void) {
    igShadeModelAttr_GetMetaObject();
}

void igShadeModelAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055ee90[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485f10[0], 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00485f30[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00149680);
    igMetaObject_NameFields(temp_s0, &DAT_00485f18[0], &DAT_00485f20[0], &DAT_00485f28[0], temp_s2);
}

