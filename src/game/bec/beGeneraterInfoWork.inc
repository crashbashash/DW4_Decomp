igMetaObject *g_beGeneraterInfoWork_metaObject;
igMetaField *g_beGeneraterInfoWork_isSystemFreezeMetaField;
igMetaField *g_beGeneraterInfoWork_isFreezeMetaField;
igMetaField *g_beGeneraterInfoWork_playerCountMetaField;
igMetaField *g_beGeneraterInfoWork_nokoriKazuMetaField;
igMetaField *g_beGeneraterInfoWork_enemyRamListMetaField;
igMetaField *g_beGeneraterInfoWork_genePointMetaField;
igMetaField *g_beGeneraterInfoWork_geneEnemyNameMetaField;
igMetaField *g_beGeneraterInfoWork_geneEnemyRecNoMetaField;
igMetaField *g_beGeneraterInfoWork_geneEnemyMHpMetaField;

void beGeneraterInfoWork_Create(int allocator) {
    beGeneraterInfoWork_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589478, allocator);
}

igMetaObject *beGeneraterInfoWork_GetOrCreateMetaObject(void) {
    if (g_beGeneraterInfoWork_metaObject == 0) {
        g_beGeneraterInfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beGeneraterInfoWork_metaObject;
}

igMetaObject *beGeneraterInfoWork_GetMetaObject(void)
{
    igMetaObject *g = g_beGeneraterInfoWork_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beGeneraterInfoWork_EnsureRegistered();
    return g_beGeneraterInfoWork_metaObject;
}

int beGeneraterInfoWork_GetVTable(void) {
    union U u;
    int t;
    char *o;
    int *a1;
    int v0;
    igObject *p0, *p1;

    igObject_InitHeader(u.b);
    p0 = (igObject *)&u.b[20];
    p1 = (igObject *)&u.b[28];
    u.vt = (int)&g_beGeneraterInfoWork_vtable[0];
    *(int *)p0 = 0;
    *(int *)p1 = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beGeneraterInfoWork_vtable[0];
    if (p1 != 0) {
        o = *(char **)p1;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (p0 != 0) {
        p0 = *(igObject **)p0;
        if (p0 != 0) {
            p0->_refCount = (int)p0->_refCount - 1;
            if (((unsigned long long) ((long long)(int)p0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p0);
            }
        }
    }
    return t;
}

void beGeneraterInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterInfoWork_Register);
}

static igMetaObjectCallback g_beGeneraterInfoWork_callbackList[] = { beBaseInfoRamList_EnsureRegistered, 0 };

void *beGeneraterInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beGeneraterInfoWork_GetMetaObjectFunction,
        "beGeneraterInfoWork",
        0x28, /* instance size */
        beGeneraterInfoWork_GetVTable,
        beGeneraterInfoWork_InitFields,
        0, /* extra callback item */
        g_beGeneraterInfoWork_callbackList /* callback list */
    );
}

void beGeneraterInfoWork_GetMetaObjectFunction(void)
{
    beGeneraterInfoWork_GetMetaObject();
}

static FieldFactory g_beGeneraterInfoWork_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igStringMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beGeneraterInfoWork_fieldTable[] = {
    "_isSystemFreeze",
    "_isFreeze",
    "_playerCount",
    "_nokoriKazu",
    "_enemyRamList",
    "_genePoint",
    "_geneEnemyName",
    "_geneEnemyRecNo",
    "_geneEnemyMHp",
};
static igMetaField **g_beGeneraterInfoWork_fieldHandles[] = {
    &g_beGeneraterInfoWork_isSystemFreezeMetaField,
    &g_beGeneraterInfoWork_isFreezeMetaField,
    &g_beGeneraterInfoWork_playerCountMetaField,
    &g_beGeneraterInfoWork_nokoriKazuMetaField,
    &g_beGeneraterInfoWork_enemyRamListMetaField,
    &g_beGeneraterInfoWork_genePointMetaField,
    &g_beGeneraterInfoWork_geneEnemyNameMetaField,
    &g_beGeneraterInfoWork_geneEnemyRecNoMetaField,
    &g_beGeneraterInfoWork_geneEnemyMHpMetaField,
};
static int g_beGeneraterInfoWork_fieldOffsets[] = {
    8,
    9,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
};

void beGeneraterInfoWork_InitFields(void) {
    int base;
    void *enemyRamList;
    void *meta;

    meta = (void *)g_beGeneraterInfoWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beGeneraterInfoWork_ctorTable, 9);
    enemyRamList = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)enemyRamList)->_metaObject = (int)beBaseInfoRamList_GetOrCreateMetaObject();
    ((igRefMetaField *)enemyRamList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beGeneraterInfoWork_fieldTable, g_beGeneraterInfoWork_fieldHandles, g_beGeneraterInfoWork_fieldOffsets, base);
}

