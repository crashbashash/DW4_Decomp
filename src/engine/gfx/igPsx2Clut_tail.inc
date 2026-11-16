igMetaObject *igPsx2Clut_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Clut_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00154490();
    return g_igPsx2Clut_metaObject;
}

int igPsx2Clut_GetVTable(void) {
    struct Obj_154450 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igPsx2Clut_vtable[0];
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
        &g_igPsx2Clut_metaObject,
        igClut_Register,
        igClut_GetPublishedMetaObject,
        thunk_igPsx2Clut_GetMetaObject,
        "igPsx2Clut",
        0x28, /* instance size */
        igPsx2Clut_GetVTable,
        &igPsx2Clut_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

igMetaObject *FUN_00154510(void) {
    return g_igClut_metaObject;
}

static FieldFactory g_igPsx2Clut_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_igPsx2Clut_fieldTable[] = {
    "_id",
    "_refCount",
};
static igMetaField **g_igPsx2Clut_fieldHandles[] = {
    &g_igPsx2Clut_idMetaField,
    &g_igPsx2Clut_refCountMetaField,
};
static int g_igPsx2Clut_fieldOffsets[] = {
    32,
    36,
};

void igPsx2Clut_InitFields(void) {
    int fieldStart;
    void *temp_v0;
    igMetaObject *meta;
    meta = g_igPsx2Clut_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igPsx2Clut_ctorTable, 2);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    igIntMetaField_SetDefault(temp_v0, -1);
    *(char *)((char *)(temp_v0) + 38) = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(meta, fieldStart + 1)) + 38) = 0;
    igMetaObject_NameFields(meta, g_igPsx2Clut_fieldTable, g_igPsx2Clut_fieldHandles, g_igPsx2Clut_fieldOffsets, fieldStart);
    *(int *)((char *)(g_igPsx2Clut_metaObject) + 64) = (int)thunk_igClut_GetMetaObject;
}

