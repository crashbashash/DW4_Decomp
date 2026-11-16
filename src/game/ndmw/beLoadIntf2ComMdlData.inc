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
    union U_3c74e0 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p3C;
    char *p40;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beLoadIntf2ComMdlData_vtable[0];
    p3C = &u.b[12];
    *(int *)p3C = 0;
    p40 = &u.b[16];
    *(int *)p40 = 0;
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beLoadIntf2ComMdlData_vtable[0];
    if (p40 != 0) {
        v1 = *(int **)p40;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (p3C != 0) {
        v1 = *(int **)p3C;
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
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beLoadIntf2ComMdlData_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beLoadIntf2ComMdlData_ctorTable, 3);
    igMetaObject_NameFields(temp_s0, g_beLoadIntf2ComMdlData_fieldTable, g_beLoadIntf2ComMdlData_fieldHandles, g_beLoadIntf2ComMdlData_fieldOffsets, temp_s1);
}

