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
    FUN_001e4620();
done:
    return g_igMersenneTwisterRandomNumber_metaObject;
}

int igMersenneTwisterRandomNumber_GetVTable(void) {
    struct Obj_1e45e0 obj;
    igObject_InitHeader(&obj);
    obj.vt = &g_igMersenneTwisterRandomNumber_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001e4620(void)
{
    igMetaObject_RunStaticInit(igMersenneTwisterRandomNumber_Register);
}

void igMersenneTwisterRandomNumber_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMersenneTwisterRandomNumber_metaObject,
        igRandomNumber_Register,
        igRandomNumber_GetPublishedMetaObject,
        thunk_igMersenneTwisterRandomNumber_GetMetaObject,
        "igMersenneTwisterRandomNumber",
        0x9CC, /* instance size */
        igMersenneTwisterRandomNumber_GetVTable,
        &igMersenneTwisterRandomNumber_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

igMetaObject *FUN_001e46a0(void) {
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
    firstField = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igMersenneTwisterRandomNumber_ctorTable, 2);
    f = (struct F *)igMetaObject_GetFieldAt(meta, firstField + 1);
    f->f52 = 0x270;
    igMetaObject_NameFields(meta, g_igMersenneTwisterRandomNumber_fieldTable, g_igMersenneTwisterRandomNumber_fieldHandles, g_igMersenneTwisterRandomNumber_fieldOffsets, firstField);
}

