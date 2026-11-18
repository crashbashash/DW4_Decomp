igMetaObject *igPsx2Clut_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Clut_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2Clut_EnsureRegistered();
    return g_igPsx2Clut_metaObject;
}

int igPsx2Clut_GetVTable(void) {
    struct Obj_154450 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igPsx2Clut_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igPsx2Clut_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2Clut_Register);
}

CallbackArray *igPsx2Clut_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2Clut_metaObject,
        igClut_Register,
        igClut_GetPublishedMetaObject,
        igPsx2Clut_GetMetaObjectFunction,
        "igPsx2Clut",
        0x28, /* instance size */
        igPsx2Clut_GetVTable,
        &igPsx2Clut_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

igMetaObject *igClut_GetPublishedMetaObject(void) {
    return g_igClut_metaObject;
}

static FieldFactory g_igPsx2Clut_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
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
    igIntMetaField_SetDefault((igMetaField *)temp_v0, -1);
    *(char *)((char *)(temp_v0) + 38) = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(meta, fieldStart + 1)) + 38) = 0;
    igMetaObject_NameFields(meta, g_igPsx2Clut_fieldTable, g_igPsx2Clut_fieldHandles, g_igPsx2Clut_fieldOffsets, fieldStart);
    *(int *)((char *)(g_igPsx2Clut_metaObject) + 64) = (int)igClut_GetMetaObjectFunction;
}

