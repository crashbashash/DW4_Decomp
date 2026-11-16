igMetaObject *g_beNDMWStatusCtrlSendBit_metaObject;
igMetaField *g_beNDMWStatusCtrlSendBit_editBitMetaField;
igMetaField *g_beNDMWStatusCtrlSendBit_editMaxMetaField;
igMetaField *g_beNDMWStatusCtrlSendBit_playerNoListMetaField;
igMetaField *g_beNDMWStatusCtrlSendBit_receiptMetaField;

void beNDMWStatusCtrlSendBit_Create(int arg0) {
    beNDMWStatusCtrlSendBit_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusCtrlSendBit_metaObject, arg0);
}

void *beNDMWStatusCtrlSendBit_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusCtrlSendBit_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusCtrlSendBit_EnsureRegistered();
    }
    return g_beNDMWStatusCtrlSendBit_metaObject;
}

int beNDMWStatusCtrlSendBit_GetVTable(void) {
    struct F_3b95f0 f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[12] = 0;
    f.w[13] = 0;
    f.w[14] = 0;
    f.w[15] = 0;
    f.w[16] = 0;
    f.w[17] = 0;
    f.w[18] = 0;
    f.vt = &g_beNDMWStatusCtrlSendBit_vtable[0];
    f.w[22] = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &g_beNDMWStatusCtrlSendBit_vtable[0];
    FUN_00150eb0(&f.w[22], -1);
    FUN_003b6430(&f, 0);
    return temp_s0;
}

void beNDMWStatusCtrlSendBit_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlSendBit_Register);
}

static igMetaObjectCallback g_beNDMWStatusCtrlSendBit_callbackList[] = { igIntList_EnsureRegistered, 0 };

void *beNDMWStatusCtrlSendBit_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusCtrlSendBit_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlSendBit_GetMetaObjectFunction,
        "beNDMWStatusCtrlSendBit",
        0x64, /* instance size */
        beNDMWStatusCtrlSendBit_GetVTable,
        beNDMWStatusCtrlSendBit_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlSendBit_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlSendBit_GetMetaObjectFunction(void)
{
    beNDMWStatusCtrlSendBit_GetMetaObject();
}

static FieldFactory g_beNDMWStatusCtrlSendBit_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWStatusCtrlSendBit_fieldTable[] = {
    "_editBit",
    "_editMax",
    "_playerNoList",
    "_receipt",
};
static igMetaField **g_beNDMWStatusCtrlSendBit_fieldHandles[] = {
    &g_beNDMWStatusCtrlSendBit_editBitMetaField,
    &g_beNDMWStatusCtrlSendBit_editMaxMetaField,
    &g_beNDMWStatusCtrlSendBit_playerNoListMetaField,
    &g_beNDMWStatusCtrlSendBit_receiptMetaField,
};
static int g_beNDMWStatusCtrlSendBit_fieldOffsets[] = {
    84,
    88,
    92,
    96,
};

void beNDMWStatusCtrlSendBit_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWStatusCtrlSendBit_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWStatusCtrlSendBit_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beNDMWStatusCtrlSendBit_fieldTable, g_beNDMWStatusCtrlSendBit_fieldHandles, g_beNDMWStatusCtrlSendBit_fieldOffsets, temp_s2);
}

