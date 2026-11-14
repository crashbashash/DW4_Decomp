void *beLoadingNode_ResolveMetaObject(void) {
    igMetaObject *g = g_beLoadingNode_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034e710();
    }
    return g_beLoadingNode_metaObject[0];
}

int beLoadingNode_GetVTable(void) {
    struct Obj_34e620 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.fC = 0;
    obj.f10 = 0;
    obj.f1C = 0;
    obj.vt = (&DAT_00538110[0]);
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&DAT_00538110[0]);
    FUN_0034e690((int **)&obj, (long long)0);
    return temp_s0;
}

int **FUN_0034e690(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_005381b0[0];
        if (arg0 != 0) {
            *arg0 = &DAT_00528dd0[0];
            FUN_001958f0((char *)arg0 + 0x1C, -1);
            FUN_00195970(arg0, 0);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_Memory_FreeBuffer(arg0);
        }
    }
    return arg0;
}

void FUN_0034e710(void)
{
    igMetaObject_RunStaticInit(beLoadingNode_Register);
}

void *beLoadingNode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLoadingNode_metaObject,
        beNodeAnim_Register,
        beNodeAnim_GetPublishedMetaObject,
        beLoadingNode_GetMetaObject,
        beLoadingNode_className,
        0x80, /* instance size */
        beLoadingNode_GetVTable,
        beLoadingNode_InitFields,
        FUN_0034e850, /* extra callback item */
        0 /* callback list */
    );
}

void beLoadingNode_GetMetaObject(void)
{
    beLoadingNode_ResolveMetaObject();
}

igMetaObject *FUN_0034e7d0(void) {
    return g_beNodeAnim_metaObject[0];
}

void beLoadingNode_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beLoadingNode_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beLoadingNode_ctorTable[0], 2);
    igMetaObject_NameFields(temp_s0, &g_beLoadingNode_fieldTable[0], &DAT_004c4a60[0], &DAT_004c4a68[0], temp_s1);
}

void FUN_0034e850(void)
{
    beLoadingNode_RegisterTraversalFunction();
}

