int FUN_00131f80(void) {
    if (DAT_0055ed40[0] == 0) {
        DAT_0055ed40[0] = igMetaEnum_Create(&DAT_004d4d08[0], &DAT_00485bf0[0], &DAT_00485c00[0], 3);
    }
    return DAT_0055ed40[0];
}

igMetaObject *FUN_00131fe0(void) {
    if (g_igTextureCubeAttr_metaObject[0] == 0) {
        g_igTextureCubeAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igTextureCubeAttr_metaObject[0];
}

igMetaObject *igTextureCubeAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureCubeAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00132420();
    return g_igTextureCubeAttr_metaObject[0];
}

int igTextureCubeAttr_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.vt = &DAT_00522aa0[0];
    o.f[2] = 0;
    o.f[11] = 0;
    o.f[13] = 0;
    o.f[15] = 0;
    FUN_00100400(&o.f[17], &FUN_00132410, &FUN_00132390, 4, 6);
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_00522aa0[0];
    FUN_00100390(&o.f[17], &FUN_00132390, 4, 6);
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
        arg0->f0 = &DAT_00522c60[0];
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
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

O *FUN_00132390(O *arg0, short arg1) {
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

void igTextureCubeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureCubeAttr_metaObject,
        igTextureAttr_Register,
        igTextureAttr_GetPublishedMetaObject,
        thunk_igTextureCubeAttr_GetMetaObject,
        igTextureCubeAttr_className,
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
    return g_igTextureAttr_metaObject[0];
}

void igTextureCubeAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igTextureCubeAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485c18[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0014dfb0();
    ((igObjectRefArrayMetaField *)temp_s1)->_num = 6;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_002dc7a0(temp_v0, &DAT_00485c58[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_00131f80);
    igMetaObject_NameFields(temp_s0, &DAT_00485c28[0], &DAT_00485c38[0], &DAT_00485c48[0], temp_s2);
}

