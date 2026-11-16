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

int FUN_0014c920(void) {
    if (g_igParticleArray_particleArrayLifeControlMetaEnum == 0) {
        g_igParticleArray_particleArrayLifeControlMetaEnum = igMetaEnum_Create("IG_GFX_PARTICLE_ARRAY_LIFE_CONTROL", g_igParticleArray_particleArrayLifeControlNames, g_igParticleArray_particleArrayLifeControlValues, 3);
    }
    return (int)g_igParticleArray_particleArrayLifeControlMetaEnum;
}

igMetaObject *FUN_0014c980(void) {
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
    t = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj.vt = &g_igParticleArray_vtable[0];
    FUN_00137260(&obj.w17, -1);
    FUN_0014cd10((ObjectRefWord *)&obj.w12, -1);
    igSmartPointer_igVisualContext_Destruct(&obj.w11, -1);
    igSmartPointer_igVertexArray_Destruct(&obj.w10, -1);
    FUN_0014cc90((void **)&obj.w2, -1);
    return t;
}

void *igParticleArray_Destroy(igParticleArray *arg0, short arg1) {
    igObject *p;
    int rc;

    if (arg0 != 0) {
        arg0->_vtable = (int)&g_igParticleArray_vtable[0];
        if (&arg0->_primLengthArray) {
            p = (igObject *)arg0->_primLengthArray;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_pointSpriteInterface) {
            p = (igObject *)arg0->_pointSpriteInterface;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_context) {
            p = (igObject *)arg0->_context;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_internalVertexArray) {
            p = (igObject *)arg0->_internalVertexArray;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_particleFormat) {
            p = (igObject *)arg0->_particleFormat;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void **FUN_0014cc90(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
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
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void FUN_0014cd90(void)
{
    igMetaObject_RunStaticInit((CallbackArray * (*)())igParticleArray_Register);
}

static igMetaObjectCallback g_igParticleArray_callbackList[] = { igParticleFormat_EnsureRegistered, igVertexArray_EnsureRegistered, igVisualContext_EnsureRegistered, FUN_0014c670, FUN_0014c0d0, 0 };

CallbackArray *igParticleArray_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igParticleArray_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igParticleArray_GetMetaObject,
        "igParticleArray",
        0x5C, /* instance size */
        igParticleArray_GetVTable,
        &igParticleArray_InitFields,
        0, /* extra callback item */
        g_igParticleArray_callbackList /* callback list */
    );
}

void thunk_igParticleArray_GetMetaObject(void) {
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
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_v0;
    igMetaObject *meta;

    meta = g_igParticleArray_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igParticleArray_ctorTable, 0x16);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0014d0b0();
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 4), 1.0f);
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 5))->_persistent = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 7));
    ((igMemoryRefMetaField *)temp_s2_2)->_memType = igFloatMetaField_GetDefaultDescriptor();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 8));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igVertexArray_GetOrCreateMetaObject();
    ((igMetaField *)temp_s2_3)->_persistent = 0;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 9));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
    ((igMetaField *)temp_s2_4)->_persistent = 0;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0xA));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_0014c2f0();
    ((igMetaField *)temp_s2_5)->_persistent = 0;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0xF));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_0014c030();
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x10))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x11))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x12))->_persistent = 0;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0x13));
    igEnumMetaField_SetDefaultValue(temp_v0, 0);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_0014c920);
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x15))->_persistent = 0;
    igMetaObject_NameFields(meta, g_igParticleArray_fieldTable, g_igParticleArray_fieldHandles, g_igParticleArray_fieldOffsets, fieldStart);
    ((igMetaObject *)g_igParticleArray_metaObject)->_abstractProxy = (int)thunk_igPsx2ParticleArray_GetMetaObject;
}

