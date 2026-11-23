static const char *g_igAnimationModifier_modifierTypeNames[] = {
    "kPre", "kPost", "kOverride", "kOverrideOrientation",
};
static int g_igAnimationModifier_modifierTypeValues[] = {
    0, 1, 2, 3,
};
namespace Gap {
namespace Sg {

igMetaEnum *igAnimationModifier::ModifierType_Meta;

igMetaEnum *igAnimationModifier::getModifierTypeMetaEnum() {
    if (ModifierType_Meta == 0) {
        ModifierType_Meta = Gap::Core::igMetaEnum::createMetaEnum("ModifierType", g_igAnimationModifier_modifierTypeNames, g_igAnimationModifier_modifierTypeValues, 4);
    }
    return ModifierType_Meta;
}

igMetaObject *igAnimationModifier::_Meta;
igMetaField *igAnimationModifier::k_boneIndex;
igMetaField *igAnimationModifier::k_transform;
igMetaField *igAnimationModifier::k_type;

igMetaObject *igAnimationModifier::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAnimationModifier::retrieveVTablePointer()
{
    igAnimationModifier temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

igSmartPointer<igObject> *igSmartPointer_igTransform_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

namespace Gap {
namespace Sg {

void igAnimationModifier::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAnimationModifier::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igTransform_EnsureRegistered, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAnimationModifier",
        sizeof(igAnimationModifier),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igAnimationModifier::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, igObjectRefMetaField_Create, igEnumMetaField_Create };
    static const char *names[] = { "_boneIndex", "_transform", "_type" };
    static igMetaField **enumStorage[] = { &k_boneIndex, &k_transform, &k_type };
    static int offsets[] = { 8, 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(-1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)igTransform_GetOrCreateMetaObject();
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(2);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Sg::igAnimationModifier::getModifierTypeMetaEnum;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

