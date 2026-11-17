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

igMetaEnum *FUN_001340f0(void) {
    if (g_igRenderDestinationAttr_textureCreateMetaEnum == 0) {
        g_igRenderDestinationAttr_textureCreateMetaEnum = igMetaEnum_Create("RENDERDESTINATION_TEXTURE_CREATE_MODE", g_igRenderDestinationAttr_textureCreateNames, g_igRenderDestinationAttr_textureCreateValues, 2);
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

igMetaEnum *FUN_00134150(void) {
    if (g_igRenderDestinationAttr_createModeMetaEnum == 0) {
        g_igRenderDestinationAttr_createModeMetaEnum = igMetaEnum_Create("RENDERDESTINATION_CREATE_MODE", g_igRenderDestinationAttr_createModeNames, g_igRenderDestinationAttr_createModeValues, 3);
    }
    return g_igRenderDestinationAttr_createModeMetaEnum;
}

int FUN_001341b0(int arg0) {
    igRenderDestinationAttr_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(*(igMetaObject * *)0x55EED8, (igMemoryPoolView *)arg0);
}

igMetaObject *FUN_001341f0(void) {
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
    temp_s0 = *(int *)&u.b[*(int *)((char *)g_objectSystem + 916)];
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
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igRenderDestinationAttr_GetMetaObject,
        "igRenderDestinationAttr",
        0x44, /* instance size */
        igRenderDestinationAttr_GetVTable,
        &igRenderDestinationAttr_InitFields,
        0, /* extra callback item */
        g_igRenderDestinationAttr_callbackList /* callback list */
    );
}

void thunk_igRenderDestinationAttr_GetMetaObject(void) {
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
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_v0;
    void *temp_v0_10;
    void *temp_v0_11;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v0_8;
    void *temp_v0_9;
    igMetaObject *temp_s1;

    temp_s1 = g_igRenderDestinationAttr_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_igRenderDestinationAttr_ctorTable, 0xE);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0, 0);
    ((igMetaField *)temp_v0)->_persistent = 0;
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00134150);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0_2, 0);
    ((igMetaField *)temp_v0_2)->_persistent = 0;
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&FUN_001340f0);
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    igIntMetaField_SetDefault((igMetaField *)temp_v0_3, -1);
    ((igMetaField *)temp_v0_3)->_persistent = 0;
    ((igMetaField *)temp_v0_3)->_deepCopyMethod = 4;
    ((igMetaField *)temp_v0_3)->_shallowCopyMethod = 4;
    ((igMetaField *)temp_v0_3)->_isAlikeShallowMethod = 3;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3))->_persistent = 0;
    temp_v0_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    igIntMetaField_SetDefault((igMetaField *)temp_v0_4, -1);
    ((igMetaField *)temp_v0_4)->_persistent = 0;
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igTextureAttr_GetOrCreateMetaObject();
    ((igMetaField *)temp_s2)->_persistent = 0;
    temp_v0_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0_5, g_igRenderDestinationAttr_iTypeDefault);
    ((igEnumMetaField *)temp_v0_5)->_getMetaEnumFunction = (int)(&FUN_00149b00);
    temp_v0_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    igIntMetaField_SetDefault((igMetaField *)temp_v0_6, -1);
    ((igMetaField *)temp_v0_6)->_persistent = 0;
    temp_v0_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    igIntMetaField_SetDefault((igMetaField *)temp_v0_7, -1);
    ((igMetaField *)temp_v0_7)->_persistent = 0;
    temp_v0_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    igIntMetaField_SetDefault((igMetaField *)temp_v0_8, -1);
    ((igMetaField *)temp_v0_8)->_persistent = 0;
    temp_v0_9 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA));
    igIntMetaField_SetDefault((igMetaField *)temp_v0_9, -1);
    ((igMetaField *)temp_v0_9)->_persistent = 0;
    temp_v0_10 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB));
    igIntMetaField_SetDefault((igMetaField *)temp_v0_10, -1);
    ((igMetaField *)temp_v0_10)->_persistent = 0;
    temp_v0_11 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xC));
    igIntMetaField_SetDefault((igMetaField *)temp_v0_11, -1);
    ((igMetaField *)temp_v0_11)->_persistent = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xD));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
    ((igMetaField *)temp_s2_2)->_persistent = 0;
    ((igMetaField *)temp_s2_2)->_deepCopyMethod = 1;
    ((igMetaField *)temp_s2_2)->_shallowCopyMethod = 1;
    ((igMetaField *)temp_s2_2)->_isAlikeShallowMethod = 3;
    igMetaObject_NameFields(temp_s1, g_igRenderDestinationAttr_fieldTable, g_igRenderDestinationAttr_fieldHandles, g_igRenderDestinationAttr_fieldOffsets, temp_s0);
}

