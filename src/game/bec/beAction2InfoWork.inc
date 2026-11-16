igMetaObject *g_beAction2InfoWork_metaObject;
igMetaField *g_beAction2InfoWork_comDataMetaField;
igMetaField *g_beAction2InfoWork_comIndexMetaField;
igMetaField *g_beAction2InfoWork_isNoHokanMetaField;
igMetaField *g_beAction2InfoWork_isMotionMetaField;
igMetaField *g_beAction2InfoWork_motionSt0MetaField;
igMetaField *g_beAction2InfoWork_motionIsEndMetaField;
igMetaField *g_beAction2InfoWork_jointSt0MetaField;
igMetaField *g_beAction2InfoWork_jointStartTimeLMetaField;
igMetaField *g_beAction2InfoWork_jointEndTimeLMetaField;
igMetaField *g_beAction2InfoWork_jointIsEndMetaField;
igMetaField *g_beAction2InfoWork_fadeSt0MetaField;
igMetaField *g_beAction2InfoWork_fadeLimitValueMetaField;
igMetaField *g_beAction2InfoWork_fadeAddValueMetaField;
igMetaField *g_beAction2InfoWork_fadeValueMetaField;
igMetaField *g_beAction2InfoWork_waitSt0MetaField;
igMetaField *g_beAction2InfoWork_flashSt0MetaField;
igMetaField *g_beAction2InfoWork_isFreezeMetaField;
igMetaField *g_beAction2InfoWork_colorAttrMetaField;
igMetaField *g_beAction2InfoWork_blendStateAttrMetaField;
igMetaField *g_beAction2InfoWork_textureStateAttrMetaField;
igMetaField *g_beAction2InfoWork_lightingStateAttrMetaField;

void beAction2InfoWork_CreateInstance(int allocator) {
    beAction2InfoWork_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589E98, allocator);
}

igMetaObject *beAction2InfoWork_GetOrCreateMetaObject(void) {
    if (g_beAction2InfoWork_metaObject == 0) {
        g_beAction2InfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beAction2InfoWork_metaObject;
}

igMetaObject *beAction2InfoWork_GetMetaObject(void)
{
    igMetaObject *g = g_beAction2InfoWork_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beAction2InfoWork_EnsureRegistered();
    return g_beAction2InfoWork_metaObject;
}

int beAction2InfoWork_GetVTable(void) {
    beAction2InfoWork obj;
    int vtable;
    char *textureStateAttrSlot;
    char *blendStateAttrSlot;
    char *colorAttrSlot;
    char *comDataSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beAction2InfoWork_vtable[0];
    comDataSlot = (char *)&obj._comData;
    *(int *)comDataSlot = 0;
    colorAttrSlot = (char *)&obj._colorAttr;
    *(int *)colorAttrSlot = 0;
    blendStateAttrSlot = (char *)&obj._blendStateAttr;
    *(int *)blendStateAttrSlot = 0;
    textureStateAttrSlot = (char *)&obj._textureStateAttr;
    *(int *)textureStateAttrSlot = 0;
    obj._lightingStateAttr = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beAction2InfoWork_vtable[0];
    igSmartPointer_igLightingStateAttr_Destruct(&obj._lightingStateAttr, -1);
    igSmartPointer_igTextureStateAttr_Destruct(textureStateAttrSlot, -1);
    igSmartPointer_igBlendStateAttr_Destruct(blendStateAttrSlot, -1);
    igSmartPointer_igColorAttr_Destruct(colorAttrSlot, -1);
    igSmartPointer_beAction2Data_Destruct((igSmartPointer<igObject> *)comDataSlot, (short)(-1));
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beAction2Data_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

void beAction2InfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2InfoWork_Register);
}

static igMetaObjectCallback g_beAction2InfoWork_callbackList[] = { beAction2Data_EnsureRegistered, igColorAttr_EnsureRegistered, igBlendStateAttr_EnsureRegistered, igTextureStateAttr_EnsureRegistered, igLightingStateAttr_EnsureRegistered, 0 };

void *beAction2InfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2InfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beAction2InfoWork_GetMetaObjectFunction,
        "beAction2InfoWork",
        0x60, /* instance size */
        beAction2InfoWork_GetVTable,
        beAction2InfoWork_InitFields,
        0, /* extra callback item */
        g_beAction2InfoWork_callbackList /* callback list */
    );
}

void beAction2InfoWork_GetMetaObjectFunction(void)
{
    beAction2InfoWork_GetMetaObject();
}

static FieldFactory g_beAction2InfoWork_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beAction2InfoWork_fieldTable[] = {
    "_comData",
    "_comIndex",
    "_isNoHokan",
    "_isMotion",
    "_motionSt0",
    "_motionIsEnd",
    "_jointSt0",
    "_jointStartTimeL",
    "_jointEndTimeL",
    "_jointIsEnd",
    "_fadeSt0",
    "_fadeLimitValue",
    "_fadeAddValue",
    "_fadeValue",
    "_waitSt0",
    "_flashSt0",
    "_isFreeze",
    "_colorAttr",
    "_blendStateAttr",
    "_textureStateAttr",
    "_lightingStateAttr",
};
static igMetaField **g_beAction2InfoWork_fieldHandles[] = {
    &g_beAction2InfoWork_comDataMetaField,
    &g_beAction2InfoWork_comIndexMetaField,
    &g_beAction2InfoWork_isNoHokanMetaField,
    &g_beAction2InfoWork_isMotionMetaField,
    &g_beAction2InfoWork_motionSt0MetaField,
    &g_beAction2InfoWork_motionIsEndMetaField,
    &g_beAction2InfoWork_jointSt0MetaField,
    &g_beAction2InfoWork_jointStartTimeLMetaField,
    &g_beAction2InfoWork_jointEndTimeLMetaField,
    &g_beAction2InfoWork_jointIsEndMetaField,
    &g_beAction2InfoWork_fadeSt0MetaField,
    &g_beAction2InfoWork_fadeLimitValueMetaField,
    &g_beAction2InfoWork_fadeAddValueMetaField,
    &g_beAction2InfoWork_fadeValueMetaField,
    &g_beAction2InfoWork_waitSt0MetaField,
    &g_beAction2InfoWork_flashSt0MetaField,
    &g_beAction2InfoWork_isFreezeMetaField,
    &g_beAction2InfoWork_colorAttrMetaField,
    &g_beAction2InfoWork_blendStateAttrMetaField,
    &g_beAction2InfoWork_textureStateAttrMetaField,
    &g_beAction2InfoWork_lightingStateAttrMetaField,
};
static int g_beAction2InfoWork_fieldOffsets[] = {
    8,
    12,
    16,
    17,
    20,
    24,
    28,
    32,
    40,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
    76,
    80,
    84,
    88,
    92,
};

void beAction2InfoWork_InitFields(void) {
    int base;
    void *comData;
    void *colorAttr;
    void *blendStateAttr;
    void *textureStateAttr;
    void *lightingStateAttr;
    void *meta;

    meta = (void *)g_beAction2InfoWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beAction2InfoWork_ctorTable, 0x15);
    comData = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)comData)->_metaObject = (int)beAction2Data_GetOrCreateMetaObject();
    colorAttr = (void *)(igMetaObject_GetFieldAt(meta, base + 0x11));
    ((igObjectRefMetaField *)colorAttr)->_metaObject = igColorAttr_GetOrCreateMetaObject();
    blendStateAttr = (void *)(igMetaObject_GetFieldAt(meta, base + 0x12));
    ((igObjectRefMetaField *)blendStateAttr)->_metaObject = igBlendStateAttr_GetOrCreateMetaObject();
    textureStateAttr = (void *)(igMetaObject_GetFieldAt(meta, base + 0x13));
    ((igObjectRefMetaField *)textureStateAttr)->_metaObject = igTextureStateAttr_GetOrCreateMetaObject();
    lightingStateAttr = (void *)(igMetaObject_GetFieldAt(meta, base + 0x14));
    ((igObjectRefMetaField *)lightingStateAttr)->_metaObject = igLightingStateAttr_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beAction2InfoWork_fieldTable, g_beAction2InfoWork_fieldHandles, g_beAction2InfoWork_fieldOffsets, base);
}

