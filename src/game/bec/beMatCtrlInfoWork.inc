void FUN_00359480(int arg0) {
    FUN_00359640();
    igMetaObject_CreateInstance(*(int *)0x5890C0, arg0);
}

igMetaObject *FUN_003594c0(void) {
    if (g_beMatCtrlInfoWork_metaObject[0] == 0) {
        g_beMatCtrlInfoWork_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMatCtrlInfoWork_metaObject[0];
}

void *FUN_00359510(void) {
    igMetaObject *g = g_beMatCtrlInfoWork_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00359640();
    }
    return g_beMatCtrlInfoWork_metaObject[0];
}

int beMatCtrlInfoWork_GetVTable(void) {
    Obj_359560 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536c40[0];
    obj.m8 = 0;
    obj.m12 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00536c40[0];
    obj.rel12();
    obj.rel8();
    return r;
}

void FUN_00359640(void)
{
    igMetaObject_RunStaticInit(beMatCtrlInfoWork_Register);
}

void *beMatCtrlInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMatCtrlInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beMatCtrlInfoWork_GetMetaObject,
        beMatCtrlInfoWork_className,
        0x10, /* instance size */
        beMatCtrlInfoWork_GetVTable,
        beMatCtrlInfoWork_InitFields,
        0, /* extra callback item */
        g_beMatCtrlInfoWork_callbackList /* callback list */
    );
}

void beMatCtrlInfoWork_GetMetaObject(void)
{
    FUN_00359510();
}

void beMatCtrlInfoWork_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMatCtrlInfoWork_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beMatCtrlInfoWork_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002cb110();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002c8980();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beMatCtrlInfoWork_fieldTable[0], &DAT_004c5fe8[0], &DAT_004c5ff0[0], temp_s2);
}

