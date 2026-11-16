igMetaObject *g_igViewportResizedMessage_metaObject;
igMetaField *g_igViewportResizedMessage_originMetaField;
igMetaField *g_igViewportResizedMessage_sizeMetaField;

int FUN_002332b0(int arg0) {
    FUN_00233380();
    return igMetaObject_CreateInstance(*(int *)0x56DC10, arg0);
}

igMetaObject *igViewportResizedMessage_GetMetaObject(void)
{
    igMetaObject *g = g_igViewportResizedMessage_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00233380();
    return g_igViewportResizedMessage_metaObject;
}

int igViewportResizedMessage_GetVTable(void) {
    struct Obj_233340 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igViewportResizedMessage_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00233380(void)
{
    igMetaObject_RunStaticInit(igViewportResizedMessage_Register);
}

void igViewportResizedMessage_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewportResizedMessage_metaObject,
        igMessage_Register,
        igMessage_GetPublishedMetaObject,
        thunk_igViewportResizedMessage_GetMetaObject,
        "igViewportResizedMessage",
        0x18, /* instance size */
        igViewportResizedMessage_GetVTable,
        &igViewportResizedMessage_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igViewportResizedMessage_GetMetaObject(void) {
    igViewportResizedMessage_GetMetaObject();
}

static FieldFactory g_igViewportResizedMessage_ctorTable[] = {
    FUN_00187b50,
    FUN_00187b50,
};
static const char *g_igViewportResizedMessage_fieldTable[] = {
    "_origin",
    "_size",
};
static igMetaField **g_igViewportResizedMessage_fieldHandles[] = {
    &g_igViewportResizedMessage_originMetaField,
    &g_igViewportResizedMessage_sizeMetaField,
};
static int g_igViewportResizedMessage_fieldOffsets[] = {
    8,
    16,
};

void igViewportResizedMessage_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igViewportResizedMessage_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igViewportResizedMessage_ctorTable, 2);
    igMetaObject_NameFields(temp_s0, g_igViewportResizedMessage_fieldTable, g_igViewportResizedMessage_fieldHandles, g_igViewportResizedMessage_fieldOffsets, temp_s1);
}

