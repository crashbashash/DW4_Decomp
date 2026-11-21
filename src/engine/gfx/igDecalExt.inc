igMetaObject *g_igDecalExt_metaObject;
igMetaField *g_igDecalExt_decalOffsetMetaField;

igMetaObject *igDecalExt_GetMetaObject(void)
{
    igMetaObject *meta = g_igDecalExt_metaObject;
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    igDecalExt_EnsureRegistered();
end:
    return g_igDecalExt_metaObject;
}

void igDecalExt_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDecalExt_Register);
}

CallbackArray *igDecalExt_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igDecalExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        igDecalExt_GetMetaObjectFunction,
        "igDecalExt",
        0x18, /* instance size */
        0,
        &igDecalExt_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igDecalExt_GetMetaObjectFunction(void) {
    igDecalExt_GetMetaObject();
}

static FieldFactory g_igDecalExt_ctorTable[] = {
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igDecalExt_fieldTable[] = {
    "_decalOffset",
};
static igMetaField **g_igDecalExt_fieldHandles[] = {
    &g_igDecalExt_decalOffsetMetaField,
};
static int g_igDecalExt_fieldOffsets[] = {
    20,
};

void igDecalExt_InitFields(void) {
    int fieldStart;
    igMetaObject *meta;

    meta = g_igDecalExt_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igDecalExt_ctorTable, 1);
    igMetaObject_NameFields(meta, g_igDecalExt_fieldTable, g_igDecalExt_fieldHandles, g_igDecalExt_fieldOffsets, fieldStart);
    *(int *)((char *)(g_igDecalExt_metaObject) + 60) = (int)(&igPsx2DecalExt_GetMetaObjectFunction);
}

