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
    return (igTextureAttr *)igMetaObject_CreateInstance(*(int *)0x55EDA0, allocator);
}

igMetaObject *igTextureAttr_GetOrCreateMetaObject(void) {
    if (g_igTextureAttr_metaObject == 0) {
        g_igTextureAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    igObject_InitHeader(u.b);
    u.vt = (int)&g_igTextureAttr_vtable[0];
    p92 = &u.b[12];
    *(int *)p92 = 0;
    p128 = &u.b[48];
    *(int *)p128 = 0;
    p136 = &u.b[56];
    *(int *)p136 = 0;
    *(int *)&u.b[64] = 0;
    temp_s = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igTextureAttr_vtable[0];
    FUN_00132130((Ref **)&u.b[64], -1);
    FUN_001321b0((void **)p136, -1);
    igSmartPointer_igImage_Destruct((O *)p128, -1);
    igSmartPointer_igVisualContext_Destruct((void **)p92, -1);
    return temp_s;
}

void igTextureAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureAttr_Register);
}

static igMetaObjectCallback g_igTextureAttr_callbackList[] = { igImage_EnsureRegistered, igTextureUnloadAttr_EnsureRegistered, igImageMipMapList_EnsureRegistered, igVisualContext_EnsureRegistered, 0 };

void igTextureAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureAttr_GetMetaObject,
        "igTextureAttr",
        0x48, /* instance size */
        igTextureAttr_GetVTable,
        &igTextureAttr_InitFields,
        0, /* extra callback item */
        g_igTextureAttr_callbackList /* callback list */
    );
}

void thunk_igTextureAttr_GetMetaObject(void) {
    igTextureAttr_GetMetaObject();
}

static FieldFactory g_igTextureAttr_ctorTable[] = {
    igUnsignedIntMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igIntMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igRawRefMetaField_Create,
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
    igMetaObject *temp_s0;
    int temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_7;

    temp_s0 = g_igTextureAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igTextureAttr_ctorTable, 0xF);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    igEnumMetaField_SetDefaultValue(temp_v0, 0);
    *(void **)&((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (void *)IG_GFX_TEXTURE_FILTER_GetMetaEnum;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    igEnumMetaField_SetDefaultValue(temp_v0_2, 0);
    *(void **)&((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (void *)IG_GFX_TEXTURE_FILTER_GetMetaEnum;
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    igEnumMetaField_SetDefaultValue(temp_v0_3, g_igTextureAttr_wrapSDefault);
    *(void **)&((igEnumMetaField *)temp_v0_3)->_getMetaEnumFunction = (void *)FUN_00149920;
    temp_v0_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    igEnumMetaField_SetDefaultValue(temp_v0_4, g_igTextureAttr_wrapTDefault);
    *(void **)&((igEnumMetaField *)temp_v0_4)->_getMetaEnumFunction = (void *)FUN_00149920;
    temp_v0_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    igIntMetaField_SetDefault(temp_v0_5, -1);
    ((igIntMetaField *)temp_v0_5)->_persistent = 0;
    ((igIntMetaField *)temp_v0_5)->_deepCopyMethod = 4;
    ((igIntMetaField *)temp_v0_5)->_shallowCopyMethod = 4;
    ((igIntMetaField *)temp_v0_5)->_isAlikeShallowMethod = 3;
    temp_v0_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    igEnumMetaField_SetDefaultValue(temp_v0_6, 0);
    *(void **)&((igEnumMetaField *)temp_v0_6)->_getMetaEnumFunction = (void *)FUN_00149860;
    temp_v0_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    igEnumMetaField_SetDefaultValue(temp_v0_7, 0);
    *(void **)&((igEnumMetaField *)temp_v0_7)->_getMetaEnumFunction = (void *)FUN_001498c0;
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igImage_GetOrCreateMetaObject();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_00131160();
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB), 1);
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_00132ff0();
    ((igObjectRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igVisualContext_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_4)->_persistent = 0;
    ((igObjectRefMetaField *)temp_s2_4)->_deepCopyMethod = 1;
    ((igObjectRefMetaField *)temp_s2_4)->_shallowCopyMethod = 1;
    ((igObjectRefMetaField *)temp_s2_4)->_isAlikeShallowMethod = 3;
    ((igRawRefMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE))->_persistent = 0;
    igMetaObject_NameFields(temp_s0, g_igTextureAttr_fieldTable, g_igTextureAttr_fieldHandles, g_igTextureAttr_fieldOffsets, temp_s1);
}

