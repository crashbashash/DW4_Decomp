void *beNodeAnim_ResolveMetaObject(void) {
    igMetaObject *g = g_beNodeAnim_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034e930();
    }
    return g_beNodeAnim_metaObject[0];
}

int beNodeAnim_GetVTable(void) {
    struct Obj_34e8c0 o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f12 = 0;
    o.f16 = 0;
    o.f28 = 0;
    o.vt = &DAT_005381b0[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_005381b0[0];
    
    FUN_00195a90(&o, 0);
    return r;
}

void FUN_0034e930(void)
{
    igMetaObject_RunStaticInit(beNodeAnim_Register);
}

void *beNodeAnim_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNodeAnim_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beNodeAnim_GetMetaObject,
        beNodeAnim_className,
        0x70, /* instance size */
        beNodeAnim_GetVTable,
        beNodeAnim_InitFields,
        FUN_0034eaf0, /* extra callback item */
        0 /* callback list */
    );
}

void beNodeAnim_GetMetaObject(void)
{
    beNodeAnim_ResolveMetaObject();
}

void beNodeAnim_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNodeAnim_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNodeAnim_ctorTable[0], 0xA);
    igLongMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s1), 0x13DE4355);
    igLongMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), 0x77359400);
    igLongMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), ((long long)0xEE6B << 0x10) | 0x2800);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4), 1);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6), 1.0f);
    igMetaObject_NameFields(temp_s0, &g_beNodeAnim_fieldTable[0], &DAT_004c4ad0[0], &DAT_004c4b00[0], temp_s1);
}

void FUN_0034eaf0(void)
{
    beNodeAnim_RegisterTraversalFunction();
}

