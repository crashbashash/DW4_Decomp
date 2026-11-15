igMetaObject *g_igDecalExt_metaObject;
igMetaField *g_igDecalExt_decalOffsetMetaField;

igMetaObject *FUN_0014f8d0(void)
{
    igMetaObject *meta = g_igDecalExt_metaObject;
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_0014f920();
end:
    return g_igDecalExt_metaObject;
}

void FUN_0014f920(void)
{
    igMetaObject_RunStaticInit(igDecalExt_Register);
}

void igDecalExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igDecalExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_FUN_0014f8d0,
        "igDecalExt",
        0x18, /* instance size */
        0,
        &igDecalExt_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_FUN_0014f8d0(void) {
    FUN_0014f8d0();
}

static FieldFactory g_igDecalExt_ctorTable[] = {
    igUnsignedIntMetaField_Create,
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
    *(int *)((char *)(g_igDecalExt_metaObject) + 60) = (int)(&thunk_igPsx2DecalExt_GetMetaObject);
}

