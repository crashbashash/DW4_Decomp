igMetaObject *g_beActionStarterData2_metaObject;
igMetaField *g_beActionStarterData2_rotationMetaField;

void *beActionStarterData2_GetMetaObject(void) {
    igMetaObject *g = g_beActionStarterData2_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beActionStarterData2_EnsureRegistered();
    }
    return g_beActionStarterData2_metaObject;
}

int beActionStarterData2_GetVTable(void) {
    union U_36ba60 u;
    int temp_s1;
    void **q2;
    void **q3;
    int *temp_a1;
    int *temp_a1_2;
    int temp_v0;
    int temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&g_beActionStarterData_vtable[0]);
    q3 = &u.p[3];
    *q3 = 0;
    u.w[0] = (int)(&g_beActionStarterData2_vtable[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beActionStarterData_vtable[0]);
    if (q3 != 0) {
        temp_v1 = *q3;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    if (q2 != 0) {
        temp_v1_2 = *q2;
        if (temp_v1_2 != 0) {
            temp_a1_2 = (int *)((char *)temp_v1_2 - 8);
            temp_v0_2 = *(int *)((char *)(temp_v1_2) - 4) - 1;
            *(int *)((char *)(temp_v1_2) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
            }
        }
    }
    return temp_s1;
}

void beActionStarterData2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beActionStarterData2_Register);
}

void *beActionStarterData2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beActionStarterData2_metaObject,
        beActionStarterData_Register,
        beActionStarterData_GetPublishedMetaObject,
        beActionStarterData2_GetMetaObjectFunction,
        "beActionStarterData2",
        0x30, /* instance size */
        beActionStarterData2_GetVTable,
        beActionStarterData2_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beActionStarterData2_GetMetaObjectFunction(void)
{
    beActionStarterData2_GetMetaObject();
}

igMetaObject *beActionStarterData_GetPublishedMetaObject(void) {
    return g_beActionStarterData_metaObject;
}

static FieldFactory g_beActionStarterData2_ctorTable[] = {
    FUN_00187890,
};
static const char *g_beActionStarterData2_fieldTable[] = {
    "_rotation",
};
static igMetaField **g_beActionStarterData2_fieldHandles[] = {
    &g_beActionStarterData2_rotationMetaField,
};
static int g_beActionStarterData2_fieldOffsets[] = {
    36,
};

void beActionStarterData2_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beActionStarterData2_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beActionStarterData2_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beActionStarterData2_fieldTable, g_beActionStarterData2_fieldHandles, g_beActionStarterData2_fieldOffsets, base);
}

