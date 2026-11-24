igMetaObject *g_beMessenger_metaObject;
igMetaField *g_beMessenger_argDataMetaField;
igMetaField *g_beMessenger_groupListMetaField;
igMetaField *g_beMessenger_workStackMetaField;
igMetaField *g_beMessenger_delayStackMetaField;
igMetaField *g_beMessenger_pushPopStackMetaField;
igMetaField *g_beMessenger_pushPopCountMetaField;
igMetaField *g_beMessenger_freezeTimeMetaField;
igMetaField *g_beMessenger_isMemoryAssignMetaField;

beMessenger *beMessenger_CreateInstance(int allocator) {
    beMessenger_EnsureRegistered();
    return (beMessenger *)igMetaObject_CreateInstance(g_beMessenger_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beMessenger_GetOrCreateMetaObject(void) {
    if (g_beMessenger_metaObject == 0) {
        g_beMessenger_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beMessenger_metaObject;
}

void *beMessenger_GetMetaObject(void) {
    igMetaObject *g = g_beMessenger_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMessenger_EnsureRegistered();
    }
    return g_beMessenger_metaObject;
}

int beMessenger_GetVTable(void) {
    beMessenger obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beMessenger_vtable[0];
    obj._argData = 0;
    obj._groupList = 0;
    obj._workStack = 0;
    obj._delayStack = 0;
    obj._pushPopStack = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beMessenger_vtable[0];
    igSmartPointer_beMessengerArgDataList_Destruct((igSmartPointer<igObject> *)(&obj._pushPopStack), (long long)(-1));
    igSmartPointer_beMessengerDelayList_Destruct((igSmartPointer<igObject> *)(&obj._delayStack), (short)(-1));
    igSmartPointer_beMessengerWorkList_Destruct((igSmartPointer<igObject> *)(&obj._workStack), (short)(-1));
    igSmartPointer_beMessengerGroupList_Destruct((igSmartPointer<igObject> *)(&obj._groupList), -1);
    igSmartPointer_beMessengerArgData_Destruct((igSmartPointer<igObject> *)&obj._argData, -1);
    igInfoManager_Destroy((igInfoManager *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beMessengerArgData_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beMessengerGroupList_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beMessengerWorkList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beMessengerDelayList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beMessengerArgDataList_Destruct(igSmartPointer<igObject> *self, long long delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beMessenger_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMessenger_Register);
}

static igMetaObjectCallback g_beMessenger_callbackList[] = { beMessengerArgData_EnsureRegistered, beMessengerGroupList_EnsureRegistered, beMessengerWorkList_EnsureRegistered, beMessengerDelayList_EnsureRegistered, beMessengerArgDataList_EnsureRegistered, 0 };

CallbackArray *beMessenger_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMessenger_metaObject,
        Gap::Insight::igInfoManager::arkRegisterInternal,
        Gap::Insight::igInfoManager::getClassMeta,
        beMessenger_GetMetaObjectFunction,
        "beMessenger",
        0x38, /* instance size */
        beMessenger_GetVTable,
        beMessenger_InitFields,
        0, /* extra callback item */
        g_beMessenger_callbackList /* callback list */
    );
}

void beMessenger_GetMetaObjectFunction(void)
{
    beMessenger_GetMetaObject();
}

static FieldFactory g_beMessenger_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igLongMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beMessenger_fieldTable[] = {
    "_argData",
    "_groupList",
    "_workStack",
    "_delayStack",
    "_pushPopStack",
    "_pushPopCount",
    "_freezeTime",
    "_isMemoryAssign",
};
static igMetaField **g_beMessenger_fieldHandles[] = {
    &g_beMessenger_argDataMetaField,
    &g_beMessenger_groupListMetaField,
    &g_beMessenger_workStackMetaField,
    &g_beMessenger_delayStackMetaField,
    &g_beMessenger_pushPopStackMetaField,
    &g_beMessenger_pushPopCountMetaField,
    &g_beMessenger_freezeTimeMetaField,
    &g_beMessenger_isMemoryAssignMetaField,
};
static int g_beMessenger_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    48,
};

void beMessenger_InitFields(void) {
    void *argData;
    void *groupList;
    void *workStack;
    void *delayStack;
    void *pushPopStack;
    void *meta;
    int base;

    meta = (void *)g_beMessenger_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beMessenger_ctorTable, 8);
    argData = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base));
    ((igObjectRefMetaField *)argData)->_metaObject = (int)beMessengerArgData_GetOrCreateMetaObject();
    groupList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1));
    ((igObjectRefMetaField *)groupList)->_metaObject = (int)beMessengerGroupList_GetOrCreateMetaObject();
    ((igRefMetaField *)groupList)->_construct = 1;
    workStack = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2));
    ((igObjectRefMetaField *)workStack)->_metaObject = (int)beMessengerWorkList_GetOrCreateMetaObject();
    ((igRefMetaField *)workStack)->_construct = 1;
    delayStack = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3));
    ((igObjectRefMetaField *)delayStack)->_metaObject = (int)beMessengerDelayList_GetOrCreateMetaObject();
    ((igRefMetaField *)delayStack)->_construct = 1;
    pushPopStack = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4));
    ((igObjectRefMetaField *)pushPopStack)->_metaObject = (int)beMessengerArgDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)pushPopStack)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beMessenger_fieldTable, g_beMessenger_fieldHandles, g_beMessenger_fieldOffsets, base);
}

