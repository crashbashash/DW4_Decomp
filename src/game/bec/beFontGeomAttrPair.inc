igMetaObject *g_beFontGeomAttrPair_metaObject;
igMetaField *g_beFontGeomAttrPair_categoryMetaField;
igMetaField *g_beFontGeomAttrPair_panelMetaField;
igMetaField *g_beFontGeomAttrPair_geomAttrsMetaField;

void beFontGeomAttrPair_Create(int allocator) {
    beFontGeomAttrPair_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5896D8, allocator);
}

void *beFontGeomAttrPair_GetMetaObject(void) {
    bool ok;
    if (g_beFontGeomAttrPair_metaObject == 0) goto make;
    ok = !!(g_beFontGeomAttrPair_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beFontGeomAttrPair_EnsureRegistered();
done:;
    return g_beFontGeomAttrPair_metaObject;
}

int beFontGeomAttrPair_GetVTable(void) {
    union U_362580 u;
    int temp_s2;
    void ** q1;
    void ** q0;
    igObject * q2;
    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    u.vt = (int)(&g_beFontGeomAttrPair_vtable[0]);
    q0 = (void **)&u.b[8];
    *q0 = 0;
    q1 = (void **)&u.b[12];
    *q1 = 0;
    q2 = (igObject *)&u.b[16];
    *(int *)q2 = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)(&g_beFontGeomAttrPair_vtable[0]);
    if (q2 != 0) {
        q2 = *(igObject **)q2;
        if (q2 != 0) {
            q2->_refCount = (int)q2->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q2->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    if (q1 != 0) {
        temp_v1 = *q1;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    if (q0 != 0) {
        temp_v1 = *q0;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s2;
}

void beFontGeomAttrPair_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFontGeomAttrPair_Register);
}

static igMetaObjectCallback g_beFontGeomAttrPair_callbackList[] = { igGeometryAttrList_EnsureRegistered, 0 };

void *beFontGeomAttrPair_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFontGeomAttrPair_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beFontGeomAttrPair_GetMetaObjectFunction,
        "beFontGeomAttrPair",
        0x14, /* instance size */
        beFontGeomAttrPair_GetVTable,
        beFontGeomAttrPair_InitFields,
        0, /* extra callback item */
        g_beFontGeomAttrPair_callbackList /* callback list */
    );
}

void beFontGeomAttrPair_GetMetaObjectFunction(void)
{
    beFontGeomAttrPair_GetMetaObject();
}

static FieldFactory g_beFontGeomAttrPair_ctorTable[] = {
    igStringMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beFontGeomAttrPair_fieldTable[] = {
    "_category",
    "_panel",
    "_geomAttrs",
};
static igMetaField **g_beFontGeomAttrPair_fieldHandles[] = {
    &g_beFontGeomAttrPair_categoryMetaField,
    &g_beFontGeomAttrPair_panelMetaField,
    &g_beFontGeomAttrPair_geomAttrsMetaField,
};
static int g_beFontGeomAttrPair_fieldOffsets[] = {
    8,
    12,
    16,
};

void beFontGeomAttrPair_InitFields(void) {
    int base;
    void *geomAttrs;
    void *meta;

    meta = (void *)g_beFontGeomAttrPair_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beFontGeomAttrPair_ctorTable, 3);
    geomAttrs = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)geomAttrs)->_metaObject = igGeometryAttrList_GetOrCreateMetaObject();
    ((igRefMetaField *)geomAttrs)->_construct = 1;
    igMetaObject_NameFields(meta, g_beFontGeomAttrPair_fieldTable, g_beFontGeomAttrPair_fieldHandles, g_beFontGeomAttrPair_fieldOffsets, base);
}

