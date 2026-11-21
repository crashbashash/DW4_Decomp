igMetaObject *g_igPsx2LongList_metaObject;

igMetaObject *igPsx2LongList_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2LongList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2LongList_EnsureRegistered();
    return g_igPsx2LongList_metaObject;
}

int igPsx2LongList_GetVTable(void) {
    struct Obj_1528a0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igPsx2LongList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igPsx2LongList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2LongList_Register);
}

CallbackArray *igPsx2LongList_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2LongList_metaObject,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        igPsx2LongList_GetMetaObjectFunction,
        "igPsx2LongList",
        0x14, /* instance size */
        igPsx2LongList_GetVTable,
        igPsx2LongList_InitFields_00152970, /* Field adder. */
        0,                                      /* extra callback-vector item (none) */
        0                                       /* zero-terminated callback-vector item list (none) */
    );
}

void igPsx2LongList_GetMetaObjectFunction(void) {
    igPsx2LongList_GetMetaObject();
}

igMetaField * g_igPsx2LongList_dataMetaField;

void FUN_00152970(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igPsx2LongList_metaObject);
    temp_v0 = (void **)(igMetaObject_FindFieldByName((igMetaObject *)temp_s1, "_data"));
    temp_s2 = ((Gap::Core::__internalNonRefCountedObjectList *)(*(int *)((char *)(temp_s1) + 40)))->find((Gap::Core::igObject *)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1_152970 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = (int)Gap::Core::igLongMetaField::getMetaField();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&g_igPsx2LongList_dataMetaField);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0);
    }
}

