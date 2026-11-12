void igTimeAttr_CreateInstance(int arg0) {
    FUN_00131040();
    igMetaObject_CreateInstance(*(int *)0x55EC80, arg0);
}

igMetaObject *FUN_00130f60(void) {
    if (g_igTimeAttr_metaObject[0] == 0) {
        g_igTimeAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igTimeAttr_metaObject[0];
}

igMetaObject *igTimeAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igTimeAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00131040();
    return g_igTimeAttr_metaObject[0];
}

int igTimeAttr_GetVTable(void) {
    union U_131000 u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00522750[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_00131040(void)
{
    igMetaObject_RunStaticInit(igTimeAttr_Register);
}

void igTimeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTimeAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTimeAttr_GetMetaObject,
        igTimeAttr_className,
        0x18, /* instance size */
        igTimeAttr_GetVTable,
        &igTimeAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTimeAttr_GetMetaObject(void) {
    igTimeAttr_GetMetaObject();
}

void igTimeAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igTimeAttr_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485a90[0], 1);
    FUN_002ebc00(igMetaObject_GetFieldAt(temp_s0, temp_s1), 0);
    igMetaObject_NameFields(temp_s0, &DAT_00485a98[0], &DAT_00485aa0[0], &DAT_00485aa8[0], temp_s1);
}

