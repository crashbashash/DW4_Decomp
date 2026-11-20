static const char *g_igAnimationModifier_modifierTypeNames[] = {
    "kPre", "kPost", "kOverride", "kOverrideOrientation",
};
static int g_igAnimationModifier_modifierTypeValues[] = {
    0, 1, 2, 3,
};
igMetaEnum *g_igAnimationModifier_modifierTypeMetaEnum;

igMetaEnum *FUN_001a7440(void) {
    if (g_igAnimationModifier_modifierTypeMetaEnum == 0) {
        g_igAnimationModifier_modifierTypeMetaEnum = igMetaEnum_Create("ModifierType", g_igAnimationModifier_modifierTypeNames, g_igAnimationModifier_modifierTypeValues, 4);
    }
    return g_igAnimationModifier_modifierTypeMetaEnum;
}

igMetaObject *g_igAnimationModifier_metaObject;
igMetaField *g_igAnimationModifier_boneIndexMetaField;
igMetaField *g_igAnimationModifier_transformMetaField;
igMetaField *g_igAnimationModifier_typeMetaField;

igMetaObject *igAnimationModifier_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationModifier_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationModifier_EnsureRegistered();
    return g_igAnimationModifier_metaObject;
}

int igAnimationModifier_GetVTable(void) {
    struct Obj_1a74f0 obj;
    char *o;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igAnimationModifier_vtable[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igAnimationModifier_vtable[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
    }
    return t;
}

igSmartPointer<igObject> *igSmartPointer_igTransform_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

void igAnimationModifier_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationModifier_Register);
}

static igMetaObjectCallback g_igAnimationModifier_callbackList[] = { igTransform_EnsureRegistered, 0 };

CallbackArray *igAnimationModifier_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationModifier_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igAnimationModifier_GetMetaObjectFunction,
        "igAnimationModifier",
        0x14, /* instance size */
        igAnimationModifier_GetVTable,
        &igAnimationModifier_InitFields,
        0, /* extra callback item */
        g_igAnimationModifier_callbackList /* callback list */
    );
}

void igAnimationModifier_GetMetaObjectFunction(void) {
    igAnimationModifier_GetMetaObject();
}

static FieldFactory g_igAnimationModifier_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igAnimationModifier_fieldTable[] = {
    "_boneIndex",
    "_transform",
    "_type",
};
static igMetaField **g_igAnimationModifier_fieldHandles[] = {
    &g_igAnimationModifier_boneIndexMetaField,
    &g_igAnimationModifier_transformMetaField,
    &g_igAnimationModifier_typeMetaField,
};
static int g_igAnimationModifier_fieldOffsets[] = {
    8,
    12,
    16,
};

void igAnimationModifier_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationModifier_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igAnimationModifier_ctorTable, 3);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)))->setDefault(-1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igTransform_GetOrCreateMetaObject();
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    ((Gap::Core::igEnumMetaField *)temp_v0)->setDefault(2);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_001a7440);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igAnimationModifier_fieldTable, g_igAnimationModifier_fieldHandles, g_igAnimationModifier_fieldOffsets, temp_s2);
}

