void *beMessengerArgData_Create(void *allocator){beMessengerArgData_EnsureRegistered();return ((void *)igMetaObject_CreateInstance((void *)g_beMessengerArgData_metaObject[0],allocator));}

igMetaObject *FUN_00358dc0(void) {
    if (g_beMessengerArgData_metaObject[0] == 0) {
        g_beMessengerArgData_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMessengerArgData_metaObject[0];
}

igMetaObject *FUN_00358e10(void) {
    if (g_beMessengerArgData_metaObject[0] == 0 || !isValid(g_beMessengerArgData_metaObject[0])) beMessengerArgData_EnsureRegistered();
    return g_beMessengerArgData_metaObject[0];
}

int beMessengerArgData_GetVTable(void) {
    struct Obj_358e60 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536ca0[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00536ca0[0];
    ObjectRef_Destruct_001c6460(&obj.w11, -1);
    FUN_0014aa70(&obj.w10, -1);
    FUN_001998f0(&obj.w9, -1);
    FUN_001374b0(&obj.w8, -1);
    FUN_00195190(&obj.w7, -1);
    FUN_001354b0(&obj.w6, -1);
    ObjectRef_Destruct_00150eb0(&obj.w5, -1);
    FUN_00226990(&obj.w4, -1);
    StringRef_Destruct_00130720(&obj.w3, -1);
    return t;
}

void beMessengerArgData_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerArgData_Register);}

void *beMessengerArgData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerArgData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beMessengerArgData_GetMetaObject,
        beMessengerArgData_className,
        0x30, /* instance size */
        beMessengerArgData_GetVTable,
        beMessengerArgData_InitFields,
        0, /* extra callback item */
        g_beMessengerArgData_callbackList /* callback list */
    );
}

void beMessengerArgData_GetMetaObject(void)
{
    FUN_00358e10();
}

void beMessengerArgData_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMessengerArgData_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beMessengerArgData_ctorTable[0], 0xA);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_002cb110();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_002c9780();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_002ca680();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0018a0a0();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_001899a0();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_002b9120();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beMessengerArgData_fieldTable[0], &DAT_004c5ee0[0], &DAT_004c5f10[0], temp_s1);
}

