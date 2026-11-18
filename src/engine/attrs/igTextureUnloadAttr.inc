igMetaObject *g_igTextureUnloadAttr_metaObject;
igMetaField *g_igTextureUnloadAttr_textureMetaField;
igMetaField *g_igTextureUnloadAttr_unitIDMetaField;

igMetaObject *FUN_00131160(void) {
    if (g_igTextureUnloadAttr_metaObject == 0) {
        g_igTextureUnloadAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTextureUnloadAttr_metaObject;
}

igMetaObject *igTextureUnloadAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureUnloadAttr_metaObject != 0) {
        ready = (g_igTextureUnloadAttr_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igTextureUnloadAttr_EnsureRegistered();
done:
    return g_igTextureUnloadAttr_metaObject;
}

int igTextureUnloadAttr_GetVTable(void) {
    struct Obj_131200 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igTextureUnloadAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igTextureUnloadAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureUnloadAttr_Register);
}

static igMetaObjectCallback g_igTextureUnloadAttr_callbackList[] = { igTextureAttr_EnsureRegistered, 0 };

CallbackArray *igTextureUnloadAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureUnloadAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureUnloadAttr_GetMetaObject,
        "igTextureUnloadAttr",
        0x14, /* instance size */
        igTextureUnloadAttr_GetVTable,
        &igTextureUnloadAttr_InitFields,
        0, /* extra callback item */
        g_igTextureUnloadAttr_callbackList /* callback list */
    );
}

void thunk_igTextureUnloadAttr_GetMetaObject(void) {
    igTextureUnloadAttr_GetMetaObject();
}

static FieldFactory g_igTextureUnloadAttr_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igTextureUnloadAttr_fieldTable[] = {
    "_texture",
    "_unitID",
};
static igMetaField **g_igTextureUnloadAttr_fieldHandles[] = {
    &g_igTextureUnloadAttr_textureMetaField,
    &g_igTextureUnloadAttr_unitIDMetaField,
};
static int g_igTextureUnloadAttr_fieldOffsets[] = {
    12,
    16,
};

void igTextureUnloadAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s3;
    igMetaObject *temp_s0;

    temp_s0 = g_igTextureUnloadAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igTextureUnloadAttr_ctorTable, 2);
    temp_s1 = igMetaObject_GetFieldAt(temp_s0, temp_s2);
    *(int *)((char *)temp_s1 + 56) = (int)igTextureAttr_GetOrCreateMetaObject();
    *(char *)((char *)temp_s1 + 60) = 0;
    temp_s3 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    *(int *)((char *)temp_s3 + 48) = (int)FUN_00141840;
    igMetaObject_NameFields(temp_s0, g_igTextureUnloadAttr_fieldTable, g_igTextureUnloadAttr_fieldHandles, g_igTextureUnloadAttr_fieldOffsets, temp_s2);
}

