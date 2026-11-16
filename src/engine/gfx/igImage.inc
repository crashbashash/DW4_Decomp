igMetaObject *g_igImage_metaObject;
igMetaField *g_igImage_pxMetaField;
igMetaField *g_igImage_pyMetaField;
igMetaField *g_igImage_pzMetaField;
igMetaField *g_igImage_psMetaField;
igMetaField *g_igImage_orderMetaField;
igMetaField *g_igImage_bitsRedMetaField;
igMetaField *g_igImage_bitsGrnMetaField;
igMetaField *g_igImage_bitsBluMetaField;
igMetaField *g_igImage_bitsAlphaMetaField;
igMetaField *g_igImage_pfmtMetaField;
igMetaField *g_igImage_imageSizeMetaField;
igMetaField *g_igImage_pImageMetaField;
igMetaField *g_igImage_pNameMetaField;
igMetaField *g_igImage_localImageMetaField;
igMetaField *g_igImage_bitsIntMetaField;
igMetaField *g_igImage_pClutMetaField;
igMetaField *g_igImage_bitsIdxMetaField;
igMetaField *g_igImage_bytesPerRowMetaField;
igMetaField *g_igImage_compressedMetaField;
igMetaField *g_igImage_bitsDepthMetaField;
igMetaField *g_igImage_pNameStringMetaField;

igImage *igImage_CreateInstance(int allocator) {
    igImage_EnsureRegistered();
    return (igImage *)igMetaObject_CreateInstance(g_igImage_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igImage_GetOrCreateMetaObject(void) {
    if (g_igImage_metaObject == 0) {
        g_igImage_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igImage_metaObject;
}

igMetaObject *igImage_GetMetaObject(void)
{
    igMetaObject *g = g_igImage_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igImage_EnsureRegistered();
    return g_igImage_metaObject;
}

void igImage_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igImage_Register);
}

static igMetaObjectCallback g_igImage_callbackList[] = { igClut_EnsureRegistered, 0 };

CallbackArray *igImage_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igImage_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igImage_GetMetaObject,
        "igImage",
        0x5C, /* instance size */
        0,
        &igImage_InitFields,
        thunk_FUN_00156300, /* extra callback item */
        g_igImage_callbackList /* callback list */
    );
}

void thunk_igImage_GetMetaObject(void) {
    igImage_GetMetaObject();
}

static FieldFactory g_igImage_ctorTable[] = {
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
};
static const char *g_igImage_fieldTable[] = {
    "_px",
    "_py",
    "_pz",
    "_ps",
    "_order",
    "_bitsRed",
    "_bitsGrn",
    "_bitsBlu",
    "_bitsAlpha",
    "_pfmt",
    "_imageSize",
    "_pImage",
    "_pName",
    "_localImage",
    "_bitsInt",
    "_pClut",
    "_bitsIdx",
    "_bytesPerRow",
    "_compressed",
    "_bitsDepth",
    "_pNameString",
};
static igMetaField **g_igImage_fieldHandles[] = {
    &g_igImage_pxMetaField,
    &g_igImage_pyMetaField,
    &g_igImage_pzMetaField,
    &g_igImage_psMetaField,
    &g_igImage_orderMetaField,
    &g_igImage_bitsRedMetaField,
    &g_igImage_bitsGrnMetaField,
    &g_igImage_bitsBluMetaField,
    &g_igImage_bitsAlphaMetaField,
    &g_igImage_pfmtMetaField,
    &g_igImage_imageSizeMetaField,
    &g_igImage_pImageMetaField,
    &g_igImage_pNameMetaField,
    &g_igImage_localImageMetaField,
    &g_igImage_bitsIntMetaField,
    &g_igImage_pClutMetaField,
    &g_igImage_bitsIdxMetaField,
    &g_igImage_bytesPerRowMetaField,
    &g_igImage_compressedMetaField,
    &g_igImage_bitsDepthMetaField,
    &g_igImage_pNameStringMetaField,
};
static int g_igImage_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
    76,
    80,
    84,
    88,
};

static int g_igImage_pfmtDefault = 7;

void igImage_InitFields(void) {
    void *temp_s1;
    int fieldStart;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_v0;
    igMetaObject *meta;

    meta = g_igImage_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igImage_ctorTable, 0x15);
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, fieldStart + 3), 1);
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, fieldStart + 4), 0x64);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 9));
    igEnumMetaField_SetDefaultValue(temp_v0, g_igImage_pfmtDefault);
    *(int *)((char *)(temp_v0) + 52) = (int)(&IG_GFX_TEXTURE_FORMAT_GetMetaEnum);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0xA), -2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0xB));
    *(int *)((char *)(temp_s1) + 60) = igUnsignedCharMetaField_GetDefaultDescriptor();
    igMemoryRefMetaField_SetPoolName(temp_s1, "Image");
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0xC));
    *(int *)((char *)(temp_s1_2) + 60) = igCharMetaField_GetDefaultDescriptor();
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, fieldStart + 0xD), 1);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0xF));
    *(int *)((char *)(temp_s1_3) + 56) = (int)FUN_0014fa90();
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x11), -1);
    igMetaObject_NameFields(meta, g_igImage_fieldTable, g_igImage_fieldHandles, g_igImage_fieldOffsets, fieldStart);
    *(int *)((char *)(g_igImage_metaObject) + 60) = (int)thunk_igPsx2Image_GetMetaObject;
}

