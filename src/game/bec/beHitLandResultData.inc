igMetaObject *g_beHitLandResultData_metaObject;
igMetaField *g_beHitLandResultData_infoNameMetaField;
igMetaField *g_beHitLandResultData_ramNoMetaField;

void beHitLandResultData_Create(int allocator) {
    beHitLandResultData_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5893E8, allocator);
}

void *beHitLandResultData_GetMetaObject(void) {
    unsigned char b;
    if (g_beHitLandResultData_metaObject != 0) {
        b = (g_beHitLandResultData_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beHitLandResultData_EnsureRegistered();
done:
    return g_beHitLandResultData_metaObject;
}

int beHitLandResultData_GetVTable(void) {
    union U_35e490 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beHitLandResultData_vtable[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beHitLandResultData_vtable[0];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void beHitLandResultData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beHitLandResultData_Register);
}

void *beHitLandResultData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beHitLandResultData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beHitLandResultData_GetMetaObjectFunction,
        "beHitLandResultData",
        0x58, /* instance size */
        beHitLandResultData_GetVTable,
        beHitLandResultData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beHitLandResultData_GetMetaObjectFunction(void)
{
    beHitLandResultData_GetMetaObject();
}

static FieldFactory g_beHitLandResultData_ctorTable[] = {
    igStringMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beHitLandResultData_fieldTable[] = {
    "_infoName",
    "_ramNo",
};
static igMetaField **g_beHitLandResultData_fieldHandles[] = {
    &g_beHitLandResultData_infoNameMetaField,
    &g_beHitLandResultData_ramNoMetaField,
};
static int g_beHitLandResultData_fieldOffsets[] = {
    8,
    12,
};

void beHitLandResultData_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beHitLandResultData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beHitLandResultData_ctorTable, 2);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(meta, base)), "");
    igMetaObject_NameFields(meta, g_beHitLandResultData_fieldTable, g_beHitLandResultData_fieldHandles, g_beHitLandResultData_fieldOffsets, base);
}

