igMetaObject *g_igPrimLengthArray_metaObject;
igMetaField *g_igPrimLengthArray_lengthDataMetaField;
igMetaField *g_igPrimLengthArray_numStripsMetaField;
igMetaField *g_igPrimLengthArray_dataSizeMetaField;

igObject *igPrimLengthArray_Create(igMemoryPoolView *pool) {
    igPrimLengthArray_EnsureRegistered();
    return igMetaObject_CreateInstance(g_igPrimLengthArray_metaObject, pool);
}

igMetaObject *igPrimLengthArray_GetOrCreateMetaObject(void) {
    if (g_igPrimLengthArray_metaObject == 0) {
        g_igPrimLengthArray_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igPrimLengthArray_metaObject;
}

igMetaObject *igPrimLengthArray_GetMetaObject(void)
{
    igMetaObject *g = g_igPrimLengthArray_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPrimLengthArray_EnsureRegistered();
    return g_igPrimLengthArray_metaObject;
}

void igPrimLengthArray_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPrimLengthArray_Register);
}

CallbackArray *igPrimLengthArray_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igPrimLengthArray_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igPrimLengthArray_GetMetaObjectFunction,
        "igPrimLengthArray",
        0x14, /* instance size */
        0,
        &igPrimLengthArray_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igPrimLengthArray_GetMetaObjectFunction(void) {
    igPrimLengthArray_GetMetaObject();
}

static FieldFactory g_igPrimLengthArray_ctorTable[] = {
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igPrimLengthArray_fieldTable[] = {
    "_lengthData",
    "_numStrips",
    "_dataSize",
};
static igMetaField **g_igPrimLengthArray_fieldHandles[] = {
    &g_igPrimLengthArray_lengthDataMetaField,
    &g_igPrimLengthArray_numStripsMetaField,
    &g_igPrimLengthArray_dataSizeMetaField,
};
static int g_igPrimLengthArray_fieldOffsets[] = {
    8,
    12,
    16,
};

void igPrimLengthArray_InitFields(void) {
    int fieldStart;
    void *temp_s1;
    igMetaObject *meta;

    meta = g_igPrimLengthArray_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igPrimLengthArray_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igMemoryRefMetaField *)temp_s1)->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    ((Gap::Core::igUnsignedIntMetaField *)(igMetaObject_GetFieldAt(meta, fieldStart + 2)))->setDefault(0x20);
    igMetaObject_NameFields(meta, g_igPrimLengthArray_fieldTable, g_igPrimLengthArray_fieldHandles, g_igPrimLengthArray_fieldOffsets, fieldStart);
    *(int *)((char *)(g_igPrimLengthArray_metaObject) + 60) = (int)(igPrimLengthArray1_1_GetMetaObjectFunction);
}

static const char *g_igPrimLengthArray_spriteTypeNames[] = {
    "IG_GFX_SPRITE_TYPE_NONE", "IG_GFX_SPRITE_TYPE_POINTS",
};
static int g_igPrimLengthArray_spriteTypeValues[] = {
    0, 1,
};
igMetaEnum *g_igPrimLengthArray_spriteTypeMetaEnum;

int IG_GFX_SPRITE_TYPE_GetMetaEnum(void) {
    if (g_igPrimLengthArray_spriteTypeMetaEnum == 0) {
        g_igPrimLengthArray_spriteTypeMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("IG_GFX_SPRITE_TYPE", g_igPrimLengthArray_spriteTypeNames, g_igPrimLengthArray_spriteTypeValues, 2);
    }
    return (int)g_igPrimLengthArray_spriteTypeMetaEnum;
}

