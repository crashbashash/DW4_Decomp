void FUN_0034fd00(int arg0) {
    FUN_0034fe80();
    igMetaObject_CreateInstance(*(int *)0x588860, arg0);
}

igMetaObject *FUN_0034fd40(void) {
    if (g_beModelCtrlNode2_metaObject[0] == 0) {
        g_beModelCtrlNode2_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beModelCtrlNode2_metaObject[0];
}

void *beModelCtrlNode2_ResolveMetaObject(void) {
    bool ok;
    if (g_beModelCtrlNode2_metaObject[0] == 0) goto make;
    ok = !!(g_beModelCtrlNode2_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_0034fe80();
done:;
    return g_beModelCtrlNode2_metaObject[0];
}

int beModelCtrlNode2_GetVTable(void) {
    ModelCtrlNode2View node;
    return *(int *)((char *)&node + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_0034fe80(void)
{
    igMetaObject_RunStaticInit(beModelCtrlNode2_Register);
}

void *beModelCtrlNode2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlNode2_metaObject,
        igTransform_Register,
        igTransform_GetPublishedMetaObject,
        beModelCtrlNode2_GetMetaObject,
        beModelCtrlNode2_className,
        0x90, /* instance size */
        beModelCtrlNode2_GetVTable,
        beModelCtrlNode2_InitFields,
        FUN_00350000, /* extra callback item */
        g_beModelCtrlNode2_callbackList /* callback list */
    );
}

void beModelCtrlNode2_GetMetaObject(void)
{
    beModelCtrlNode2_ResolveMetaObject();
}

void beModelCtrlNode2_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlNode2_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4d50[0], 4);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1.0f);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    *(int *)((char *)(temp_s1) + 56) = FUN_0013af00();
    *(char *)((char *)(temp_s1) + 52) = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c4d60[0], &DAT_004c4d70[0], &DAT_004c4d80[0], temp_s2);
}

void FUN_00350000(void)
{
    beModelCtrlNode2_RegisterTraversalFunction();
}

