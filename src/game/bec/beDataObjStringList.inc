void FUN_003647c0(int arg0) {
    FUN_00364930();
    igMetaObject_CreateInstance(*(int *)0x589868, arg0);
}

void *FUN_00364800(void) {
    bool ok;
    if (g_beDataObjStringList_metaObject[0] == 0) goto make;
    ok = !!(g_beDataObjStringList_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_00364930();
done:;
    return g_beDataObjStringList_metaObject[0];
}

int beDataObjStringList_GetVTable(void) {
    Obj_364850 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m8 = 0;
    obj.vt = &DAT_00535410[0];
    obj.m12 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00535410[0];
    obj.rel12();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel8();
    return r;
}

void FUN_00364930(void)
{
    igMetaObject_RunStaticInit(beDataObjStringList_Register);
}

void *beDataObjStringList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjStringList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjStringList_GetMetaObject,
        beDataObjStringList_className,
        0x10, /* instance size */
        beDataObjStringList_GetVTable,
        beDataObjStringList_InitFields,
        0, /* extra callback item */
        g_beDataObjStringList_callbackList /* callback list */
    );
}

void beDataObjStringList_GetMetaObject(void)
{
    FUN_00364800();
}

void beDataObjStringList_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beDataObjStringList_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7168[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002b9120();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c7170[0], &DAT_004c7178[0], &DAT_004c7180[0], temp_s2);
}

