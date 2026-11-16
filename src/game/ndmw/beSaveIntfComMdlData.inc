igMetaObject *g_beSaveIntfComMdlData_metaObject;
igMetaField *g_beSaveIntfComMdlData_ramNoMetaField;
igMetaField *g_beSaveIntfComMdlData_openSQMetaField;
igMetaField *g_beSaveIntfComMdlData_infoNameMetaField;

void *beSaveIntfComMdlData_GetMetaObject(void) {
    igMetaObject *g = g_beSaveIntfComMdlData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSaveIntfComMdlData_EnsureRegistered();
    }
    return g_beSaveIntfComMdlData_metaObject;
}

int beSaveIntfComMdlData_GetVTable(void) {
    beSaveIntfComMdlData obj;
    int vtable;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beSaveIntfComMdlData_vtable[0];
    obj._openSQ = 0;
    obj._infoName = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beSaveIntfComMdlData_vtable[0];
    if (&obj._infoName != 0) {
        releaseString((const char *)obj._infoName);
    }
    if (&obj._openSQ != 0) {
        releaseString((const char *)obj._openSQ);
    }
    return vtable;
}

void beSaveIntfComMdlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSaveIntfComMdlData_Register);
}

void *beSaveIntfComMdlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSaveIntfComMdlData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSaveIntfComMdlData_GetMetaObjectFunction,
        "beSaveIntfComMdlData",
        0x14, /* instance size */
        beSaveIntfComMdlData_GetVTable,
        beSaveIntfComMdlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSaveIntfComMdlData_GetMetaObjectFunction(void)
{
    beSaveIntfComMdlData_GetMetaObject();
}

static FieldFactory g_beSaveIntfComMdlData_ctorTable[] = {
    igIntMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_beSaveIntfComMdlData_fieldTable[] = {
    "_ramNo",
    "_openSQ",
    "_infoName",
};
static igMetaField **g_beSaveIntfComMdlData_fieldHandles[] = {
    &g_beSaveIntfComMdlData_ramNoMetaField,
    &g_beSaveIntfComMdlData_openSQMetaField,
    &g_beSaveIntfComMdlData_infoNameMetaField,
};
static int g_beSaveIntfComMdlData_fieldOffsets[] = {
    8,
    12,
    16,
};

void beSaveIntfComMdlData_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beSaveIntfComMdlData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSaveIntfComMdlData_ctorTable, 3);
    igMetaObject_NameFields(meta, g_beSaveIntfComMdlData_fieldTable, g_beSaveIntfComMdlData_fieldHandles, g_beSaveIntfComMdlData_fieldOffsets, base);
}

