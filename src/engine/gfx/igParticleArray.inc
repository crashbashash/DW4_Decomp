igMetaObject *g_igParticleArray_metaObject;
igMetaField *g_igParticleArray_particleFormatMetaField;
igMetaField *g_igParticleArray_maxNumMetaField;
igMetaField *g_igParticleArray_arrayIndexMetaField;
igMetaField *g_igParticleArray_particleLifeStartMetaField;
igMetaField *g_igParticleArray_particleLifeEndMetaField;
igMetaField *g_igParticleArray_currentTimeMetaField;
igMetaField *g_igParticleArray_particleDataSizeMetaField;
igMetaField *g_igParticleArray_particleArrayMetaField;
igMetaField *g_igParticleArray_internalVertexArrayMetaField;
igMetaField *g_igParticleArray_contextMetaField;
igMetaField *g_igParticleArray_pointSpriteInterfaceMetaField;
igMetaField *g_igParticleArray_particleOffsetMetaField;
igMetaField *g_igParticleArray_particleNumMetaField;
igMetaField *g_igParticleArray_primLengthArrayNumMetaField;
igMetaField *g_igParticleArray_primLengthArrayOffsetMetaField;
igMetaField *g_igParticleArray_primLengthArrayMetaField;
igMetaField *g_igParticleArray_setConstantMetaField;
igMetaField *g_igParticleArray_configuredMetaField;
igMetaField *g_igParticleArray_updateFunctionMetaField;
igMetaField *g_igParticleArray_timeControlStateMetaField;
igMetaField *g_igParticleArray_particleLifetimeEndOffsetMetaField;
igMetaField *g_igParticleArray_aliveParticleNumMetaField;

static const char *g_igParticleArray_particleArrayLifeControlNames[] = {
    "IG_GFX_PARTICLE_ARRAY_NONE", "IG_GFX_PARTICLE_ARRAY_LOOP", "IG_GFX_PARTICLE_ARRAY_START_END",
};
static int g_igParticleArray_particleArrayLifeControlValues[] = {
    0, 1, 2,
};
igMetaEnum *g_igParticleArray_particleArrayLifeControlMetaEnum;

int IG_GFX_PARTICLE_ARRAY_LIFE_CONTROL_GetMetaEnum(void) {
    if (g_igParticleArray_particleArrayLifeControlMetaEnum == 0) {
        g_igParticleArray_particleArrayLifeControlMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("IG_GFX_PARTICLE_ARRAY_LIFE_CONTROL", g_igParticleArray_particleArrayLifeControlNames, g_igParticleArray_particleArrayLifeControlValues, 3);
    }
    return (int)g_igParticleArray_particleArrayLifeControlMetaEnum;
}

igMetaObject *igParticleArray_GetOrCreateMetaObject(void) {
    if (g_igParticleArray_metaObject == 0) {
        g_igParticleArray_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igParticleArray_metaObject;
}

igMetaObject *igParticleArray_GetMetaObject(void)
{
    igMetaObject *g = g_igParticleArray_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014cd90();
    return g_igParticleArray_metaObject;
}

int igParticleArray_GetVTable(void) {
    struct Obj_14ca20 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igParticleArray_vtable[0];
    obj.w2 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w17 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igParticleArray_vtable[0];
    FUN_00137260((void **)&obj.w17, (short)-1);
    FUN_0014cd10((ObjectRefWord *)&obj.w12, -1);
    igSmartPointer_igVisualContext_Destruct((igSmartPointer<igObject> *)&obj.w11, -1);
    igSmartPointer_igVertexArray_Destruct((igSmartPointer<igObject> *)&obj.w10, -1);
    FUN_0014cc90((void **)&obj.w2, -1);
    return t;
}

void *igParticleArray_Destroy(igParticleArray *self, short deleteFlags) {
    igObject *p;
    int rc;

    if (self != 0) {
        self->_vtable = (int)&g_igParticleArray_vtable[0];
        if (&self->_primLengthArray) {
            p = (igObject *)self->_primLengthArray;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&self->_pointSpriteInterface) {
            p = (igObject *)self->_pointSpriteInterface;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&self->_context) {
            p = (igObject *)self->_context;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&self->_internalVertexArray) {
            p = (igObject *)self->_internalVertexArray;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&self->_particleFormat) {
            p = (igObject *)self->_particleFormat;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (deleteFlags > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

void **FUN_0014cc90(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy((igObject *)r);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_0014cd10(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

void FUN_0014cd90(void)
{
    igMetaObject_RunStaticInit((CallbackArray * (*)())igParticleArray_Register);
}

static igMetaObjectCallback g_igParticleArray_callbackList[] = { igParticleFormat_EnsureRegistered, Gap::Gfx::igVertexArray::arkRegister, Gap::Gfx::igVisualContext::arkRegister, igPointSpriteExt_EnsureRegistered, Gap::Gfx::igPrimLengthArray::arkRegister, 0 };

CallbackArray *igParticleArray_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igParticleArray_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igParticleArray_GetMetaObjectFunction,
        "igParticleArray",
        0x5C, /* instance size */
        igParticleArray_GetVTable,
        &igParticleArray_InitFields,
        0, /* extra callback item */
        g_igParticleArray_callbackList /* callback list */
    );
}

void igParticleArray_GetMetaObjectFunction(void) {
    igParticleArray_GetMetaObject();
}

static FieldFactory g_igParticleArray_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igParticleArray_fieldTable[] = {
    "_particleFormat",
    "_maxNum",
    "_arrayIndex",
    "_particleLifeStart",
    "_particleLifeEnd",
    "_currentTime",
    "_particleDataSize",
    "_particleArray",
    "_internalVertexArray",
    "_context",
    "_pointSpriteInterface",
    "_particleOffset",
    "_particleNum",
    "_primLengthArrayNum",
    "_primLengthArrayOffset",
    "_primLengthArray",
    "_setConstant",
    "_configured",
    "_updateFunction",
    "_timeControlState",
    "_particleLifetimeEndOffset",
    "_aliveParticleNum",
};
static igMetaField **g_igParticleArray_fieldHandles[] = {
    &g_igParticleArray_particleFormatMetaField,
    &g_igParticleArray_maxNumMetaField,
    &g_igParticleArray_arrayIndexMetaField,
    &g_igParticleArray_particleLifeStartMetaField,
    &g_igParticleArray_particleLifeEndMetaField,
    &g_igParticleArray_currentTimeMetaField,
    &g_igParticleArray_particleDataSizeMetaField,
    &g_igParticleArray_particleArrayMetaField,
    &g_igParticleArray_internalVertexArrayMetaField,
    &g_igParticleArray_contextMetaField,
    &g_igParticleArray_pointSpriteInterfaceMetaField,
    &g_igParticleArray_particleOffsetMetaField,
    &g_igParticleArray_particleNumMetaField,
    &g_igParticleArray_primLengthArrayNumMetaField,
    &g_igParticleArray_primLengthArrayOffsetMetaField,
    &g_igParticleArray_primLengthArrayMetaField,
    &g_igParticleArray_setConstantMetaField,
    &g_igParticleArray_configuredMetaField,
    &g_igParticleArray_updateFunctionMetaField,
    &g_igParticleArray_timeControlStateMetaField,
    &g_igParticleArray_particleLifetimeEndOffsetMetaField,
    &g_igParticleArray_aliveParticleNumMetaField,
};
static int g_igParticleArray_fieldOffsets[] = {
    8,
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
    52,
    56,
    60,
    64,
    68,
    72,
    73,
    76,
    80,
    84,
    88,
};

void igParticleArray_InitFields(void) {
    int fieldStart;
    void *formatField;
    void *particleArrayField;
    void *vertexArrayField;
    void *contextField;
    void *pointSpriteField;
    void *primLengthField;
    void *timeControlField;
    igMetaObject *meta;

    meta = g_igParticleArray_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igParticleArray_ctorTable, 0x16);
    formatField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igObjectRefMetaField *)formatField)->_metaObject = (int)igParticleFormat_GetOrCreateMetaObject();
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt(meta, fieldStart + 4)))->setDefault(1.0f);
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 5))->_persistent = 0;
    particleArrayField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 7));
    ((igMemoryRefMetaField *)particleArrayField)->_memType = (int)Gap::Core::igFloatMetaField::getMetaField();
    vertexArrayField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 8));
    ((igObjectRefMetaField *)vertexArrayField)->_metaObject = (int)Gap::Gfx::igVertexArray::getClassTypeLazy();
    ((igMetaField *)vertexArrayField)->_persistent = 0;
    contextField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 9));
    ((igObjectRefMetaField *)contextField)->_metaObject = (int)Gap::Gfx::igVisualContext::getClassTypeLazy();
    ((igMetaField *)contextField)->_persistent = 0;
    pointSpriteField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0xA));
    ((igObjectRefMetaField *)pointSpriteField)->_metaObject = (int)igPointSpriteExt_GetOrCreateMetaObject();
    ((igMetaField *)pointSpriteField)->_persistent = 0;
    primLengthField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0xF));
    ((igObjectRefMetaField *)primLengthField)->_metaObject = (int)Gap::Gfx::igPrimLengthArray::getClassTypeLazy();
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x10))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x11))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x12))->_persistent = 0;
    timeControlField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0x13));
    ((Gap::Core::igEnumMetaField *)timeControlField)->setDefault(0);
    ((igEnumMetaField *)timeControlField)->_getMetaEnumFunction = (int)(IG_GFX_PARTICLE_ARRAY_LIFE_CONTROL_GetMetaEnum);
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x15))->_persistent = 0;
    igMetaObject_NameFields(meta, g_igParticleArray_fieldTable, g_igParticleArray_fieldHandles, g_igParticleArray_fieldOffsets, fieldStart);
    ((igMetaObject *)g_igParticleArray_metaObject)->_abstractProxy = (int)igPsx2ParticleArray_GetMetaObjectFunction;
}

