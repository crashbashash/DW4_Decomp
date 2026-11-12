void FUN_00365240(int arg0) {
    FUN_003653b0();
    igMetaObject_CreateInstance(*(int *)0x5898A8, arg0);
}

void *FUN_00365280(void) {
    igMetaObject *g = g_beDataObjIntList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003653b0();
    }
    return g_beDataObjIntList_metaObject[0];
}

int beDataObjIntList_GetVTable(void) {
    Obj_3652d0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m8 = 0;
    obj.vt = &DAT_00535290[0];
    obj.m12 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00535290[0];
    obj.rel12();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel8();
    return r;
}

void FUN_003653b0(void)
{
    igMetaObject_RunStaticInit(beDataObjIntList_Register);
}

void *beDataObjIntList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjIntList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjIntList_GetMetaObject,
        beDataObjIntList_className,
        0x10, /* instance size */
        beDataObjIntList_GetVTable,
        beDataObjIntList_InitFields,
        0, /* extra callback item */
        g_beDataObjIntList_callbackList /* callback list */
    );
}

void beDataObjIntList_GetMetaObject(void)
{
    FUN_00365280();
}

void beDataObjIntList_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beDataObjIntList_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c71f8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c7200[0], &DAT_004c7208[0], &DAT_004c7210[0], temp_s2);
}

