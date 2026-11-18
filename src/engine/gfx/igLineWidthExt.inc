igMetaObject *g_igLineWidthExt_metaObject;
igMetaField *g_igLineWidthExt_fWidthMetaField;

igMetaObject *igLineWidthExt_GetMetaObject(void)
{
    igMetaObject *meta = g_igLineWidthExt_metaObject;
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    igLineWidthExt_EnsureRegistered();
end:
    return g_igLineWidthExt_metaObject;
}

void igLineWidthExt_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLineWidthExt_Register);
}

CallbackArray *igLineWidthExt_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igLineWidthExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_igLineWidthExt_GetMetaObject_0014d750,
        "igLineWidthExt",
        0x18, /* instance size */
        0,
        &igLineWidthExt_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igLineWidthExt_GetMetaObjectFunction(void) {
    igLineWidthExt_GetMetaObject();
}

static FieldFactory g_igLineWidthExt_ctorTable[] = {
    (FieldFactory)igFloatMetaField_Create,
};
static const char *g_igLineWidthExt_fieldTable[] = {
    "_fWidth",
};
static igMetaField **g_igLineWidthExt_fieldHandles[] = {
    &g_igLineWidthExt_fWidthMetaField,
};
static int g_igLineWidthExt_fieldOffsets[] = {
    20,
};

void igLineWidthExt_InitFields(void) {
    int fieldStart;
    igMetaObject *meta;

    meta = g_igLineWidthExt_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igLineWidthExt_ctorTable, 1);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart), 1.0f);
    igMetaObject_NameFields(meta, g_igLineWidthExt_fieldTable, g_igLineWidthExt_fieldHandles, g_igLineWidthExt_fieldOffsets, fieldStart);
}

