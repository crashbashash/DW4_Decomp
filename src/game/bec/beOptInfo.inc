igMetaObject *FUN_0034d080(void)
{
    igMetaObject *g = g_beOptInfo_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0034d160();
    return g_beOptInfo_metaObject[0];
}

int beOptInfo_GetVTable(void) {
    Obj_34d0d0 o;
    int r;

    igObject_InitHeader(&o);
    o.f8 = 0;
    o.vt = &DAT_00538590[0];
    o.a = 0;
    o.b = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_00538590[0];
    StringRef_Destruct_00130720(&o.b, -1);
    StringRef_Destruct_00130720(&o.a, -1);
    FUN_00131b20(&o, 0);
    return r;
}

void FUN_0034d160(void)
{
    igMetaObject_RunStaticInit(beOptInfo_Register);
}

void *beOptInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beOptInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beOptInfo_GetMetaObject,
        beOptInfo_className,
        0x24, /* instance size */
        beOptInfo_GetVTable,
        beOptInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beOptInfo_GetMetaObject(void)
{
    FUN_0034d080();
}

void beOptInfo_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beOptInfo_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c48c0[0], 4);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)), 0);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3)), 0);
    igMetaObject_NameFields(temp_s0, &DAT_004c48d0[0], &DAT_004c48e0[0], &DAT_004c48f0[0], temp_s1);
}

