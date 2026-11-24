igMetaObject *g_beTransformSync_metaObject;
igMetaField *g_beTransformSync_syncTransformListMetaField;

void *beTransformSync_GetMetaObject(void) {
    igMetaObject *g = g_beTransformSync_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beTransformSync_EnsureRegistered();
    }
    return g_beTransformSync_metaObject;
}

int beTransformSync_GetVTable(void) {
    TransformSyncView transform;
    return *(int *)((char *)&transform + g_objectSystem->vtableProbeOffset);
}

igSmartPointer<igObject> *igSmartPointer_igTransformList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

void beTransformSync_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTransformSync_Register);
}

static igMetaObjectCallback g_beTransformSync_callbackList[] = { igTransformList_EnsureRegistered, 0 };

CallbackArray *beTransformSync_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTransformSync_metaObject,
        Gap::Sg::igTransform::arkRegisterInternal,
        Gap::Sg::igTransform::getClassMeta,
        beTransformSync_GetMetaObjectFunction,
        "beTransformSync",
        0x70, /* instance size */
        beTransformSync_GetVTable,
        beTransformSync_InitFields,
        0, /* extra callback item */
        g_beTransformSync_callbackList /* callback list */
    );
}

void beTransformSync_GetMetaObjectFunction(void)
{
    beTransformSync_GetMetaObject();
}

static FieldFactory g_beTransformSync_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beTransformSync_fieldTable[] = {
    "_syncTransformList",
};
static igMetaField **g_beTransformSync_fieldHandles[] = {
    &g_beTransformSync_syncTransformListMetaField,
};
static int g_beTransformSync_fieldOffsets[] = {
    108,
};

void beTransformSync_InitFields(void) {
    int base;
    void *syncTransformList;
    igMetaObject *meta;

    meta = g_beTransformSync_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beTransformSync_ctorTable, 1);
    syncTransformList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)syncTransformList)->_metaObject = (int)igTransformList_GetOrCreateMetaObject();
    ((igRefMetaField *)syncTransformList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beTransformSync_fieldTable, g_beTransformSync_fieldHandles, g_beTransformSync_fieldOffsets, base);
}

