igMetaObject *g_beNumVerInsideData_metaObject;
igMetaField *g_beNumVerInsideData_indexMetaField;
igMetaField *g_beNumVerInsideData_kindMetaField;

int FUN_0034de60(int arg0) {
    FUN_0034df30();
    return igMetaObject_CreateInstance(*(int *)0x5886B0, arg0);
}

void *FUN_0034dea0(void) {
    bool ok;
    if (g_beNumVerInsideData_metaObject == 0) goto make;
    ok = !!(g_beNumVerInsideData_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_0034df30();
done:;
    return g_beNumVerInsideData_metaObject;
}

int beNumVerInsideData_GetVTable(void) {
    struct Obj_34def0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538330[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0034df30(void)
{
    igMetaObject_RunStaticInit(beNumVerInsideData_Register);
}

void *beNumVerInsideData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNumVerInsideData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNumVerInsideData_GetMetaObject,
        "beNumVerInsideData",
        0x10, /* instance size */
        beNumVerInsideData_GetVTable,
        beNumVerInsideData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNumVerInsideData_GetMetaObject(void)
{
    FUN_0034dea0();
}

static FieldFactory g_beNumVerInsideData_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNumVerInsideData_fieldTable[] = {
    "_index",
    "_kind",
};
static igMetaField **g_beNumVerInsideData_fieldHandles[] = {
    &g_beNumVerInsideData_indexMetaField,
    &g_beNumVerInsideData_kindMetaField,
};
static int g_beNumVerInsideData_fieldOffsets[] = {
    8,
    12,
};

void beNumVerInsideData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNumVerInsideData_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNumVerInsideData_ctorTable, 2);
    igMetaObject_NameFields(temp_s0, g_beNumVerInsideData_fieldTable, g_beNumVerInsideData_fieldHandles, g_beNumVerInsideData_fieldOffsets, temp_s1);
}

