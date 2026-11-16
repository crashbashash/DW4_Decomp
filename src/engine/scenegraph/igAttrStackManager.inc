igMetaObject *g_igAttrStackManager_metaObject;
igMetaField *g_igAttrStackManager_numAttrStacksMetaField;
igMetaField *g_igAttrStackManager_attrStacksMetaField;
igMetaField *g_igAttrStackManager_attrDefaultsMetaField;
igMetaField *g_igAttrStackManager_attrIncrementalUpdateListMetaField;
igMetaField *g_igAttrStackManager_attrRootUpdateListMetaField;
igMetaField *g_igAttrStackManager_nextAttrUpdateListMetaField;
igMetaField *g_igAttrStackManager_lightAttrAddrsMetaField;
igMetaField *g_igAttrStackManager_lightAttrStackAddrsMetaField;
igMetaField *g_igAttrStackManager_updateLightAttrsMetaField;
igMetaField *g_igAttrStackManager_popProcDataMetaField;
igMetaField *g_igAttrStackManager_capabilityManagerMetaField;
igMetaField *g_igAttrStackManager_defaultManagerMetaField;
igMetaField *g_igAttrStackManager_simpleLightMgrMetaField;
igMetaField *g_igAttrStackManager_lightDisableAttrPoolMetaField;
igMetaField *g_igAttrStackManager_stackChangedMetaField;
igMetaField *g_igAttrStackManager_attrStackIndexTableMetaField;
igMetaField *g_igAttrStackManager_attrStackIndexTableSizeMetaField;

igMetaObject *FUN_001a5330(void) {
    if (g_igAttrStackManager_metaObject == 0) {
        g_igAttrStackManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAttrStackManager_metaObject;
}

igMetaObject *igAttrStackManager_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrStackManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a5640();
    return g_igAttrStackManager_metaObject;
}

int igAttrStackManager_GetVTable(void) {
    struct Obj_1a53d0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &g_igAttrStackManager_vtable[0];
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w16 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_igAttrStackManager_vtable[0];
    FUN_001a55c0((void * *)&obj.w16, -1);
    FUN_0019ff90((struct T_19fde0 * *)&obj.w14, -1);
    FUN_0019ff10((struct R * *)&obj.w13, -1);
    FUN_001380e0(&obj.w11, -1);
    igSmartPointer_igIntList_Destruct(&obj.w10, -1);
    FUN_001380e0(&obj.w9, -1);
    igSmartPointer_igIntList_Destruct(&obj.w8, -1);
    igSmartPointer_igIntList_Destruct(&obj.w7, -1);
    igSmartPointer_igIntList_Destruct(&obj.w6, -1);
    FUN_0013bfe0(&obj.w5, -1);
    FUN_001a5540((void * *)&obj.w4, -1);
    return t;
}

void **FUN_001a5540(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_001a55c0(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_001a5640(void)
{
    igMetaObject_RunStaticInit(igAttrStackManager_Register);
}

static igMetaObjectCallback g_igAttrStackManager_callbackList[] = { FUN_001a59e0, igAttrList_EnsureRegistered, igIntList_EnsureRegistered, igNonRefCountedAttrList_EnsureRegistered, igIntList_EnsureRegistered, FUN_0014fde0, FUN_0013ab50, FUN_0019a650, 0 };

void igAttrStackManager_Register(void) {
    SceneGraphLibrary_MarkRegistered();  /* Shared set-once latch run before every registration of this family. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAttrStackManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAttrStackManager_GetMetaObject,
        "igAttrStackManager",
        0x4C, /* instance size */
        igAttrStackManager_GetVTable,
        &igAttrStackManager_InitFields,
        FUN_001a58e0,                         /* static-initializer callback item (appended on fresh configuration) */
        g_igAttrStackManager_callbackList  /* 0-terminated dependency-callback list */
    );
}

void thunk_igAttrStackManager_GetMetaObject(void) {
    igAttrStackManager_GetMetaObject();
}

static FieldFactory g_igAttrStackManager_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igRawRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igMemoryRefMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_igAttrStackManager_fieldTable[] = {
    "_numAttrStacks",
    "_attrStacks",
    "_attrDefaults",
    "_attrIncrementalUpdateList",
    "_attrRootUpdateList",
    "_nextAttrUpdateList",
    "_lightAttrAddrs",
    "_lightAttrStackAddrs",
    "_updateLightAttrs",
    "_popProcData",
    "_capabilityManager",
    "_defaultManager",
    "_simpleLightMgr",
    "_lightDisableAttrPool",
    "_stackChanged",
    "_attrStackIndexTable",
    "_attrStackIndexTableSize",
};
static igMetaField **g_igAttrStackManager_fieldHandles[] = {
    &g_igAttrStackManager_numAttrStacksMetaField,
    &g_igAttrStackManager_attrStacksMetaField,
    &g_igAttrStackManager_attrDefaultsMetaField,
    &g_igAttrStackManager_attrIncrementalUpdateListMetaField,
    &g_igAttrStackManager_attrRootUpdateListMetaField,
    &g_igAttrStackManager_nextAttrUpdateListMetaField,
    &g_igAttrStackManager_lightAttrAddrsMetaField,
    &g_igAttrStackManager_lightAttrStackAddrsMetaField,
    &g_igAttrStackManager_updateLightAttrsMetaField,
    &g_igAttrStackManager_popProcDataMetaField,
    &g_igAttrStackManager_capabilityManagerMetaField,
    &g_igAttrStackManager_defaultManagerMetaField,
    &g_igAttrStackManager_simpleLightMgrMetaField,
    &g_igAttrStackManager_lightDisableAttrPoolMetaField,
    &g_igAttrStackManager_stackChangedMetaField,
    &g_igAttrStackManager_attrStackIndexTableMetaField,
    &g_igAttrStackManager_attrStackIndexTableSizeMetaField,
};
static int g_igAttrStackManager_fieldOffsets[] = {
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
    8,
    68,
    72,
};

void igAttrStackManager_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_11;
    void *temp_s2_12;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s0;

    temp_s0 = (void *)g_igAttrStackManager_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igAttrStackManager_ctorTable, 0x11);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_001a5900();
    ((igObjectRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igAttrList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_0013ad40();
    ((igObjectRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7)));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8)));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_0013ad40();
    ((igObjectRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA)));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_0014fd40();
    temp_s2_10 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB)));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_0013aab0();
    temp_s2_11 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD)));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = (int)FUN_0019a570();
    ((igObjectRefMetaField *)temp_s2_11)->_construct = 1;
    temp_s2_12 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF)));
    ((igMemoryRefMetaField *)temp_s2_12)->_memType = igIntMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)temp_s2_12)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s2_12)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s2_12)->_releaseOnReset = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igAttrStackManager_fieldTable, g_igAttrStackManager_fieldHandles, g_igAttrStackManager_fieldOffsets, temp_s1);
    igMetaObject_AddExitCallback(&thunk_FUN_001afb00);
}

void FUN_001a58e0(void) {
    igMetaObject_AddRegistrationCallback(&FUN_001afb60);
}

void thunk_FUN_001afb00(void) {
    FUN_001afb00();
}

