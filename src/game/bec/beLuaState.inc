void FUN_0035aa20(int arg0) {
    FUN_0035abe0();
    igMetaObject_CreateInstance(*(int *)0x5891B0, arg0);
}

igMetaObject *FUN_0035aa60(void) {
    if (g_beLuaState_metaObject[0] == 0) {
        g_beLuaState_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beLuaState_metaObject[0];
}

void *FUN_0035aab0(void) {
    igMetaObject *g = g_beLuaState_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035abe0();
    }
    return g_beLuaState_metaObject[0];
}

int beLuaState_GetVTable(void) {
    Obj_35ab00 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &g_igLuaState_vtable[0];
    obj.r1 = 0;
    obj.r2 = 0;
    obj.vt = &DAT_0053aa60[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_igLuaState_vtable[0];
    obj.rel2();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel1();
    return r;
}

void FUN_0035abe0(void)
{
    igMetaObject_RunStaticInit(beLuaState_Register);
}

void *beLuaState_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLuaState_metaObject,
        igLuaState_Register,
        igLuaState_GetPublishedMetaObject,
        beLuaState_GetMetaObject,
        beLuaState_className,
        0x18, /* instance size */
        beLuaState_GetVTable,
        beLuaState_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beLuaState_GetMetaObject(void)
{
    FUN_0035aab0();
}

int FUN_0035ac90(void) {
    return g_igLuaState_metaObject[0];
}

void beLuaState_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beLuaState_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beLuaState_ctorTable[0], 1);
    igMetaObject_NameFields(temp_s0, &g_beLuaState_fieldTable[0], &DAT_004c6248[0], &DAT_004c6250[0], temp_s1);
}

