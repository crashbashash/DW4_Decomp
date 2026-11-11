int FUN_0014c920(void) {
    if (DAT_0055fbd8[0] == 0) {
        DAT_0055fbd8[0] = igMetaEnum_Create(&DAT_004dc210[0], &DAT_004889c0[0], &DAT_004889d0[0], 3);
    }
    return DAT_0055fbd8[0];
}

int FUN_0014c980(void) {
    if (DAT_0055fbe0[0] == 0) {
        DAT_0055fbe0[0] = (int)igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055fbe0[0];
}

igMetaObject *igParticleArray_GetMetaObject(void)
{
    igMetaObject *g = g_igParticleArray_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014cd90();
    return g_igParticleArray_metaObject[0];
}

int igParticleArray_GetVTable(void) {
    struct Obj_14ca20 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_005266c0[0];
    obj.w2 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w17 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_005266c0[0];
    FUN_00137260(&obj.w17, -1);
    FUN_0014cd10((ObjectRefWord *)&obj.w12, -1);
    FUN_00130140(&obj.w11, -1);
    FUN_001338d0(&obj.w10, -1);
    FUN_0014cc90((void **)&obj.w2, -1);
    return t;
}

void *FUN_0014caf0(igParticleArray *arg0, short arg1) {
    igObject *p;
    int rc;

    if (arg0 != 0) {
        arg0->_vtable = (int)&DAT_005266c0[0];
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
            thunk_FUN_002ed460__002ff810(arg0);
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
            FUN_00100610(arg0);
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
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void FUN_0014cd90(void)
{
    igMetaObject_RunStaticInit(igParticleArray_Register);
}

void igParticleArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igParticleArray_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igParticleArray_GetMetaObject,
        igParticleArray_className,
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

void igParticleArray_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_v0;
    void *temp_s1;

    temp_s1 = (void *)(DAT_0055fbe0[0]);
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_00488a00[0], 0x16);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0014d0b0();
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), 1.0f);
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5))->_persistent = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igMemoryRefMetaField *)temp_s2_2)->_memType = FUN_002c4870();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0014b980();
    ((igMetaField *)temp_s2_3)->_persistent = 0;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0014a040();
    ((igMetaField *)temp_s2_4)->_persistent = 0;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0014c2f0();
    ((igMetaField *)temp_s2_5)->_persistent = 0;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xF));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_0014c030();
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x10))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x11))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x12))->_persistent = 0;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x13));
    FUN_002dc7a0(temp_v0, &DAT_00488b78[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_0014c920);
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x15))->_persistent = 0;
    igMetaObject_NameFields(temp_s1, &DAT_00488a60[0], &DAT_00488ac0[0], &DAT_00488b20[0], temp_s0);
    ((igMetaObject *)DAT_0055fbe0[0])->_abstractProxy = (int)thunk_igPsx2ParticleArray_GetMetaObject;
}

