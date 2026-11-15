igMetaObject *g_beFontGeomAttrPair_metaObject;
igMetaField *g_beFontGeomAttrPair_categoryMetaField;
igMetaField *g_beFontGeomAttrPair_panelMetaField;
igMetaField *g_beFontGeomAttrPair_geomAttrsMetaField;

void beFontGeomAttrPair_Create(int arg0) {
    FUN_00362690();
    igMetaObject_CreateInstance(*(int *)0x5896D8, arg0);
}

void *FUN_00362530(void) {
    bool ok;
    if (g_beFontGeomAttrPair_metaObject == 0) goto make;
    ok = !!(g_beFontGeomAttrPair_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_00362690();
done:;
    return g_beFontGeomAttrPair_metaObject;
}

int beFontGeomAttrPair_GetVTable(void) {
    union U_362580 u;
    int temp_s2;
    void ** q1;
    void ** q0;
    S_ref * q2;
    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    u.vt = (int)(&DAT_005358e0[0]);
    q0 = (void **)&u.b[8];
    *q0 = 0;
    q1 = (void **)&u.b[12];
    *q1 = 0;
    q2 = (S_ref *)&u.b[16];
    *(int *)q2 = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)(&DAT_005358e0[0]);
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
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

void FUN_00362690(void)
{
    igMetaObject_RunStaticInit(beFontGeomAttrPair_Register);
}

static igMetaObjectCallback g_beFontGeomAttrPair_callbackList[] = { FUN_0013a5b0, 0 };

void *beFontGeomAttrPair_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFontGeomAttrPair_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beFontGeomAttrPair_GetMetaObject,
        "beFontGeomAttrPair",
        0x14, /* instance size */
        beFontGeomAttrPair_GetVTable,
        beFontGeomAttrPair_InitFields,
        0, /* extra callback item */
        g_beFontGeomAttrPair_callbackList /* callback list */
    );
}

void beFontGeomAttrPair_GetMetaObject(void)
{
    FUN_00362530();
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
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beFontGeomAttrPair_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beFontGeomAttrPair_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0013a4d0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beFontGeomAttrPair_fieldTable, g_beFontGeomAttrPair_fieldHandles, g_beFontGeomAttrPair_fieldOffsets, temp_s2);
}

