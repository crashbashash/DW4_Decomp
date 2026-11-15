igMetaObject *g_beNDMWDegiData_metaObject;
igMetaField *g_beNDMWDegiData_insightMetaField;
igMetaField *g_beNDMWDegiData_isUseMetaField;
igMetaField *g_beNDMWDegiData_idMetaField;
igMetaField *g_beNDMWDegiData_dmkindMetaField;
igMetaField *g_beNDMWDegiData_dmNameMetaField;
igMetaField *g_beNDMWDegiData_dmNameUniMetaField;
igMetaField *g_beNDMWDegiData_lvMetaField;
igMetaField *g_beNDMWDegiData_hpMetaField;
igMetaField *g_beNDMWDegiData_maxHpMetaField;
igMetaField *g_beNDMWDegiData_mpMetaField;
igMetaField *g_beNDMWDegiData_maxMpMetaField;
igMetaField *g_beNDMWDegiData_dataSizeMetaField;
igMetaField *g_beNDMWDegiData_dataMetaField;

void beNDMWDegiData_Create(int arg0) {
    beNDMWDegiData_RunStaticInit();
    igMetaObject_CreateInstance(g_beNDMWDegiData_metaObject, arg0);
}

void *beNDMWDegiData_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWDegiData_metaObject;
    bool ready;
    if (g) {
        /* matching construct: the bool compared against false keeps the retail sltu normalisation under the
         * unit profile (exceptions on); `if (ready = ...)` folds it away */
        ready = g->_validity & 4;
        if (ready != false) goto end;
    }
    beNDMWDegiData_RunStaticInit();
end:
    return g_beNDMWDegiData_metaObject;
}

int beNDMWDegiData_GetVTable(void) {
    union U_3c68c0 u;
    int temp_s0;
    char *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053c9a0[0];
    q1 = &u.b[48];
    *(int *)q1 = 0;
    q0 = &u.b[52];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053c9a0[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
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

void beNDMWDegiData_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(beNDMWDegiData_Register);
}

static igMetaObjectCallback g_beNDMWDegiData_callbackList[] = { FUN_00232de0, 0 };

void *beNDMWDegiData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWDegiData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWDegiData_GetMetaObject,
        "beNDMWDegiData",
        0x4c, /* instance size */
        beNDMWDegiData_GetVTable,
        beNDMWDegiData_InitFields,
        0, /* extra callback item */
        g_beNDMWDegiData_callbackList /* callback list */
    );
}

void beNDMWDegiData_GetMetaObject(void)
{
    beNDMWDegiData_GetReadyMetaObject();
}

static FieldFactory g_beNDMWDegiData_ctorTable[] = {
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igUnsignedShortArrayMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igMemoryRefMetaField_Create,
};
static const char *g_beNDMWDegiData_fieldTable[] = {
    "_insight",
    "_isUse",
    "_id",
    "_dmkind",
    "_dmName",
    "_dmNameUni",
    "_lv",
    "_hp",
    "_maxHp",
    "_mp",
    "_maxMp",
    "_dataSize",
    "_data",
};
static igMetaField **g_beNDMWDegiData_fieldHandles[] = {
    &g_beNDMWDegiData_insightMetaField,
    &g_beNDMWDegiData_isUseMetaField,
    &g_beNDMWDegiData_idMetaField,
    &g_beNDMWDegiData_dmkindMetaField,
    &g_beNDMWDegiData_dmNameMetaField,
    &g_beNDMWDegiData_dmNameUniMetaField,
    &g_beNDMWDegiData_lvMetaField,
    &g_beNDMWDegiData_hpMetaField,
    &g_beNDMWDegiData_maxHpMetaField,
    &g_beNDMWDegiData_mpMetaField,
    &g_beNDMWDegiData_maxMpMetaField,
    &g_beNDMWDegiData_dataSizeMetaField,
    &g_beNDMWDegiData_dataMetaField,
};
static int g_beNDMWDegiData_fieldOffsets[] = {
    32,
    40,
    44,
    48,
    52,
    8,
    56,
    60,
    64,
    68,
    72,
    36,
    28,
};

void beNDMWDegiData_InitFields(void) {
    igMetaObject *temp_s0;
    int temp_s2;
    void *temp_s1;
    void *temp_v0;
    void *temp_s1_2;

    temp_s0 = g_beNDMWDegiData_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWDegiData_ctorTable, 0xD);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_00232840();
    *(char *)((char *)(temp_s1) + 60) = 0;
    temp_v0 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5);
    *(int *)((char *)(temp_v0) + 52) = 0xA;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC));
    *(int *)((char *)(temp_s1_2) + 60) = igCharMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields(temp_s0, g_beNDMWDegiData_fieldTable, g_beNDMWDegiData_fieldHandles, g_beNDMWDegiData_fieldOffsets, temp_s2);
}

