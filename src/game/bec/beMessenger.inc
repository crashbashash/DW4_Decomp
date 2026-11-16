igMetaObject *g_beMessenger_metaObject;
igMetaField *g_beMessenger_argDataMetaField;
igMetaField *g_beMessenger_groupListMetaField;
igMetaField *g_beMessenger_workStackMetaField;
igMetaField *g_beMessenger_delayStackMetaField;
igMetaField *g_beMessenger_pushPopStackMetaField;
igMetaField *g_beMessenger_pushPopCountMetaField;
igMetaField *g_beMessenger_freezeTimeMetaField;
igMetaField *g_beMessenger_isMemoryAssignMetaField;

void beMessenger_CreateInstance(int allocator) {
    beMessenger_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588F38, allocator);
}

igMetaObject *beMessenger_GetOrCreateMetaObject(void) {
    if (g_beMessenger_metaObject == 0) {
        g_beMessenger_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    union U_3579b0 u;
    int r;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    u.vt = (int)&g_beMessenger_vtable[0];
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[32] = 0;
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beMessenger_vtable[0];
    FUN_00357c90((igSmartPointer<igObject> *)(&u.b[32]), (long long)(-1));
    FUN_00357c10((igSmartPointer<igObject> *)(&u.b[28]), (short)(-1));
    FUN_00357b90((igSmartPointer<igObject> *)(&u.b[24]), (short)(-1));
    FUN_00357b10((igSmartPointer<igObject> *)(&u.b[20]), -1);
    FUN_00357a90((igSmartPointer<igObject> *)&u.b[16], -1);
    FUN_00231030(u.b, 0);
    return r;
}

igSmartPointer<igObject> *FUN_00357a90(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_00357b10(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_00357b90(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_00357c10(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_00357c90(igSmartPointer<igObject> *self, long long delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void beMessenger_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMessenger_Register);
}

static igMetaObjectCallback g_beMessenger_callbackList[] = { beMessengerArgData_EnsureRegistered, beMessengerGroupList_EnsureRegistered, beMessengerWorkList_EnsureRegistered, beMessengerDelayList_EnsureRegistered, beMessengerArgDataList_EnsureRegistered, 0 };

void *beMessenger_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMessenger_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
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
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMessenger_ctorTable, 8);
    argData = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)argData)->_metaObject = (int)beMessengerArgData_GetOrCreateMetaObject();
    groupList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)groupList)->_metaObject = (int)beMessengerGroupList_GetOrCreateMetaObject();
    ((igRefMetaField *)groupList)->_construct = 1;
    workStack = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)workStack)->_metaObject = (int)beMessengerWorkList_GetOrCreateMetaObject();
    ((igRefMetaField *)workStack)->_construct = 1;
    delayStack = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)delayStack)->_metaObject = (int)beMessengerDelayList_GetOrCreateMetaObject();
    ((igRefMetaField *)delayStack)->_construct = 1;
    pushPopStack = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)pushPopStack)->_metaObject = (int)beMessengerArgDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)pushPopStack)->_construct = 1;
    igMetaObject_NameFields(meta, g_beMessenger_fieldTable, g_beMessenger_fieldHandles, g_beMessenger_fieldOffsets, base);
}

