igMetaObject *g_beLoadIntf2ComMdlData_metaObject;
igMetaField *g_beLoadIntf2ComMdlData_ramNoMetaField;
igMetaField *g_beLoadIntf2ComMdlData_openSQMetaField;
igMetaField *g_beLoadIntf2ComMdlData_infoNameMetaField;

void beLoadIntf2ComMdlData__Create(int allocator) {
    beLoadIntf2ComMdlData_EnsureRegistered();
    igMetaObject_CreateInstance(g_beLoadIntf2ComMdlData_metaObject, allocator);
}

void *beLoadIntf2ComMdlData_GetReadyMetaObject(void) {
    igMetaObject *g = g_beLoadIntf2ComMdlData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beLoadIntf2ComMdlData_EnsureRegistered();
    }
    return g_beLoadIntf2ComMdlData_metaObject;
}

int beLoadIntf2ComMdlData_GetVTable(void) {
    beLoadIntf2ComMdlData obj;
    int vtable;
    int *openSQRef;
    int *infoNameRef;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beLoadIntf2ComMdlData_vtable[0];
    openSQRef = &obj._openSQ;
    *openSQRef = 0;
    infoNameRef = &obj._infoName;
    *infoNameRef = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beLoadIntf2ComMdlData_vtable[0];
    if (infoNameRef != 0) {
        releaseString((const char *)*infoNameRef);
    }
    if (openSQRef != 0) {
        releaseString((const char *)*openSQRef);
    }
    return vtable;
}

void beLoadIntf2ComMdlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLoadIntf2ComMdlData_Register);
}

void *beLoadIntf2ComMdlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLoadIntf2ComMdlData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beLoadIntf2ComMdlData_GetMetaObject,
        "beLoadIntf2ComMdlData",
        0x14, /* instance size */
        beLoadIntf2ComMdlData_GetVTable,
        beLoadIntf2ComMdlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beLoadIntf2ComMdlData_GetMetaObject(void)
{
    beLoadIntf2ComMdlData_GetReadyMetaObject();
}

static FieldFactory g_beLoadIntf2ComMdlData_ctorTable[] = {
    igIntMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_beLoadIntf2ComMdlData_fieldTable[] = {
    "_ramNo",
    "_openSQ",
    "_infoName",
};
static igMetaField **g_beLoadIntf2ComMdlData_fieldHandles[] = {
    &g_beLoadIntf2ComMdlData_ramNoMetaField,
    &g_beLoadIntf2ComMdlData_openSQMetaField,
    &g_beLoadIntf2ComMdlData_infoNameMetaField,
};
static int g_beLoadIntf2ComMdlData_fieldOffsets[] = {
    8,
    12,
    16,
};

void beLoadIntf2ComMdlData_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beLoadIntf2ComMdlData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beLoadIntf2ComMdlData_ctorTable, 3);
    igMetaObject_NameFields(meta, g_beLoadIntf2ComMdlData_fieldTable, g_beLoadIntf2ComMdlData_fieldHandles, g_beLoadIntf2ComMdlData_fieldOffsets, base);
}

