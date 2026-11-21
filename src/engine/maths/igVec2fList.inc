igMetaObject *g_igVec2fList_metaObject;
int g_igVec2fList_externalStorage;

igVec2fList *igVec2fList_Create(igMemoryPoolView *pool) {
    igVec2fList_EnsureRegistered();
    return (igVec2fList *)igMetaObject_CreateInstance(g_igVec2fList_metaObject, pool);
}

igMetaObject *igVec2fList_GetMetaObject(void)
{
    igMetaObject *g = g_igVec2fList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVec2fList_EnsureRegistered();
    return g_igVec2fList_metaObject;
}

int igVec2fList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igVec2fList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igVec2fList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVec2fList_Register);
}

CallbackArray *igVec2fList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVec2fList_metaObject,
        Gap::Core::igDataList::arkRegisterInternal,                 /* base class registrar (igDataList) */
        Gap::Core::igDataList::getClassMeta,
        igVec2fList_GetMetaObjectFunction,
        "igVec2fList",
        0x14, /* instance size */
        igVec2fList_GetVTable,
        (igMetaObjectCallback)&igVec2fList_InitFields_0018a430[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igVec2fList_GetMetaObjectFunction(void) {
    igVec2fList_GetMetaObject();
}

void FUN_0018a430(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igVec2fList_metaObject);
    temp_v0 = (void **)(igMetaObject_FindFieldByName((igMetaObject *)temp_s1, "_data"));
    temp_s2 = ((Gap::Core::__internalNonRefCountedObjectList *)(*(int *)((char *)(temp_s1) + 40)))->find((Gap::Core::igObject *)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = (int)Gap::Math::igVec2fMetaField::getMetaField();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&g_igVec2fList_externalStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0);
    }
}

