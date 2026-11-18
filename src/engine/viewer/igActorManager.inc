igMetaObject *g_igActorManager_metaObject;
igMetaField *g_igActorManager_skelOnlysMetaField;
igMetaField *g_igActorManager_skelAndSkinsMetaField;
igMetaField *g_igActorManager_actorsMetaField;
igMetaField *g_igActorManager_paramsMetaField;
igMetaField *g_igActorManager_travFuncsMetaField;
igMetaField *g_igActorManager_actorMetasMetaField;
igMetaField *g_igActorManager_viewportMetaField;
igMetaField *g_igActorManager_skelViewportMetaField;
igMetaField *g_igActorManager_vsimMetaField;
igMetaField *g_igActorManager_referencesMetaField;

igObject *igActorManager_Create(igMemoryPoolView *pool) {
    igActorManager_EnsureRegistered();
    return igMetaObject_CreateInstance(g_igActorManager_metaObject, pool);
}

void *igActorManager_GetMetaObject(void) {
    igMetaObject *g = g_igActorManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igActorManager_EnsureRegistered();
    }
    return g_igActorManager_metaObject;
}

int igActorManager_GetVTable(void) {
    struct Obj_45e2c0 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.vt = &g_igActorManager_vtable[0];
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w13 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igActorManager_vtable[0];
    igSmartPointer_igObjectList_Destruct((igSmartPointer<igObject> *)&obj.w13, -1);
    igSmartPointer_igViewerSceneInfoManager_Destruct((igSmartPointer<igObject> *)&obj.w12, -1);
    igSmartPointer_igViewportAttr_Destruct((igSmartPointer<igObject> *)&obj.w11, -1);
    igSmartPointer_igViewportAttr_Destruct((igSmartPointer<igObject> *)&obj.w10, -1);
    igSmartPointer_igMetaObjectList_Destruct((igSmartPointer<igObject> *)&obj.w9, -1);
    igSmartPointer_igPointerList_Destruct((igSmartPointer<igObject> *)&obj.w8, -1);
    FUN_0045e420((O *)&obj.w7, -1);
    igSmartPointer_igActorList_Destruct((igSmartPointer<igObject> *)&obj.w6, -1);
    igSmartPointer_igNodeList_Destruct((igSmartPointer<igObject> *)&obj.w5, -1);
    igSmartPointer_igAppearanceList_Destruct((igSmartPointer<igObject> *)&obj.w4, -1);
    igInfoManager_Destroy((igInfoManager *)&obj, 0);
    return t;
}

O *FUN_0045e420(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        if (arg1 > 0) operator delete(arg0);
    }
    return arg0;
}

void igActorManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igActorManager_Register);
}

static igMetaObjectCallback g_igActorManager_callbackList[] = { igAppearanceList_EnsureRegistered, igNodeList_EnsureRegistered, igActorList_EnsureRegistered, igActorManagerParams_EnsureRegistered, igPointerList_EnsureRegistered, igMetaObjectList_EnsureRegistered, igViewportAttr_EnsureRegistered, igViewerSceneInfoManager_EnsureRegistered, igObjectList_EnsureRegistered, 0 };

CallbackArray *igActorManager_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igActorManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        igActorManager_GetMetaObjectFunction,
        "igActorManager",
        0x38, /* instance size */
        igActorManager_GetVTable,
        &igActorManager_InitFields,
        0, /* extra callback item */
        g_igActorManager_callbackList /* callback list */
    );
}

void igActorManager_GetMetaObjectFunction(void) {
    igActorManager_GetMetaObject();
}

static FieldFactory g_igActorManager_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igActorManager_fieldTable[] = {
    "_skelOnlys",
    "_skelAndSkins",
    "_actors",
    "_params",
    "_travFuncs",
    "_actorMetas",
    "_viewport",
    "_skelViewport",
    "_vsim",
    "_references",
};
static igMetaField **g_igActorManager_fieldHandles[] = {
    &g_igActorManager_skelOnlysMetaField,
    &g_igActorManager_skelAndSkinsMetaField,
    &g_igActorManager_actorsMetaField,
    &g_igActorManager_paramsMetaField,
    &g_igActorManager_travFuncsMetaField,
    &g_igActorManager_actorMetasMetaField,
    &g_igActorManager_viewportMetaField,
    &g_igActorManager_skelViewportMetaField,
    &g_igActorManager_vsimMetaField,
    &g_igActorManager_referencesMetaField,
};
static int g_igActorManager_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
};

void igActorManager_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s0;

    temp_s0 = g_igActorManager_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igActorManager_ctorTable, 0xA);
    temp_s2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)(igAppearanceList_GetOrCreateMetaObject());
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)(igNodeList_GetOrCreateMetaObject());
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)(igActorList_GetOrCreateMetaObject());
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igActorManagerParams_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)igPointerList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)(igMetaObjectList_GetOrCreateMetaObject());
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)igViewportAttr_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = (int)igViewportAttr_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = (int)igViewerSceneInfoManager_GetOrCreateMetaObject();
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igActorManager_fieldTable, g_igActorManager_fieldHandles, g_igActorManager_fieldOffsets, temp_s1);
}

