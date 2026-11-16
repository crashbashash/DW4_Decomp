igMetaObject *g_beCriVolume_metaObject;
igMetaField *g_beCriVolume_isExecMetaField;
igMetaField *g_beCriVolume_maxMetaField;
igMetaField *g_beCriVolume_currentMetaField;
igMetaField *g_beCriVolume_staMetaField;
igMetaField *g_beCriVolume_endMetaField;
igMetaField *g_beCriVolume_unitMetaField;

igMetaObject *beCriVolume_GetOrCreateMetaObject(void) {
    if (g_beCriVolume_metaObject == 0) {
        g_beCriVolume_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beCriVolume_metaObject;
}

igMetaObject *beCriVolume_GetMetaObject(void) {
    igMetaObject *g = g_beCriVolume_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beCriVolume_EnsureRegistered();
done:
    return g_beCriVolume_metaObject;
}

int beCriVolume_GetVTable(void) {
    beCriVolume obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beCriVolume_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void beCriVolume_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCriVolume_Register);
}

CallbackArray *beCriVolume_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCriVolume_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCriVolume_GetMetaObjectFunction,
        "beCriVolume",
        0x20, /* instance size */
        beCriVolume_GetVTable,
        beCriVolume_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beCriVolume_GetMetaObjectFunction(void)
{
    beCriVolume_GetMetaObject();
}

static FieldFactory g_beCriVolume_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_beCriVolume_fieldTable[] = {
    "_isExec",
    "_max",
    "_current",
    "_sta",
    "_end",
    "_unit",
};
static igMetaField **g_beCriVolume_fieldHandles[] = {
    &g_beCriVolume_isExecMetaField,
    &g_beCriVolume_maxMetaField,
    &g_beCriVolume_currentMetaField,
    &g_beCriVolume_staMetaField,
    &g_beCriVolume_endMetaField,
    &g_beCriVolume_unitMetaField,
};
static int g_beCriVolume_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
};

void beCriVolume_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beCriVolume_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beCriVolume_ctorTable, 6);
    igMetaObject_NameFields(meta, g_beCriVolume_fieldTable, g_beCriVolume_fieldHandles, g_beCriVolume_fieldOffsets, base);
}

