igMetaObject *g_beTargetObj_metaObject;
igMetaField *g_beTargetObj_playerPosListMetaField;
igMetaField *g_beTargetObj_playerRamNoListMetaField;
igMetaField *g_beTargetObj_enemyPosListMetaField;

void beTargetObj_CreateInstance(int arg0) {
    FUN_00342b00();
    igMetaObject_CreateInstance(*(int *)0x587CE8, arg0);
}

igMetaObject *FUN_003429b0(void) {
    if (g_beTargetObj_metaObject == 0) {
        g_beTargetObj_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beTargetObj_metaObject;
}

void *FUN_00342a00(void) {
    igMetaObject *g = g_beTargetObj_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00342b00();
    }
    return g_beTargetObj_metaObject;
}

int beTargetObj_GetVTable(void) {
    union U_342a50 u;
    int temp_s2;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[0] = (int)(&DAT_0053ba50[0]);
    u.w[4] = 0;
    u.w[5] = 0;
    u.w[6] = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_0053ba50[0]);
    FUN_001374b0(&u.w[6], -1);
    igSmartPointer_igIntList_Destruct(&u.w[5], -1);
    FUN_001374b0(&u.w[4], -1);
    FUN_00231030(u.b, 0);
    return temp_s2;
}

void FUN_00342b00(void)
{
    igMetaObject_RunStaticInit(beTargetObj_Register);
}

static igMetaObjectCallback g_beTargetObj_callbackList[] = { FUN_0018a180, igIntList_EnsureRegistered, 0 };

void *beTargetObj_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTargetObj_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beTargetObj_GetMetaObject,
        "beTargetObj",
        0x1c, /* instance size */
        beTargetObj_GetVTable,
        beTargetObj_InitFields,
        0, /* extra callback item */
        g_beTargetObj_callbackList /* callback list */
    );
}

void beTargetObj_GetMetaObject(void)
{
    FUN_00342a00();
}

static FieldFactory g_beTargetObj_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beTargetObj_fieldTable[] = {
    "_playerPosList",
    "_playerRamNoList",
    "_enemyPosList",
};
static igMetaField **g_beTargetObj_fieldHandles[] = {
    &g_beTargetObj_playerPosListMetaField,
    &g_beTargetObj_playerRamNoListMetaField,
    &g_beTargetObj_enemyPosListMetaField,
};
static int g_beTargetObj_fieldOffsets[] = {
    16,
    20,
    24,
};

void beTargetObj_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beTargetObj_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beTargetObj_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0018a0a0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0018a0a0();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beTargetObj_fieldTable, g_beTargetObj_fieldHandles, g_beTargetObj_fieldOffsets, temp_s2);
}

