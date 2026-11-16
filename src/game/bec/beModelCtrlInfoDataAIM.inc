igMetaObject *g_beModelCtrlInfoDataAIM_metaObject;
int g_beModelCtrlInfoDataAIM_nameStorage;
igMetaField *g_beModelCtrlInfoDataAIM_aIMapListMetaField;

void *beModelCtrlInfoDataAIM_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlInfoDataAIM_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlInfoDataAIM_EnsureRegistered();
    }
    return g_beModelCtrlInfoDataAIM_metaObject;
}

int beModelCtrlInfoDataAIM_GetVTable(void) {
    union U_353ee0 u;
    int t;
    char *o;
    int *a1;
    int v0;
    igObject *p0, *p1;

    igObject_InitHeader(u.b);
    p0 = (igObject *)&u.b[8];
    *(int *)p0 = 0;
    u.vt = (int)&g_beModelCtrlInfoDataAIM_vtable[0];
    p1 = (igObject *)&u.b[16];
    *(int *)p1 = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beModelCtrlInfoDataAIM_vtable[0];
    if (p1 != 0) {
        p1 = *(igObject **)p1;
        if (p1 != 0) {
            p1->_refCount = (int)p1->_refCount - 1;
            if (((unsigned long long) ((long long)(int)p1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p1);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (p0 != 0) {
        o = *(char **)p0;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void beModelCtrlInfoDataAIM_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataAIM_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoDataAIM_callbackList[] = { beModelCtrlAIMapList_EnsureRegistered, 0 };

void *beModelCtrlInfoDataAIM_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoDataAIM_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataAIM_GetMetaObjectFunction,
        "beModelCtrlInfoDataAIM",
        0x14, /* instance size */
        beModelCtrlInfoDataAIM_GetVTable,
        beModelCtrlInfoDataAIM_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoDataAIM_callbackList /* callback list */
    );
}

void beModelCtrlInfoDataAIM_GetMetaObjectFunction(void)
{
    beModelCtrlInfoDataAIM_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoDataAIM_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beModelCtrlInfoDataAIM_fieldTable[] = {
    "_aIMapList",
};
static igMetaField **g_beModelCtrlInfoDataAIM_fieldHandles[] = {
    &g_beModelCtrlInfoDataAIM_aIMapListMetaField,
};
static int g_beModelCtrlInfoDataAIM_fieldOffsets[] = {
    16,
};

void beModelCtrlInfoDataAIM_InitFields(void) {
    int base;
    int index;
    void **found;
    void *aIMapList;
    void *meta;
    igStringMetaField *clone;

    meta = (void *)g_beModelCtrlInfoDataAIM_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlInfoDataAIM_ctorTable, 1);
    found = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    index = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, found);
    clone = (igStringMetaField *)(((DW4VC_84_1 *)(found))->vX((int)(1)));
    igStringMetaField_SetDefaultText(clone, "AIM");
    clone->_externalEnumStorage = (int)(&g_beModelCtrlInfoDataAIM_nameStorage);
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    aIMapList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)aIMapList)->_metaObject = (int)beModelCtrlAIMapList_GetOrCreateMetaObject();
    ((igRefMetaField *)aIMapList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beModelCtrlInfoDataAIM_fieldTable, g_beModelCtrlInfoDataAIM_fieldHandles, g_beModelCtrlInfoDataAIM_fieldOffsets, base);
}

