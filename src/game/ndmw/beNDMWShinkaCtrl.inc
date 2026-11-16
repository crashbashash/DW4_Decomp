igMetaObject *g_beNDMWShinkaCtrl_metaObject;
igMetaField *g_beNDMWShinkaCtrl_messengerMetaField;
igMetaField *g_beNDMWShinkaCtrl_gameRamMetaField;
igMetaField *g_beNDMWShinkaCtrl_playerNoMetaField;
igMetaField *g_beNDMWShinkaCtrl_playerParameterMetaField;
igMetaField *g_beNDMWShinkaCtrl_dBShinkaMetaField;
igMetaField *g_beNDMWShinkaCtrl_listMetaField;

igMetaObject *beNDMWShinkaCtrl_GetOrCreateMetaObject(void) {
    if (g_beNDMWShinkaCtrl_metaObject == 0) {
        g_beNDMWShinkaCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWShinkaCtrl_metaObject;
}

void *beNDMWShinkaCtrl_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWShinkaCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShinkaCtrl_EnsureRegistered();
    }
    return g_beNDMWShinkaCtrl_metaObject;
}

int beNDMWShinkaCtrl_GetVTable(void) {
    union U_3c9520 u;
    int temp_s2;
    S_ref * q1;
    S_ref * q0;
    S_ref * q2;
    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    u.vt = (int)(&g_beNDMWShinkaCtrl_vtable[0]);
    q0 = (S_ref *)&u.b[20];
    *(int *)q0 = 0;
    q1 = (S_ref *)&u.b[24];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[28];
    *(int *)q2 = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)(&g_beNDMWShinkaCtrl_vtable[0]);
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
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
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s2;
}

void beNDMWShinkaCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShinkaCtrl_Register);
}

static igMetaObjectCallback g_beNDMWShinkaCtrl_callbackList[] = { beMessenger_EnsureRegistered, beNDMWGameRam_EnsureRegistered, beDataObjList_EnsureRegistered, beDataBase_EnsureRegistered, beNDMWShinkaObjectList_EnsureRegistered, 0 };

void *beNDMWShinkaCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShinkaCtrl_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWShinkaCtrl_GetMetaObject,
        "beNDMWShinkaCtrl",
        0x20, /* instance size */
        beNDMWShinkaCtrl_GetVTable,
        beNDMWShinkaCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWShinkaCtrl_callbackList /* callback list */
    );
}

void beNDMWShinkaCtrl_GetMetaObject(void)
{
    beNDMWShinkaCtrl_ResolveMetaObject();
}

static FieldFactory g_beNDMWShinkaCtrl_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWShinkaCtrl_fieldTable[] = {
    "_messenger",
    "_gameRam",
    "_playerNo",
    "_playerParameter",
    "_dBShinka",
    "_list",
};
static igMetaField **g_beNDMWShinkaCtrl_fieldHandles[] = {
    &g_beNDMWShinkaCtrl_messengerMetaField,
    &g_beNDMWShinkaCtrl_gameRamMetaField,
    &g_beNDMWShinkaCtrl_playerNoMetaField,
    &g_beNDMWShinkaCtrl_playerParameterMetaField,
    &g_beNDMWShinkaCtrl_dBShinkaMetaField,
    &g_beNDMWShinkaCtrl_listMetaField,
};
static int g_beNDMWShinkaCtrl_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
};

void beNDMWShinkaCtrl_InitFields(void) {
    int base;
    void *list;
    void *dBShinka;
    void *playerParameter;
    void *gameRam;
    void *messenger;
    igMetaObject *meta;

    meta = g_beNDMWShinkaCtrl_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShinkaCtrl_ctorTable, 6);
    messenger = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)messenger)->_metaObject = beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    gameRam = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)gameRam)->_metaObject = (int)beNDMWGameRam_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)gameRam)->_refCounted = 0;
    playerParameter = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)playerParameter)->_metaObject = beDataObjList_GetOrCreateMetaObject();
    dBShinka = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)dBShinka)->_metaObject = beDataBase_GetOrCreateMetaObject();
    list = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)list)->_metaObject = (int)beNDMWShinkaObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)list)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWShinkaCtrl_fieldTable, g_beNDMWShinkaCtrl_fieldHandles, g_beNDMWShinkaCtrl_fieldOffsets, base);
}

