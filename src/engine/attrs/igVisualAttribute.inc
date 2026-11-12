int FUN_00130310(void) {
    if (DAT_0055ebd0[0] == 0) {
        DAT_0055ebd0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055ebd0[0];
}

igMetaObject *igVisualAttribute_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualAttribute_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001303b0();
    return g_igVisualAttribute_metaObject[0];
}

void FUN_001303b0(void)
{
    igMetaObject_RunStaticInit(igVisualAttribute_Register);
}

void igVisualAttribute_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igVisualAttribute_metaObject,
        igAttr_Register,
        igAttr_GetPublishedMetaObject,
        thunk_igVisualAttribute_GetMetaObject,
        igVisualAttribute_className,
        0xC, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igVisualAttribute_GetMetaObject(void) {
    igVisualAttribute_GetMetaObject();
}

int FUN_00130430(void) {
    return DAT_0055f468[0];
}

