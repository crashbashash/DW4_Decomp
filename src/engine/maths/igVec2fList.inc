igMetaObject *g_igVec2fList_metaObject;
int g_igVec2fList_externalStorage;

void FUN_0018a2d0(int arg0) {
    FUN_0018a3a0();
    igMetaObject_CreateInstance((igMetaObject *)g_igVec2fList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igVec2fList_GetMetaObject(void)
{
    igMetaObject *g = g_igVec2fList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0018a3a0();
    return g_igVec2fList_metaObject;
}

int igVec2fList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igVec2fList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_0018a3a0(void)
{
    igMetaObject_RunStaticInit(igVec2fList_Register);
}

CallbackArray *igVec2fList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVec2fList_metaObject,
        igDataList_Register,                 /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igVec2fList_GetMetaObject,
        "igVec2fList",
        0x14, /* instance size */
        igVec2fList_GetVTable,
        (igMetaObjectCallback)&igVec2fList_InitFields_0018a430[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igVec2fList_GetMetaObject(void) {
    igVec2fList_GetMetaObject();
}

void FUN_0018a430(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igVec2fList_metaObject);
    temp_v0 = (void **)(igMetaObject_FindFieldByName((igMetaObject *)temp_s1, "_data"));
    temp_s2 = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_00187dd0();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&g_igVec2fList_externalStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0);
    }
}

