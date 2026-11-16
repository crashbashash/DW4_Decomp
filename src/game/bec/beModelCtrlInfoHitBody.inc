igMetaObject *g_beModelCtrlInfoHitBody_metaObject;
igMetaField *g_beModelCtrlInfoHitBody_isFirstMetaField;
igMetaField *g_beModelCtrlInfoHitBody_calcTimeMetaField;
igMetaField *g_beModelCtrlInfoHitBody_countMetaField;
igMetaField *g_beModelCtrlInfoHitBody_orgAABoxListMetaField;
igMetaField *g_beModelCtrlInfoHitBody_AABoxMinListMetaField;
igMetaField *g_beModelCtrlInfoHitBody_AABoxMaxListMetaField;
igMetaField *g_beModelCtrlInfoHitBody_AABoxListMetaField;

void beModelCtrlInfoHitBody_Create(int allocator) {
    beModelCtrlInfoHitBody_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588B00, allocator);
}

igMetaObject *beModelCtrlInfoHitBody_GetOrCreateMetaObject(void) {
    if (g_beModelCtrlInfoHitBody_metaObject == 0) {
        g_beModelCtrlInfoHitBody_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beModelCtrlInfoHitBody_metaObject;
}

void *beModelCtrlInfoHitBody_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlInfoHitBody_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlInfoHitBody_EnsureRegistered();
    }
    return g_beModelCtrlInfoHitBody_metaObject;
}

int beModelCtrlInfoHitBody_GetVTable(void) {
    union U u;
    int temp_s0;
    igObject *q0;
    igObject *q1;
    igObject *q2;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beModelCtrlInfoHitBody_vtable[0];
    q2 = (igObject *)&u.b[32];
    *(int *)q2 = 0;
    q1 = (igObject *)&u.b[36];
    *(int *)q1 = 0;
    q0 = (igObject *)&u.b[40];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beModelCtrlInfoHitBody_vtable[0];
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        if (q0 != 0) {
            q0->_refCount = (int)q0->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(igObject **)q1;
        if (q1 != 0) {
            q1->_refCount = (int)q1->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(igObject **)q2;
        if (q2 != 0) {
            q2->_refCount = (int)q2->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q2->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    return temp_s0;
}

void beModelCtrlInfoHitBody_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoHitBody_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoHitBody_callbackList[] = { igAABoxList_EnsureRegistered, igVec3fList_EnsureRegistered, 0 };

void *beModelCtrlInfoHitBody_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoHitBody_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlInfoHitBody_GetMetaObjectFunction,
        "beModelCtrlInfoHitBody",
        0x30, /* instance size */
        beModelCtrlInfoHitBody_GetVTable,
        beModelCtrlInfoHitBody_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoHitBody_callbackList /* callback list */
    );
}

void beModelCtrlInfoHitBody_GetMetaObjectFunction(void)
{
    beModelCtrlInfoHitBody_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoHitBody_ctorTable[] = {
    igBoolMetaField_Create,
    igLongMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beModelCtrlInfoHitBody_fieldTable[] = {
    "_isFirst",
    "_calcTime",
    "_count",
    "_orgAABoxList",
    "_AABoxMinList",
    "_AABoxMaxList",
    "_AABoxList",
};
static igMetaField **g_beModelCtrlInfoHitBody_fieldHandles[] = {
    &g_beModelCtrlInfoHitBody_isFirstMetaField,
    &g_beModelCtrlInfoHitBody_calcTimeMetaField,
    &g_beModelCtrlInfoHitBody_countMetaField,
    &g_beModelCtrlInfoHitBody_orgAABoxListMetaField,
    &g_beModelCtrlInfoHitBody_AABoxMinListMetaField,
    &g_beModelCtrlInfoHitBody_AABoxMaxListMetaField,
    &g_beModelCtrlInfoHitBody_AABoxListMetaField,
};
static int g_beModelCtrlInfoHitBody_fieldOffsets[] = {
    8,
    16,
    24,
    28,
    32,
    36,
    40,
};

void beModelCtrlInfoHitBody_InitFields(void) {
    int base;
    void *orgAABoxList;
    void *AABoxMinList;
    void *AABoxMaxList;
    void *AABoxList;
    void *meta;

    meta = (void *)g_beModelCtrlInfoHitBody_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlInfoHitBody_ctorTable, 7);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base), 1);
    orgAABoxList = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)orgAABoxList)->_metaObject = igAABoxList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)orgAABoxList)->_refCounted = 0;
    AABoxMinList = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)AABoxMinList)->_metaObject = igVec3fList_GetOrCreateMetaObject();
    ((igRefMetaField *)AABoxMinList)->_construct = 1;
    AABoxMaxList = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)AABoxMaxList)->_metaObject = igVec3fList_GetOrCreateMetaObject();
    ((igRefMetaField *)AABoxMaxList)->_construct = 1;
    AABoxList = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)AABoxList)->_metaObject = igAABoxList_GetOrCreateMetaObject();
    ((igRefMetaField *)AABoxList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beModelCtrlInfoHitBody_fieldTable, g_beModelCtrlInfoHitBody_fieldHandles, g_beModelCtrlInfoHitBody_fieldOffsets, base);
}

