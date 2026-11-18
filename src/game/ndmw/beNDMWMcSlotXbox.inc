igMetaObject *g_beNDMWMcSlotXbox_metaObject;
igMetaField *g_beNDMWMcSlotXbox_mNameMetaField;

beNDMWMcSlotXbox *beNDMWMcSlotXbox_Create(int allocator) {
    beNDMWMcSlotXbox_EnsureRegistered();
    return (beNDMWMcSlotXbox *)igMetaObject_CreateInstance(g_beNDMWMcSlotXbox_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWMcSlotXbox_GetReadyMetaObject(void)
{
    igMetaObject *g = g_beNDMWMcSlotXbox_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beNDMWMcSlotXbox_EnsureRegistered();
    return g_beNDMWMcSlotXbox_metaObject;
}

int beNDMWMcSlotXbox_GetVTable(void) {
    beNDMWMcSlotXbox obj;
    int vtable;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWMcSlotXbox_vtable[0];
    obj._mName = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWMcSlotXbox_vtable[0];
    if (&obj._mName != 0) {
        releaseString((const char *)obj._mName);
    }
    return vtable;
}

void beNDMWMcSlotXbox_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlotXbox_Register);
}

CallbackArray *beNDMWMcSlotXbox_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMcSlotXbox_metaObject,
        beNDMWMcSlot_Register,
        beNDMWMcSlot_GetPublishedMetaObject,
        beNDMWMcSlotXbox_GetMetaObject,
        "beNDMWMcSlotXbox",
        0x1c, /* instance size */
        beNDMWMcSlotXbox_GetVTable,
        beNDMWMcSlotXbox_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMcSlotXbox_GetMetaObject(void)
{
    beNDMWMcSlotXbox_GetReadyMetaObject();
}

igMetaObject *beNDMWMcSlot_GetPublishedMetaObject(void) {
    return g_beNDMWMcSlot_metaObject;
}

static FieldFactory g_beNDMWMcSlotXbox_ctorTable[] = {
    igStringMetaField_Create,
};
static const char *g_beNDMWMcSlotXbox_fieldTable[] = {
    "_mName",
};
static igMetaField **g_beNDMWMcSlotXbox_fieldHandles[] = {
    &g_beNDMWMcSlotXbox_mNameMetaField,
};
static int g_beNDMWMcSlotXbox_fieldOffsets[] = {
    24,
};

void beNDMWMcSlotXbox_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWMcSlotXbox_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWMcSlotXbox_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beNDMWMcSlotXbox_fieldTable, g_beNDMWMcSlotXbox_fieldHandles, g_beNDMWMcSlotXbox_fieldOffsets, base);
}

