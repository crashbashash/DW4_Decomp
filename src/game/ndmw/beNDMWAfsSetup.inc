igMetaObject *g_beNDMWAfsSetup_metaObject;
igMetaField *g_beNDMWAfsSetup_infoListMetaField;
igMetaField *g_beNDMWAfsSetup_customMenuMetaField;
igMetaField *g_beNDMWAfsSetup_subMenuMetaField;
igMetaField *g_beNDMWAfsSetup_subMenuHolderMetaField;

void beNDMWAfsSetup_CreateInstance(int arg0) {
    beNDMWAfsSetup_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWAfsSetup_metaObject, arg0);
}

igMetaObject *beNDMWAfsSetup_GetOrCreateMetaObject(void) {
    if (g_beNDMWAfsSetup_metaObject == 0) {
        g_beNDMWAfsSetup_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWAfsSetup_metaObject;
}

void *beNDMWAfsSetup_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWAfsSetup_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWAfsSetup_EnsureRegistered();
    }
    return g_beNDMWAfsSetup_metaObject;
}

int beNDMWAfsSetup_GetVTable(void) {
    struct Obj_3caee0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &g_beNDMWAfsSetup_vtable[0];
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWAfsSetup_vtable[0];
    FUN_003cafa0((igObject **)&obj.w7, (short)(-1));
    GameMain_igSmartPointer_igObject_Destruct(&obj.w6, -1);
    GameMain_igSmartPointer_igObject_Destruct(&obj.w5, -1);
    igSmartPointer_igInfoList_Destruct(&obj.w4, -1);
    FUN_00231030(&obj, 0);
    return t;
}

igObject **FUN_003cafa0(igObject **arg0, short arg1) {
    igObject *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->_refCount = temp_a0->_refCount - 1;
            if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void beNDMWAfsSetup_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetup_Register);
}

static igMetaObjectCallback g_beNDMWAfsSetup_callbackList[] = { igInfoList_EnsureRegistered, igBoxComponent_RunStaticInit, igGuiComponent_EnsureRegistered, 0 };

void *beNDMWAfsSetup_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWAfsSetup_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beNDMWAfsSetup_GetMetaObject,
        "beNDMWAfsSetup",
        0x20, /* instance size */
        beNDMWAfsSetup_GetVTable,
        beNDMWAfsSetup_InitFields,
        0, /* extra callback item */
        g_beNDMWAfsSetup_callbackList /* callback list */
    );
}

void beNDMWAfsSetup_GetMetaObject(void)
{
    beNDMWAfsSetup_ResolveMetaObject();
}

static FieldFactory g_beNDMWAfsSetup_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWAfsSetup_fieldTable[] = {
    "_infoList",
    "_customMenu",
    "_subMenu",
    "_subMenuHolder",
};
static igMetaField **g_beNDMWAfsSetup_fieldHandles[] = {
    &g_beNDMWAfsSetup_infoListMetaField,
    &g_beNDMWAfsSetup_customMenuMetaField,
    &g_beNDMWAfsSetup_subMenuMetaField,
    &g_beNDMWAfsSetup_subMenuHolderMetaField,
};
static int g_beNDMWAfsSetup_fieldOffsets[] = {
    16,
    20,
    24,
    28,
};

void beNDMWAfsSetup_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWAfsSetup_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWAfsSetup_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igBoxComponent_GetOrCreateMetaObject();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = igBoxComponent_GetOrCreateMetaObject();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = igGuiComponent_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beNDMWAfsSetup_fieldTable, g_beNDMWAfsSetup_fieldHandles, g_beNDMWAfsSetup_fieldOffsets, temp_s2);
}

