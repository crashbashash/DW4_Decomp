igMetaObject *g_beHitLandModelOrder_metaObject;
igMetaField *g_beHitLandModelOrder_infoNameMetaField;
igMetaField *g_beHitLandModelOrder_ramNoMetaField;
igMetaField *g_beHitLandModelOrder_kindMetaField;
igMetaField *g_beHitLandModelOrder_raymaxMetaField;
igMetaField *g_beHitLandModelOrder_rayminMetaField;
igMetaField *g_beHitLandModelOrder_rayCountMetaField;
igMetaField *g_beHitLandModelOrder_rayListMetaField;
igMetaField *g_beHitLandModelOrder_hitdataCountMetaField;
igMetaField *g_beHitLandModelOrder_hitdataListMetaField;

void FUN_0035de90(int arg0) {
    FUN_0035e090();
    igMetaObject_CreateInstance(*(int *)0x589390, arg0);
}

igMetaObject *FUN_0035ded0(void) {
    if (g_beHitLandModelOrder_metaObject == 0) {
        g_beHitLandModelOrder_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beHitLandModelOrder_metaObject;
}

void *FUN_0035df20(void) {
    bool ok;
    if (g_beHitLandModelOrder_metaObject == 0) goto make;
    ok = !!(g_beHitLandModelOrder_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_0035e090();
done:;
    return g_beHitLandModelOrder_metaObject;
}

int beHitLandModelOrder_GetVTable(void) {
    union U_35df70 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    char *q2;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053a7a0[0];
    q2 = &u.b[32];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[48];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[56];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053a7a0[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    if (q2 != 0) {
        temp_v1 = *(int **)q2;
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

void FUN_0035e090(void)
{
    igMetaObject_RunStaticInit(beHitLandModelOrder_Register);
}

static igMetaObjectCallback g_beHitLandModelOrder_callbackList[] = { FUN_00188190, FUN_0035e350, 0 };

void *beHitLandModelOrder_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beHitLandModelOrder_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beHitLandModelOrder_GetMetaObject,
        "beHitLandModelOrder",
        0x3c, /* instance size */
        beHitLandModelOrder_GetVTable,
        beHitLandModelOrder_InitFields,
        0, /* extra callback item */
        g_beHitLandModelOrder_callbackList /* callback list */
    );
}

void beHitLandModelOrder_GetMetaObject(void)
{
    FUN_0035df20();
}

static FieldFactory g_beHitLandModelOrder_ctorTable[] = {
    igStringMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    FUN_00187890,
    FUN_00187890,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beHitLandModelOrder_fieldTable[] = {
    "_infoName",
    "_ramNo",
    "_kind",
    "_raymax",
    "_raymin",
    "_rayCount",
    "_rayList",
    "_hitdataCount",
    "_hitdataList",
};
static igMetaField **g_beHitLandModelOrder_fieldHandles[] = {
    &g_beHitLandModelOrder_infoNameMetaField,
    &g_beHitLandModelOrder_ramNoMetaField,
    &g_beHitLandModelOrder_kindMetaField,
    &g_beHitLandModelOrder_raymaxMetaField,
    &g_beHitLandModelOrder_rayminMetaField,
    &g_beHitLandModelOrder_rayCountMetaField,
    &g_beHitLandModelOrder_rayListMetaField,
    &g_beHitLandModelOrder_hitdataCountMetaField,
    &g_beHitLandModelOrder_hitdataListMetaField,
};
static int g_beHitLandModelOrder_fieldOffsets[] = {
    32,
    36,
    40,
    8,
    20,
    44,
    48,
    52,
    56,
};

void beHitLandModelOrder_InitFields(void) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_s1;
    int temp_s2;
    void *temp_s1_2;
    void *temp_s0;
    int sp50[3];
    int sp40[3];

    temp_s0 = (void *)g_beHitLandModelOrder_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beHitLandModelOrder_ctorTable, 9);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2), "");
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    sp50[0] = 0;
    sp50[1] = 0;
    sp50[2] = 0;
    FUN_0018e470(temp_a0, sp50);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    sp40[0] = 0;
    sp40[1] = 0;
    sp40[2] = 0;
    FUN_0018e470(temp_a0_2, sp40);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    *(int *)((char *)(temp_s1) + 56) = FUN_001880b0();
    *(char *)((char *)(temp_s1) + 52) = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    *(int *)((char *)(temp_s1_2) + 56) = (int)FUN_0035e270();
    *(char *)((char *)(temp_s1_2) + 52) = 1;
    igMetaObject_NameFields(temp_s0, g_beHitLandModelOrder_fieldTable, g_beHitLandModelOrder_fieldHandles, g_beHitLandModelOrder_fieldOffsets, temp_s2);
}

