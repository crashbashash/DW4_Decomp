igMetaObject *FUN_00134940(void) {
    if (g_igPolygonModeAttr_metaObject[0] == 0) {
        g_igPolygonModeAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igPolygonModeAttr_metaObject[0];
}

igMetaObject *igPolygonModeAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igPolygonModeAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00134a20();
    return g_igPolygonModeAttr_metaObject[0];
}

int igPolygonModeAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523170[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00134a20(void)
{
    igMetaObject_RunStaticInit(igPolygonModeAttr_Register);
}

void igPolygonModeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPolygonModeAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igPolygonModeAttr_GetMetaObject,
        igPolygonModeAttr_className,
        0x10, /* instance size */
        igPolygonModeAttr_GetVTable,
        &igPolygonModeAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igPolygonModeAttr_GetMetaObject(void) {
    igPolygonModeAttr_GetMetaObject();
}

void igPolygonModeAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)g_igPolygonModeAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igPolygonModeAttr_ctorTable[0], 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    igEnumMetaField_SetDefaultValue(temp_v0, &DAT_00486120[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_001495c0);
    igMetaObject_NameFields(temp_s0, &g_igPolygonModeAttr_fieldTable[0], &DAT_00486110[0], &DAT_00486118[0], temp_s2);
}

