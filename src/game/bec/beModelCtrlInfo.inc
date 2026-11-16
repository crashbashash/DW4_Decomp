igMetaObject *g_beModelCtrlInfo_metaObject;
igMetaField *g_beModelCtrlInfo_kindStringMetaField;

igMetaObject *beModelCtrlInfo_GetMetaObject(void) {
    if (g_beModelCtrlInfo_metaObject == 0 || !isValid(g_beModelCtrlInfo_metaObject)) beModelCtrlInfo_EnsureRegistered();
    return g_beModelCtrlInfo_metaObject;
}

int beModelCtrlInfo_GetVTable(void) {
    union U_352d20 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[5] = 0;
    u.w[6] = 0;
    u.w[0] = (int)(&g_beModelCtrlInfo_vtable[0]);
    u.w[7] = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beModelCtrlInfo_vtable[0]);
    igStringRef_Destruct(&u.w[7], -1);
    FUN_0033ec80((struct S_33ec80 *)(&u.w[0]), (short)0);
    return temp_s0;
}

void beModelCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfo_Register);
}

void *beModelCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beModelCtrlInfo_GetMetaObjectFunction,
        "beModelCtrlInfo",
        0x20, /* instance size */
        beModelCtrlInfo_GetVTable,
        beModelCtrlInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlInfo_GetMetaObjectFunction(void)
{
    beModelCtrlInfo_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfo_ctorTable[] = {
    igStringMetaField_Create,
};
static const char *g_beModelCtrlInfo_fieldTable[] = {
    "_kindString",
};
static igMetaField **g_beModelCtrlInfo_fieldHandles[] = {
    &g_beModelCtrlInfo_kindStringMetaField,
};
static int g_beModelCtrlInfo_fieldOffsets[] = {
    28,
};

void beModelCtrlInfo_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beModelCtrlInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlInfo_ctorTable, 1);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(meta, base)), 0);
    igMetaObject_NameFields(meta, g_beModelCtrlInfo_fieldTable, g_beModelCtrlInfo_fieldHandles, g_beModelCtrlInfo_fieldOffsets, base);
}

