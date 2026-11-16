igMetaObject *g_beNDMWListCtrl_metaObject;
igMetaField *g_beNDMWListCtrl_nowPageMetaField;
igMetaField *g_beNDMWListCtrl_maxPageMetaField;
igMetaField *g_beNDMWListCtrl_cursorMetaField;

void *beNDMWListCtrl_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWListCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWListCtrl_EnsureRegistered();
    }
    return g_beNDMWListCtrl_metaObject;
}

void beNDMWListCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWListCtrl_Register);
}

void *beNDMWListCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWListCtrl_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWListCtrl_GetMetaObjectFunction,
        "beNDMWListCtrl",
        0x60, /* instance size */
        0,
        beNDMWListCtrl_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWListCtrl_GetMetaObjectFunction(void)
{
    beNDMWListCtrl_GetMetaObject();
}

static FieldFactory g_beNDMWListCtrl_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWListCtrl_fieldTable[] = {
    "_nowPage",
    "_maxPage",
    "_cursor",
};
static igMetaField **g_beNDMWListCtrl_fieldHandles[] = {
    &g_beNDMWListCtrl_nowPageMetaField,
    &g_beNDMWListCtrl_maxPageMetaField,
    &g_beNDMWListCtrl_cursorMetaField,
};
static int g_beNDMWListCtrl_fieldOffsets[] = {
    84,
    88,
    92,
};

void beNDMWListCtrl_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWListCtrl_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWListCtrl_ctorTable, 3);
    igMetaObject_NameFields(temp_s0, g_beNDMWListCtrl_fieldTable, g_beNDMWListCtrl_fieldHandles, g_beNDMWListCtrl_fieldOffsets, temp_s1);
}

