int FUN_001535d0(void) {
    if (DAT_00560570[0] == 0) {
        DAT_00560570[0] = igMetaEnum_Create(&BLENDING_FUNCTION_ALPHA_PSX2_2[0], &DAT_00489f28[0], &DAT_00489f38[0], 3);
    }
    return DAT_00560570[0];
}

int FUN_00153630(void) {
    if (DAT_00560578[0] == 0) {
        DAT_00560578[0] = igMetaEnum_Create(&BLENDING_FUNCTION_COLOR_PSX2_2[0], &DAT_00489f48[0], &DAT_00489f58[0], 3);
    }
    return DAT_00560578[0];
}

int FUN_00153690(void) {
    if (DAT_00560580[0] == 0) {
        DAT_00560580[0] = igMetaEnum_Create(&TEXTURE_FUNCTION_PSX2[0], &DAT_00489f70[0], &DAT_00489fa0[0], 0xC);
    }
    return DAT_00560580[0];
}

igMetaObject *igPsx2MultiTextureExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2MultiTextureExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00153820();
    return g_igPsx2MultiTextureExt_metaObject[0];
}

int igPsx2MultiTextureExt_GetVTable(void) {
    Obj_153740 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.r1 = 0;
    obj.vt = &DAT_00530a10[0];
    obj.r2 = 0;
    obj.vt = &DAT_00525510[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00530a10[0];
    obj.rel(&obj.r2);
    obj.rel(&obj.r1);
    return r;
}

void FUN_00153820(void)
{
    igMetaObject_RunStaticInit(igPsx2MultiTextureExt_Register);
}

void igPsx2MultiTextureExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2MultiTextureExt_metaObject,
        igMultiTextureExt_Register,
        igMultiTextureExt_GetPublishedMetaObject,
        thunk_igPsx2MultiTextureExt_GetMetaObject,
        igPsx2MultiTextureExt_className,
        0x34, /* instance size */
        igPsx2MultiTextureExt_GetVTable,
        &igPsx2MultiTextureExt_InitFields,
        0, /* extra callback item */
        g_igPsx2MultiTextureExt_callbackList /* callback list */
    );
}

int FUN_001538b0(void) {
    return (int)g_igMultiTextureExt_metaObject[0];
}

void igPsx2MultiTextureExt_InitFields(void) {
    void *f;
    void *m;
    int base;

    m = (void *)g_igPsx2MultiTextureExt_metaObject[0];
    base = igMetaObject_GetFieldCount(m);
    igMetaObject_CreateFields(m, &g_igPsx2MultiTextureExt_ctorTable[0], 8);
    f = igMetaObject_GetFieldAt(m, base);
    ((igObjectRefMetaField *)f)->_metaObject = (int)FUN_00150770();
    ((igObjectRefMetaField *)f)->_refCounted = 0;
    f = igMetaObject_GetFieldAt(m, base + 1);
    igEnumMetaField_SetDefaultValue(f, &DAT_0048a060[0]);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)(&FUN_00153690);
    f = igMetaObject_GetFieldAt(m, base + 3);
    igEnumMetaField_SetDefaultValue(f, &DAT_0048a068[0]);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)(&FUN_00153630);
    f = igMetaObject_GetFieldAt(m, base + 4);
    igEnumMetaField_SetDefaultValue(f, &DAT_0048a070[0]);
    *(void **)&((igEnumMetaField *)f)->_getMetaEnumFunction = (void *)FUN_00153630;
    f = igMetaObject_GetFieldAt(m, base + 5);
    igEnumMetaField_SetDefaultValue(f, &DAT_0048a078[0]);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)(&FUN_001535d0);
    f = igMetaObject_GetFieldAt(m, base + 6);
    igEnumMetaField_SetDefaultValue(f, &DAT_0048a080[0]);
    *(void **)&((igEnumMetaField *)f)->_getMetaEnumFunction = (void *)FUN_00153630;
    igUnsignedCharMetaField_SetDefaultValue(igMetaObject_GetFieldAt(m, base + 7), 0x80);
    igMetaObject_NameFields(m, &g_igPsx2MultiTextureExt_fieldTable[0], &DAT_0048a020[0], &DAT_0048a040[0], base);
}

