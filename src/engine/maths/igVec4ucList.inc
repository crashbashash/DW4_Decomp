igMetaObject *g_igVec4ucList_metaObject;
int g_igVec4ucList_externalStorage;

igVec4ucList *igVec4ucList_Create(igMemoryPoolView *pool) {
    igVec4ucList_EnsureRegistered();
    return (igVec4ucList *)igMetaObject_CreateInstance(g_igVec4ucList_metaObject, pool);
}

igMetaObject *igVec4ucList_GetMetaObject(void)
{
    igMetaObject *g = g_igVec4ucList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVec4ucList_EnsureRegistered();
    return g_igVec4ucList_metaObject;
}

int igVec4ucList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igVec4ucList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igVec4ucList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVec4ucList_Register);
}

CallbackArray *igVec4ucList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVec4ucList_metaObject,
        Gap::Core::igDataList::arkRegisterInternal,                  /* base class registrar (igDataList) */
        Gap::Core::igDataList::getClassMeta,
        igVec4ucList_GetMetaObjectFunction,
        "igVec4ucList",
        0x14, /* instance size */
        igVec4ucList_GetVTable,
        (igMetaObjectCallback)&igVec4ucList_InitFields_00189fa0[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igVec4ucList_GetMetaObjectFunction(void) {
    igVec4ucList_GetMetaObject();
}

void FUN_00189fa0(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igVec4ucList_metaObject);
    temp_v0 = (void **)(igMetaObject_FindFieldByName((igMetaObject *)temp_s1, "_data"));
    temp_s2 = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = (int)Gap::Math::igVec4ucMetaField::getMetaField();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&g_igVec4ucList_externalStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0);
    }
}

