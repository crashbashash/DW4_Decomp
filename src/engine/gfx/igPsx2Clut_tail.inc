igMetaObject *igPsx2Clut_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Clut_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00154490();
    return g_igPsx2Clut_metaObject[0];
}

int igPsx2Clut_GetVTable(void) {
    struct Obj_154450 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00526a60[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00154490(void)
{
    igMetaObject_RunStaticInit(igPsx2Clut_Register);
}

void igPsx2Clut_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2Clut_metaObject,
        igClut_Register,
        igClut_GetPublishedMetaObject,
        thunk_igPsx2Clut_GetMetaObject,
        igPsx2Clut_className,
        0x28, /* instance size */
        igPsx2Clut_GetVTable,
        &igPsx2Clut_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

igMetaObject *FUN_00154510(void) {
    return g_igClut_metaObject[0];
}

void igPsx2Clut_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s0;
    temp_s0 = (void *)(g_igPsx2Clut_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igPsx2Clut_ctorTable[0], 2);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002ea4b0(temp_v0, -1);
    *(char *)((char *)(temp_v0) + 38) = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &g_igPsx2Clut_fieldTable[0], &DAT_0048a0e8[0], &DAT_0048a0f0[0], temp_s2);
    *(int *)((char *)(g_igPsx2Clut_metaObject[0]) + 64) = (int)thunk_igClut_GetMetaObject;
}

