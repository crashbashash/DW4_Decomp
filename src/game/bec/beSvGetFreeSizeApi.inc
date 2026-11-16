igMetaObject *g_beSvGetFreeSizeApi_metaObject;
igMetaField *g_beSvGetFreeSizeApi_memNeedMetaField;
igMetaField *g_beSvGetFreeSizeApi_memCapaMetaField;
igMetaField *g_beSvGetFreeSizeApi_fileCapaMetaField;

void beSvGetFreeSizeApi_Create(int allocator) {
    beSvGetFreeSizeApi_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588200, allocator);
}

igMetaObject *beSvGetFreeSizeApi_GetMetaObject(void) {
    igMetaObject *g = g_beSvGetFreeSizeApi_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beSvGetFreeSizeApi_EnsureRegistered();
    return g_beSvGetFreeSizeApi_metaObject;
}

int beSvGetFreeSizeApi_GetVTable(void) {
    union U_348d00 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p74;
    char *p70;
    char *p78;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beSaveApi_vtable[0];
    p70 = &u.b[48];
    *(int *)p70 = 0;
    p74 = &u.b[52];
    *(int *)p74 = 0;
    p78 = &u.b[56];
    *(int *)p78 = 0;
    u.vt = (int)&g_beSvGetFreeSizeApi_vtable[0];
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beSaveApi_vtable[0];
    if (p78 != 0) {
        v1 = *(int **)p78;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p74 != 0) {
        v1 = *(int **)p74;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p70 != 0) {
        v1 = *(int **)p70;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}

void beSvGetFreeSizeApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvGetFreeSizeApi_Register);
}

void *beSvGetFreeSizeApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvGetFreeSizeApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvGetFreeSizeApi_GetMetaObjectFunction,
        "beSvGetFreeSizeApi",
        0x58, /* instance size */
        beSvGetFreeSizeApi_GetVTable,
        beSvGetFreeSizeApi_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvGetFreeSizeApi_GetMetaObjectFunction(void)
{
    beSvGetFreeSizeApi_GetMetaObject();
}

static FieldFactory g_beSvGetFreeSizeApi_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beSvGetFreeSizeApi_fieldTable[] = {
    "_memNeed",
    "_memCapa",
    "_fileCapa",
};
static igMetaField **g_beSvGetFreeSizeApi_fieldHandles[] = {
    &g_beSvGetFreeSizeApi_memNeedMetaField,
    &g_beSvGetFreeSizeApi_memCapaMetaField,
    &g_beSvGetFreeSizeApi_fileCapaMetaField,
};
static int g_beSvGetFreeSizeApi_fieldOffsets[] = {
    64,
    68,
    72,
};

void beSvGetFreeSizeApi_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beSvGetFreeSizeApi_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSvGetFreeSizeApi_ctorTable, 3);
    igMetaObject_NameFields(meta, g_beSvGetFreeSizeApi_fieldTable, g_beSvGetFreeSizeApi_fieldHandles, g_beSvGetFreeSizeApi_fieldOffsets, base);
}

