void beMovie_CreateInstance(int arg0) {
    FUN_0034f0a0();
    igMetaObject_CreateInstance(*(int *)0x588788, arg0);
}

igMetaObject *FUN_0034ef70(void) {
    if (g_beMovie_metaObject[0] == 0) {
        g_beMovie_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beMovie_metaObject[0];
}

igMetaObject *FUN_0034efc0(void)
{
    igMetaObject *g = g_beMovie_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0034f0a0();
    return g_beMovie_metaObject[0];
}

int beMovie_GetVTable(void) {
    struct Obj_34f010 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_0053bad0[0];
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053bad0[0];
    StringRef_Destruct_00130720(&obj.w9, -1);
    FUN_003369f0(&obj.w8, -1);
    FUN_0033f5e0((O_33f5e0 *)&obj, (short)0);
    return t;
}

void FUN_0034f0a0(void)
{
    igMetaObject_RunStaticInit(beMovie_Register);
}

void *beMovie_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMovie_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beMovie_GetMetaObject,
        beMovie_className,
        0x28, /* instance size */
        beMovie_GetVTable,
        beMovie_InitFields,
        0, /* extra callback item */
        g_beMovie_callbackList /* callback list */
    );
}

void beMovie_GetMetaObject(void)
{
    FUN_0034efc0();
}

void beMovie_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMovie_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beMovie_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00336c10();
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 0);
    igMetaObject_NameFields(temp_s0, &g_beMovie_fieldTable[0], &DAT_004c4ba8[0], &DAT_004c4bb0[0], temp_s2);
}

