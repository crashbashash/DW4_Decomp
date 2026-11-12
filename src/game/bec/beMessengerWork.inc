void *beMessengerWork_Create(void *allocator){beMessengerWork_EnsureRegistered();return ((void *)igMetaObject_CreateInstance((void *)g_beMessengerWork_metaObject[0],allocator));}

void *FUN_003580b0(void) {
    igMetaObject *g = g_beMessengerWork_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMessengerWork_EnsureRegistered();
    }
    return g_beMessengerWork_metaObject[0];
}

int beMessengerWork_GetVTable(void) {
    beMessengerWork obj;
    int t;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&DAT_00536f10[0];
    obj._groupName = 0;
    obj._infoName = 0;
    obj._message = 0;
    obj._findRamNoList = 0;
    obj._findRamList = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&DAT_00536f10[0];
    FUN_0033ec00((igObject **)&obj._findRamList, (short)(-1));
    ObjectRef_Destruct_00150eb0(&obj._findRamNoList, -1);
    StringRef_Destruct_00130720(&obj._message, -1);
    StringRef_Destruct_00130720(&obj._infoName, -1);
    StringRef_Destruct_00130720(&obj._groupName, -1);
    return t;
}

void beMessengerWork_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerWork_Register);}

void *beMessengerWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beMessengerWork_GetMetaObject,
        beMessengerWork_className,
        0x20, /* instance size */
        beMessengerWork_GetVTable,
        beMessengerWork_InitFields,
        0, /* extra callback item */
        g_beMessengerWork_callbackList /* callback list */
    );
}

void beMessengerWork_GetMetaObject(void)
{
    FUN_003580b0();
}

void beMessengerWork_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMessengerWork_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5ce0[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)beBaseInfoRamList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c5d00[0], &DAT_004c5d20[0], &DAT_004c5d40[0], temp_s2);
}

