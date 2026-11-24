namespace Gap {
namespace Sg {

igMetaObject *igAnimationTrack::_Meta;
igMetaField *igAnimationTrack::k_source;
igMetaField *igAnimationTrack::k_constantQuaternion;
igMetaField *igAnimationTrack::k_constantTranslation;

igMetaObject *igAnimationTrack::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAnimationTrack::retrieveVTablePointer()
{
    igAnimationTrack temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igAnimationTrack::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAnimationTrack::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igTransformSource::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAnimationTrack",
        sizeof(igAnimationTrack),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igAnimationTrack::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool };
    static const char *names[] = { "_source", "_constantQuaternion", "_constantTranslation" };
    static igMetaField **enumStorage[] = { &k_source, &k_constantQuaternion, &k_constantTranslation };
    static int offsets[] = { 12, 16, 32 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igTransformSource::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

