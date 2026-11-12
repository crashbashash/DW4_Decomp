void **FUN_00137260(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_001372e0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) FUN_00100610(self);
    }
    return (void **)self;
}

void **FUN_00137360(void **arg0, long long arg1) {
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
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

igMetaObject *igGeometryAttr1_5_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryAttr1_5_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001376d0();
    return g_igGeometryAttr1_5_metaObject[0];
}

int igGeometryAttr1_5_GetVTable(void) {
    struct W_137430 o;
    int r;
    igObject_InitHeader(&o);
    o.f[2] = 0;
    o.f[3] = 0;
    o.f[7] = 0;
    o.f[9] = 0;
    o.f[10] = 0;
    o.vt = DAT_005238c0;
    o.f[11] = 0;
    r = *(int *)((char *)&o + *(int *)(g_objectSystem[0] + 916));
    o.vt = DAT_005238c0;
    FUN_00137260((void **)&o.f[11], -1);
    FUN_00137530((O_137530 *)&o, 0);
    return r;
}

O *FUN_001374b0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

O_137530 *FUN_00137530(O_137530 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_00523970[0];
        if (&arg0->m44) {
            S1 *t = arg0->m44;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m40) {
            S1 *t = arg0->m40;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m32) {
            S1 *t = arg0->m32;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m16) {
            S1 *t = arg0->m16;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m12) {
            S1 *t = arg0->m12;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (arg1 > 0) thunk_FUN_002ed460__002ff810(arg0);
    }
    return arg0;
}

void FUN_001376d0(void)
{
    igMetaObject_RunStaticInit(igGeometryAttr1_5_Register);
}

void igGeometryAttr1_5_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGeometryAttr1_5_metaObject,
        igGeometryAttr_Register,
        igGeometryAttr_GetPublishedMetaObject,
        thunk_igGeometryAttr1_5_GetMetaObject,
        igGeometryAttr1_5_className,
        0x34, /* instance size */
        igGeometryAttr1_5_GetVTable,
        &igGeometryAttr1_5_InitFields,
        0, /* extra callback item */
        g_igGeometryAttr1_5_callbackList /* callback list */
    );
}

void thunk_igGeometryAttr1_5_GetMetaObject(void) {
    igGeometryAttr1_5_GetMetaObject();
}

igMetaObject *FUN_00137770(void) {
    return g_igGeometryAttr_metaObject[0];
}

void igGeometryAttr1_5_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igGeometryAttr1_5_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486558[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0014c030();
    igMetaObject_NameFields(temp_s0, &DAT_00486560[0], &DAT_00486568[0], &DAT_00486570[0], temp_s2);
}

