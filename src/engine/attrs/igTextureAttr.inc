igMetaObject *g_igTextureAttr_metaObject;
igMetaField *g_igTextureAttr_bColorMetaField;
igMetaField *g_igTextureAttr_magFilterMetaField;
igMetaField *g_igTextureAttr_minFilterMetaField;
igMetaField *g_igTextureAttr_wrapSMetaField;
igMetaField *g_igTextureAttr_wrapTMetaField;
igMetaField *g_igTextureAttr_texIdMetaField;
igMetaField *g_igTextureAttr_mipmapModeMetaField;
igMetaField *g_igTextureAttr_sourceMetaField;
igMetaField *g_igTextureAttr_imageMetaField;
igMetaField *g_igTextureAttr_pagingMetaField;
igMetaField *g_igTextureAttr_tuMetaField;
igMetaField *g_igTextureAttr_imageCountMetaField;
igMetaField *g_igTextureAttr_imageMipMapsMetaField;
igMetaField *g_igTextureAttr_vcMetaField;
igMetaField *g_igTextureAttr_videoBufferMetaField;

igTextureAttr *igTextureAttr_CreateInstance(int allocator) {
    igTextureAttr_EnsureRegistered();
    return (igTextureAttr *)igMetaObject_CreateInstance(g_igTextureAttr_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igTextureAttr_GetOrCreateMetaObject(void) {
    if (g_igTextureAttr_metaObject == 0) {
        g_igTextureAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTextureAttr_metaObject;
}

igMetaObject *igTextureAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureAttr_metaObject != 0) {
        ready = (g_igTextureAttr_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igTextureAttr_EnsureRegistered();
done:
    return g_igTextureAttr_metaObject;
}

int igTextureAttr_GetVTable(void) {
    union U_132c40 u;
    int temp_s;
    char *p136;
    char *p128;
    char *p92;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igTextureAttr_vtable[0];
    p92 = &u.b[12];
    *(int *)p92 = 0;
    p128 = &u.b[48];
    *(int *)p128 = 0;
    p136 = &u.b[56];
    *(int *)p136 = 0;
    *(int *)&u.b[64] = 0;
    temp_s = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igTextureAttr_vtable[0];
    FUN_00132130((Ref **)&u.b[64], -1);
    FUN_001321b0((void **)p136, -1);
    igSmartPointer_igImage_Destruct((igSmartPointer<igObject> *)p128, -1);
    igSmartPointer_igVisualContext_Destruct((igSmartPointer<igObject> *)p92, -1);
    return temp_s;
}

void igTextureAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureAttr_Register);
}

static igMetaObjectCallback g_igTextureAttr_callbackList[] = { igImage_EnsureRegistered, Gap::Attrs::igTextureUnloadAttr::arkRegister, igImageMipMapList_EnsureRegistered, igVisualContext_EnsureRegistered, 0 };

CallbackArray *igTextureAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureAttr_metaObject,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        igTextureAttr_GetMetaObjectFunction,
        "igTextureAttr",
        0x48, /* instance size */
        igTextureAttr_GetVTable,
        &igTextureAttr_InitFields,
        0, /* extra callback item */
        g_igTextureAttr_callbackList /* callback list */
    );
}

void igTextureAttr_GetMetaObjectFunction(void) {
    igTextureAttr_GetMetaObject();
}

static FieldFactory g_igTextureAttr_ctorTable[] = {
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
};
static const char *g_igTextureAttr_fieldTable[] = {
    "_bColor",
    "_magFilter",
    "_minFilter",
    "_wrapS",
    "_wrapT",
    "_texId",
    "_mipmapMode",
    "_source",
    "_image",
    "_paging",
    "_tu",
    "_imageCount",
    "_imageMipMaps",
    "_vc",
    "_videoBuffer",
};
static igMetaField **g_igTextureAttr_fieldHandles[] = {
    &g_igTextureAttr_bColorMetaField,
    &g_igTextureAttr_magFilterMetaField,
    &g_igTextureAttr_minFilterMetaField,
    &g_igTextureAttr_wrapSMetaField,
    &g_igTextureAttr_wrapTMetaField,
    &g_igTextureAttr_texIdMetaField,
    &g_igTextureAttr_mipmapModeMetaField,
    &g_igTextureAttr_sourceMetaField,
    &g_igTextureAttr_imageMetaField,
    &g_igTextureAttr_pagingMetaField,
    &g_igTextureAttr_tuMetaField,
    &g_igTextureAttr_imageCountMetaField,
    &g_igTextureAttr_imageMipMapsMetaField,
    &g_igTextureAttr_vcMetaField,
    &g_igTextureAttr_videoBufferMetaField,
};
static int g_igTextureAttr_fieldOffsets[] = {
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
    12,
    68,
};

int g_igTextureAttr_wrapSDefault = 1;
int g_igTextureAttr_wrapTDefault = 1;

void igTextureAttr_InitFields(void) {
    igMetaObject *meta;
    int base;
    void *field;
    void *field2;
    void *field3;
    void *field4;
    void *field5;
    void *field6;
    void *field7;
    void *field8;
    void *field9;
    void *field10;
    void *field11;

    meta = g_igTextureAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igTextureAttr_ctorTable, 0xF);
    field5 = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((Gap::Core::igEnumMetaField *)field5)->setDefault(0);
    *(void **)&((igEnumMetaField *)field5)->_getMetaEnumFunction = (void *)IG_GFX_TEXTURE_FILTER_GetMetaEnum;
    field6 = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((Gap::Core::igEnumMetaField *)field6)->setDefault(0);
    *(void **)&((igEnumMetaField *)field6)->_getMetaEnumFunction = (void *)IG_GFX_TEXTURE_FILTER_GetMetaEnum;
    field7 = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((Gap::Core::igEnumMetaField *)field7)->setDefault(g_igTextureAttr_wrapSDefault);
    *(void **)&((igEnumMetaField *)field7)->_getMetaEnumFunction = (void *)IG_GFX_TEXTURE_WRAP_GetMetaEnum;
    field8 = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((Gap::Core::igEnumMetaField *)field8)->setDefault(g_igTextureAttr_wrapTDefault);
    *(void **)&((igEnumMetaField *)field8)->_getMetaEnumFunction = (void *)IG_GFX_TEXTURE_WRAP_GetMetaEnum;
    field9 = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((Gap::Core::igIntMetaField *)field9)->setDefault(-1);
    ((igIntMetaField *)field9)->_persistent = 0;
    ((igIntMetaField *)field9)->_deepCopyMethod = 4;
    ((igIntMetaField *)field9)->_shallowCopyMethod = 4;
    ((igIntMetaField *)field9)->_isAlikeShallowMethod = 3;
    field10 = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((Gap::Core::igEnumMetaField *)field10)->setDefault(0);
    *(void **)&((igEnumMetaField *)field10)->_getMetaEnumFunction = (void *)IG_GFX_TEXTURE_MODE_GetMetaEnum;
    field11 = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((Gap::Core::igEnumMetaField *)field11)->setDefault(0);
    *(void **)&((igEnumMetaField *)field11)->_getMetaEnumFunction = (void *)IG_GFX_TEXTURE_SOURCE_GetMetaEnum;
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igImage_GetOrCreateMetaObject();
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base + 0xA));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)Gap::Attrs::igTextureUnloadAttr::getClassTypeLazy();
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt(meta, base + 0xB)))->setDefault(1);
    field3 = (void *)(igMetaObject_GetFieldAt(meta, base + 0xC));
    ((igObjectRefMetaField *)field3)->_metaObject = (int)igImageMipMapList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field3)->_construct = 1;
    field4 = (void *)(igMetaObject_GetFieldAt(meta, base + 0xD));
    ((igObjectRefMetaField *)field4)->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field4)->_persistent = 0;
    ((igObjectRefMetaField *)field4)->_deepCopyMethod = 1;
    ((igObjectRefMetaField *)field4)->_shallowCopyMethod = 1;
    ((igObjectRefMetaField *)field4)->_isAlikeShallowMethod = 3;
    ((igRawRefMetaField *)igMetaObject_GetFieldAt(meta, base + 0xE))->_persistent = 0;
    igMetaObject_NameFields(meta, g_igTextureAttr_fieldTable, g_igTextureAttr_fieldHandles, g_igTextureAttr_fieldOffsets, base);
}

