igMetaObject *FUN_0045b8d0(void) {
    if (g_igViewerGuiFactory_metaObject[0] == 0) {
        g_igViewerGuiFactory_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igViewerGuiFactory_metaObject[0];
}

igMetaObject *igViewerGuiFactory_GetMetaObject(void)
{
    igMetaObject *g = ((igMetaObject *)g_igViewerGuiFactory_metaObject[0]);
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0045bc10();
    return ((igMetaObject *)g_igViewerGuiFactory_metaObject[0]);
}

int igViewerGuiFactory_GetVTable(void) {
    struct Obj_45b970 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00542390[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)g_objectSystem[0])) + 916));
    obj.vt = &DAT_00542390[0];
    FUN_0045bb90((void **)&obj.w9, -1);
    FUN_0045bb10((Ref **)&obj.w8, -1);
    FUN_0045bb10((Ref **)&obj.w7, -1);
    FUN_0045bb10((Ref **)&obj.w6, -1);
    FUN_0045ba90((void **)&obj.w5, -1);
    FUN_0045bb10((Ref **)&obj.w4, -1);
    FUN_0045ba90((void **)&obj.w3, -1);
    FUN_0045ba90((void **)&obj.w2, -1);
    return t;
}

void **FUN_0045ba90(void **arg0, short arg1) {
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

void **FUN_0045bb10(struct Ref **self, short flag) {
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

void **FUN_0045bb90(void **arg0, long long arg1) {
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

void FUN_0045bc10(void)
{
    igMetaObject_RunStaticInit(igViewerGuiFactory_Register);
}

void igViewerGuiFactory_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerGuiFactory_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igViewerGuiFactory_GetMetaObject,
        igViewerGuiFactory_className,
        0x28, /* instance size */
        igViewerGuiFactory_GetVTable,
        &igViewerGuiFactory_InitFields,
        0, /* extra callback item */
        g_igViewerGuiFactory_callbackList /* callback list */
    );
}

void thunk_igViewerGuiFactory_GetMetaObject(void) {
    igViewerGuiFactory_GetMetaObject();
}

void igViewerGuiFactory_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igViewerGuiFactory_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igViewerGuiFactory_ctorTable[0], 8);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00451fc0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00451fc0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00451e40();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00451fc0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00451e40();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00451e40();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_00451e40();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_004524f0();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_igViewerGuiFactory_fieldTable[0], &DAT_004d1310[0], &DAT_004d1330[0], temp_s1);
}

