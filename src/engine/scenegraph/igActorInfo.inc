igMetaObject *g_igActorInfo_metaObject;
igMetaField *g_igActorInfo_actorMetaField;
igMetaField *g_igActorInfo_actorListMetaField;
igMetaField *g_igActorInfo_animationDatabaseMetaField;
igMetaField *g_igActorInfo_combinerListMetaField;
igMetaField *g_igActorInfo_appearanceListMetaField;

igMetaObject *igActorInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igActorInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001aa410();
    return g_igActorInfo_metaObject;
}

int igActorInfo_GetVTable(void) {
    struct Obj_1aa1b0 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.vt = &g_igActorInfo_vtable[0];
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igActorInfo_vtable[0];
    igSmartPointer_igAppearanceList_Destruct((igSmartPointer<igObject> *)&obj.w9, -1);
    FUN_001a7a80((void * *)&obj.w8, -1);
    igSmartPointer_igAnimationDatabase_Destruct((igSmartPointer<igObject> *)&obj.w7, -1);
    igSmartPointer_igActorList_Destruct((igSmartPointer<igObject> *)&obj.w6, -1);
    FUN_001aa290((void * *)&obj.w5, -1);
    igInfo_Destroy((igInfo *)&obj, 0);
    return t;
}

void **FUN_001aa290(void **arg0, long long arg1) {
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

igSmartPointer<igObject> *igSmartPointer_igActorList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

igSmartPointer<igObject> *igSmartPointer_igAnimationDatabase_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

void FUN_001aa410(void)
{
    igMetaObject_RunStaticInit(igActorInfo_Register);
}

static igMetaObjectCallback g_igActorInfo_callbackList[] = { igActor_EnsureRegistered, igActorList_EnsureRegistered, igAnimationDatabase_EnsureRegistered, igAnimationCombinerList_EnsureRegistered, igAppearanceList_EnsureRegistered, 0 };

CallbackArray *igActorInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igActorInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igActorInfo_GetMetaObject,
        "igActorInfo",
        0x28, /* instance size */
        igActorInfo_GetVTable,
        &igActorInfo_InitFields,
        0, /* extra callback item */
        g_igActorInfo_callbackList /* callback list */
    );
}

void thunk_igActorInfo_GetMetaObject(void) {
    igActorInfo_GetMetaObject();
}

static FieldFactory g_igActorInfo_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igActorInfo_fieldTable[] = {
    "_actor",
    "_actorList",
    "_animationDatabase",
    "_combinerList",
    "_appearanceList",
};
static igMetaField **g_igActorInfo_fieldHandles[] = {
    &g_igActorInfo_actorMetaField,
    &g_igActorInfo_actorListMetaField,
    &g_igActorInfo_animationDatabaseMetaField,
    &g_igActorInfo_combinerListMetaField,
    &g_igActorInfo_appearanceListMetaField,
};
static int g_igActorInfo_fieldOffsets[] = {
    20,
    24,
    28,
    32,
    36,
};

void igActorInfo_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s1;

    temp_s1 = (void *)g_igActorInfo_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igActorInfo_ctorTable, 5);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_001aa730();
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igActorList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igAnimationDatabase_GetOrCreateMetaObject();
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_001a83b0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)igAppearanceList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igActorInfo_fieldTable, g_igActorInfo_fieldHandles, g_igActorInfo_fieldOffsets, temp_s0);
}

