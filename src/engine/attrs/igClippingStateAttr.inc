int FUN_00139170(void) {
    if (DAT_0055f2f8[0] == 0) {
        DAT_0055f2f8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f2f8[0];
}

igMetaObject *igClippingStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igClippingStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00139250();
    return g_igClippingStateAttr_metaObject[0];
}

int igClippingStateAttr_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523f70[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00139250(void)
{
    igMetaObject_RunStaticInit(igClippingStateAttr_Register);
}

void igClippingStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igClippingStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igClippingStateAttr_GetMetaObject,
        igClippingStateAttr_className,
        0x10, /* instance size */
        igClippingStateAttr_GetVTable,
        &igClippingStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igClippingStateAttr_GetMetaObject(void) {
    igClippingStateAttr_GetMetaObject();
}

void igClippingStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f2f8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486938[0], 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_00486940[0], &DAT_00486948[0], &DAT_00486950[0], temp_s1);
}

