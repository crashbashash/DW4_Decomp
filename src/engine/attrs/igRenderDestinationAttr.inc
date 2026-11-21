igMetaEnum *g_igRenderDestinationAttr_textureCreateMetaEnum;
igMetaEnum *g_igRenderDestinationAttr_createModeMetaEnum;
igMetaObject *g_igRenderDestinationAttr_metaObject;
igMetaField *g_igRenderDestinationAttr_iCreateModeMetaField;
igMetaField *g_igRenderDestinationAttr_iTexCreateModeMetaField;
igMetaField *g_igRenderDestinationAttr_iRDHandleMetaField;
igMetaField *g_igRenderDestinationAttr_bEnabledMetaField;
igMetaField *g_igRenderDestinationAttr_iPrevRDHandleMetaField;
igMetaField *g_igRenderDestinationAttr_pTexMetaField;
igMetaField *g_igRenderDestinationAttr_iTypeMetaField;
igMetaField *g_igRenderDestinationAttr_iSizeXMetaField;
igMetaField *g_igRenderDestinationAttr_iSizeYMetaField;
igMetaField *g_igRenderDestinationAttr_iColorBitCountMetaField;
igMetaField *g_igRenderDestinationAttr_iAlphaBitCountMetaField;
igMetaField *g_igRenderDestinationAttr_iDepthBitCountMetaField;
igMetaField *g_igRenderDestinationAttr_iStencilBitCountMetaField;
igMetaField *g_igRenderDestinationAttr_vcMetaField;

static const char *g_igRenderDestinationAttr_textureCreateNames[] = {
    "RENDERDESTINATION_TEXTURE_CREATE_MODE_AUTO_CREATE",
    "RENDERDESTINATION_TEXTURE_CREATE_MODE_USE_SPECIFIED",
};
static int g_igRenderDestinationAttr_textureCreateValues[] = {
    0,
    1,
};

igMetaEnum *igRenderDestinationAttr_GetTextureCreateModeMetaEnum(void) {
    if (g_igRenderDestinationAttr_textureCreateMetaEnum == 0) {
        g_igRenderDestinationAttr_textureCreateMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("RENDERDESTINATION_TEXTURE_CREATE_MODE", g_igRenderDestinationAttr_textureCreateNames, g_igRenderDestinationAttr_textureCreateValues, 2);
    }
    return g_igRenderDestinationAttr_textureCreateMetaEnum;
}

static const char *g_igRenderDestinationAttr_createModeNames[] = {
    "RENDERDESTINATION_CREATE_MODE_INHERIT",
    "RENDERDESTINATION_CREATE_MODE_AUTONOMOUS",
    "RENDERDESTINATION_CREATE_MODE_USE_DEFAULT",
};
static int g_igRenderDestinationAttr_createModeValues[] = {
    0,
    1,
    2,
};

igMetaEnum *igRenderDestinationAttr_GetCreateModeMetaEnum(void) {
    if (g_igRenderDestinationAttr_createModeMetaEnum == 0) {
        g_igRenderDestinationAttr_createModeMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("RENDERDESTINATION_CREATE_MODE", g_igRenderDestinationAttr_createModeNames, g_igRenderDestinationAttr_createModeValues, 3);
    }
    return g_igRenderDestinationAttr_createModeMetaEnum;
}

igRenderDestinationAttr *igRenderDestinationAttr_Create(igMemoryPoolView *pool) {
    igRenderDestinationAttr_EnsureRegistered();
    return (igRenderDestinationAttr *)igMetaObject_CreateInstance(g_igRenderDestinationAttr_metaObject, pool);
}

igMetaObject *igRenderDestinationAttr_GetOrCreateMetaObject(void) {
    if (g_igRenderDestinationAttr_metaObject == 0) {
        g_igRenderDestinationAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRenderDestinationAttr_metaObject;
}

igMetaObject *igRenderDestinationAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderDestinationAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRenderDestinationAttr_EnsureRegistered();
    return g_igRenderDestinationAttr_metaObject;
}

int igRenderDestinationAttr_GetVTable(void) {
    union U_134290 u;
    int temp_s0;
    S_ref *p1;
    S_ref *p2;
    S_ref *t1;
    S_ref *t2;

    igObject_InitHeader((igObject *)u.b);
    p1 = (S_ref *)&u.b[64];
    p2 = (S_ref *)&u.b[32];
    u.vt = (int)&g_igRenderDestinationAttr_vtable[0];
    *(int *)p2 = 0;
    *(int *)p1 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igRenderDestinationAttr_vtable[0];
    if (p1 != 0) {
        t1 = *(S_ref **)p1;
        if (t1 != 0) {
            t1->f4 = (int)((int) (t1->f4 - 1));
            if (((unsigned long long) ((long long) t1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t1);
            }
        }
    }
    if (p2 != 0) {
        t2 = *(S_ref **)p2;
        if (t2 != 0) {
            t2->f4 = (int)((int) (t2->f4 - 1));
            if (((unsigned long long) ((long long) t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t2);
            }
        }
    }
    return temp_s0;
}

void igRenderDestinationAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRenderDestinationAttr_Register);
}

static igMetaObjectCallback g_igRenderDestinationAttr_callbackList[] = { igTextureAttr_EnsureRegistered, igVisualContext_EnsureRegistered, 0 };

CallbackArray *igRenderDestinationAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRenderDestinationAttr_metaObject,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        igRenderDestinationAttr_GetMetaObjectFunction,
        "igRenderDestinationAttr",
        0x44, /* instance size */
        igRenderDestinationAttr_GetVTable,
        &igRenderDestinationAttr_InitFields,
        0, /* extra callback item */
        g_igRenderDestinationAttr_callbackList /* callback list */
    );
}

void igRenderDestinationAttr_GetMetaObjectFunction(void) {
    igRenderDestinationAttr_GetMetaObject();
}

static FieldFactory g_igRenderDestinationAttr_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igRenderDestinationAttr_fieldTable[] = {
    "_iCreateMode",
    "_iTexCreateMode",
    "_iRDHandle",
    "_bEnabled",
    "_iPrevRDHandle",
    "_pTex",
    "_iType",
    "_iSizeX",
    "_iSizeY",
    "_iColorBitCount",
    "_iAlphaBitCount",
    "_iDepthBitCount",
    "_iStencilBitCount",
    "_vc",
};
static igMetaField **g_igRenderDestinationAttr_fieldHandles[] = {
    &g_igRenderDestinationAttr_iCreateModeMetaField,
    &g_igRenderDestinationAttr_iTexCreateModeMetaField,
    &g_igRenderDestinationAttr_iRDHandleMetaField,
    &g_igRenderDestinationAttr_bEnabledMetaField,
    &g_igRenderDestinationAttr_iPrevRDHandleMetaField,
    &g_igRenderDestinationAttr_pTexMetaField,
    &g_igRenderDestinationAttr_iTypeMetaField,
    &g_igRenderDestinationAttr_iSizeXMetaField,
    &g_igRenderDestinationAttr_iSizeYMetaField,
    &g_igRenderDestinationAttr_iColorBitCountMetaField,
    &g_igRenderDestinationAttr_iAlphaBitCountMetaField,
    &g_igRenderDestinationAttr_iDepthBitCountMetaField,
    &g_igRenderDestinationAttr_iStencilBitCountMetaField,
    &g_igRenderDestinationAttr_vcMetaField,
};
static int g_igRenderDestinationAttr_fieldOffsets[] = {
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
};

int g_igRenderDestinationAttr_iTypeDefault = 1;

void igRenderDestinationAttr_InitFields(void) {
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
    void *field12;
    void *field13;
    igMetaObject *meta;

    meta = g_igRenderDestinationAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igRenderDestinationAttr_ctorTable, 0xE);
    field3 = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((Gap::Core::igEnumMetaField *)field3)->setDefault(0);
    ((igMetaField *)field3)->_persistent = 0;
    ((igEnumMetaField *)field3)->_getMetaEnumFunction = (int)(&igRenderDestinationAttr_GetCreateModeMetaEnum);
    field6 = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((Gap::Core::igEnumMetaField *)field6)->setDefault(0);
    ((igMetaField *)field6)->_persistent = 0;
    ((igEnumMetaField *)field6)->_getMetaEnumFunction = (int)(&igRenderDestinationAttr_GetTextureCreateModeMetaEnum);
    field7 = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((Gap::Core::igIntMetaField *)field7)->setDefault(-1);
    ((igMetaField *)field7)->_persistent = 0;
    ((igMetaField *)field7)->_deepCopyMethod = 4;
    ((igMetaField *)field7)->_shallowCopyMethod = 4;
    ((igMetaField *)field7)->_isAlikeShallowMethod = 3;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 3))->_persistent = 0;
    field8 = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((Gap::Core::igIntMetaField *)field8)->setDefault(-1);
    ((igMetaField *)field8)->_persistent = 0;
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igTextureAttr_GetOrCreateMetaObject();
    ((igMetaField *)field)->_persistent = 0;
    field9 = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((Gap::Core::igEnumMetaField *)field9)->setDefault(g_igRenderDestinationAttr_iTypeDefault);
    ((igEnumMetaField *)field9)->_getMetaEnumFunction = (int)(&IG_GFX_RENDERDESTINATION_TYPE_GetMetaEnum);
    field10 = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((Gap::Core::igIntMetaField *)field10)->setDefault(-1);
    ((igMetaField *)field10)->_persistent = 0;
    field11 = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((Gap::Core::igIntMetaField *)field11)->setDefault(-1);
    ((igMetaField *)field11)->_persistent = 0;
    field12 = (void *)(igMetaObject_GetFieldAt(meta, base + 9));
    ((Gap::Core::igIntMetaField *)field12)->setDefault(-1);
    ((igMetaField *)field12)->_persistent = 0;
    field13 = (void *)(igMetaObject_GetFieldAt(meta, base + 0xA));
    ((Gap::Core::igIntMetaField *)field13)->setDefault(-1);
    ((igMetaField *)field13)->_persistent = 0;
    field4 = (void *)(igMetaObject_GetFieldAt(meta, base + 0xB));
    ((Gap::Core::igIntMetaField *)field4)->setDefault(-1);
    ((igMetaField *)field4)->_persistent = 0;
    field5 = (void *)(igMetaObject_GetFieldAt(meta, base + 0xC));
    ((Gap::Core::igIntMetaField *)field5)->setDefault(-1);
    ((igMetaField *)field5)->_persistent = 0;
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base + 0xD));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
    ((igMetaField *)field2)->_persistent = 0;
    ((igMetaField *)field2)->_deepCopyMethod = 1;
    ((igMetaField *)field2)->_shallowCopyMethod = 1;
    ((igMetaField *)field2)->_isAlikeShallowMethod = 3;
    igMetaObject_NameFields(meta, g_igRenderDestinationAttr_fieldTable, g_igRenderDestinationAttr_fieldHandles, g_igRenderDestinationAttr_fieldOffsets, base);
}

