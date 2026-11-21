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
    beNDMWAfsStageLoad_EnsureRegistered();
done:
    return g_beNDMWAfsStageLoad_metaObject;
}

int beNDMWAfsStageLoad_GetVTable(void) {
    beNDMWAfsStageLoad obj;
    int vtable;
    int *stageRef;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWAfsStageLoad_vtable[0];
    stageRef = &obj._stage;
    *stageRef = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWAfsStageLoad_vtable[0];
    if (stageRef != 0) {
        igObject::release((igObject *)*stageRef);
    }
    return vtable;
}

void beNDMWAfsStageLoad_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsStageLoad_Register);
}

static igMetaObjectCallback g_beNDMWAfsStageLoad_callbackList[] = { igInsightCore_EnsureRegistered, igNamedObject_EnsureRegistered, 0 };

CallbackArray *beNDMWAfsStageLoad_Register(void) {
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

igMetaObject *igAction_GetPublishedMetaObject(void) {
    return g_igAction_metaObject;
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
    int base;
    void *insight;
    void *stage;
    igMetaObject *meta;

    meta = g_beNDMWAfsStageLoad_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWAfsStageLoad_ctorTable, 2);
    insight = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)insight)->_metaObject = (int)igInsightCore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)insight)->_refCounted = 0;
    stage = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)stage)->_metaObject = (int)igNamedObject_GetOrCreateMetaObject();
    ((igRefMetaField *)stage)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWAfsStageLoad_fieldTable, g_beNDMWAfsStageLoad_fieldHandles, g_beNDMWAfsStageLoad_fieldOffsets, base);
}

