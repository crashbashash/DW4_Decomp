igMetaObject *g_igMousePosObserver_metaObject;
igMetaField *g_igMousePosObserver_guiSystemMetaField;
igMetaField *g_igMousePosObserver_intersectTraversalMetaField;
igMetaField *g_igMousePosObserver_rayMetaField;
igMetaField *g_igMousePosObserver_impactLengthMetaField;
igMetaField *g_igMousePosObserver_hitMetaField;
igMetaField *g_igMousePosObserver_hitPathMetaField;
igMetaField *g_igMousePosObserver_inverseProjectionMatrixMetaField;

int igMousePosObserver_Create(int arg0) {
    igMousePosObserver_RunStaticInit();
    return (int)(igMetaObject_CreateInstance(g_igMousePosObserver_metaObject, (igMemoryPoolView *)arg0));
}

igMetaObject *igMousePosObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igMousePosObserver_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMousePosObserver_RunStaticInit();
    return g_igMousePosObserver_metaObject;
}

int igMousePosObserver_GetVTable(void) {
    igMousePosObserver s; igMousePosObserver *o = &s; igObject *a; int t; int *p2; int *p1; int *p0;
    igObject_InitHeader((igObject *)o);
    o->_vtable = (int)&g_igMousePosObserver_vtable[0];
    p0 = &o->_intersectTraversal; p1 = &o->_ray; p2 = &o->_hitPath;
    *p0 = 0; *p1 = 0; *p2 = 0;
    igMatrix44f_SetIdentity(o->_inverseProjectionMatrix);
    t = *(int *)((char *)o + g_objectSystem->vtableProbeOffset);
    o->_vtable = (int)&D_00541090[0];
    if (p2 != 0) {
        a = *(igObject **)p2;
        if (a != 0) {
            *(int *)&a->_refCount = (int)((int) (*(int *)&a->_refCount - 1));
            if (((unsigned long long) ((long long) *(int *)&a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (p1 != 0) {
        a = *(igObject **)p1;
        if (a != 0) {
            *(int *)&a->_refCount = (int)((int) (*(int *)&a->_refCount - 1));
            if (((unsigned long long) ((long long) *(int *)&a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (p0 != 0) {
        a = *(igObject **)p0;
        if (a != 0) {
            *(int *)&a->_refCount = (int)((int) (*(int *)&a->_refCount - 1));
            if (((unsigned long long) ((long long) *(int *)&a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    return t;
}

ObjectRefWord *FUN_0044ee80(ObjectRefWord *self,int delete_storage) {
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

void igMousePosObserver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igMousePosObserver_Register);
}

static igMetaObjectCallback g_igMousePosObserver_callbackList[] = { Gap::Gui::igGuiSystem::arkRegister, Gap::Sg::igIntersectTraversal::arkRegister, igRay_EnsureRegistered, Gap::Sg::igGraphPath::arkRegister, 0 };

CallbackArray *igMousePosObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMousePosObserver_metaObject,
        Gap::Gui::igView::arkRegisterInternal,
        Gap::Gui::igView::getClassMeta,
        thunk_igMousePosObserver_GetMetaObject,
        "igMousePosObserver",
        0x64, /* instance size */
        igMousePosObserver_GetVTable,
        &igMousePosObserver_InitFields,
        0, /* extra callback item */
        g_igMousePosObserver_callbackList /* callback list */
    );
}

void thunk_igMousePosObserver_GetMetaObject(void) {
    igMousePosObserver_GetMetaObject();
}

static FieldFactory g_igMousePosObserver_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
};
static const char *g_igMousePosObserver_fieldTable[] = {
    "_guiSystem",
    "_intersectTraversal",
    "_ray",
    "_impactLength",
    "_hit",
    "_hitPath",
    "_inverseProjectionMatrix",
};
static igMetaField **g_igMousePosObserver_fieldHandles[] = {
    &g_igMousePosObserver_guiSystemMetaField,
    &g_igMousePosObserver_intersectTraversalMetaField,
    &g_igMousePosObserver_rayMetaField,
    &g_igMousePosObserver_impactLengthMetaField,
    &g_igMousePosObserver_hitMetaField,
    &g_igMousePosObserver_hitPathMetaField,
    &g_igMousePosObserver_inverseProjectionMatrixMetaField,
};
static int g_igMousePosObserver_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
};

void igMousePosObserver_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_igMousePosObserver_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igMousePosObserver_ctorTable, 7);
    temp_s2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)Gap::Gui::igGuiSystem::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)Gap::Sg::igIntersectTraversal::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igRay_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_3)->_construct = 1;
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3)))->setDefault(0.0f);
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)(Gap::Sg::igGraphPath::getClassTypeLazy());
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igMousePosObserver_fieldTable, g_igMousePosObserver_fieldHandles, g_igMousePosObserver_fieldOffsets, temp_s0);
}

