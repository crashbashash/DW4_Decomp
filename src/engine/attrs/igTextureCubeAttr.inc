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

igMetaEnum *FUN_00131f80(void) {
    if (g_igTextureCubeAttr_applyTypeMetaEnum == 0) {
        g_igTextureCubeAttr_applyTypeMetaEnum = igMetaEnum_Create("ApplyType", g_igTextureCubeAttr_applyTypeNames, g_igTextureCubeAttr_applyTypeValues, 3);
    }
    return g_igTextureCubeAttr_applyTypeMetaEnum;
}

igMetaObject *FUN_00131fe0(void) {
    if (g_igTextureCubeAttr_metaObject == 0) {
        g_igTextureCubeAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igTextureCubeAttr_metaObject;
}

igMetaObject *igTextureCubeAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureCubeAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00132420();
    return g_igTextureCubeAttr_metaObject;
}

int igTextureCubeAttr_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.vt = &g_igTextureCubeAttr_vtable[0];
    o.f[2] = 0;
    o.f[11] = 0;
    o.f[13] = 0;
    o.f[15] = 0;
    __construct_array(&o.f[17], &FUN_00132410, &igSmartPointer_igImage_Destruct, 4, 6);
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_igTextureCubeAttr_vtable[0];
    __destroy_arr(&o.f[17], &igSmartPointer_igImage_Destruct, 4, 6);
    FUN_00132230((S_132230 *)&o, 0);
    return r;
}

void **FUN_00132130(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
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
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
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
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f56) {
            p = arg0->f56;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f48) {
            p = arg0->f48;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f12) {
            p = arg0->f12;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
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

O *igSmartPointer_igImage_Destruct(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

int *FUN_00132410(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void FUN_00132420(void)
{
    igMetaObject_RunStaticInit(igTextureCubeAttr_Register);
}

static igMetaObjectCallback g_igTextureCubeAttr_callbackList[] = { igImage_EnsureRegistered, 0 };

void igTextureCubeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureCubeAttr_metaObject,
        igTextureAttr_Register,
        igTextureAttr_GetPublishedMetaObject,
        thunk_igTextureCubeAttr_GetMetaObject,
        "igTextureCubeAttr",
        0x68, /* instance size */
        igTextureCubeAttr_GetVTable,
        &igTextureCubeAttr_InitFields,
        0, /* extra callback item */
        g_igTextureCubeAttr_callbackList /* callback list */
    );
}

void thunk_igTextureCubeAttr_GetMetaObject(void) {
    igTextureCubeAttr_GetMetaObject();
}

igMetaObject *FUN_001324c0(void) {
    return g_igTextureAttr_metaObject;
}

static FieldFactory g_igTextureCubeAttr_ctorTable[] = {
    igObjectRefArrayMetaField_Create,
    igEnumMetaField_Create,
    igIntMetaField_Create,
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
    int temp_s2;
    void *temp_v0;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igTextureCubeAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igTextureCubeAttr_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igImage_GetOrCreateMetaObject();
    ((igObjectRefArrayMetaField *)temp_s1)->_num = 6;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    igEnumMetaField_SetDefaultValue(temp_v0, 0);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_00131f80);
    igMetaObject_NameFields(temp_s0, g_igTextureCubeAttr_fieldTable, g_igTextureCubeAttr_fieldHandles, g_igTextureCubeAttr_fieldOffsets, temp_s2);
}

