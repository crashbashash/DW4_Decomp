igMetaObject *g_beSelectCtrlInfoRamData_metaObject;
int g_beSelectCtrlInfoRamData_nameStorage;
igMetaField *g_beSelectCtrlInfoRamData_isTateSelectMetaField;
igMetaField *g_beSelectCtrlInfoRamData_maxSelectMetaField;
igMetaField *g_beSelectCtrlInfoRamData_selectNoMetaField;
igMetaField *g_beSelectCtrlInfoRamData_workMetaField;

void *beSelectCtrlInfoRamData_GetMetaObject(void) {
    igMetaObject *g = g_beSelectCtrlInfoRamData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSelectCtrlInfoRamData_EnsureRegistered();
    }
    return g_beSelectCtrlInfoRamData_metaObject;
}

int beSelectCtrlInfoRamData_GetVTable(void) {
    beSelectCtrlInfoRamData obj;
    int vtable;
    igObject **workSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beSelectCtrlInfoRamData_vtable[0];
    workSlot = (igObject **)&obj._work;
    *workSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSelectCtrlInfoRamData_vtable[0];
    igObjectRef_Release(workSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beSelectCtrlInfoWork_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beSelectCtrlInfoRamData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSelectCtrlInfoRamData_Register);
}

static igMetaObjectCallback g_beSelectCtrlInfoRamData_callbackList[] = { beSelectCtrlInfoWork_EnsureRegistered, 0 };

CallbackArray *beSelectCtrlInfoRamData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSelectCtrlInfoRamData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beSelectCtrlInfoRamData_GetMetaObjectFunction,
        "beSelectCtrlInfoRamData",
        0x20, /* instance size */
        beSelectCtrlInfoRamData_GetVTable,
        beSelectCtrlInfoRamData_InitFields,
        0, /* extra callback item */
        g_beSelectCtrlInfoRamData_callbackList /* callback list */
    );
}

void beSelectCtrlInfoRamData_GetMetaObjectFunction(void)
{
    beSelectCtrlInfoRamData_GetMetaObject();
}

static FieldFactory g_beSelectCtrlInfoRamData_ctorTable[] = {
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSelectCtrlInfoRamData_fieldTable[] = {
    "_isTateSelect",
    "_maxSelect",
    "_selectNo",
    "_work",
};
static igMetaField **g_beSelectCtrlInfoRamData_fieldHandles[] = {
    &g_beSelectCtrlInfoRamData_isTateSelectMetaField,
    &g_beSelectCtrlInfoRamData_maxSelectMetaField,
    &g_beSelectCtrlInfoRamData_selectNoMetaField,
    &g_beSelectCtrlInfoRamData_workMetaField,
};
static int g_beSelectCtrlInfoRamData_fieldOffsets[] = {
    16,
    20,
    24,
    28,
};

void beSelectCtrlInfoRamData_InitFields(void) {
    int base;
    int index;
    void **found;
    void *work;
    void *meta;
    igStringMetaField *clone;

    meta = (void *)g_beSelectCtrlInfoRamData_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beSelectCtrlInfoRamData_ctorTable, 4);
    found = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_name"));
    index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(((igMetaObject *)meta)->_metaFields), (int)found);
    clone = (igStringMetaField *)(((igObjectDispatchView *)found)->CloneViaMetadata(1));
    ((Gap::Core::igStringMetaField *)clone)->setDefault("ONE");
    clone->_externalEnumStorage = (int)(&g_beSelectCtrlInfoRamData_nameStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, index, (igMetaField *)clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    work = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3));
    ((igObjectRefMetaField *)work)->_metaObject = (int)beSelectCtrlInfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_beSelectCtrlInfoRamData_fieldTable, g_beSelectCtrlInfoRamData_fieldHandles, g_beSelectCtrlInfoRamData_fieldOffsets, base);
}

