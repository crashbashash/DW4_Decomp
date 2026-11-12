int FUN_00133430(void) {
    if (DAT_0055ee40[0] == 0) {
        DAT_0055ee40[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055ee40[0];
}

igMetaObject *igStencilStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igStencilStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00133510();
    return g_igStencilStateAttr_metaObject[0];
}

int igStencilStateAttr_GetVTable(void) {
    struct Obj_1334d0 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00522d90[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00133510(void)
{
    igMetaObject_RunStaticInit(igStencilStateAttr_Register);
}

void igStencilStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStencilStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igStencilStateAttr_GetMetaObject,
        igStencilStateAttr_className,
        0x10, /* instance size */
        igStencilStateAttr_GetVTable,
        &igStencilStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igStencilStateAttr_GetMetaObject(void) {
    igStencilStateAttr_GetMetaObject();
}

void igStencilStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055ee40[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485e48[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_00485e50[0], &DAT_00485e58[0], &DAT_00485e60[0], temp_s1);
}

