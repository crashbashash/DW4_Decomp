igMetaObject *g_beNDMWAfsStageLoad_metaObject;
igMetaField *g_beNDMWAfsStageLoad_insightMetaField;
igMetaField *g_beNDMWAfsStageLoad_stageMetaField;

igMetaObject *beNDMWAfsStageLoad_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWAfsStageLoad_metaObject != 0) {
        ready = (g_beNDMWAfsStageLoad_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_003cac70();
done:
    return g_beNDMWAfsStageLoad_metaObject;
}

int beNDMWAfsStageLoad_GetVTable(void) {
    union U_3cabe0 u;
    int temp_s0;
    char *ps;
    int *temp_a0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053df40[0];
    ps = &u.b[12];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053df40[0];
    if (ps != 0) {
        temp_a0 = *(int **)ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

void FUN_003cac70(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsStageLoad_Register);
}

static igMetaObjectCallback g_beNDMWAfsStageLoad_callbackList[] = { FUN_00232de0, igNamedObject_EnsureRegistered, 0 };

void *beNDMWAfsStageLoad_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWAfsStageLoad_metaObject,
        igAction_Register,
        igAction_GetPublishedMetaObject,
        beNDMWAfsStageLoad_GetMetaObject,
        "beNDMWAfsStageLoad",
        0x10, /* instance size */
        beNDMWAfsStageLoad_GetVTable,
        beNDMWAfsStageLoad_InitFields,
        0, /* extra callback item */
        g_beNDMWAfsStageLoad_callbackList /* callback list */
    );
}

void beNDMWAfsStageLoad_GetMetaObject(void)
{
    beNDMWAfsStageLoad_ResolveMetaObject();
}

int FUN_003cad30(void) {
    return g_igAction_metaObject[0];
}

static FieldFactory g_beNDMWAfsStageLoad_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWAfsStageLoad_fieldTable[] = {
    "_insight",
    "_stage",
};
static igMetaField **g_beNDMWAfsStageLoad_fieldHandles[] = {
    &g_beNDMWAfsStageLoad_insightMetaField,
    &g_beNDMWAfsStageLoad_stageMetaField,
};
static int g_beNDMWAfsStageLoad_fieldOffsets[] = {
    8,
    12,
};

void beNDMWAfsStageLoad_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWAfsStageLoad_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWAfsStageLoad_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00232840();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igNamedObject_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beNDMWAfsStageLoad_fieldTable, g_beNDMWAfsStageLoad_fieldHandles, g_beNDMWAfsStageLoad_fieldOffsets, temp_s2);
}

