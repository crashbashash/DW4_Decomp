igMetaObject *FUN_00340490(void) {
    if (g_beWaterMove_metaObject[0] == 0) {
        g_beWaterMove_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beWaterMove_metaObject[0];
}

void *FUN_003404e0(void) {
    igMetaObject *g = g_beWaterMove_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003405c0();
    }
    return g_beWaterMove_metaObject[0];
}

int beWaterMove_GetVTable(void) {
    struct W o;
    int r;
    struct Ref *p;

    igObject_InitHeader(&o);
    o.vt = DAT_00539a10;
    *(int *)((char *)&o + 36) = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_00539a10;
    if (&*(int *)((char *)&o + 36) != 0) { p = *(struct Ref **)((char *)&o + 36); if (p != 0) { p->u.w = p->u.w - 1; if (p->u.b.cnt == 0) igObject_Destroy(p); } }
    return r;
}

void FUN_003405c0(void)
{
    igMetaObject_RunStaticInit(beWaterMove_Register);
}

void *beWaterMove_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWaterMove_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beWaterMove_GetMetaObject,
        beWaterMove_className,
        0x28, /* instance size */
        beWaterMove_GetVTable,
        beWaterMove_InitFields,
        0, /* extra callback item */
        g_beWaterMove_callbackList /* callback list */
    );
}

void beWaterMove_GetMetaObject(void)
{
    FUN_003404e0();
}

void beWaterMove_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beWaterMove_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3280[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00340720();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c32a0[0], &DAT_004c32c0[0], &DAT_004c32e0[0], temp_s2);
}

