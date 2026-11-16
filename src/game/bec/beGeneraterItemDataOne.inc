igMetaObject *g_beGeneraterItemDataOne_metaObject;
igMetaField *g_beGeneraterItemDataOne_idMetaField;
igMetaField *g_beGeneraterItemDataOne_rankMetaField;
igMetaField *g_beGeneraterItemDataOne_rateMetaField;

void *beGeneraterItemDataOne_GetMetaObject(void) {
    igMetaObject *g = g_beGeneraterItemDataOne_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beGeneraterItemDataOne_EnsureRegistered();
    }
    return g_beGeneraterItemDataOne_metaObject;
}

int beGeneraterItemDataOne_GetVTable(void) {
    union U_360960 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beGeneraterItemDataOne_vtable[0];
    s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return s0;
}

void beGeneraterItemDataOne_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterItemDataOne_Register);
}

void *beGeneraterItemDataOne_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterItemDataOne_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beGeneraterItemDataOne_GetMetaObjectFunction,
        "beGeneraterItemDataOne",
        0x18, /* instance size */
        beGeneraterItemDataOne_GetVTable,
        beGeneraterItemDataOne_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beGeneraterItemDataOne_GetMetaObjectFunction(void)
{
    beGeneraterItemDataOne_GetMetaObject();
}

static FieldFactory g_beGeneraterItemDataOne_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beGeneraterItemDataOne_fieldTable[] = {
    "_id",
    "_rank",
    "_rate",
};
static igMetaField **g_beGeneraterItemDataOne_fieldHandles[] = {
    &g_beGeneraterItemDataOne_idMetaField,
    &g_beGeneraterItemDataOne_rankMetaField,
    &g_beGeneraterItemDataOne_rateMetaField,
};
static int g_beGeneraterItemDataOne_fieldOffsets[] = {
    12,
    16,
    20,
};

void beGeneraterItemDataOne_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beGeneraterItemDataOne_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beGeneraterItemDataOne_ctorTable, 3);
    igMetaObject_NameFields(temp_s0, g_beGeneraterItemDataOne_fieldTable, g_beGeneraterItemDataOne_fieldHandles, g_beGeneraterItemDataOne_fieldOffsets, temp_s1);
}

igMetaEnum *g_beGeneraterItemDataOne_msgActionMetaEnum;
static const char *g_beGeneraterItemDataOne_msgActionNames[] = {
    "START", "STOP", "STOPREVERS", "RESET",
    "RESTART", "PERFECTDROP", "ONFREEZE", "OFFREEZE",
};
static int g_beGeneraterItemDataOne_msgActionValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
};

igMetaEnum *FUN_00360b10(void) {
    if (g_beGeneraterItemDataOne_msgActionMetaEnum == 0) {
        g_beGeneraterItemDataOne_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beGeneraterItemDataOne_msgActionNames, g_beGeneraterItemDataOne_msgActionValues, 8);
    }
    return g_beGeneraterItemDataOne_msgActionMetaEnum;
}

