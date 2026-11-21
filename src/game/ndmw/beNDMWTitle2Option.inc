igMetaObject *g_beNDMWTitle2Option_metaObject;
int g_beNDMWTitle2Option_nameExternalEnumStorage;
igMetaField *g_beNDMWTitle2Option_messengerMetaField;
igMetaField *g_beNDMWTitle2Option_selLangMetaField;
igMetaField *g_beNDMWTitle2Option_ctrlPosMetaField;
igMetaField *g_beNDMWTitle2Option_isOKMetaField;
igMetaField *g_beNDMWTitle2Option_comConfMetaField;
igMetaField *g_beNDMWTitle2Option_lightConfMetaField;
igMetaField *g_beNDMWTitle2Option_oldCountryMetaField;
igMetaField *g_beNDMWTitle2Option_dispComConfMetaField;
igMetaField *g_beNDMWTitle2Option_dispLightConfMetaField;
igMetaField *g_beNDMWTitle2Option_dispCountryConfMetaField;

beNDMWTitle2Option *beNDMWTitle2Option_Create(int allocator) {
    beNDMWTitle2Option_EnsureRegistered();
    return (beNDMWTitle2Option *)igMetaObject_CreateInstance(g_beNDMWTitle2Option_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWTitle2Option_GetMetaObject(void) {
    bool ok;
    if (g_beNDMWTitle2Option_metaObject == 0) goto make;
    ok = !!(g_beNDMWTitle2Option_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNDMWTitle2Option_EnsureRegistered();
done:;
    return g_beNDMWTitle2Option_metaObject;
}

int beNDMWTitle2Option_GetVTable(void) {
    beNDMWTitle2Option obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_beNDMWTitle2Option_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWTitle2Option_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWTitle2Option_Register);
}

static igMetaObjectCallback g_beNDMWTitle2Option_callbackList[] = { beMessenger_EnsureRegistered, 0 };

CallbackArray *beNDMWTitle2Option_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWTitle2Option_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWTitle2Option_GetMetaObjectFunction,
        "beNDMWTitle2Option",
        0x38, /* instance size */
        beNDMWTitle2Option_GetVTable,
        beNDMWTitle2Option_InitFields,
        0, /* extra callback item */
        g_beNDMWTitle2Option_callbackList /* callback list */
    );
}

void beNDMWTitle2Option_GetMetaObjectFunction(void)
{
    beNDMWTitle2Option_GetMetaObject();
}

static FieldFactory g_beNDMWTitle2Option_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWTitle2Option_fieldTable[] = {
    "_messenger",
    "_selLang",
    "_ctrlPos",
    "_isOK",
    "_comConf",
    "_lightConf",
    "_oldCountry",
    "_dispComConf",
    "_dispLightConf",
    "_dispCountryConf",
};
static igMetaField **g_beNDMWTitle2Option_fieldHandles[] = {
    &g_beNDMWTitle2Option_messengerMetaField,
    &g_beNDMWTitle2Option_selLangMetaField,
    &g_beNDMWTitle2Option_ctrlPosMetaField,
    &g_beNDMWTitle2Option_isOKMetaField,
    &g_beNDMWTitle2Option_comConfMetaField,
    &g_beNDMWTitle2Option_lightConfMetaField,
    &g_beNDMWTitle2Option_oldCountryMetaField,
    &g_beNDMWTitle2Option_dispComConfMetaField,
    &g_beNDMWTitle2Option_dispLightConfMetaField,
    &g_beNDMWTitle2Option_dispCountryConfMetaField,
};
static int g_beNDMWTitle2Option_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
};

void beNDMWTitle2Option_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    void *messenger;
    void *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWTitle2Option_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWTitle2Option_ctorTable, 0xA);
    inheritedName = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_name"));
    nameIndex = ((Gap::Core::__internalNonRefCountedObjectList *)((char *)((igMetaObject *)meta)->_metaFields))->find((Gap::Core::igObject *)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    ((Gap::Core::igStringMetaField *)nameField)->setDefault("OPTION");
    nameField->_externalEnumStorage = (int)(&g_beNDMWTitle2Option_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, nameIndex, (igMetaField *)nameField);
    nameField->release();
    messenger = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base));
    ((igObjectRefMetaField *)messenger)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWTitle2Option_fieldTable, g_beNDMWTitle2Option_fieldHandles, g_beNDMWTitle2Option_fieldOffsets, base);
}

