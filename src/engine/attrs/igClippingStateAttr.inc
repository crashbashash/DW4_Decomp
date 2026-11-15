igMetaObject *g_igClippingStateAttr_metaObject;
igMetaField *g_igClippingStateAttr_enabledMetaField;

igMetaObject *FUN_00139170(void) {
    if (g_igClippingStateAttr_metaObject == 0) {
        g_igClippingStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igClippingStateAttr_metaObject;
}

igMetaObject *igClippingStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igClippingStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00139250();
    return g_igClippingStateAttr_metaObject;
}

int igClippingStateAttr_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523f70[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00139250(void)
{
    igMetaObject_RunStaticInit(igClippingStateAttr_Register);
}

void igClippingStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igClippingStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igClippingStateAttr_GetMetaObject,
        "igClippingStateAttr",
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

static FieldFactory g_igClippingStateAttr_ctorTable[] = {
    igBoolMetaField_Create,
};
static const char *g_igClippingStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igClippingStateAttr_fieldHandles[] = {
    &g_igClippingStateAttr_enabledMetaField,
};
static int g_igClippingStateAttr_fieldOffsets[] = {
    12,
};

void igClippingStateAttr_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igClippingStateAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igClippingStateAttr_ctorTable, 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, g_igClippingStateAttr_fieldTable, g_igClippingStateAttr_fieldHandles, g_igClippingStateAttr_fieldOffsets, temp_s1);
}

