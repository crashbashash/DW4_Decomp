void beDataObjObjectList_Create(int arg0) {
    FUN_00364660();
    igMetaObject_CreateInstance(*(int *)0x589858, arg0);
}

void *FUN_00364530(void) {
    igMetaObject *g = g_beDataObjObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00364660();
    }
    return g_beDataObjObjectList_metaObject[0];
}

int beDataObjObjectList_GetVTable(void) {
    Obj_364580 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.r1 = 0;
    obj.vt = &DAT_00535470[0];
    obj.r2 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00535470[0];
    obj.rel2();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel1();
    return r;
}

void FUN_00364660(void)
{
    igMetaObject_RunStaticInit(beDataObjObjectList_Register);
}

void *beDataObjObjectList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjObjectList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjObjectList_GetMetaObject,
        beDataObjObjectList_className,
        0x10, /* instance size */
        beDataObjObjectList_GetVTable,
        beDataObjObjectList_InitFields,
        0, /* extra callback item */
        g_beDataObjObjectList_callbackList /* callback list */
    );
}

void beDataObjObjectList_GetMetaObject(void)
{
    FUN_00364530();
}

void beDataObjObjectList_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beDataObjObjectList_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beDataObjObjectList_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beDataObjObjectList_fieldTable[0], &DAT_004c7150[0], &DAT_004c7158[0], temp_s2);
}

