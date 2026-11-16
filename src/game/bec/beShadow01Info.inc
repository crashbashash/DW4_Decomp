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
    union U u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&g_beShadow01Info_vtable[0];
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[32] = 0;
    *(int *)&u.b[36] = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beShadow01Info_vtable[0];
    FUN_00344c40((igSmartPointer<igObject> *)(&u.b[36]), -1);
    FUN_00198210(&u.b[32], -1);
    FUN_00198210(&u.b[28], -1);
    FUN_0033ec80((struct S_33ec80 *)u.b, (short)0);
    return t;
}

igSmartPointer<igObject> *FUN_00344c40(igSmartPointer<igObject> *self, int delete_storage) {
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

void beShadow01Info_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beShadow01Info_Register);
}

static igMetaObjectCallback g_beShadow01Info_callbackList[] = { igNode_EnsureRegistered, igProjectiveShadowShader_EnsureRegistered, 0 };

void *beShadow01Info_Register(void) {
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
    void *meta;

    meta = (void *)g_beShadow01Info_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beShadow01Info_ctorTable, 3);
    receiverNode = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)receiverNode)->_metaObject = igNode_GetOrCreateMetaObject();
    casterNode = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)casterNode)->_metaObject = igNode_GetOrCreateMetaObject();
    projShadowShader = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)projShadowShader)->_metaObject = igProjectiveShadowShader_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beShadow01Info_fieldTable, g_beShadow01Info_fieldHandles, g_beShadow01Info_fieldOffsets, base);
}

