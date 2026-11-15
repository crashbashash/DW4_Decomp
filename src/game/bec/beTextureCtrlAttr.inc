igMetaObject *g_beTextureCtrlAttr_metaObject;
igMetaField *g_beTextureCtrlAttr_attrSetMetaField;

igMetaObject *FUN_00341e10(void) {
    if (g_beTextureCtrlAttr_metaObject == 0 || !isValid(g_beTextureCtrlAttr_metaObject)) FUN_00341f40();
    return g_beTextureCtrlAttr_metaObject;
}

int beTextureCtrlAttr_GetVTable(void) {
    union U_341e60 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_005395c0[0];
    q0 = (S_ref *)&u.b[12];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_005395c0[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_00341f40(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlAttr_Register);
}

static igMetaObjectCallback g_beTextureCtrlAttr_callbackList[] = { FUN_001a5e90, 0 };

void *beTextureCtrlAttr_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTextureCtrlAttr_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beTextureCtrlAttr_GetMetaObject,
        "beTextureCtrlAttr",
        0x10, /* instance size */
        beTextureCtrlAttr_GetVTable,
        beTextureCtrlAttr_InitFields,
        0, /* extra callback item */
        g_beTextureCtrlAttr_callbackList /* callback list */
    );
}

void beTextureCtrlAttr_GetMetaObject(void)
{
    FUN_00341e10();
}

static FieldFactory g_beTextureCtrlAttr_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beTextureCtrlAttr_fieldTable[] = {
    "_attrSet",
};
static igMetaField **g_beTextureCtrlAttr_fieldHandles[] = {
    &g_beTextureCtrlAttr_attrSetMetaField,
};
static int g_beTextureCtrlAttr_fieldOffsets[] = {
    12,
};

void beTextureCtrlAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beTextureCtrlAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beTextureCtrlAttr_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001a5d70();
    igMetaObject_NameFields(temp_s0, g_beTextureCtrlAttr_fieldTable, g_beTextureCtrlAttr_fieldHandles, g_beTextureCtrlAttr_fieldOffsets, temp_s2);
}

