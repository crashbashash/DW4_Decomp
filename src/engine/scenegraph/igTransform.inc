igTransform *igTransform_CreateInstance(int allocator) {
    igTransform_EnsureRegistered();
    return (igTransform *)igMetaObject_CreateInstance((igMetaObject *)g_igTransform_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *g_igTransform_metaObject;
igMetaField *g_igTransform_mMetaField;
igMetaField *g_igTransform_targetMetaField;
igMetaField *g_igTransform_mvmMetaField;
igMetaField *g_igTransform_transformInputMetaField;

igMetaObject *igTransform_GetOrCreateMetaObject(void) {
    if (g_igTransform_metaObject == 0) {
        g_igTransform_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTransform_metaObject;
}

igMetaObject *igTransform_GetMetaObject(void)
{
    igMetaObject *g = g_igTransform_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTransform_EnsureRegistered();
    return g_igTransform_metaObject;
}

int igTransform_GetVTable(void) {
    struct W o;
    int r;
    int *pa = (int *)&o;
    igObject_InitHeader((igObject *)&o);
    o.f[1] = 0;
    o.vt = &g_igTransform_vtable[0];
    o.f[2] = 0;
    o.f[3] = 0;
    o.f[6] = 0;
    igMatrix44f_SetIdentity((float *)((char *)&o + 32));
    pa[25] = 0;
    pa[26] = 0;
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = &g_igTransform_vtable[0];
    igSmartPointer_igTransformSource_Destruct((void * *)&o.f[25], -1);
    igSmartPointer_igVisualAttribute_Destruct((ObjectRefWord *)&o.f[24], -1);
    igGroup_Destroy((igGroup *)&o, 0);
    return r;
}

void *FUN_001962d0(struct S_1962d0 *arg0, short arg1) {
    igObject *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &g_igTransform_vtable[0];
        if (&arg0->f68) {
            p = (igObject *)arg0->f68;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)p);
                }
            }
        }
        if (&arg0->f64) {
            p = (igObject *)arg0->f64;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)p);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = &g_igGroup_vtable[0];
            igSmartPointer_igNodeList_Destruct((igSmartPointer<igObject> *)((char *)arg0 + 0x1C), -1);
            igNode_Destroy((igNode *)arg0, 0);
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *igSmartPointer_igVisualAttribute_Destruct(ObjectRefWord *self,int delete_storage) {
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

void **igSmartPointer_igTransformSource_Destruct(void **arg0, short arg1) {
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

void igTransform_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((CallbackArray * (*)())igTransform_Register);
}

static igMetaObjectCallback g_igTransform_callbackList[] = { igVisualAttribute_EnsureRegistered, igTransformSource_EnsureRegistered, 0 };

CallbackArray *igTransform_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTransform_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        igTransform_GetMetaObjectFunction,
        "igTransform",
        0x6C, /* instance size */
        igTransform_GetVTable,
        &igTransform_InitFields,
        0, /* extra callback item */
        g_igTransform_callbackList /* callback list */
    );
}

void igTransform_GetMetaObjectFunction(void) {
    igTransform_GetMetaObject();
}

static FieldFactory g_igTransform_ctorTable[] = {
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igTransform_fieldTable[] = {
    "_m",
    "_target",
    "_mvm",
    "_transformInput",
};
static igMetaField **g_igTransform_fieldHandles[] = {
    &g_igTransform_mMetaField,
    &g_igTransform_targetMetaField,
    &g_igTransform_mvmMetaField,
    &g_igTransform_transformInputMetaField,
};
static int g_igTransform_fieldOffsets[] = {
    32,
    96,
    100,
    104,
};

void igTransform_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igTransform_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igTransform_ctorTable, 4);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    FUN_0018c640((igMetaField *)temp_s1, igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                     igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)).m);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)))->setDefault(0);
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    *(int *)((char *)(temp_s1_2) + 56) = (int)igVisualAttribute_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s1_2) + 38) = 0;
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3)));
    *(int *)((char *)(temp_s1_3) + 56) = (int)igTransformSource_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igTransform_fieldTable, g_igTransform_fieldHandles, g_igTransform_fieldOffsets, temp_s2);
}

igSmartPointer<igObject> *igSmartPointer_igTextureMatrixAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

