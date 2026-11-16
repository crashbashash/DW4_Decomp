igMetaObject *g_beNDMWMdlItemInfoWork_metaObject;
igMetaField *g_beNDMWMdlItemInfoWork_dbIdMetaField;
igMetaField *g_beNDMWMdlItemInfoWork_itemObjectMetaField;
igMetaField *g_beNDMWMdlItemInfoWork_kindMetaField;
igMetaField *g_beNDMWMdlItemInfoWork_isNamedMetaField;
igMetaField *g_beNDMWMdlItemInfoWork_dispPlayerRamNoMetaField;
igMetaField *g_beNDMWMdlItemInfoWork_isDispNameMetaField;
igMetaField *g_beNDMWMdlItemInfoWork_fontTypeMetaField;
igMetaField *g_beNDMWMdlItemInfoWork_isColorLightMetaField;

void beNDMWMdlItemInfoWork_Create(int arg0) {
    beNDMWMdlItemInfoWork_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWMdlItemInfoWork_metaObject, arg0);
}

igMetaObject *beNDMWMdlItemInfoWork_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlItemInfoWork_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWMdlItemInfoWork_EnsureRegistered();
done:
    return g_beNDMWMdlItemInfoWork_metaObject;
}

int beNDMWMdlItemInfoWork_GetVTable(void) {
    ItemInfoWork work;
    return *(int *)((char *)&work + *(int *)((char *)g_objectSystem[0] + 916));
}

void **FUN_003c1520(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

int *FUN_003c15a0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void beNDMWMdlItemInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlItemInfoWork_Register);
}

static igMetaObjectCallback g_beNDMWMdlItemInfoWork_callbackList[] = { beNDMWItemBase_EnsureRegistered, 0 };

void *beNDMWMdlItemInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlItemInfoWork_metaObject,
        beModelCtrlInfoWork_Register,
        beModelCtrlInfoWork_GetPublishedMetaObject,
        beNDMWMdlItemInfoWork_GetMetaObject,
        "beNDMWMdlItemInfoWork",
        0x10c, /* instance size */
        beNDMWMdlItemInfoWork_GetVTable,
        beNDMWMdlItemInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlItemInfoWork_callbackList /* callback list */
    );
}

void beNDMWMdlItemInfoWork_GetMetaObject(void)
{
    beNDMWMdlItemInfoWork_GetReadyMetaObject();
}

static FieldFactory g_beNDMWMdlItemInfoWork_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igStringMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beNDMWMdlItemInfoWork_fieldTable[] = {
    "_dbId",
    "_itemObject",
    "_kind",
    "_isNamed",
    "_dispPlayerRamNo",
    "_isDispName",
    "_fontType",
    "_isColorLight",
};
static igMetaField **g_beNDMWMdlItemInfoWork_fieldHandles[] = {
    &g_beNDMWMdlItemInfoWork_dbIdMetaField,
    &g_beNDMWMdlItemInfoWork_itemObjectMetaField,
    &g_beNDMWMdlItemInfoWork_kindMetaField,
    &g_beNDMWMdlItemInfoWork_isNamedMetaField,
    &g_beNDMWMdlItemInfoWork_dispPlayerRamNoMetaField,
    &g_beNDMWMdlItemInfoWork_isDispNameMetaField,
    &g_beNDMWMdlItemInfoWork_fontTypeMetaField,
    &g_beNDMWMdlItemInfoWork_isColorLightMetaField,
};
static int g_beNDMWMdlItemInfoWork_fieldOffsets[] = {
    236,
    240,
    244,
    248,
    252,
    256,
    260,
    264,
};

void beNDMWMdlItemInfoWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWMdlItemInfoWork_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWMdlItemInfoWork_ctorTable, 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beNDMWItemBase_GetOrCreateMetaObject();
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), -1);
    igMetaObject_NameFields(temp_s0, g_beNDMWMdlItemInfoWork_fieldTable, g_beNDMWMdlItemInfoWork_fieldHandles, g_beNDMWMdlItemInfoWork_fieldOffsets, temp_s2);
}

