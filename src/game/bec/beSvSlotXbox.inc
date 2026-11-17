igMetaObject *g_beSvSlotXbox_metaObject;
igMetaField *g_beSvSlotXbox_nameMetaField;
igMetaField *g_beSvSlotXbox_totalBytesMetaField;
igMetaField *g_beSvSlotXbox_freeBytesMetaField;
igMetaField *g_beSvSlotXbox_useBytesMetaField;

void *beSvSlotXbox_GetMetaObject(void) {
    igMetaObject *g = g_beSvSlotXbox_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvSlotXbox_EnsureRegistered();
    }
    return g_beSvSlotXbox_metaObject;
}

int beSvSlotXbox_GetVTable(void) {
    beSvSlotXbox obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beSvSlotXbox_vtable[0];
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beSvSlotXbox_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beSvSlotXbox_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvSlotXbox_Register);
}

CallbackArray *beSvSlotXbox_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvSlotXbox_metaObject,
        beSvSlotData_Register,
        beSvSlotData_GetPublishedMetaObject,
        beSvSlotXbox_GetMetaObjectFunction,
        "beSvSlotXbox",
        0x38, /* instance size */
        beSvSlotXbox_GetVTable,
        beSvSlotXbox_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvSlotXbox_GetMetaObjectFunction(void)
{
    beSvSlotXbox_GetMetaObject();
}

static FieldFactory g_beSvSlotXbox_ctorTable[] = {
    igStringMetaField_Create,
    igUnsignedLongMetaField_Create,
    igUnsignedLongMetaField_Create,
    igUnsignedLongMetaField_Create,
};
static const char *g_beSvSlotXbox_fieldTable[] = {
    "_name",
    "_totalBytes",
    "_freeBytes",
    "_useBytes",
};
static igMetaField **g_beSvSlotXbox_fieldHandles[] = {
    &g_beSvSlotXbox_nameMetaField,
    &g_beSvSlotXbox_totalBytesMetaField,
    &g_beSvSlotXbox_freeBytesMetaField,
    &g_beSvSlotXbox_useBytesMetaField,
};
static int g_beSvSlotXbox_fieldOffsets[] = {
    24,
    32,
    40,
    48,
};

void beSvSlotXbox_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beSvSlotXbox_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSvSlotXbox_ctorTable, 4);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base), "");
    igMetaObject_NameFields(meta, g_beSvSlotXbox_fieldTable, g_beSvSlotXbox_fieldHandles, g_beSvSlotXbox_fieldOffsets, base);
}

