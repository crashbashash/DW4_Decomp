igMetaObject *g_beModelCtrlInfoHitBody_metaObject;
igMetaField *g_beModelCtrlInfoHitBody_isFirstMetaField;
igMetaField *g_beModelCtrlInfoHitBody_calcTimeMetaField;
igMetaField *g_beModelCtrlInfoHitBody_countMetaField;
igMetaField *g_beModelCtrlInfoHitBody_orgAABoxListMetaField;
igMetaField *g_beModelCtrlInfoHitBody_AABoxMinListMetaField;
igMetaField *g_beModelCtrlInfoHitBody_AABoxMaxListMetaField;
igMetaField *g_beModelCtrlInfoHitBody_AABoxListMetaField;

void beModelCtrlInfoHitBody_Create(int arg0) {
    beModelCtrlInfoHitBody_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588B00, arg0);
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
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beModelCtrlInfoHitBody_vtable[0];
    q2 = (S_ref *)&u.b[32];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[36];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[40];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beModelCtrlInfoHitBody_vtable[0];
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
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
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
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_beModelCtrlInfoHitBody_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beModelCtrlInfoHitBody_ctorTable, 7);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s1, temp_s0), 1);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igAABoxList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igVec3fList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igVec3fList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igAABoxList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields(temp_s1, g_beModelCtrlInfoHitBody_fieldTable, g_beModelCtrlInfoHitBody_fieldHandles, g_beModelCtrlInfoHitBody_fieldOffsets, temp_s0);
}

