igMetaObject *g_beNDMWMcSlot_metaObject;
igMetaField *g_beNDMWMcSlot_isConnectMetaField;
igMetaField *g_beNDMWMcSlot_isFileMetaField;
igMetaField *g_beNDMWMcSlot_totalSizeMetaField;
igMetaField *g_beNDMWMcSlot_freeSizeMetaField;
igMetaField *g_beNDMWMcSlot_isFormatMetaField;

void *beNDMWMcSlot_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMcSlot_metaObject;
    bool ready;
    if (g) {
        /* matching construct: the bool compared against false keeps the retail sltu normalisation under the
         * unit profile (3.0 -O3, exceptions on); a member-function spelling matched only under the combat -O3,p override */
        ready = g->_validity & 4;
        if (ready != false) goto end;
    }
    FUN_003c60b0();
end:
    return g_beNDMWMcSlot_metaObject;
}

void FUN_003c60b0(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlot_Register);
}

void *beNDMWMcSlot_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWMcSlot_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWMcSlot_GetMetaObject,
        "beNDMWMcSlot",
        0x18, /* instance size */
        0,
        beNDMWMcSlot_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMcSlot_GetMetaObject(void)
{
    beNDMWMcSlot_GetReadyMetaObject();
}

static FieldFactory g_beNDMWMcSlot_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beNDMWMcSlot_fieldTable[] = {
    "_isConnect",
    "_isFile",
    "_totalSize",
    "_freeSize",
    "_isFormat",
};
static igMetaField **g_beNDMWMcSlot_fieldHandles[] = {
    &g_beNDMWMcSlot_isConnectMetaField,
    &g_beNDMWMcSlot_isFileMetaField,
    &g_beNDMWMcSlot_totalSizeMetaField,
    &g_beNDMWMcSlot_freeSizeMetaField,
    &g_beNDMWMcSlot_isFormatMetaField,
};
static int g_beNDMWMcSlot_fieldOffsets[] = {
    8,
    9,
    12,
    16,
    20,
};

void beNDMWMcSlot_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWMcSlot_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWMcSlot_ctorTable, 5);
    igMetaObject_NameFields(temp_s0, g_beNDMWMcSlot_fieldTable, g_beNDMWMcSlot_fieldHandles, g_beNDMWMcSlot_fieldOffsets, temp_s1);
}

