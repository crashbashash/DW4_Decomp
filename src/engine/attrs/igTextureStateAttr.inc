igMetaObject *g_igTextureStateAttr_metaObject;
igMetaField *g_igTextureStateAttr_enabledMetaField;
igMetaField *g_igTextureStateAttr_unitIDMetaField;

igTextureStateAttr *igTextureStateAttr_CreateInstance(int allocator) {
    igTextureStateAttr_EnsureRegistered();
    return (igTextureStateAttr *)igMetaObject_CreateInstance(*(igMetaObject * *)0x55ECA8, (igMemoryPoolView *)allocator);
}

igMetaObject *igTextureStateAttr_GetOrCreateMetaObject(void) {
    if (g_igTextureStateAttr_metaObject == 0) {
        g_igTextureStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTextureStateAttr_metaObject;
}

igMetaObject *igTextureStateAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureStateAttr_metaObject != 0) {
        ready = (g_igTextureStateAttr_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igTextureStateAttr_EnsureRegistered();
done:
    return g_igTextureStateAttr_metaObject;
}

int igTextureStateAttr_GetVTable(void) {
    struct Obj_131470 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igTextureStateAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igTextureStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureStateAttr_Register);
}

CallbackArray *igTextureStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureStateAttr_GetMetaObject,
        "igTextureStateAttr",
        0x14, /* instance size */
        igTextureStateAttr_GetVTable,
        &igTextureStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTextureStateAttr_GetMetaObject(void) {
    igTextureStateAttr_GetMetaObject();
}

static FieldFactory g_igTextureStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igTextureStateAttr_fieldTable[] = {
    "_enabled",
    "_unitID",
};
static igMetaField **g_igTextureStateAttr_fieldHandles[] = {
    &g_igTextureStateAttr_enabledMetaField,
    &g_igTextureStateAttr_unitIDMetaField,
};
static int g_igTextureStateAttr_fieldOffsets[] = {
    12,
    16,
};

void igTextureStateAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;
    temp_s0 = g_igTextureStateAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igTextureStateAttr_ctorTable, 2);
    temp_s1 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    *(int *)((char *)temp_s1 + 48) = (int)FUN_00141710;
    igMetaObject_NameFields(temp_s0, g_igTextureStateAttr_fieldTable, g_igTextureStateAttr_fieldHandles, g_igTextureStateAttr_fieldOffsets, temp_s2);
}

