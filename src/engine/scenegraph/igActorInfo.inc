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
        igActorInfo_EnsureRegistered();
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
    igSmartPointer_igAnimationCombinerList_Destruct((void * *)&obj.w8, -1);
    igSmartPointer_igAnimationDatabase_Destruct((igSmartPointer<igObject> *)&obj.w7, -1);
    igSmartPointer_igActorList_Destruct((igSmartPointer<igObject> *)&obj.w6, -1);
    igSmartPointer_igActor_Destruct((void * *)&obj.w5, -1);
    igInfo_Destroy((igInfo *)&obj, 0);
    return t;
}

void **igSmartPointer_igActor_Destruct(void **arg0, long long arg1) {
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

void igActorInfo_EnsureRegistered(void)
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
        igActorInfo_GetMetaObjectFunction,
        "igActorInfo",
        0x28, /* instance size */
        igActorInfo_GetVTable,
        &igActorInfo_InitFields,
        0, /* extra callback item */
        g_igActorInfo_callbackList /* callback list */
    );
}

void igActorInfo_GetMetaObjectFunction(void) {
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
    int base;
    void *actorField;
    void *actorListField;
    void *animationDatabaseField;
    void *combinerListField;
    void *appearanceListField;
    void *meta;

    meta = (void *)g_igActorInfo_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igActorInfo_ctorTable, 5);
    actorField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)actorField)->_metaObject = (int)igActor_GetOrCreateMetaObject();
    actorListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)actorListField)->_metaObject = (int)igActorList_GetOrCreateMetaObject();
    ((igRefMetaField *)actorListField)->_construct = 1;
    animationDatabaseField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)animationDatabaseField)->_metaObject = (int)igAnimationDatabase_GetOrCreateMetaObject();
    combinerListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)combinerListField)->_metaObject = (int)igAnimationCombinerList_GetOrCreateMetaObject();
    ((igRefMetaField *)combinerListField)->_construct = 1;
    appearanceListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4)));
    ((igObjectRefMetaField *)appearanceListField)->_metaObject = (int)igAppearanceList_GetOrCreateMetaObject();
    ((igRefMetaField *)appearanceListField)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igActorInfo_fieldTable, g_igActorInfo_fieldHandles, g_igActorInfo_fieldOffsets, base);
}

