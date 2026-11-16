igMetaObject *g_beBkColorInfo_metaObject;
igMetaField *g_beBkColorInfo_rgbaMetaField;

void *beBkColorInfo_GetMetaObject(void) {
    igMetaObject *g = g_beBkColorInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beBkColorInfo_EnsureRegistered();
    }
    return g_beBkColorInfo_metaObject;
}

int beBkColorInfo_GetVTable(void) {
    struct Obj_369c30 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.vt = &g_beBkColorInfo_vtable[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beBkColorInfo_vtable[0];
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return t;
}

void beBkColorInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBkColorInfo_Register);
}

void *beBkColorInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beBkColorInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beBkColorInfo_GetMetaObjectFunction,
        "beBkColorInfo",
        0x2c, /* instance size */
        beBkColorInfo_GetVTable,
        beBkColorInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beBkColorInfo_GetMetaObjectFunction(void)
{
    beBkColorInfo_GetMetaObject();
}

static FieldFactory g_beBkColorInfo_ctorTable[] = {
    FUN_001872a0,
};
static const char *g_beBkColorInfo_fieldTable[] = {
    "_rgba",
};
static igMetaField **g_beBkColorInfo_fieldHandles[] = {
    &g_beBkColorInfo_rgbaMetaField,
};
static int g_beBkColorInfo_fieldOffsets[] = {
    28,
};

void beBkColorInfo_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beBkColorInfo_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beBkColorInfo_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beBkColorInfo_fieldTable, g_beBkColorInfo_fieldHandles, g_beBkColorInfo_fieldOffsets, temp_s1);
}

