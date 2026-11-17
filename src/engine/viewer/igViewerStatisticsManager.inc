void *igViewerStatisticsManager_GetMetaObject(void) {
    igMetaObject *g = g_igViewerStatisticsManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_004588e0();
    }
    return g_igViewerStatisticsManager_metaObject;
}

int igViewerStatisticsManager_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igViewerStatisticsManager_vtable[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)g_objectSystem)) + 916));
    obj.vt = &g_igViewerStatisticsManager_vtable[0];
    igSmartPointer_igMetaFieldList_Destruct(&obj.w10, -1);
    igSmartPointer_igMetaObjectList_Destruct(&obj.w9, -1);
    igSmartPointer_igStringObj_Destruct(&obj.w7, -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&obj.w6, -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&obj.w5, -1);
    FUN_004583f0(&obj.w4, -1);
    igSmartPointer_igVisualContext_Destruct(&obj.w3, -1);
    FUN_00458860((ObjectRefWord *)&obj.w2, -1);
    return t;
}

/* Deleting destructor; the deletion flag is a signed short. */
ObjectRefWord *FUN_00458860(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

void FUN_004588e0(void)
{
    igMetaObject_RunStaticInit(igViewerStatisticsManager_Register);
}

static igMetaObjectCallback g_igViewerStatisticsManager_callbackList[] = { FUN_00458bc0, igVisualContext_EnsureRegistered, FUN_0045bc10, igBoxComponent_RunStaticInit, igStringObj_EnsureRegistered, igMetaObjectList_EnsureRegistered, igMetaFieldList_EnsureRegistered, 0 };

CallbackArray *igViewerStatisticsManager_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewerStatisticsManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igViewerStatisticsManager_GetMetaObject,
        "igViewerStatisticsManager",
        0x48, /* instance size */
        igViewerStatisticsManager_GetVTable,
        &igViewerStatisticsManager_InitFields,
        0, /* extra callback item */
        g_igViewerStatisticsManager_callbackList /* callback list */
    );
}

void thunk_igViewerStatisticsManager_GetMetaObject(void) {
    igViewerStatisticsManager_GetMetaObject();
}

static FieldFactory g_igViewerStatisticsManager_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_igViewerStatisticsManager_fieldTable[] = {
    "_items",
    "_visualContext",
    "_guiFactory",
    "_menu",
    "_boxComponent",
    "_string",
    "_recordStatisticMaximum",
    "_attrMetaObjects",
    "_extraSgStatistics",
    "_attrCount",
    "_displayListAttrCount",
    "_textureAttrCount",
    "_geometryAttrCount",
    "_geometrySetAttrCount",
    "_mvmAttrCount",
};
static igMetaField **g_igViewerStatisticsManager_fieldHandles[] = {
    &g_igViewerStatisticsManager_itemsMetaField,
    &g_igViewerStatisticsManager_visualContextMetaField,
    &g_igViewerStatisticsManager_guiFactoryMetaField,
    &g_igViewerStatisticsManager_menuMetaField,
    &g_igViewerStatisticsManager_boxComponentMetaField,
    &g_igViewerStatisticsManager_stringMetaField,
    &g_igViewerStatisticsManager_recordStatisticMaximumMetaField,
    &g_igViewerStatisticsManager_attrMetaObjectsMetaField,
    &g_igViewerStatisticsManager_extraSgStatisticsMetaField,
    &g_igViewerStatisticsManager_attrCountMetaField,
    &g_igViewerStatisticsManager_displayListAttrCountMetaField,
    &g_igViewerStatisticsManager_textureAttrCountMetaField,
    &g_igViewerStatisticsManager_geometryAttrCountMetaField,
    &g_igViewerStatisticsManager_geometrySetAttrCountMetaField,
    &g_igViewerStatisticsManager_mvmAttrCountMetaField,
};
static int g_igViewerStatisticsManager_fieldOffsets[] = {
    8,
    12,
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
    56,
    60,
    64,
};

void igViewerStatisticsManager_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s1;

    temp_s1 = g_igViewerStatisticsManager_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igViewerStatisticsManager_ctorTable, 0xF);
    temp_s2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_00458ae0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)(igVisualContext_GetOrCreateMetaObject());
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_0045b8d0();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)(igBoxComponent_GetOrCreateMetaObject());
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)(igBoxComponent_GetOrCreateMetaObject());
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = igStringObj_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)(igMetaObjectList_GetOrCreateMetaObject());
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = igMetaFieldList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igViewerStatisticsManager_fieldTable, g_igViewerStatisticsManager_fieldHandles, g_igViewerStatisticsManager_fieldOffsets, temp_s0);
}

