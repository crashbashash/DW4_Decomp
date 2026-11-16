igMetaObject *g_igTextureCoordSourceAttr_metaObject;
igMetaField *g_igTextureCoordSourceAttr_modeMetaField;
igMetaField *g_igTextureCoordSourceAttr_texCoordIndexMetaField;
igMetaField *g_igTextureCoordSourceAttr_unitIDMetaField;

void FUN_001325a0(int arg0) {
    igTextureCoordSourceAttr_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x55ED68, arg0);
}

igMetaObject *FUN_001325e0(void) {
    if (g_igTextureCoordSourceAttr_metaObject == 0) {
        g_igTextureCoordSourceAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igTextureCoordSourceAttr_metaObject;
}

igMetaObject *igTextureCoordSourceAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureCoordSourceAttr_metaObject != 0) {
        ready = (g_igTextureCoordSourceAttr_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igTextureCoordSourceAttr_EnsureRegistered();
done:
    return g_igTextureCoordSourceAttr_metaObject;
}

int igTextureCoordSourceAttr_GetVTable(void) {
    struct Obj_132680 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igTextureCoordSourceAttr_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igTextureCoordSourceAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureCoordSourceAttr_Register);
}

void igTextureCoordSourceAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureCoordSourceAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureCoordSourceAttr_GetMetaObject,
        "igTextureCoordSourceAttr",
        0x18, /* instance size */
        igTextureCoordSourceAttr_GetVTable,
        &igTextureCoordSourceAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTextureCoordSourceAttr_GetMetaObject(void) {
    igTextureCoordSourceAttr_GetMetaObject();
}

static FieldFactory g_igTextureCoordSourceAttr_ctorTable[] = {
    igEnumMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_igTextureCoordSourceAttr_fieldTable[] = {
    "_mode",
    "_texCoordIndex",
    "_unitID",
};
static igMetaField **g_igTextureCoordSourceAttr_fieldHandles[] = {
    &g_igTextureCoordSourceAttr_modeMetaField,
    &g_igTextureCoordSourceAttr_texCoordIndexMetaField,
    &g_igTextureCoordSourceAttr_unitIDMetaField,
};
static int g_igTextureCoordSourceAttr_fieldOffsets[] = {
    12,
    16,
    20,
};

void igTextureCoordSourceAttr_InitFields(void) {
    void *temp_v0_2;
    igMetaObject *temp_s0;
    int temp_s2;
    void *temp_v0;

    temp_s0 = g_igTextureCoordSourceAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igTextureCoordSourceAttr_ctorTable, 3);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    igEnumMetaField_SetDefaultValue(temp_v0, 0);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_001497a0);
    temp_v0_2 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2);
    *(int *)((char *)(temp_v0_2) + 48) = (int)(FUN_00140fd0);
    igMetaObject_NameFields(temp_s0, g_igTextureCoordSourceAttr_fieldTable, g_igTextureCoordSourceAttr_fieldHandles, g_igTextureCoordSourceAttr_fieldOffsets, temp_s2);
}

