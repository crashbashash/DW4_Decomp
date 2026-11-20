igMetaObject *g_igPsx2AudioContext_metaObject;
igMetaField *g_igPsx2AudioContext_connectionMetaField;
igMetaField *g_igPsx2AudioContext_streamingThreadMetaField;
igMetaField *g_igPsx2AudioContext_windowMetaField;
igMetaField *g_igPsx2AudioContext_sdInitValueMetaField;
igMetaField *g_igPsx2AudioContext_callBackForSetSourceDataASyncMetaField;
igMetaField *g_igPsx2AudioContext_maxWavCountMetaField;
igMetaField *g_igPsx2AudioContext_maxVagCountMetaField;
igMetaField *g_igPsx2AudioContext_batchMemoryMetaField;
igMetaField *g_igPsx2AudioContext_batchOffsetMetaField;
igMetaField *g_igPsx2AudioContext_lastRequestIDMetaField;

igMetaObject *igPsx2AudioContext_GetMetaObject(void)
{
    igMetaObject *meta = g_igPsx2AudioContext_metaObject;
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    igPsx2AudioContext_EnsureRegistered();
end:
    return g_igPsx2AudioContext_metaObject;
}

int igPsx2AudioContext_GetVTable(void) {
    union AudioContextProbe u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igPsx2AudioContext_vtable[0];
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[48] = 0;
    t = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igPsx2AudioContext_vtable[0];
    igSmartPointer_igWindow_Destruct((igSmartPointer<igObject> *)&u.b[48], -1);
    igSmartPointer_igWindow_Destruct((igSmartPointer<igObject> *)&u.b[20], -1);
    igSmartPointer_igThread_Destruct((igSmartPointer<igObject> *)&u.b[16], -1);
    FUN_00143250((void **)&u.b[12], -1);
    return t;
}

void **FUN_00143250(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

igSmartPointer<igObject> *igSmartPointer_igThread_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igWindow_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

void igPsx2AudioContext_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2AudioContext_Register);
}

static igMetaObjectCallback g_igPsx2AudioContext_callbackList[] = { igPsx2IopRpcConnection_EnsureRegistered, igThread_EnsureRegistered, igWindow_EnsureRegistered, 0 };

CallbackArray *igPsx2AudioContext_Register(void) {
    AudioLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2AudioContext_metaObject,
        igAudioContext_Register,
        igAudioContext_GetPublishedMetaObject,
        igPsx2AudioContext_GetMetaObjectFunction,
        "igPsx2AudioContext",
        sizeof(igPsx2AudioContext),                     /* Instance size. */
        igPsx2AudioContext_GetVTable,
        &igPsx2AudioContext_InitFields,
        0, /* extra callback item */
        g_igPsx2AudioContext_callbackList /* callback list */
    );
}

igMetaObject *igAudioContext_GetPublishedMetaObject(void) {
    return g_igAudioContext_metaObject;
}

static FieldFactory g_igPsx2AudioContext_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igUnsignedIntMetaField_Create,
    igRawRefMetaField_Create,
    igUnsignedIntMetaField_Create,
    igUnsignedIntMetaField_Create,
    igMemoryRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igPsx2AudioContext_fieldTable[] = {
    "_connection",
    "_streamingThread",
    "_window",
    "_sdInitValue",
    "_callBackForSetSourceDataASync",
    "_maxWavCount",
    "_maxVagCount",
    "_batchMemory",
    "_batchOffset",
    "_lastRequestID",
};
static igMetaField **g_igPsx2AudioContext_fieldHandles[] = {
    &g_igPsx2AudioContext_connectionMetaField,
    &g_igPsx2AudioContext_streamingThreadMetaField,
    &g_igPsx2AudioContext_windowMetaField,
    &g_igPsx2AudioContext_sdInitValueMetaField,
    &g_igPsx2AudioContext_callBackForSetSourceDataASyncMetaField,
    &g_igPsx2AudioContext_maxWavCountMetaField,
    &g_igPsx2AudioContext_maxVagCountMetaField,
    &g_igPsx2AudioContext_batchMemoryMetaField,
    &g_igPsx2AudioContext_batchOffsetMetaField,
    &g_igPsx2AudioContext_lastRequestIDMetaField,
};
static int g_igPsx2AudioContext_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
};

void igPsx2AudioContext_InitFields(void) {
    /* matching construct: declaration-order sweep — this order sets the saved registers */
    void *temp_s1;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1_5;
    int temp_s2;
    void *temp_s1_4;
    void *temp_s0;

    temp_s0 = (void *)(g_igPsx2AudioContext_metaObject);
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igPsx2AudioContext_ctorTable, 0xA);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igPsx2IopRpcConnection_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igThread_GetOrCreateMetaObject();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)igWindow_GetOrCreateMetaObject();
    ((Gap::Core::igUnsignedIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3)))->setDefault(0);
    ((Gap::Core::igUnsignedIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 5)))->setDefault(2);
    ((Gap::Core::igUnsignedIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 6)))->setDefault(0x30);
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 7));
    ((igMemoryRefMetaField *)temp_s1_4)->_memType = (int)Gap::Core::igUnsignedIntMetaField::getMetaField();
    temp_s1_5 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 9));
    ((igObjectRefMetaField *)temp_s1_5)->_metaObject = (int)igWindow_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igPsx2AudioContext_fieldTable, g_igPsx2AudioContext_fieldHandles, g_igPsx2AudioContext_fieldOffsets, temp_s2);
    *(int *)((char *)(g_igPsx2AudioContext_metaObject) + 64) = (int)igAudioContext_GetMetaObjectFunction;
}

