igMetaEnum *g_igTextureCubeAttr_applyTypeMetaEnum;
igMetaObject *g_igTextureCubeAttr_metaObject;
igMetaField *g_igTextureCubeAttr_cubeImageMetaField;
igMetaField *g_igTextureCubeAttr_applyTypeMetaField;
igMetaField *g_igTextureCubeAttr_unusedMetaField;

static const char *g_igTextureCubeAttr_applyTypeNames[] = {
    "NOT_SET",
    "CUBE_MAP",
    "SPHERE_MAP",
};
static int g_igTextureCubeAttr_applyTypeValues[] = {
    0,
    1,
    2,
};

igMetaEnum *igTextureCubeAttr_GetApplyTypeMetaEnum(void) {
    if (g_igTextureCubeAttr_applyTypeMetaEnum == 0) {
        g_igTextureCubeAttr_applyTypeMetaEnum = igMetaEnum_Create("ApplyType", g_igTextureCubeAttr_applyTypeNames, g_igTextureCubeAttr_applyTypeValues, 3);
    }
    return g_igTextureCubeAttr_applyTypeMetaEnum;
}

igMetaObject *igTextureCubeAttr_GetOrCreateMetaObject(void) {
    if (g_igTextureCubeAttr_metaObject == 0) {
        g_igTextureCubeAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTextureCubeAttr_metaObject;
}

igMetaObject *igTextureCubeAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureCubeAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTextureCubeAttr_EnsureRegistered();
    return g_igTextureCubeAttr_metaObject;
}

int igTextureCubeAttr_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igTextureCubeAttr_vtable[0];
    o.f[2] = 0;
    o.f[11] = 0;
    o.f[13] = 0;
    o.f[15] = 0;
    /* the element constructor and destructor in the runtime's ConstructorDestructor form */
    __construct_array(&o.f[17], (ConstructorDestructor)&FUN_00132410, (ConstructorDestructor)&igSmartPointer_igImage_Destruct, 4, 6);
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = &g_igTextureCubeAttr_vtable[0];
    __destroy_arr(&o.f[17], (ConstructorDestructor)&igSmartPointer_igImage_Destruct, 4, 6);
    FUN_00132230((S_132230 *)&o, 0);
    return r;
}

void **FUN_00132130(struct Ref **self, short flag) {
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

void **FUN_001321b0(void **arg0, long long arg1) {
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

void *FUN_00132230(struct S_132230 *arg0, short arg1) {
    struct R *p;

    if (arg0 != 0) {
        arg0->f0 = &g_igTextureAttr_vtable[0];
        if (&arg0->f64) {
            p = arg0->f64;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy((igObject *)p);
                }
            }
        }
        if (&arg0->f56) {
            p = arg0->f56;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy((igObject *)p);
                }
            }
        }
        if (&arg0->f48) {
            p = arg0->f48;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy((igObject *)p);
                }
            }
        }
        if (&arg0->f12) {
            p = arg0->f12;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy((igObject *)p);
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

igSmartPointer<igObject> *igSmartPointer_igImage_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

int *FUN_00132410(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void igTextureCubeAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureCubeAttr_Register);
}

static igMetaObjectCallback g_igTextureCubeAttr_callbackList[] = { igImage_EnsureRegistered, 0 };

CallbackArray *igTextureCubeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureCubeAttr_metaObject,
        igTextureAttr_Register,
        igTextureAttr_GetPublishedMetaObject,
        igTextureCubeAttr_GetMetaObjectFunction,
        "igTextureCubeAttr",
        0x68, /* instance size */
        igTextureCubeAttr_GetVTable,
        &igTextureCubeAttr_InitFields,
        0, /* extra callback item */
        g_igTextureCubeAttr_callbackList /* callback list */
    );
}

void igTextureCubeAttr_GetMetaObjectFunction(void) {
    igTextureCubeAttr_GetMetaObject();
}

igMetaObject *igTextureAttr_GetPublishedMetaObject(void) {
    return g_igTextureAttr_metaObject;
}

static FieldFactory g_igTextureCubeAttr_ctorTable[] = {
    (FieldFactory)igObjectRefArrayMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igTextureCubeAttr_fieldTable[] = {
    "_cubeImage",
    "_applyType",
    "_unused",
};
static igMetaField **g_igTextureCubeAttr_fieldHandles[] = {
    &g_igTextureCubeAttr_cubeImageMetaField,
    &g_igTextureCubeAttr_applyTypeMetaField,
    &g_igTextureCubeAttr_unusedMetaField,
};
static int g_igTextureCubeAttr_fieldOffsets[] = {
    72,
    96,
    100,
};

void igTextureCubeAttr_InitFields(void) {
    int base;
    void *field;
    void *field2;
    igMetaObject *meta;

    meta = g_igTextureCubeAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igTextureCubeAttr_ctorTable, 3);
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)igImage_GetOrCreateMetaObject();
    ((igObjectRefArrayMetaField *)field2)->_num = 6;
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    igEnumMetaField_SetDefaultValue((igMetaField *)field, 0);
    ((igEnumMetaField *)field)->_getMetaEnumFunction = (int)(igTextureCubeAttr_GetApplyTypeMetaEnum);
    igMetaObject_NameFields(meta, g_igTextureCubeAttr_fieldTable, g_igTextureCubeAttr_fieldHandles, g_igTextureCubeAttr_fieldOffsets, base);
}

