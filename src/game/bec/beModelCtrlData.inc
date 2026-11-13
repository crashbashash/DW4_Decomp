igMetaObject *FUN_003567d0(void) {
    if (g_beModelCtrlData_metaObject[0] == 0) {
        g_beModelCtrlData_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beModelCtrlData_metaObject[0];
}

igMetaObject *FUN_00356820(void) {
    igMetaObject *g = g_beModelCtrlData_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_00356950();
done:
    return g_beModelCtrlData_metaObject[0];
}

int beModelCtrlData_GetVTable(void) {
    Obj_356870 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.s = 0;
    obj.vt = &DAT_005371c0[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_005371c0[0];
    obj.releaseRef();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.releaseStr();
    return r;
}

void FUN_00356950(void)
{
    igMetaObject_RunStaticInit(beModelCtrlData_Register);
}

void *beModelCtrlData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlData_GetMetaObject,
        beModelCtrlData_className,
        0x10, /* instance size */
        beModelCtrlData_GetVTable,
        beModelCtrlData_InitFields,
        0, /* extra callback item */
        g_beModelCtrlData_callbackList /* callback list */
    );
}

void beModelCtrlData_GetMetaObject(void)
{
    FUN_00356820();
}

void beModelCtrlData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlData_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beModelCtrlData_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be100();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beModelCtrlData_fieldTable[0], &DAT_004c58d8[0], &DAT_004c58e0[0], temp_s2);
}

int beModelCtrl_GetMessageEnum(void) {
    if (DAT_00588e50[0] == 0) {
        DAT_00588e50[0] = igMetaEnum_Create(&text_MsgAction[0], &DAT_004c58f0[0], &DAT_004c5980[0], 0x21);
    }
    return DAT_00588e50[0];
}

