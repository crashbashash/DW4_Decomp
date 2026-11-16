igMetaObject *g_beSoundData_metaObject;
igMetaField *g_beSoundData_typeMetaField;
igMetaField *g_beSoundData_fnameIdxMetaField;
igMetaField *g_beSoundData_memoryIdxMetaField;
igMetaField *g_beSoundData_channelMetaField;
igMetaField *g_beSoundData_volumeMetaField;
igMetaField *g_beSoundData_priorityMetaField;

igMetaObject *beSoundData_GetMetaObject(void) {
    igMetaObject *g = g_beSoundData_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beSoundData_EnsureRegistered();
    return g_beSoundData_metaObject;
}

int beSoundData_GetVTable(void) {
    union U_343fa0 u;
    int temp_s0;
    char *q1;
    int *tv1, *ta1;
    int tc1;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&g_beSoundData_vtable[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    if (q1 != 0) {
        tv1 = *(int **)q1;
        if (tv1 != 0) {
            ta1 = tv1 - 2;
            tc1 = tv1[-1] - 1;
            tv1[-1] = tc1;
            if (tc1 == 0) {
                StringChunk_ReleaseHeader(*ta1, ta1);
            }
        }
    }
    return temp_s0;
}

struct W_344030 *FUN_00344030(struct W_344030 *arg0, short arg1) {
    int *temp_a1;
    int temp_v0;
    int *temp_v1;

    if (arg0 != 0) {
        arg0->vt = &g_beBaseInfoData_vtable[0];
        if (arg0 != 0) {
            arg0->vt = &g_igNamedObject_vtable[0];
            if (&arg0->name != 0) {
                temp_v1 = arg0->name;
                if (temp_v1 != 0) {
                    temp_a1 = temp_v1 - 2;
                    temp_v0 = temp_v1[-1] - 1;
                    temp_v1[-1] = temp_v0;
                    if (temp_v0 == 0) {
                        StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                    }
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void beSoundData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSoundData_Register);
}

void *beSoundData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSoundData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beSoundData_GetMetaObjectFunction,
        "beSoundData",
        0x20, /* instance size */
        beSoundData_GetVTable,
        beSoundData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSoundData_GetMetaObjectFunction(void)
{
    beSoundData_GetMetaObject();
}

static FieldFactory g_beSoundData_ctorTable[] = {
    igShortMetaField_Create,
    igShortMetaField_Create,
    igIntMetaField_Create,
    igShortMetaField_Create,
    igShortMetaField_Create,
    igShortMetaField_Create,
};
static const char *g_beSoundData_fieldTable[] = {
    "_type",
    "_fnameIdx",
    "_memoryIdx",
    "_channel",
    "_volume",
    "_priority",
};
static igMetaField **g_beSoundData_fieldHandles[] = {
    &g_beSoundData_typeMetaField,
    &g_beSoundData_fnameIdxMetaField,
    &g_beSoundData_memoryIdxMetaField,
    &g_beSoundData_channelMetaField,
    &g_beSoundData_volumeMetaField,
    &g_beSoundData_priorityMetaField,
};
static int g_beSoundData_fieldOffsets[] = {
    16,
    18,
    20,
    24,
    26,
    28,
};

void beSoundData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSoundData_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSoundData_ctorTable, 6);
    igShortMetaField_SetDefault(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1)), -1);
    igShortMetaField_SetDefault(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1)), -1);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)), -1);
    igShortMetaField_SetDefault(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3)), 1);
    igMetaObject_NameFields(temp_s0, g_beSoundData_fieldTable, g_beSoundData_fieldHandles, g_beSoundData_fieldOffsets, temp_s1);
}

igMetaEnum *g_beSoundData_messageMetaEnum;
static const char *g_beSoundData_messageNames[] = {
    "MODENONE", "STOP", "PLAY", "PLAYatPAUSE",
    "PAUSEOFF", "VOLUMECTL", "BGMSTOP", "ENVSTOP",
    "SESTOP", "GETWORDLIST", "VOLUMECTL2", "FXCTL",
    "ISREADY", "ISBGMREADY", "ISENVREADY", "ISALLREADY",
    "GETCURRENTBGM", "SNDFVOLUME", "OFFREEZE", "ONFREEZE",
    "MAKEBINLIST", "ISDONETRANS", "FREESFPDATA",
};
static int g_beSoundData_messageValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
};

igMetaEnum *beSound_GetMessageEnum(void) {
    if (g_beSoundData_messageMetaEnum == 0) {
        g_beSoundData_messageMetaEnum = igMetaEnum_Create("Message", g_beSoundData_messageNames, g_beSoundData_messageValues, 0x17);
    }
    return g_beSoundData_messageMetaEnum;
}

