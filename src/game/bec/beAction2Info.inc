igMetaObject *g_beAction2Info_metaObject;
igMetaField *g_beAction2Info_switchMetaField;
igMetaField *g_beAction2Info_animationDatabaseMetaField;
igMetaField *g_beAction2Info_dataListMetaField;

igMetaObject *beAction2Info_GetMetaObject(void) {
    if (g_beAction2Info_metaObject == 0 || !isValid(g_beAction2Info_metaObject)) beAction2Info_EnsureRegistered();
    return g_beAction2Info_metaObject;
}

int beAction2Info_GetVTable(void) {
    beAction2Info obj;
    int *switchSlot;
    int vtable;
    int *animationDatabaseSlot;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beAction2Info_vtable[0];
    switchSlot = &obj._switch;
    *switchSlot = 0;
    animationDatabaseSlot = &obj._animationDatabase;
    *animationDatabaseSlot = 0;
    obj._dataList_ = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beAction2Info_vtable[0];
    igSmartPointer_beAction2DataList_Destruct((igSmartPointer<igObject> *)(&obj._dataList_), -1);
    igSmartPointer_igAnimationDatabase_Destruct(animationDatabaseSlot, -1);
    igSmartPointer_igSwitch_Destruct((igSmartPointer<igObject> *)switchSlot, -1);
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beAction2DataList_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

void beAction2Info_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2Info_Register);
}

static igMetaObjectCallback g_beAction2Info_callbackList[] = { igSwitch_EnsureRegistered, igAnimationDatabase_EnsureRegistered, beAction2DataList_EnsureRegistered, 0 };

void *beAction2Info_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beAction2Info_GetMetaObjectFunction,
        "beAction2Info",
        0x28, /* instance size */
        beAction2Info_GetVTable,
        beAction2Info_InitFields,
        0, /* extra callback item */
        g_beAction2Info_callbackList /* callback list */
    );
}

void beAction2Info_GetMetaObjectFunction(void)
{
    beAction2Info_GetMetaObject();
}

static FieldFactory g_beAction2Info_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beAction2Info_fieldTable[] = {
    "_switch",
    "_animationDatabase",
    "_dataList",
};
static igMetaField **g_beAction2Info_fieldHandles[] = {
    &g_beAction2Info_switchMetaField,
    &g_beAction2Info_animationDatabaseMetaField,
    &g_beAction2Info_dataListMetaField,
};
static int g_beAction2Info_fieldOffsets[] = {
    28,
    32,
    36,
};

void beAction2Info_InitFields(void) {
    int base;
    void *switchField;
    void *animationDatabase;
    void *dataList;
    void *meta;

    meta = (void *)g_beAction2Info_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beAction2Info_ctorTable, 3);
    switchField = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)switchField)->_metaObject = igSwitch_GetOrCreateMetaObject();
    animationDatabase = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)animationDatabase)->_metaObject = igAnimationDatabase_GetOrCreateMetaObject();
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beAction2DataList_GetOrCreateMetaObject();
    ((igRefMetaField *)dataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beAction2Info_fieldTable, g_beAction2Info_fieldHandles, g_beAction2Info_fieldOffsets, base);
}

