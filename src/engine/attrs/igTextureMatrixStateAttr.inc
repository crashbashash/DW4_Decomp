igMetaObject *g_igTextureMatrixStateAttr_metaObject;
igMetaField *g_igTextureMatrixStateAttr_enabledMetaField;
igMetaField *g_igTextureMatrixStateAttr_unitIDMetaField;

void FUN_001315d0(int arg0) {
    igTextureMatrixStateAttr_EnsureRegistered();
    igMetaObject_CreateInstance(*(igMetaObject * *)0x55ECC0, (igMemoryPoolView *)arg0);
}

igMetaObject *igTextureMatrixStateAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureMatrixStateAttr_metaObject != 0) {
        ready = (g_igTextureMatrixStateAttr_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igTextureMatrixStateAttr_EnsureRegistered();
done:
    return g_igTextureMatrixStateAttr_metaObject;
}

int igTextureMatrixStateAttr_GetVTable(void) {
    struct Obj_131660 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igTextureMatrixStateAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igTextureMatrixStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureMatrixStateAttr_Register);
}

CallbackArray *igTextureMatrixStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureMatrixStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureMatrixStateAttr_GetMetaObject,
        "igTextureMatrixStateAttr",
        0x14, /* instance size */
        igTextureMatrixStateAttr_GetVTable,
        &igTextureMatrixStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTextureMatrixStateAttr_GetMetaObject(void) {
    igTextureMatrixStateAttr_GetMetaObject();
}

static FieldFactory g_igTextureMatrixStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igTextureMatrixStateAttr_fieldTable[] = {
    "_enabled",
    "_unitID",
};
static igMetaField **g_igTextureMatrixStateAttr_fieldHandles[] = {
    &g_igTextureMatrixStateAttr_enabledMetaField,
    &g_igTextureMatrixStateAttr_unitIDMetaField,
};
static int g_igTextureMatrixStateAttr_fieldOffsets[] = {
    12,
    16,
};

void igTextureMatrixStateAttr_InitFields(void) {
    igMetaObject *temp_s0;
    int temp_s1;
    struct F *f;

    temp_s0 = g_igTextureMatrixStateAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igTextureMatrixStateAttr_ctorTable, 2);
    f = (struct F *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    f->f48 = (int *)FUN_00141620;
    igMetaObject_NameFields(temp_s0, g_igTextureMatrixStateAttr_fieldTable, g_igTextureMatrixStateAttr_fieldHandles, g_igTextureMatrixStateAttr_fieldOffsets, temp_s1);
}

