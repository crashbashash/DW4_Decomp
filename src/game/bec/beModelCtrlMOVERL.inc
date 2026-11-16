igMetaObject *g_beModelCtrlMOVERL_metaObject;
igMetaField *g_beModelCtrlMOVERL_modelNameMetaField;
igMetaField *g_beModelCtrlMOVERL_boneNameMetaField;

void *beModelCtrlMOVERL_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlMOVERL_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlMOVERL_EnsureRegistered();
    }
    return g_beModelCtrlMOVERL_metaObject;
}

int beModelCtrlMOVERL_GetVTable(void) {
    union U_355410 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p4C;
    char *p48;
    char *p50;

    igObject_InitHeader(u.b);
    p48 = &u.b[8];
    *(int *)p48 = 0;
    u.vt = (int)&g_beModelCtrlMOVERL_vtable[0];
    p4C = &u.b[12];
    *(int *)p4C = 0;
    p50 = &u.b[16];
    *(int *)p50 = 0;
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beModelCtrlMOVERL_vtable[0];
    if (p50 != 0) {
        v1 = *(int **)p50;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (p4C != 0) {
        v1 = *(int **)p4C;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (p48 != 0) {
        v1 = *(int **)p48;
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

void beModelCtrlMOVERL_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMOVERL_Register);
}

void *beModelCtrlMOVERL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlMOVERL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMOVERL_GetMetaObjectFunction,
        "beModelCtrlMOVERL",
        0x14, /* instance size */
        beModelCtrlMOVERL_GetVTable,
        beModelCtrlMOVERL_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMOVERL_GetMetaObjectFunction(void)
{
    beModelCtrlMOVERL_GetMetaObject();
}

static FieldFactory g_beModelCtrlMOVERL_ctorTable[] = {
    igStringMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_beModelCtrlMOVERL_fieldTable[] = {
    "_modelName",
    "_boneName",
};
static igMetaField **g_beModelCtrlMOVERL_fieldHandles[] = {
    &g_beModelCtrlMOVERL_modelNameMetaField,
    &g_beModelCtrlMOVERL_boneNameMetaField,
};
static int g_beModelCtrlMOVERL_fieldOffsets[] = {
    12,
    16,
};

void beModelCtrlMOVERL_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beModelCtrlMOVERL_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlMOVERL_ctorTable, 2);
    igMetaObject_NameFields(meta, g_beModelCtrlMOVERL_fieldTable, g_beModelCtrlMOVERL_fieldHandles, g_beModelCtrlMOVERL_fieldOffsets, base);
}

