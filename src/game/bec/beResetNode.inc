igMetaObject *g_beResetNode_metaObject;
igMetaField *g_beResetNode_isResetTimeMetaField;
igMetaField *g_beResetNode_isResetRotAndScaleMetaField;

void *beResetNode_GetMetaObject(void) {
    igMetaObject *g = g_beResetNode_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beResetNode_EnsureRegistered();
    }
    return g_beResetNode_metaObject;
}

int beResetNode_GetVTable(void) {
    struct W_34b4f0 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[2] = 0;
    o.w[3] = 0;
    o.w[6] = 0;
    o.vt = g_beResetNode_vtable;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beResetNode_vtable;
    FUN_00195a90(&o, 0);
    return r;
}

void beResetNode_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beResetNode_Register);
}

void *beResetNode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beResetNode_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beResetNode_GetMetaObjectFunction,
        "beResetNode",
        0x24, /* instance size */
        beResetNode_GetVTable,
        beResetNode_InitFields,
        FUN_0034b690, /* extra callback item */
        0 /* callback list */
    );
}

void beResetNode_GetMetaObjectFunction(void)
{
    beResetNode_GetMetaObject();
}

static FieldFactory g_beResetNode_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beResetNode_fieldTable[] = {
    "_isResetTime",
    "_isResetRotAndScale",
};
static igMetaField **g_beResetNode_fieldHandles[] = {
    &g_beResetNode_isResetTimeMetaField,
    &g_beResetNode_isResetRotAndScaleMetaField,
};
static int g_beResetNode_fieldOffsets[] = {
    32,
    33,
};

void beResetNode_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beResetNode_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beResetNode_ctorTable, 2);
    igMetaObject_NameFields(temp_s0, g_beResetNode_fieldTable, g_beResetNode_fieldHandles, g_beResetNode_fieldOffsets, temp_s1);
}

void FUN_0034b690(void)
{
    FUN_0039c8c0();
}

