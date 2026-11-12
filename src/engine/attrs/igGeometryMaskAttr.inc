void FUN_00137070(int arg0) {
    FUN_00137140();
    igMetaObject_CreateInstance(*(int *)0x55F148, arg0);
}

igMetaObject *igGeometryMaskAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryMaskAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00137140();
    return g_igGeometryMaskAttr_metaObject[0];
}

int igGeometryMaskAttr_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523840[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00137140(void)
{
    igMetaObject_RunStaticInit(igGeometryMaskAttr_Register);
}

void igGeometryMaskAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGeometryMaskAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igGeometryMaskAttr_GetMetaObject,
        igGeometryMaskAttr_className,
        0x10, /* instance size */
        igGeometryMaskAttr_GetVTable,
        &igGeometryMaskAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igGeometryMaskAttr_GetMetaObject(void) {
    igGeometryMaskAttr_GetMetaObject();
}

void igGeometryMaskAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f148[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486530[0], 1);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), -1);
    igMetaObject_NameFields(temp_s0, &DAT_00486538[0], &DAT_00486540[0], &DAT_00486548[0], temp_s1);
}

