igGeometry *igGeometry_CreateInstance(int allocator) {
    igGeometry_EnsureRegistered();
    return (igGeometry *)igMetaObject_CreateInstance((igMetaObject *)g_igGeometry_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igGeometry_GetOrCreateMetaObject(void) {
    if (g_igGeometry_metaObject == 0) {
        g_igGeometry_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGeometry_metaObject;
}

igMetaObject *igGeometry_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometry_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGeometry_EnsureRegistered();
    return g_igGeometry_metaObject;
}

int igGeometry_GetVTable(void) {
    struct Obj_19fb80 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.vt = &g_igGeometry_vtable[0];
    obj.w10 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj.vt = &g_igGeometry_vtable[0];
    FUN_0019d0a0((void * *)&obj.w10, -1);
    FUN_0019c0e0((struct S_19c0e0 *)&obj, 0);
    return t;
}

void igGeometry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((CallbackArray * (*)())igGeometry_Register);
}

static igMetaObjectCallback g_igGeometry_callbackList[] = { FUN_00133f80, 0 };

CallbackArray *igGeometry_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGeometry_metaObject,
        igAttrSet_Register,
        igAttrSet_GetPublishedMetaObject,
        thunk_igGeometry_GetMetaObject,
        "igGeometry",
        0x2C, /* instance size */
        igGeometry_GetVTable,
        FUN_0019fca0,
        FUN_0019fdd0, /* extra callback item */
        g_igGeometry_callbackList /* callback list */
    );
}

void thunk_igGeometry_GetMetaObject(void) {
    igGeometry_GetMetaObject();
}

static FieldFactory g_igGeometry_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igGeometry_fieldTable[] = {
    "_renderList",
};
static igMetaField **g_igGeometry_fieldHandles[] = {
    &g_igGeometry_renderListMetaField,
};
static int g_igGeometry_fieldOffsets[] = {
    40,
};

void FUN_0019fca0(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0_2;

    temp_s1 = (void *)(g_igGeometry_metaObject);
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igGeometry_ctorTable, 1);
    temp_v0 = (void **)(((void * *)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, "_trigger")));
    temp_s3 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igBoolMetaField_SetDefaultValue((igMetaField *)temp_v0_2, 1);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&g_igGeometry_triggerMetaField);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s3, (igMetaField *)temp_v0_2);
    *(int *)((char *)(temp_v0_2) + 4) = (int)((int) (*(int *)((char *)(temp_v0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_v0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_v0_2);
    }
    temp_s0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2)));
    *(int *)((char *)(temp_s0) + 56) = FUN_00133e50();
    *(char *)((char *)(temp_s0) + 38) = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igGeometry_fieldTable, g_igGeometry_fieldHandles, g_igGeometry_fieldOffsets, temp_s2);
}

void thunk_FUN_001c51d0(void) {
    FUN_001c51d0();
}

