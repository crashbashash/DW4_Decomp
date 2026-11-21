igMetaObject *g_beNDMWLoadIntf2MakeChr_metaObject;
int g_beNDMWLoadIntf2MakeChr_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2MakeChr_chaSelDegiMetaField;
igMetaField *g_beNDMWLoadIntf2MakeChr_degiNameMetaField;
igMetaField *g_beNDMWLoadIntf2MakeChr_nameCurMetaField;
igMetaField *g_beNDMWLoadIntf2MakeChr_mojiSelPointMetaField;

beNDMWLoadIntf2MakeChr *beNDMWLoadIntf2MakeChr_Create(int allocator) {
    beNDMWLoadIntf2MakeChr_EnsureRegistered();
    return (beNDMWLoadIntf2MakeChr *)igMetaObject_CreateInstance(g_beNDMWLoadIntf2MakeChr_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWLoadIntf2MakeChr_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWLoadIntf2MakeChr_metaObject != 0) {
        ready = (g_beNDMWLoadIntf2MakeChr_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    beNDMWLoadIntf2MakeChr_EnsureRegistered();
done:
    return g_beNDMWLoadIntf2MakeChr_metaObject;
}

int beNDMWLoadIntf2MakeChr_GetVTable(void) {
    beNDMWLoadIntf2MakeChr obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2MakeChr_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWLoadIntf2MakeChr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2MakeChr_Register);
}

CallbackArray *beNDMWLoadIntf2MakeChr_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2MakeChr_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2MakeChr_GetMetaObject,
        "beNDMWLoadIntf2MakeChr",
        0x3c, /* instance size */
        beNDMWLoadIntf2MakeChr_GetVTable,
        beNDMWLoadIntf2MakeChr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWLoadIntf2MakeChr_GetMetaObject(void)
{
    beNDMWLoadIntf2MakeChr_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2MakeChr_ctorTable[] = {
    igIntMetaField_Create,
    igCharArrayMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2MakeChr_fieldTable[] = {
    "_chaSelDegi",
    "_degiName",
    "_nameCur",
    "_mojiSelPoint",
};
static igMetaField **g_beNDMWLoadIntf2MakeChr_fieldHandles[] = {
    &g_beNDMWLoadIntf2MakeChr_chaSelDegiMetaField,
    &g_beNDMWLoadIntf2MakeChr_degiNameMetaField,
    &g_beNDMWLoadIntf2MakeChr_nameCurMetaField,
    &g_beNDMWLoadIntf2MakeChr_mojiSelPointMetaField,
};
static int g_beNDMWLoadIntf2MakeChr_fieldOffsets[] = {
    48,
    16,
    52,
    56,
};

void beNDMWLoadIntf2MakeChr_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    igMetaObject *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (igMetaObject *)(g_beNDMWLoadIntf2MakeChr_metaObject);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLoadIntf2MakeChr_ctorTable, 4);
    inheritedName = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    nameIndex = ((Gap::Core::__internalNonRefCountedObjectList *)meta->_metaFields)->find((Gap::Core::igObject *)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    ((Gap::Core::igStringMetaField *)nameField)->setDefault("MAKECHR");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2MakeChr_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, nameIndex, (igMetaField *)nameField);
    nameField->release();
    igCharArrayMetaField *degiName = (igCharArrayMetaField *)igMetaObject_GetFieldAt(meta, base + 1);
    degiName->_num = 0x20;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLoadIntf2MakeChr_fieldTable, g_beNDMWLoadIntf2MakeChr_fieldHandles, g_beNDMWLoadIntf2MakeChr_fieldOffsets, base);
}

