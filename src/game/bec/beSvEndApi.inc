igMetaObject *g_beSvEndApi_metaObject;
int g_beSvEndApi_orderTypeStorage;

void beSvEndApi_Create(int arg0) {
    beSvEndApi_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5881E0, arg0);
}

void *beSvEndApi_GetMetaObject(void) {
    igMetaObject *g = g_beSvEndApi_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvEndApi_EnsureRegistered();
    }
    return g_beSvEndApi_metaObject;
}

int beSvEndApi_GetVTable(void) {
    Obj_348680 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &g_beSaveApi_vtable[0];
    obj.r1 = 0;
    obj.r2 = 0;
    obj.r3 = 0;
    obj.vt = &g_beSvEndApi_vtable[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beSaveApi_vtable[0];
    obj.rel(&obj.r3);
    obj.rel(&obj.r2);
    obj.rel(&obj.r1);
    return r;
}

void beSvEndApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvEndApi_Register);
}

void *beSvEndApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvEndApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvEndApi_GetMetaObjectFunction,
        "beSvEndApi",
        0x40, /* instance size */
        beSvEndApi_GetVTable,
        beSvEndApi_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvEndApi_GetMetaObjectFunction(void)
{
    beSvEndApi_GetMetaObject();
}

void beSvEndApi_InitFields(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s1;
    void *temp_v0_2;

    temp_s1 = (void *)(((void * *)&g_beSvEndApi_metaObject)[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_orderType"));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igIntMetaField_SetDefault(temp_v0_2, 0xB);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&g_beSvEndApi_orderTypeStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_v0_2);
    ((SR *)temp_v0_2)->f4 = ((SR *)temp_v0_2)->f4 - 1;
    if ((((SR *)temp_v0_2)->f4 & 0x7FFFFF) == 0) {
        igObject_Destroy(temp_v0_2);
    }
}

