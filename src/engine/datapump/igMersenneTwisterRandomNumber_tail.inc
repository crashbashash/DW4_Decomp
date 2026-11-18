igMetaObject *g_igMersenneTwisterRandomNumber_metaObject;
igMetaField *g_igMersenneTwisterRandomNumber_mtiMetaField;
igMetaField *g_igMersenneTwisterRandomNumber_mtMetaField;

igMetaObject *igMersenneTwisterRandomNumber_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igMersenneTwisterRandomNumber_metaObject != 0) {
        ready = (g_igMersenneTwisterRandomNumber_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igMersenneTwisterRandomNumber_EnsureRegistered();
done:
    return g_igMersenneTwisterRandomNumber_metaObject;
}

int igMersenneTwisterRandomNumber_GetVTable(void) {
    struct Obj_1e45e0 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igMersenneTwisterRandomNumber_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igMersenneTwisterRandomNumber_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMersenneTwisterRandomNumber_Register);
}

CallbackArray *igMersenneTwisterRandomNumber_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMersenneTwisterRandomNumber_metaObject,
        igRandomNumber_Register,
        igRandomNumber_GetPublishedMetaObject,
        igMersenneTwisterRandomNumber_GetMetaObjectFunction,
        "igMersenneTwisterRandomNumber",
        0x9CC, /* instance size */
        igMersenneTwisterRandomNumber_GetVTable,
        &igMersenneTwisterRandomNumber_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

igMetaObject *igRandomNumber_GetPublishedMetaObject(void) {
    return g_igRandomNumber_metaObject;
}

static FieldFactory g_igMersenneTwisterRandomNumber_ctorTable[] = {
    igIntMetaField_Create,
    igUnsignedIntArrayMetaField_Create,
};
static const char *g_igMersenneTwisterRandomNumber_fieldTable[] = {
    "_mti",
    "_mt",
};
static igMetaField **g_igMersenneTwisterRandomNumber_fieldHandles[] = {
    &g_igMersenneTwisterRandomNumber_mtiMetaField,
    &g_igMersenneTwisterRandomNumber_mtMetaField,
};
static int g_igMersenneTwisterRandomNumber_fieldOffsets[] = {
    8,
    12,
};

void igMersenneTwisterRandomNumber_InitFields(void) {
    igMetaObject *meta;
    int firstField;
    struct F *f;

    meta = g_igMersenneTwisterRandomNumber_metaObject;
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMersenneTwisterRandomNumber_ctorTable, 2);
    f = (struct F *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 1);
    f->f52 = 0x270;
    igMetaObject_NameFields((igMetaObject *)meta, g_igMersenneTwisterRandomNumber_fieldTable, g_igMersenneTwisterRandomNumber_fieldHandles, g_igMersenneTwisterRandomNumber_fieldOffsets, firstField);
}

