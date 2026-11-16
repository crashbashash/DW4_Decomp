igMetaObject *g_igViewerGuiFactory_metaObject;
igMetaField *g_igViewerGuiFactory_menuBackColorMetaField;
igMetaField *g_igViewerGuiFactory_menuItemForeColorMetaField;
igMetaField *g_igViewerGuiFactory_menuMarkColorMetaField;
igMetaField *g_igViewerGuiFactory_iconBackColorMetaField;
igMetaField *g_igViewerGuiFactory_bigIconColorMetaField;
igMetaField *g_igViewerGuiFactory_bigIconHighlightColorMetaField;
igMetaField *g_igViewerGuiFactory_smallIconOnOffColorMetaField;
igMetaField *g_igViewerGuiFactory_fontMetaField;

igMetaObject *FUN_0045b8d0(void) {
    if (g_igViewerGuiFactory_metaObject == 0) {
        g_igViewerGuiFactory_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igViewerGuiFactory_metaObject;
}

igMetaObject *igViewerGuiFactory_GetMetaObject(void)
{
    igMetaObject *g = ((igMetaObject *)g_igViewerGuiFactory_metaObject);
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0045bc10();
    return ((igMetaObject *)g_igViewerGuiFactory_metaObject);
}

int igViewerGuiFactory_GetVTable(void) {
    struct Obj_45b970 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igViewerGuiFactory_vtable[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)g_objectSystem)) + 916));
    obj.vt = &g_igViewerGuiFactory_vtable[0];
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

static igMetaObjectCallback g_igViewerGuiFactory_callbackList[] = { igBasicColorChanger_RunStaticInit, igOnOffColorChanger_RunStaticInit, igBitmapFont_RunStaticInit, 0 };

CallbackArray *igViewerGuiFactory_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewerGuiFactory_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igViewerGuiFactory_GetMetaObject,
        "igViewerGuiFactory",
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

static FieldFactory g_igViewerGuiFactory_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igViewerGuiFactory_fieldTable[] = {
    "_menuBackColor",
    "_menuItemForeColor",
    "_menuMarkColor",
    "_iconBackColor",
    "_bigIconColor",
    "_bigIconHighlightColor",
    "_smallIconOnOffColor",
    "_font",
};
static igMetaField **g_igViewerGuiFactory_fieldHandles[] = {
    &g_igViewerGuiFactory_menuBackColorMetaField,
    &g_igViewerGuiFactory_menuItemForeColorMetaField,
    &g_igViewerGuiFactory_menuMarkColorMetaField,
    &g_igViewerGuiFactory_iconBackColorMetaField,
    &g_igViewerGuiFactory_bigIconColorMetaField,
    &g_igViewerGuiFactory_bigIconHighlightColorMetaField,
    &g_igViewerGuiFactory_smallIconOnOffColorMetaField,
    &g_igViewerGuiFactory_fontMetaField,
};
static int g_igViewerGuiFactory_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
};

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

    temp_s0 = g_igViewerGuiFactory_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igViewerGuiFactory_ctorTable, 8);
    temp_s2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00451fc0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00451fc0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00451e40();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00451fc0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00451e40();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00451e40();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_00451e40();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_004524f0();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igViewerGuiFactory_fieldTable, g_igViewerGuiFactory_fieldHandles, g_igViewerGuiFactory_fieldOffsets, temp_s1);
}

