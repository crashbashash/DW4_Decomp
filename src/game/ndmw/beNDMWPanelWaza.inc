igMetaObject *g_beNDMWPanelWaza_metaObject;
igMetaField *g_beNDMWPanelWaza_padManagerMetaField;

void beNDMWPanelWaza_CreateInstance(int arg0) {
    FUN_003bf050();
    igMetaObject_CreateInstance(g_beNDMWPanelWaza_metaObject, arg0);
}

igMetaObject *FUN_003beed0(void) {
    if (g_beNDMWPanelWaza_metaObject == 0) {
        g_beNDMWPanelWaza_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWPanelWaza_metaObject;
}

void *beNDMWPanelWaza_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWPanelWaza_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003bf050();
    }
    return g_beNDMWPanelWaza_metaObject;
}

int beNDMWPanelWaza_GetVTable(void) {
    union U_3bef70 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p38;
    char *p48;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053a0d0[0];
    p38 = &u.b[8];
    *(int *)p38 = 0;
    p48 = &u.b[24];
    *(int *)p48 = 0;
    u.vt = (int)&DAT_0053e020[0];
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053a0d0[0];
    if (p48 != 0) {
        v1 = *(int **)p48;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (p38 != 0) {
        v1 = *(int **)p38;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return r;
}

void FUN_003bf050(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelWaza_Register);
}

static igMetaObjectCallback g_beNDMWPanelWaza_callbackList[] = { FUN_0034cb30, 0 };

void *beNDMWPanelWaza_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWPanelWaza_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWPanelWaza_GetMetaObject,
        "beNDMWPanelWaza",
        0x24, /* instance size */
        beNDMWPanelWaza_GetVTable,
        beNDMWPanelWaza_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelWaza_callbackList /* callback list */
    );
}

void beNDMWPanelWaza_GetMetaObject(void)
{
    beNDMWPanelWaza_ResolveMetaObject();
}

static FieldFactory g_beNDMWPanelWaza_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWPanelWaza_fieldTable[] = {
    "_padManager",
};
static igMetaField **g_beNDMWPanelWaza_fieldHandles[] = {
    &g_beNDMWPanelWaza_padManagerMetaField,
};
static int g_beNDMWPanelWaza_fieldOffsets[] = {
    32,
};

void beNDMWPanelWaza_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWPanelWaza_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWPanelWaza_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, g_beNDMWPanelWaza_fieldTable, g_beNDMWPanelWaza_fieldHandles, g_beNDMWPanelWaza_fieldOffsets, temp_s2);
}

