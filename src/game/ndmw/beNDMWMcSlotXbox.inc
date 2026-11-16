igMetaObject *g_beNDMWMcSlotXbox_metaObject;
igMetaField *g_beNDMWMcSlotXbox_mNameMetaField;

void beNDMWMcSlotXbox_Create(int allocator) {
    beNDMWMcSlotXbox_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWMcSlotXbox_metaObject, allocator);
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
    struct W_3c5b30 o;
    int r;

    int *p; int *a1; int t;
    igObject_InitHeader(&o);
    o.vt = g_beNDMWMcSlotXbox_vtable;
    *(int *)((char *)&o + 24) = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beNDMWMcSlotXbox_vtable;
    if (&*(int *)((char *)&o + 24) != 0) { p = *(int **)((char *)&o + 24); if (p != 0) { a1 = p - 2; t = p[-1] - 1; p[-1] = t; if (t == 0) StringChunk_ReleaseHeader(*a1, a1); } }
    return r;
}

void beNDMWMcSlotXbox_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlotXbox_Register);
}

void *beNDMWMcSlotXbox_Register(void) {
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

