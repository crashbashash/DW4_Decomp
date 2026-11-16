igMetaObject *g_igPointSpriteExt_metaObject;
igMetaField *g_igPointSpriteExt_contextMetaField;
igMetaField *g_igPointSpriteExt_vertexArrayMetaField;
igMetaField *g_igPointSpriteExt_spriteSizeMetaField;
igMetaField *g_igPointSpriteExt_inSpriteModeMetaField;
igMetaField *g_igPointSpriteExt_spriteSizeSpaceMetaField;
igMetaField *g_igPointSpriteExt_previousModelviewMetaField;
igMetaField *g_igPointSpriteExt_previousProjectionMetaField;
igMetaField *g_igPointSpriteExt_orthoMatrixMetaField;
igMetaField *g_igPointSpriteExt_modelviewMatrixMetaField;
igMetaField *g_igPointSpriteExt_modelviewMatrixFrustumMetaField;
igMetaField *g_igPointSpriteExt_currentWindowWidthMetaField;
igMetaField *g_igPointSpriteExt_currentWindowHeightMetaField;
igMetaField *g_igPointSpriteExt_frustumLeftMetaField;
igMetaField *g_igPointSpriteExt_frustumRightMetaField;
igMetaField *g_igPointSpriteExt_frustumBottomMetaField;
igMetaField *g_igPointSpriteExt_frustumTopMetaField;
igMetaField *g_igPointSpriteExt_frustumNearMetaField;
igMetaField *g_igPointSpriteExt_frustumFarMetaField;

static const char *g_igPointSpriteExt_spriteSizeSpaceNames[] = {
    "IG_GFX_SPRITE_SIZE_WORLD_COORDINATE", "IG_GFX_SPRITE_SIZE_SCREEN_COORDINATE",
};
static int g_igPointSpriteExt_spriteSizeSpaceValues[] = {
    0, 1,
};
igMetaEnum *g_igPointSpriteExt_spriteSizeSpaceMetaEnum;

int FUN_0014c290(void) {
    if (g_igPointSpriteExt_spriteSizeSpaceMetaEnum == 0) {
        g_igPointSpriteExt_spriteSizeSpaceMetaEnum = igMetaEnum_Create("IG_GFX_SPRITE_SIZE_SPACE", g_igPointSpriteExt_spriteSizeSpaceNames, g_igPointSpriteExt_spriteSizeSpaceValues, 2);
    }
    return (int)g_igPointSpriteExt_spriteSizeSpaceMetaEnum;
}

igMetaObject *FUN_0014c2f0(void) {
    if (g_igPointSpriteExt_metaObject == 0) {
        g_igPointSpriteExt_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igPointSpriteExt_metaObject;
}

igMetaObject *igPointSpriteExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPointSpriteExt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014c670();
    return g_igPointSpriteExt_metaObject;
}

int igPointSpriteExt_GetVTable(void) {
    struct PointSpriteExtInstance o;
    int r;
    char *pa = (char *)&o;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.vt = &g_igPointSpriteExt_vtable[0];
    o.f16 = 0;
    o.f24 = 0;
    igMatrix44f_SetIdentity((float *)&o.t[8]);
    igMatrix44f_SetIdentity((float *)(pa + 104));
    igMatrix44f_SetIdentity((float *)(pa + 168));
    igMatrix44f_SetIdentity((float *)(pa + 232));
    igMatrix44f_SetIdentity((float *)(pa + 296));
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_igPointSpriteExt_vtable[0];
    FUN_001338d0(&o.f24, -1);
    FUN_0014c580((O_14c580 *)&o, 0);
    return r;
}

O *FUN_0014c440(O *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &g_igPointSpriteExt_vtable[0];
        if (&arg0->m24) {
            S1 *t0 = arg0->m24;
            if (t0) { t0->f4 -= 1; if ((t0->f4 & 0x7fffff) == 0) igObject_Destroy(t0); }
        }
        if (arg0) {
            arg0->vt = &DAT_00527020[0];
            if (arg0) {
                arg0->vt = &DAT_00530a10[0];
                if (&arg0->m16) {
                    S1 *t = arg0->m16;
                    if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
                }
                if (&arg0->m8) {
                    S1 *t2 = arg0->m8;
                    if (t2) { t2->f4 -= 1; if ((t2->f4 & 0x7fffff) == 0) igObject_Destroy(t2); }
                }
            }
        }
        if (arg1 > 0) Memory_FreeBufferAliasC(arg0);
    }
    return arg0;
}

O_14c580 *FUN_0014c580(O_14c580 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_00527020[0];
        if (arg0) {
            arg0->vt = &DAT_00530a10[0];
            if (&arg0->m16) {
                S1 *t = arg0->m16;
                if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
            }
            if (&arg0->m8) {
                S1 *t2 = arg0->m8;
                if (t2) { t2->f4 -= 1; if ((t2->f4 & 0x7fffff) == 0) igObject_Destroy(t2); }
            }
        }
        if (arg1 > 0) Memory_FreeBufferAliasC(arg0);
    }
    return arg0;
}

void FUN_0014c670(void)
{
    igMetaObject_RunStaticInit(igPointSpriteExt_Register);
}

static igMetaObjectCallback g_igPointSpriteExt_callbackList[] = { igVisualContext_EnsureRegistered, igVertexArray_EnsureRegistered, 0 };

void igPointSpriteExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPointSpriteExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_igPointSpriteExt_GetMetaObject,
        "igPointSpriteExt",
        0x188, /* instance size */
        igPointSpriteExt_GetVTable,
        &igPointSpriteExt_InitFields,
        0, /* extra callback item */
        g_igPointSpriteExt_callbackList /* callback list */
    );
}

void thunk_igPointSpriteExt_GetMetaObject(void) {
    igPointSpriteExt_GetMetaObject();
}

static FieldFactory g_igPointSpriteExt_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igEnumMetaField_Create,
    FUN_00188660,
    FUN_00188660,
    FUN_00188660,
    FUN_00188660,
    FUN_00188660,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_igPointSpriteExt_fieldTable[] = {
    "_context",
    "_vertexArray",
    "_spriteSize",
    "_inSpriteMode",
    "_spriteSizeSpace",
    "_previousModelview",
    "_previousProjection",
    "_orthoMatrix",
    "_modelviewMatrix",
    "_modelviewMatrixFrustum",
    "_currentWindowWidth",
    "_currentWindowHeight",
    "_frustumLeft",
    "_frustumRight",
    "_frustumBottom",
    "_frustumTop",
    "_frustumNear",
    "_frustumFar",
};
static igMetaField **g_igPointSpriteExt_fieldHandles[] = {
    &g_igPointSpriteExt_contextMetaField,
    &g_igPointSpriteExt_vertexArrayMetaField,
    &g_igPointSpriteExt_spriteSizeMetaField,
    &g_igPointSpriteExt_inSpriteModeMetaField,
    &g_igPointSpriteExt_spriteSizeSpaceMetaField,
    &g_igPointSpriteExt_previousModelviewMetaField,
    &g_igPointSpriteExt_previousProjectionMetaField,
    &g_igPointSpriteExt_orthoMatrixMetaField,
    &g_igPointSpriteExt_modelviewMatrixMetaField,
    &g_igPointSpriteExt_modelviewMatrixFrustumMetaField,
    &g_igPointSpriteExt_currentWindowWidthMetaField,
    &g_igPointSpriteExt_currentWindowHeightMetaField,
    &g_igPointSpriteExt_frustumLeftMetaField,
    &g_igPointSpriteExt_frustumRightMetaField,
    &g_igPointSpriteExt_frustumBottomMetaField,
    &g_igPointSpriteExt_frustumTopMetaField,
    &g_igPointSpriteExt_frustumNearMetaField,
    &g_igPointSpriteExt_frustumFarMetaField,
};
static int g_igPointSpriteExt_fieldOffsets[] = {
    20,
    24,
    28,
    32,
    36,
    40,
    104,
    168,
    232,
    296,
    360,
    364,
    368,
    372,
    376,
    380,
    384,
    388,
};

void igPointSpriteExt_InitFields(void) {
    int fieldStart;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_v0;
    void *temp_v0_2;
    igMetaObject *meta;

    meta = g_igPointSpriteExt_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igPointSpriteExt_ctorTable, 0x12);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    ((igMetaField *)temp_s2)->_persistent = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igVertexArray_GetOrCreateMetaObject();
    ((igMetaField *)temp_s2_2)->_persistent = 0;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 2));
    igFloatMetaField_SetDefault(temp_v0, 1.0f);
    ((igMetaField *)temp_v0)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 3))->_persistent = 0;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 4));
    igEnumMetaField_SetDefaultValue(temp_v0_2, 0);
    ((igMetaField *)temp_v0_2)->_persistent = 0;
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&FUN_0014c290);
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 5))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 6))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 7))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 8))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 9))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0xA))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0xB))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0xC))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0xD))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0xE))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0xF))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x10))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x11))->_persistent = 0;
    igMetaObject_NameFields(meta, g_igPointSpriteExt_fieldTable, g_igPointSpriteExt_fieldHandles, g_igPointSpriteExt_fieldOffsets, fieldStart);
    *(int *)((char *)(g_igPointSpriteExt_metaObject) + 60) = (int)(&thunk_igPsx2PointSpriteExt_GetMetaObject);
}

