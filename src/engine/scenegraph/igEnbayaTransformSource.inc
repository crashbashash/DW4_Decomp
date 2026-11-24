namespace Gap {
namespace Sg {

igMetaObject *igEnbayaTransformSource::_Meta;
igMetaField *igEnbayaTransformSource::k_trackId;
igMetaField *igEnbayaTransformSource::k_enbayaAnimationSource;

igMetaObject *igEnbayaTransformSource::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igEnbayaTransformSource::retrieveVTablePointer()
{
    igEnbayaTransformSource temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igEnbayaTransformSource::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igEnbayaTransformSource::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igEnbayaAnimationSource::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igTransformSource::arkRegisterInternal,
        Gap::Sg::igTransformSource::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igEnbayaTransformSource",
        sizeof(igEnbayaTransformSource),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igEnbayaTransformSource::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create };
    static const char *names[] = { "_trackId", "_enbayaAnimationSource" };
    static igMetaField **enumStorage[] = { &k_trackId, &k_enbayaAnimationSource };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(-1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Sg::igEnbayaAnimationSource::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

