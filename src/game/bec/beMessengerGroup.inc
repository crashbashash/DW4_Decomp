void *beMessengerGroup_Create(void *allocator){beMessengerGroup_EnsureRegistered();return ((void *)igMetaObject_CreateInstance((void *)g_beMessengerGroup_metaObject[0],allocator));}

void *FUN_00358520(void) {
    igMetaObject *g = g_beMessengerGroup_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMessengerGroup_EnsureRegistered();
    }
    return g_beMessengerGroup_metaObject[0];
}

int beMessengerGroup_GetVTable(void) {
    struct Obj_358570 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00536e40[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00536e40[0];
    FUN_0033ec00((igObject **)&obj.w5, (short)(-1));
    ObjectRef_Destruct_00150eb0(&obj.w4, -1);
    ObjectRef_Destruct_001c6460(&obj.w3, -1);
    FUN_00131bc0(&obj, 0);
    return t;
}

void beMessengerGroup_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerGroup_Register);}

void *beMessengerGroup_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerGroup_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beMessengerGroup_GetMetaObject,
        beMessengerGroup_className,
        0x18, /* instance size */
        beMessengerGroup_GetVTable,
        beMessengerGroup_InitFields,
        0, /* extra callback item */
        g_beMessengerGroup_callbackList /* callback list */
    );
}

void beMessengerGroup_GetMetaObject(void)
{
    FUN_00358520();
}

void beMessengerGroup_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMessengerGroup_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5d70[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002b9120();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)beBaseInfoRamList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c5d80[0], &DAT_004c5d90[0], &DAT_004c5da0[0], temp_s2);
}

