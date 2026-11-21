igMetaObject *g_beNDMWLoadIntf2DegiStateCtrl_metaObject;
int g_beNDMWLoadIntf2DegiStateCtrl_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2DegiStateCtrl_statDataListMetaField;

beNDMWLoadIntf2DegiStateCtrl *beNDMWLoadIntf2DegiStateCtrl_Create(int allocator) {
    beNDMWLoadIntf2DegiStateCtrl_EnsureRegistered();
    return (beNDMWLoadIntf2DegiStateCtrl *)igMetaObject_CreateInstance(g_beNDMWLoadIntf2DegiStateCtrl_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWLoadIntf2DegiStateCtrl_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadIntf2DegiStateCtrl_metaObject == 0) {
        g_beNDMWLoadIntf2DegiStateCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWLoadIntf2DegiStateCtrl_metaObject;
}

igMetaObject *beNDMWLoadIntf2DegiStateCtrl_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2DegiStateCtrl_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWLoadIntf2DegiStateCtrl_EnsureRegistered();
done:
    return g_beNDMWLoadIntf2DegiStateCtrl_metaObject;
}

int beNDMWLoadIntf2DegiStateCtrl_GetVTable(void) {
    beNDMWLoadIntf2DegiStateCtrl obj;
    int vtable;
    int *nameRef;
    int *statDataListRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2DegiStateCtrl_vtable[0];
    statDataListRef = &obj._statDataList;
    *statDataListRef = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2DegiStateCtrl_vtable[0];
    if (statDataListRef != 0) {
        igObject::release((igObject *)*statDataListRef);
    }
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWLoadIntf2DegiStateCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2DegiStateCtrl_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2DegiStateCtrl_callbackList[] = { beNDMWLoadIntf2DegiStateList_EnsureRegistered, 0 };

CallbackArray *beNDMWLoadIntf2DegiStateCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2DegiStateCtrl_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2DegiStateCtrl_GetMetaObject,
        "beNDMWLoadIntf2DegiStateCtrl",
        0x14, /* instance size */
        beNDMWLoadIntf2DegiStateCtrl_GetVTable,
        beNDMWLoadIntf2DegiStateCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2DegiStateCtrl_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2DegiStateCtrl_GetMetaObject(void)
{
    beNDMWLoadIntf2DegiStateCtrl_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2DegiStateCtrl_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWLoadIntf2DegiStateCtrl_fieldTable[] = {
    "_statDataList",
};
static igMetaField **g_beNDMWLoadIntf2DegiStateCtrl_fieldHandles[] = {
    &g_beNDMWLoadIntf2DegiStateCtrl_statDataListMetaField,
};
static int g_beNDMWLoadIntf2DegiStateCtrl_fieldOffsets[] = {
    16,
};

void beNDMWLoadIntf2DegiStateCtrl_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    igObjectRefMetaField *statDataList;
    igMetaObject *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (igMetaObject *)(g_beNDMWLoadIntf2DegiStateCtrl_metaObject);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLoadIntf2DegiStateCtrl_ctorTable, 1);
    inheritedName = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)meta->_metaFields, (int)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    ((Gap::Core::igStringMetaField *)nameField)->setDefault("DEGISTATECTRL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2DegiStateCtrl_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, nameIndex, (igMetaField *)nameField);
    nameField->release();
    statDataList = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base));
    statDataList->_metaObject = (int)beNDMWLoadIntf2DegiStateList_GetOrCreateMetaObject();
    statDataList->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLoadIntf2DegiStateCtrl_fieldTable, g_beNDMWLoadIntf2DegiStateCtrl_fieldHandles, g_beNDMWLoadIntf2DegiStateCtrl_fieldOffsets, base);
}

