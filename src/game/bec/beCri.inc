igMetaObject *g_beCri_metaObject;
igMetaField *g_beCri_systemMetaField;
igMetaField *g_beCri_execDvdErrMetaField;
igMetaField *g_beCri_requestMetaField;
igMetaField *g_beCri_hdBGMMetaField;
igMetaField *g_beCri_hdENVMetaField;
igMetaField *g_beCri_hdSEsMetaField;
igMetaField *g_beCri_infoListMetaField;
igMetaField *g_beCri_lsBinObjsMetaField;
igMetaField *g_beCri_baseVolumeMetaField;
igMetaField *g_beCri_sndfVolumeMetaField;
igMetaField *g_beCri_pauseOnetimeMetaField;
igMetaField *g_beCri_dataTypeMetaField;

void beCri_CreateInstance(int arg0) {
    beCri_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589AD8, arg0);
}

igMetaObject *beCri_GetOrCreateMetaObject(void) {
    if (g_beCri_metaObject == 0) {
        g_beCri_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beCri_metaObject;
}

void *beCri_GetMetaObject(void) {
    igMetaObject *g = g_beCri_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beCri_EnsureRegistered();
    }
    return g_beCri_metaObject;
}

int beCri_GetVTable(void) {
    struct Obj_367940 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.vt = &g_beCri_vtable[0];
    obj.w[7] = 0;
    obj.w[8] = 0;
    obj.w[9] = 0;
    obj.w[10] = 0;
    obj.w[11] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beCri_vtable[0];
    igSmartPointer_igObjectList_Destruct(&obj.w[11], -1);
    igSmartPointer_igInfoList_Destruct(&obj.w[10], -1);
    FUN_00367aa0((struct Ref **)(&obj.w[9]), (short)(-1));
    igSmartPointer_beCriHandle_Destruct((void **)(&obj.w[8]), (short)(-1));
    igSmartPointer_beCriHandle_Destruct((void **)(&obj.w[7]), (short)(-1));
    FUN_00231030(&obj, 0);
    return r;
}

void **igSmartPointer_beCriHandle_Destruct(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_00367aa0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void beCri_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCri_Register);
}

static igMetaObjectCallback g_beCri_callbackList[] = { beSystem_EnsureRegistered, beCriHandle_EnsureRegistered, beCriHandleList_EnsureRegistered, igInfoList_EnsureRegistered, igObjectList_EnsureRegistered, 0 };

void *beCri_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCri_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beCri_GetMetaObjectFunction,
        "beCri",
        0x48, /* instance size */
        beCri_GetVTable,
        beCri_InitFields,
        0, /* extra callback item */
        g_beCri_callbackList /* callback list */
    );
}

void beCri_GetMetaObjectFunction(void)
{
    beCri_GetMetaObject();
}

static FieldFactory g_beCri_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igLongMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beCri_fieldTable[] = {
    "_system",
    "_execDvdErr",
    "_request",
    "_hdBGM",
    "_hdENV",
    "_hdSEs",
    "_infoList",
    "_lsBinObjs",
    "_baseVolume",
    "_sndfVolume",
    "_pauseOnetime",
    "_dataType",
};
static igMetaField **g_beCri_fieldHandles[] = {
    &g_beCri_systemMetaField,
    &g_beCri_execDvdErrMetaField,
    &g_beCri_requestMetaField,
    &g_beCri_hdBGMMetaField,
    &g_beCri_hdENVMetaField,
    &g_beCri_hdSEsMetaField,
    &g_beCri_infoListMetaField,
    &g_beCri_lsBinObjsMetaField,
    &g_beCri_baseVolumeMetaField,
    &g_beCri_sndfVolumeMetaField,
    &g_beCri_pauseOnetimeMetaField,
    &g_beCri_dataTypeMetaField,
};
static int g_beCri_fieldOffsets[] = {
    16,
    20,
    24,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
};

void beCri_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_beCri_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beCri_ctorTable, 0xC);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)beSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)beCriHandle_GetOrCreateMetaObject();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)beCriHandle_GetOrCreateMetaObject();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)beCriHandleList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = igInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    igMetaObject_NameFields(temp_s1, g_beCri_fieldTable, g_beCri_fieldHandles, g_beCri_fieldOffsets, temp_s0);
}

