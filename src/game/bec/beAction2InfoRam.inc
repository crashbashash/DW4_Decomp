igMetaObject *g_beAction2InfoRam_metaObject;
igMetaField *g_beAction2InfoRam_nodeMetaField;
igMetaField *g_beAction2InfoRam_appearanceListMetaField;
igMetaField *g_beAction2InfoRam_actorListMetaField;
igMetaField *g_beAction2InfoRam_workMetaField;

igMetaObject *beAction2InfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beAction2InfoRam_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beAction2InfoRam_EnsureRegistered();
    return g_beAction2InfoRam_metaObject;
}

int beAction2InfoRam_GetVTable(void) {
    beAction2InfoRam obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._dataList = 0;
    obj._vtable = (int)&g_beAction2InfoRam_vtable[0];
    obj._node = 0;
    obj._appearanceList = 0;
    obj._actorList = 0;
    obj._work = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beAction2InfoRam_vtable[0];
    igSmartPointer_beAction2InfoWork_Destruct((igSmartPointer<igObject> *)(&obj._work), (short)(-1));
    igSmartPointer_igActorList_Destruct((igSmartPointer<igObject> *)&obj._actorList, -1);
    igSmartPointer_igAppearanceList_Destruct((igSmartPointer<igObject> *)&obj._appearanceList, -1);
    igSmartPointer_beModelCtrlNode2_Destruct((igSmartPointer<igObject> *)&obj._node, -1);
    beBaseInfoRam_Destroy((beBaseInfoRam *)&obj, (long long)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beAction2InfoWork_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

void beAction2InfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2InfoRam_Register);
}

static igMetaObjectCallback g_beAction2InfoRam_callbackList[] = { beModelCtrlNode2_EnsureRegistered, Gap::Sg::igAppearanceList::arkRegister, Gap::Sg::igActorList::arkRegister, Gap::Bec::beAction2InfoWork::arkRegister, 0 };

CallbackArray *beAction2InfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2InfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beAction2InfoRam_GetMetaObjectFunction,
        "beAction2InfoRam",
        0x3c, /* instance size */
        beAction2InfoRam_GetVTable,
        beAction2InfoRam_InitFields,
        0, /* extra callback item */
        g_beAction2InfoRam_callbackList /* callback list */
    );
}

void beAction2InfoRam_GetMetaObjectFunction(void)
{
    beAction2InfoRam_GetMetaObject();
}

static FieldFactory g_beAction2InfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beAction2InfoRam_fieldTable[] = {
    "_node",
    "_appearanceList",
    "_actorList",
    "_work",
};
static igMetaField **g_beAction2InfoRam_fieldHandles[] = {
    &g_beAction2InfoRam_nodeMetaField,
    &g_beAction2InfoRam_appearanceListMetaField,
    &g_beAction2InfoRam_actorListMetaField,
    &g_beAction2InfoRam_workMetaField,
};
static int g_beAction2InfoRam_fieldOffsets[] = {
    44,
    48,
    52,
    56,
};

void beAction2InfoRam_InitFields(void) {
    void *node;
    void *appearanceList;
    void *actorList;
    void *work;
    void *meta;
    int base;

    meta = (void *)g_beAction2InfoRam_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beAction2InfoRam_ctorTable, 4);
    node = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base));
    ((igObjectRefMetaField *)node)->_metaObject = (int)beModelCtrlNode2_GetOrCreateMetaObject();
    appearanceList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1));
    ((igObjectRefMetaField *)appearanceList)->_metaObject = (int)Gap::Sg::igAppearanceList::getClassTypeLazy();
    ((igRefMetaField *)appearanceList)->_construct = 1;
    actorList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2));
    ((igObjectRefMetaField *)actorList)->_metaObject = (int)Gap::Sg::igActorList::getClassTypeLazy();
    ((igRefMetaField *)actorList)->_construct = 1;
    work = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3));
    ((igObjectRefMetaField *)work)->_metaObject = (int)Gap::Bec::beAction2InfoWork::getClassTypeLazy();
    igMetaObject_NameFields((igMetaObject *)meta, g_beAction2InfoRam_fieldTable, g_beAction2InfoRam_fieldHandles, g_beAction2InfoRam_fieldOffsets, base);
}

