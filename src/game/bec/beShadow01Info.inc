igMetaObject *g_beShadow01Info_metaObject;
igMetaField *g_beShadow01Info_receiverNodeMetaField;
igMetaField *g_beShadow01Info_casterNodeMetaField;
igMetaField *g_beShadow01Info_projShadowShaderMetaField;

void *beShadow01Info_GetMetaObject(void) {
    bool ok;
    if (g_beShadow01Info_metaObject == 0) goto make;
    ok = !!(g_beShadow01Info_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beShadow01Info_EnsureRegistered();
done:;
    return g_beShadow01Info_metaObject;
}

int beShadow01Info_GetVTable(void) {
    beShadow01Info obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beShadow01Info_vtable[0];
    obj._receiverNode = 0;
    obj._casterNode = 0;
    obj._projShadowShader = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beShadow01Info_vtable[0];
    igSmartPointer_igProjectiveShadowShader_Destruct((igSmartPointer<igObject> *)(&obj._projShadowShader), -1);
    igSmartPointer_igNode_Destruct((igSmartPointer<igObject> *)&obj._casterNode, -1);
    igSmartPointer_igNode_Destruct((igSmartPointer<igObject> *)&obj._receiverNode, -1);
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_igProjectiveShadowShader_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beShadow01Info_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beShadow01Info_Register);
}

static igMetaObjectCallback g_beShadow01Info_callbackList[] = { Gap::Sg::igNode::arkRegister, Gap::Sg::igProjectiveShadowShader::arkRegister, 0 };

CallbackArray *beShadow01Info_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beShadow01Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beShadow01Info_GetMetaObjectFunction,
        "beShadow01Info",
        0x28, /* instance size */
        beShadow01Info_GetVTable,
        beShadow01Info_InitFields,
        0, /* extra callback item */
        g_beShadow01Info_callbackList /* callback list */
    );
}

void beShadow01Info_GetMetaObjectFunction(void)
{
    beShadow01Info_GetMetaObject();
}

static FieldFactory g_beShadow01Info_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beShadow01Info_fieldTable[] = {
    "_receiverNode",
    "_casterNode",
    "_projShadowShader",
};
static igMetaField **g_beShadow01Info_fieldHandles[] = {
    &g_beShadow01Info_receiverNodeMetaField,
    &g_beShadow01Info_casterNodeMetaField,
    &g_beShadow01Info_projShadowShaderMetaField,
};
static int g_beShadow01Info_fieldOffsets[] = {
    28,
    32,
    36,
};

void beShadow01Info_InitFields(void) {
    int base;
    void *receiverNode;
    void *casterNode;
    void *projShadowShader;
    igMetaObject *meta;

    meta = g_beShadow01Info_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beShadow01Info_ctorTable, 3);
    receiverNode = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)receiverNode)->_metaObject = (int)Gap::Sg::igNode::getClassTypeLazy();
    casterNode = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)casterNode)->_metaObject = (int)Gap::Sg::igNode::getClassTypeLazy();
    projShadowShader = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)projShadowShader)->_metaObject = (int)igProjectiveShadowShader_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beShadow01Info_fieldTable, g_beShadow01Info_fieldHandles, g_beShadow01Info_fieldOffsets, base);
}

