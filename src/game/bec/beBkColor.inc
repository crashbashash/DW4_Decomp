igMetaObject *g_beBkColor_metaObject;
igMetaField *g_beBkColor_isClearMetaField;

void beBkColor_CreateInstance(int allocator) {
    beBkColor_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589D10, allocator);
}

igMetaObject *beBkColor_GetOrCreateMetaObject(void) {
    if (g_beBkColor_metaObject == 0) {
        g_beBkColor_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beBkColor_metaObject;
}

void *beBkColor_GetMetaObject(void) {
    igMetaObject *g = g_beBkColor_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beBkColor_EnsureRegistered();
    }
    return g_beBkColor_metaObject;
}

int beBkColor_GetVTable(void) {
    union U_369ea0 u;
    int temp_s1;
    void **q2;
    void **q3;
    int *temp_a1;
    int temp_v0_2;
    void *temp_a0;
    void *temp_v1_2;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&g_beBaseInfoManager_vtable[0]);
    q3 = &u.p[6];
    *q3 = 0;
    u.w[0] = (int)(&g_beBkColor_vtable[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beBaseInfoManager_vtable[0]);
    if (q3 != 0) {
        temp_a0 = *q3;
        if (temp_a0 != 0) {
            ((igObject *)temp_a0)->_refCount = (int)((int) (((igObject *)temp_a0)->_refCount - 1));
            if (((unsigned long long) ((long long) (int) ((igObject *)temp_a0)->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    if (q2 != 0) {
        temp_v1_2 = *q2;
        if (temp_v1_2 != 0) {
            temp_a1 = (int *)((char *)temp_v1_2 - 8);
            temp_v0_2 = *(int *)((char *)(temp_v1_2) - 4) - 1;
            *(int *)((char *)(temp_v1_2) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s1;
}

void beBkColor_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBkColor_Register);
}

void *beBkColor_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beBkColor_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beBkColor_GetMetaObjectFunction,
        "beBkColor",
        0x24, /* instance size */
        beBkColor_GetVTable,
        beBkColor_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beBkColor_GetMetaObjectFunction(void)
{
    beBkColor_GetMetaObject();
}

static FieldFactory g_beBkColor_ctorTable[] = {
    igBoolMetaField_Create,
};
static const char *g_beBkColor_fieldTable[] = {
    "_isClear",
};
static igMetaField **g_beBkColor_fieldHandles[] = {
    &g_beBkColor_isClearMetaField,
};
static int g_beBkColor_fieldOffsets[] = {
    32,
};

void beBkColor_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beBkColor_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beBkColor_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beBkColor_fieldTable, g_beBkColor_fieldHandles, g_beBkColor_fieldOffsets, base);
}

