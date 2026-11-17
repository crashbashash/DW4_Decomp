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

igMetaObject *FUN_00143150(void)
{
    igMetaObject *meta = g_igPsx2AudioContext_metaObject;
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_001433d0();
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
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem) + 916)];
    u.vt = (int)&g_igPsx2AudioContext_vtable[0];
    FUN_00143350((void **)&u.b[48], -1);
    FUN_00143350((void **)&u.b[20], -1);
    igSmartPointer_igThread_Destruct((struct RefCountBits **)&u.b[16], -1);
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

void **igSmartPointer_igThread_Destruct(struct RefCountBits **self, short flag) {
    struct RefCountBits *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy((igObject *)p);
        }
        if (flag > 0) operator delete(self);
    }
    return (void **)self;
}

void **FUN_00143350(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void FUN_001433d0(void)
{
    igMetaObject_RunStaticInit(igPsx2AudioContext_Register);
}

static igMetaObjectCallback g_igPsx2AudioContext_callbackList[] = { igPsx2IopRpcConnection_EnsureRegistered, igThread_EnsureRegistered, FUN_00145de0, 0 };

CallbackArray *igPsx2AudioContext_Register(void) {
    AudioLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2AudioContext_metaObject,
        igAudioContext_Register,
        igAudioContext_GetPublishedMetaObject,
        thunk_FUN_00143150,
        "igPsx2AudioContext",
        sizeof(igPsx2AudioContext),                     /* Instance size. */
        igPsx2AudioContext_GetVTable,
        &igPsx2AudioContext_InitFields,
        0, /* extra callback item */
        g_igPsx2AudioContext_callbackList /* callback list */
    );
}

igMetaObject *FUN_00143460(void) {
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
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igPsx2IopRpcConnection_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igThread_GetOrCreateMetaObject();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_00145d40();
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3), 0);
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 5), 2);
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 6), 0x30);
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 7));
    ((igMemoryRefMetaField *)temp_s1_4)->_memType = igUnsignedIntMetaField_GetDefaultDescriptor();
    temp_s1_5 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 9));
    ((igObjectRefMetaField *)temp_s1_5)->_metaObject = FUN_00145d40();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igPsx2AudioContext_fieldTable, g_igPsx2AudioContext_fieldHandles, g_igPsx2AudioContext_fieldOffsets, temp_s2);
    *(int *)((char *)(g_igPsx2AudioContext_metaObject) + 64) = (int)thunk_igAudioContext_GetMetaObject;
}

