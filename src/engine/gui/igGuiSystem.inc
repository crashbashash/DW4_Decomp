igMetaObject *g_igGuiSystem_metaObject;
igMetaField *g_igGuiSystem_rendererMetaField;
igMetaField *g_igGuiSystem_modelMetaField;
igMetaField *g_igGuiSystem_viewListMetaField;
igMetaField *g_igGuiSystem_rootMetaField;
igMetaField *g_igGuiSystem_mouseCursorMetaField;
igMetaField *g_igGuiSystem_mouseCursorTransformMetaField;
igMetaField *g_igGuiSystem_mouseCursorVisibleMetaField;

igMetaObject *igGuiSystem_GetOrCreateMetaObject(void) {
    if (g_igGuiSystem_metaObject == 0) {
        g_igGuiSystem_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGuiSystem_metaObject;
}

igMetaObject *igGuiSystem_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiSystem_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiSystem_RunStaticInit();
    return g_igGuiSystem_metaObject;
}

int igGuiSystem_GetVTable(void) {
    struct Obj_44df70 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igGuiSystem_vtable[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igGuiSystem_vtable[0];
    igSmartPointer_igTransform_Destruct((igSmartPointer<igObject> *)&obj.w7, -1);
    igSmartPointer_igMouseCursor_Destruct((igSmartPointer<igObject> *)&obj.w6, -1);
    igSmartPointer_igAttrSet_Destruct((igSmartPointer<igObject> *)&obj.w5, -1);
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
                igObject_Destroy((igObject *)o);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
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
            if (p->u.b.cnt == 0) igObject_Destroy((igObject *)p);
        }
        if (flag > 0) operator delete(self);
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
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

igSmartPointer<igObject> *igSmartPointer_igMouseCursor_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

void igGuiSystem_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiSystem_Register);
}

static igMetaObjectCallback g_igGuiSystem_callbackList[] = { igGuiSystemRenderer_RunStaticInit, igGuiSystemModel_RunStaticInit, igViewList_EnsureRegistered, igAttrSet_EnsureRegistered, igMouseCursor_RunStaticInit, igTransform_EnsureRegistered, 0 };

CallbackArray *igGuiSystem_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGuiSystem_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igGuiSystem_GetMetaObject,
        "igGuiSystem",
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

static FieldFactory g_igGuiSystem_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_igGuiSystem_fieldTable[] = {
    "_renderer",
    "_model",
    "_viewList",
    "_root",
    "_mouseCursor",
    "_mouseCursorTransform",
    "_mouseCursorVisible",
};
static igMetaField **g_igGuiSystem_fieldHandles[] = {
    &g_igGuiSystem_rendererMetaField,
    &g_igGuiSystem_modelMetaField,
    &g_igGuiSystem_viewListMetaField,
    &g_igGuiSystem_rootMetaField,
    &g_igGuiSystem_mouseCursorMetaField,
    &g_igGuiSystem_mouseCursorTransformMetaField,
    &g_igGuiSystem_mouseCursorVisibleMetaField,
};
static int g_igGuiSystem_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
};

void igGuiSystem_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s1;

    temp_s1 = (void *)g_igGuiSystem_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igGuiSystem_ctorTable, 7);
    temp_s2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igGuiSystemRenderer_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igGuiSystemModel_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igViewList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)(igAttrSet_GetOrCreateMetaObject());
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)igMouseCursor_GetOrCreateMetaObject();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)(igTransform_GetOrCreateMetaObject());
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igGuiSystem_fieldTable, g_igGuiSystem_fieldHandles, g_igGuiSystem_fieldOffsets, temp_s0);
}

