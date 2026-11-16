igMetaObject *g_igPlane_metaObject;
igMetaField *g_igPlane_normMetaField;
igMetaField *g_igPlane_offsetMetaField;
igMetaField *g_igPlane_octantMetaField;

igMetaObject *igPlane_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igPlane_metaObject != 0) {
        ready = (g_igPlane_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00188520();
done:
    return g_igPlane_metaObject;
}

int igPlane_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igPlane_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void FUN_00188520(void)
{
    igMetaObject_RunStaticInit(igPlane_Register);
}

CallbackArray *igPlane_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPlane_metaObject,
        igVolume_Register,
        (igMetaObjectGetFunction)igVolume_GetPublishedMetaObject,
        thunk_igPlane_GetMetaObject,
        "igPlane",
        0x1C, /* instance size */
        igPlane_GetVTable,
        &igPlane_InitFields,
        thunk_FUN_0018c660, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igPlane_GetMetaObject(void) {
    igPlane_GetMetaObject();
}

static FieldFactory g_igPlane_ctorTable[] = {
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
};

static const char *g_igPlane_fieldTable[] = {
    "_norm",
    "_offset",
    "_octant",
};

static igMetaField **g_igPlane_fieldHandles[] = {
    &g_igPlane_normMetaField,
    &g_igPlane_offsetMetaField,
    &g_igPlane_octantMetaField,
};

static int g_igPlane_fieldOffsets[] = {
    8,
    20,
    24,
};

void igPlane_InitFields(void) {
    igMetaObject *temp_s0;
    int temp_s1;
    void *f;

    temp_s0 = g_igPlane_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igPlane_ctorTable, 3);
    f = (void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2);
    *(int *)((char *)f + 52) = (int)(&FUN_001869e0);
    igMetaObject_NameFields(temp_s0, g_igPlane_fieldTable, g_igPlane_fieldHandles, g_igPlane_fieldOffsets, temp_s1);
}

void thunk_FUN_0018c660(void) {
    FUN_0018c660();
}

