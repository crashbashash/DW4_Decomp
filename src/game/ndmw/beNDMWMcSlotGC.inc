igMetaObject *g_beNDMWMcSlotGC_metaObject;
igMetaField *g_beNDMWMcSlotGC_fileKazMetaField;
igMetaField *g_beNDMWMcSlotGC_detailMetaField;

void beNDMWMcSlotGC_Create(int arg0) {
    beNDMWMcSlotGC_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWMcSlotGC_metaObject, arg0);
}

igMetaObject *beNDMWMcSlotGC_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMcSlotGC_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNDMWMcSlotGC_EnsureRegistered();
    return g_beNDMWMcSlotGC_metaObject;
}

int beNDMWMcSlotGC_GetVTable(void) {
    Obj_3c5d80 o;

    igObject_InitHeader(&o);
    o.vt = &g_beNDMWMcSlotGC_vtable[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beNDMWMcSlotGC_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlotGC_Register);
}

void *beNDMWMcSlotGC_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMcSlotGC_metaObject,
        beNDMWMcSlot_Register,
        beNDMWMcSlot_GetPublishedMetaObject,
        beNDMWMcSlotGC_GetMetaObject,
        "beNDMWMcSlotGC",
        0x20, /* instance size */
        beNDMWMcSlotGC_GetVTable,
        beNDMWMcSlotGC_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMcSlotGC_GetMetaObject(void)
{
    beNDMWMcSlotGC_GetReadyMetaObject();
}

static FieldFactory g_beNDMWMcSlotGC_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWMcSlotGC_fieldTable[] = {
    "_fileKaz",
    "_detail",
};
static igMetaField **g_beNDMWMcSlotGC_fieldHandles[] = {
    &g_beNDMWMcSlotGC_fileKazMetaField,
    &g_beNDMWMcSlotGC_detailMetaField,
};
static int g_beNDMWMcSlotGC_fieldOffsets[] = {
    24,
    28,
};

void beNDMWMcSlotGC_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWMcSlotGC_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWMcSlotGC_ctorTable, 2);
    igMetaObject_NameFields(temp_s0, g_beNDMWMcSlotGC_fieldTable, g_beNDMWMcSlotGC_fieldHandles, g_beNDMWMcSlotGC_fieldOffsets, temp_s1);
}

