void FUN_001e5950(int arg0) {
    FUN_001e5ab0();
    igMetaObject_CreateInstance(*(int *)0x562C20, arg0);
}

igMetaObject *igDataPump_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPump_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5ab0();
    return g_igDataPump_metaObject[0];
}

int igDataPump_GetVTable(void) {
    struct Obj_1e59e0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052b950[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0052b950[0];
    FUN_001c7600(&obj.w6, -1);
    StringRef_Destruct_00130720(&obj.w5, -1);
    StringRef_Destruct_00130720(&obj.w4, -1);
    FUN_0014ec50(&obj.w3, -1);
    ObjectRef_Destruct_001363f0(&obj.w2, -1);
    return t;
}

void FUN_001e5ab0(void)
{
    igMetaObject_RunStaticInit(igDataPump_Register);
}

void igDataPump_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDataPump_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDataPump_GetMetaObject,
        igDataPump_className,
        0x1C, /* instance size */
        igDataPump_GetVTable,
        &igDataPump_InitFields,
        0, /* extra callback item */
        g_igDataPump_callbackList /* callback list */
    );
}

void thunk_igDataPump_GetMetaObject(void) {
    igDataPump_GetMetaObject();
}

void igDataPump_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igDataPump_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igDataPump_ctorTable[0], 5);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_v0) + 56) = (int)((int) g_igObject_metaObject[0]);
    *(char *)((char *)(temp_v0) + 52) = 1;
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    *(int *)((char *)(temp_s1) + 56) = igMetaField_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s1) + 38) = 0;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 0);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    *(int *)((char *)(temp_s1_2) + 56) = (int)FUN_001e5530();
    igMetaObject_NameFields(temp_s0, &g_igDataPump_fieldTable[0], &DAT_0048dc30[0], &DAT_0048dc50[0], temp_s2);
}

