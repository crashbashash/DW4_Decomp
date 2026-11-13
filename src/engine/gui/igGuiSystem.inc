igMetaObject *FUN_0044ded0(void) {
    if (g_igGuiSystem_metaObject[0] == 0) {
        g_igGuiSystem_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igGuiSystem_metaObject[0];
}

igMetaObject *igGuiSystem_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiSystem_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiSystem_RunStaticInit();
    return g_igGuiSystem_metaObject[0];
}

int igGuiSystem_GetVTable(void) {
    struct Obj_44df70 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00540f20[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00540f20[0];
    FUN_001a7580(&obj.w7, -1);
    FUN_0044e1e0((O_44e1e0 *)&obj.w6, -1);
    FUN_001d97f0(&obj.w5, -1);
    FUN_0044e160((void **)&obj.w4, -1);
    FUN_0044e0e0((Ref **)&obj.w3, -1);
    FUN_0044e060((void **)&obj.w2, -1);
    return t;
}

void **FUN_0044e060(void **arg0, short arg1) {
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
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_0044e0e0(struct Ref **self, short flag) {
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

void **FUN_0044e160(void **arg0, long long arg1) {
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

O_44e1e0 *FUN_0044e1e0(O_44e1e0 *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void igGuiSystem_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiSystem_Register);
}

void igGuiSystem_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiSystem_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igGuiSystem_GetMetaObject,
        igGuiSystem_className,
        0x24, /* instance size */
        igGuiSystem_GetVTable,
        &igGuiSystem_InitFields,
        0, /* extra callback item */
        g_igGuiSystem_callbackList /* callback list */
    );
}

void thunk_igGuiSystem_GetMetaObject(void) {
    igGuiSystem_GetMetaObject();
}

void igGuiSystem_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s1;

    temp_s1 = (void *)g_igGuiSystem_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d01b0[0], 7);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0044e6b0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_0044f210();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_0044b9f0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_001a5d70();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_0044e430();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00196190();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004d01d0[0], &DAT_004d01f0[0], &DAT_004d0210[0], temp_s0);
}

