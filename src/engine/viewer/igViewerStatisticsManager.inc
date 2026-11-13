void *igViewerStatisticsManager_GetMetaObject(void) {
    igMetaObject *g = g_igViewerStatisticsManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_004588e0();
    }
    return g_igViewerStatisticsManager_metaObject[0];
}

int igViewerStatisticsManager_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_005425b0[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)g_objectSystem[0])) + 916));
    obj.vt = &DAT_005425b0[0];
    FUN_0014e420(&obj.w10, -1);
    FUN_0013a880(&obj.w9, -1);
    FUN_001489a0(&obj.w7, -1);
    FUN_0025a2b0(&obj.w6, -1);
    FUN_0025a2b0(&obj.w5, -1);
    FUN_004583f0(&obj.w4, -1);
    FUN_00130140(&obj.w3, -1);
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
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void FUN_004588e0(void)
{
    igMetaObject_RunStaticInit(igViewerStatisticsManager_Register);
}

void igViewerStatisticsManager_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerStatisticsManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igViewerStatisticsManager_GetMetaObject,
        igViewerStatisticsManager_className,
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

    temp_s1 = (void *)g_igViewerStatisticsManager_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d08c0[0], 0xF);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_00458ae0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0014a040();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_0045b8d0();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00452340();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00452340();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_002b9540();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_002c8e50();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_002c8b30();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004d0900[0], &DAT_004d0940[0], &DAT_004d0980[0], temp_s0);
}

