void FUN_0019fde0(int arg0) {
    igFrustCullTraversal_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)g_igFrustCullTraversal_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *g_igFrustCullTraversal_metaObject;
igMetaField *g_igFrustCullTraversal_compMatMetaField;
igMetaField *g_igFrustCullTraversal_curMVMatMetaField;
igMetaField *g_igFrustCullTraversal_curProjectionMatMetaField;
igMetaField *g_igFrustCullTraversal_cdMetaField;
igMetaField *g_igFrustCullTraversal_outerFrustCullScaleMetaField;
igMetaField *g_igFrustCullTraversal_outerScissorWindowScaleMetaField;
igMetaField *g_igFrustCullTraversal_boundingBoxMetaField;

igMetaObject *igFrustCullTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igFrustCullTraversal_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFrustCullTraversal_EnsureRegistered();
    return g_igFrustCullTraversal_metaObject;
}

int igFrustCullTraversal_GetVTable(void) {
    struct S_19fde0 s; char *p;
    int r;
    p = (char *)&s; FUN_001a10a0((igCommonTraversal *)p);
    s.vt = &g_igFrustCullTraversal_vtable[0];
    igSmartPointer_igAABox_Construct(&s.a);
    FUN_001510a0((int)s.b);
    FUN_001a1080((int *)(p + 548));
    r = *(int *)((char *)&s + g_objectSystem->vtableProbeOffset);
    s.vt = &g_igFrustCullTraversal_vtable[0];
    igSmartPointer_igClippingStateAttr_Destruct((void **)&s.c, -1);
    igSmartPointer_igAABox_Destruct((igSmartPointer<igObject> *)&s.a, -1);
    FUN_001a0910((Obj_19fde0 *)&s, 0);
    return r;
}

struct R **igSmartPointer_igCapabilityManager_Destruct(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

struct T_19fde0 **igSmartPointer_igAttrDefaultManager_Destruct(struct T_19fde0 **arg0, short arg1) {
    struct T_19fde0 *o;
    if (arg0 != 0) {
        o = *arg0;
        if (o != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void **igSmartPointer_igAttrStackManager_Destruct(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void **igSmartPointer_igTransformStack_Destruct(void **arg0, short arg1) {
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

void **igSmartPointer_igSorter_Destruct(struct Ref **self, short flag) {
    struct Ref *p;
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

void **igSmartPointer_igModelViewMatrixAttrPool_Destruct(void **arg0, long long arg1) {
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

O *igSmartPointer_igTimeAttrPool_Destruct(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        if (arg1 > 0) operator delete(arg0);
    }
    return arg0;
}

void **igSmartPointer_igVertexBlendMatrixAttrPool_Destruct(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void **igSmartPointer_igTextureMatrixAttrPool_Destruct(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *igSmartPointer_igVertexBlendMatrixListAttrPool_Destruct(ObjectRefWord *self,int delete_storage) {
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

void **igSmartPointer_igMatrixObjectPool_Destruct(void **arg0, short arg1) {
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

ObjectRefWord *igSmartPointer_igProjectionMatrixAttrPool_Destruct(ObjectRefWord *self,int delete_storage) {
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

ObjectRefWord *igSmartPointer_igNormalizeNormalsStateAttr_Destruct(ObjectRefWord *self,int delete_storage) {
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

void **igSmartPointer_igLongStack_Destruct(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void **igSmartPointer_igNonRefCountedMatrixObjectList_Destruct(void **arg0, short arg1) {
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

void **igSmartPointer_igNonRefCountedTransformList_Destruct(struct Ref **self, short flag) {
    struct Ref *p;
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

igSmartPointer<igObject> *igSmartPointer_igStringObjList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

O *igSmartPointer_igBlendMatricesAttrPool_Destruct(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        if (arg1 > 0) operator delete(arg0);
    }
    return arg0;
}

ObjectRefWord *igSmartPointer_igTimeAttr_Destruct(ObjectRefWord *self,int delete_storage) {
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

Obj_19fde0 *FUN_001a0910(Obj_19fde0 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = g_igCommonTraversal_vtable;
        arg0->rel(&arg0->m336);
        arg0->rel(&arg0->m268);
        arg0->rel(&arg0->m264);
        arg0->rel(&arg0->m260);
        arg0->rel(&arg0->m256);
        arg0->rel(&arg0->m252);
        arg0->rel(&arg0->m248);
        arg0->rel(&arg0->m244);
        arg0->rel(&arg0->m240);
        arg0->rel(&arg0->m236);
        arg0->rel(&arg0->m232);
        arg0->rel(&arg0->m96);
        arg0->rel(&arg0->m92);
        arg0->rel(&arg0->m88);
        arg0->rel(&arg0->m84);
        arg0->rel(&arg0->m80);
        arg0->rel(&arg0->m76);
        arg0->rel(&arg0->m72);
        arg0->rel(&arg0->m68);
        arg0->rel(&arg0->m64);
        arg0->rel(&arg0->m60);
        arg0->rel(&arg0->m56);
        arg0->rel(&arg0->m52);
        arg0->rel(&arg0->m36);
        arg0->rel(&arg0->m32);
        if (arg0) {
            arg0->vt = g_igTraversal_vtable;
            arg0->rel(&arg0->m28);
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void **igSmartPointer_igClippingStateAttr_Destruct(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

int *FUN_001a1080(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_igAABox_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void *FUN_001a10a0(igCommonTraversal *arg0) {
    igObject_InitHeader((igObject *)arg0);
    arg0->_vtable = (int)(&g_igTraversal_vtable[0]);
    arg0->_travProcs = 0;
    arg0->_vtable = (int)(&g_igCommonTraversal_vtable[0]);
    arg0->_capabilityManager = 0;
    arg0->_defaultManager = 0;
    arg0->_attrStack = 0;
    arg0->_transformStack = 0;
    arg0->_vc = 0;
    arg0->_flushedAttrs = 0;
    arg0->_sorter = 0;
    arg0->_matrixPool = 0;
    arg0->_timePool = 0;
    arg0->_blendMatrixPool = 0;
    arg0->_texMatPool = 0;
    arg0->_vertexBlendMatListPool = 0;
    arg0->_matrixObjectPool = 0;
    arg0->_projectionMatrixPool = 0;
    igMatrix44f_SetIdentity((float *)((char *)arg0 + 0x64));
    igMatrix44f_SetIdentity((float *)((char *)arg0 + 0xA4));
    arg0->_matrixOptimization = 0;
    arg0->_normalizeNormalsEnable = 0;
    arg0->_timeStack = 0;
    arg0->_matrixObjectList = 0;
    arg0->_boneMatrixPaletteList = 0;
    arg0->_blendMatrixPaletteList = 0;
    arg0->_blendMatrixPaletteLengths = 0;
    arg0->_segmentOverrideNames = 0;
    arg0->_segmentOverrideStacks = 0;
    arg0->_blendMatricesAttrPool = 0;
    igMatrix44f_SetIdentity((float *)((char *)arg0 + 0x110));
    arg0->_defaultTimeAttr = 0;
    igMatrix44f_SetIdentity((float *)((char *)arg0 + 0x158));
    igMatrix44f_SetIdentity((float *)((char *)arg0 + 0x198));
    return arg0;
}

void igFrustCullTraversal_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFrustCullTraversal_Register);
}

static igMetaObjectCallback g_igFrustCullTraversal_callbackList[] = { igClippingStateAttr_EnsureRegistered, igAABox_EnsureRegistered, 0 };

CallbackArray *igFrustCullTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFrustCullTraversal_metaObject,
        igCommonTraversal_Register,
        igCommonTraversal_GetPublishedMetaObject,
        igFrustCullTraversal_GetMetaObjectFunction,
        "igFrustCullTraversal",
        0x230, /* instance size */
        igFrustCullTraversal_GetVTable,
        &igFrustCullTraversal_InitFields,
        &FUN_001a13a0, /* extra callback item */
        g_igFrustCullTraversal_callbackList /* callback list */
    );
}

void igFrustCullTraversal_GetMetaObjectFunction(void) {
    igFrustCullTraversal_GetMetaObject();
}

igMetaObject *g_igCommonTraversal_metaObject;
igMetaField *g_igCommonTraversal_attrStackMetaField;
igMetaField *g_igCommonTraversal_transformStackMetaField;
igMetaField *g_igCommonTraversal_vcMetaField;
igMetaField *g_igCommonTraversal_capabilityManagerMetaField;
igMetaField *g_igCommonTraversal_defaultManagerMetaField;
igMetaField *g_igCommonTraversal_flushedAttrsMetaField;
igMetaField *g_igCommonTraversal_sorterMetaField;
igMetaField *g_igCommonTraversal_matrixPoolMetaField;
igMetaField *g_igCommonTraversal_timePoolMetaField;
igMetaField *g_igCommonTraversal_blendMatrixPoolMetaField;
igMetaField *g_igCommonTraversal_texMatPoolMetaField;
igMetaField *g_igCommonTraversal_vertexBlendMatListPoolMetaField;
igMetaField *g_igCommonTraversal_matrixObjectPoolMetaField;
igMetaField *g_igCommonTraversal_projectionMatrixPoolMetaField;
igMetaField *g_igCommonTraversal_viewMatMetaField;
igMetaField *g_igCommonTraversal_viewMatInvMetaField;
igMetaField *g_igCommonTraversal_modeMaskMetaField;
igMetaField *g_igCommonTraversal_matrixOptimizationMetaField;
igMetaField *g_igCommonTraversal_normalizeNormalsEnableMetaField;
igMetaField *g_igCommonTraversal_timeStackMetaField;
igMetaField *g_igCommonTraversal_matrixObjectListMetaField;
igMetaField *g_igCommonTraversal_timeLongBufMetaField;
igMetaField *g_igCommonTraversal_timeBufferedMetaField;
igMetaField *g_igCommonTraversal_boneMatrixPaletteListMetaField;
igMetaField *g_igCommonTraversal_blendMatrixPaletteListMetaField;
igMetaField *g_igCommonTraversal_blendMatrixPaletteLengthsMetaField;
igMetaField *g_igCommonTraversal_segmentOverrideNamesMetaField;
igMetaField *g_igCommonTraversal_segmentOverrideStacksMetaField;
igMetaField *g_igCommonTraversal_blendMatricesAttrPoolMetaField;
igMetaField *g_igCommonTraversal_projMatMetaField;
igMetaField *g_igCommonTraversal_defaultTimeAttrMetaField;
igMetaField *g_igCommonTraversal_jointChainCountMetaField;
igMetaField *g_igCommonTraversal_jointMvmBaseMetaField;
igMetaField *g_igCommonTraversal_jointMvmInverseBaseMetaField;
igMetaField *g_igCommonTraversal_jointGraphRootTraversedMetaField;

igMetaObject *igCommonTraversal_GetPublishedMetaObject(void) {
    return g_igCommonTraversal_metaObject;
}

static FieldFactory g_igFrustCullTraversal_ctorTable[] = {
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igFrustCullTraversal_fieldTable[] = {
    "_compMat",
    "_curMVMat",
    "_curProjectionMat",
    "_cd",
    "_outerFrustCullScale",
    "_outerScissorWindowScale",
    "_boundingBox",
};
static igMetaField **g_igFrustCullTraversal_fieldHandles[] = {
    &g_igFrustCullTraversal_compMatMetaField,
    &g_igFrustCullTraversal_curMVMatMetaField,
    &g_igFrustCullTraversal_curProjectionMatMetaField,
    &g_igFrustCullTraversal_cdMetaField,
    &g_igFrustCullTraversal_outerFrustCullScaleMetaField,
    &g_igFrustCullTraversal_outerScissorWindowScaleMetaField,
    &g_igFrustCullTraversal_boundingBoxMetaField,
};
static int g_igFrustCullTraversal_fieldOffsets[] = {
    476,
    540,
    544,
    548,
    552,
    556,
    472,
};

void igFrustCullTraversal_InitFields(void) {
    void *temp_s2_3;
    void *temp_s2_2;
    void *temp_s2;
    void *temp_s1;
    int temp_s0;
    struct M_19fde0 o1;
    struct V o2;
    struct V o3;
    struct V o4;
    struct V o5;

    temp_s1 = (void *)g_igFrustCullTraversal_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igFrustCullTraversal_ctorTable, 7);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    o5.x = 0;
    o5.y = 0;
    o5.z = 0;
    o5.w = 0x3F800000;
    o4.x = 0;
    o4.y = 0;
    o4.z = 0x3F800000;
    o4.w = 0;
    o3.x = 0;
    o3.y = 0x3F800000;
    o3.z = 0;
    o3.w = 0;
    o2.x = 0x3F800000;
    o2.y = 0;
    o2.z = 0;
    o2.w = 0;
    igMatrix44f_FromRows((float *)&o1, (igVec4f *)&o2, (igVec4f *)&o3, (igVec4f *)&o4, (igVec4f *)&o5);
    FUN_0018c640(temp_s2, &o1);
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igClippingStateAttr_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4), 1.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5), 2.0f);
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igAABox_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igFrustCullTraversal_fieldTable, g_igFrustCullTraversal_fieldHandles, g_igFrustCullTraversal_fieldOffsets, temp_s0);
    igMetaObject_AddExitCallback((int)&thunk_FUN_001c45d0);
}

void FUN_001a13a0(void) {
    FUN_001c45a0();
    igMetaObject_AddRegistrationCallback((int)((int *)FUN_001c4590));
}

void thunk_FUN_001c45d0(void) {
    FUN_001c45d0();
}

