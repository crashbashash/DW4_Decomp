igMetaObject *g_beHitLandResultData_metaObject;
igMetaField *g_beHitLandResultData_infoNameMetaField;
igMetaField *g_beHitLandResultData_ramNoMetaField;

beHitLandResultData *beHitLandResultData_Create(int allocator) {
    beHitLandResultData_EnsureRegistered();
    return (beHitLandResultData *)igMetaObject_CreateInstance(g_beHitLandResultData_metaObject, (igMemoryPoolView *)allocator);
}

void *beHitLandResultData_GetMetaObject(void) {
    unsigned char b;
    if (g_beHitLandResultData_metaObject != 0) {
        b = (g_beHitLandResultData_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beHitLandResultData_EnsureRegistered();
done:
    return g_beHitLandResultData_metaObject;
}

int beHitLandResultData_GetVTable(void) {
    beHitLandResultData obj;
    int vtable;
    char **infoNameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beHitLandResultData_vtable[0];
    infoNameSlot = (char **)&obj._infoName;
    *infoNameSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beHitLandResultData_vtable[0];
    igStringRef_Release(infoNameSlot);
    return vtable;
}

void beHitLandResultData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beHitLandResultData_Register);
}

CallbackArray *beHitLandResultData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beHitLandResultData_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beHitLandResultData_GetMetaObjectFunction,
        "beHitLandResultData",
        0x58, /* instance size */
        beHitLandResultData_GetVTable,
        beHitLandResultData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beHitLandResultData_GetMetaObjectFunction(void)
{
    beHitLandResultData_GetMetaObject();
}

static FieldFactory g_beHitLandResultData_ctorTable[] = {
    igStringMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beHitLandResultData_fieldTable[] = {
    "_infoName",
    "_ramNo",
};
static igMetaField **g_beHitLandResultData_fieldHandles[] = {
    &g_beHitLandResultData_infoNameMetaField,
    &g_beHitLandResultData_ramNoMetaField,
};
static int g_beHitLandResultData_fieldOffsets[] = {
    8,
    12,
};

void beHitLandResultData_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beHitLandResultData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beHitLandResultData_ctorTable, 2);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base), "");
    igMetaObject_NameFields(meta, g_beHitLandResultData_fieldTable, g_beHitLandResultData_fieldHandles, g_beHitLandResultData_fieldOffsets, base);
}

