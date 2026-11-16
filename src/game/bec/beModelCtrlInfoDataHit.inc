igMetaObject *g_beModelCtrlInfoDataHit_metaObject;
int g_beModelCtrlInfoDataHit_nameStorage;
igMetaField *g_beModelCtrlInfoDataHit_isHitPlayerBulletMetaField;
igMetaField *g_beModelCtrlInfoDataHit_isHitEnemyBulletMetaField;
igMetaField *g_beModelCtrlInfoDataHit_hitBulletAABoxListMetaField;
igMetaField *g_beModelCtrlInfoDataHit_isHitPlayerTalkMetaField;

void *beModelCtrlInfoDataHit_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlInfoDataHit_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlInfoDataHit_EnsureRegistered();
    }
    return g_beModelCtrlInfoDataHit_metaObject;
}

int beModelCtrlInfoDataHit_GetVTable(void) {
    union U_353920 u;
    int temp_s1;
    void **q2;
    igObject *q5;
    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&g_beModelCtrlInfoDataHit_vtable[0]);
    q5 = (igObject *)&u.p[5];
    *(int *)q5 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beModelCtrlInfoDataHit_vtable[0]);
    if (q5 != 0) {
        q5 = *(igObject **)q5;
        if (q5 != 0) {
            q5->_refCount = (int)q5->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q5->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q5);
            }
        }
    }
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    if (q2 != 0) {
        temp_v1 = *q2;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s1;
}

void beModelCtrlInfoDataHit_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataHit_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoDataHit_callbackList[] = { igAABoxList_EnsureRegistered, 0 };

void *beModelCtrlInfoDataHit_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoDataHit_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataHit_GetMetaObjectFunction,
        "beModelCtrlInfoDataHit",
        0x1c, /* instance size */
        beModelCtrlInfoDataHit_GetVTable,
        beModelCtrlInfoDataHit_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoDataHit_callbackList /* callback list */
    );
}

void beModelCtrlInfoDataHit_GetMetaObjectFunction(void)
{
    beModelCtrlInfoDataHit_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoDataHit_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beModelCtrlInfoDataHit_fieldTable[] = {
    "_isHitPlayerBullet",
    "_isHitEnemyBullet",
    "_hitBulletAABoxList",
    "_isHitPlayerTalk",
};
static igMetaField **g_beModelCtrlInfoDataHit_fieldHandles[] = {
    &g_beModelCtrlInfoDataHit_isHitPlayerBulletMetaField,
    &g_beModelCtrlInfoDataHit_isHitEnemyBulletMetaField,
    &g_beModelCtrlInfoDataHit_hitBulletAABoxListMetaField,
    &g_beModelCtrlInfoDataHit_isHitPlayerTalkMetaField,
};
static int g_beModelCtrlInfoDataHit_fieldOffsets[] = {
    16,
    17,
    20,
    24,
};

void beModelCtrlInfoDataHit_InitFields(void) {
    int base;
    int index;
    void **found;
    void *hitBulletAABoxList;
    void *meta;
    igStringMetaField *clone;

    meta = (void *)g_beModelCtrlInfoDataHit_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlInfoDataHit_ctorTable, 4);
    found = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    index = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, found);
    clone = (igStringMetaField *)(((DW4VC_84_1 *)(found))->vX((int)(1)));
    igStringMetaField_SetDefaultText(clone, "HIT");
    clone->_externalEnumStorage = (int)(&g_beModelCtrlInfoDataHit_nameStorage);
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    hitBulletAABoxList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)hitBulletAABoxList)->_metaObject = igAABoxList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beModelCtrlInfoDataHit_fieldTable, g_beModelCtrlInfoDataHit_fieldHandles, g_beModelCtrlInfoDataHit_fieldOffsets, base);
}

