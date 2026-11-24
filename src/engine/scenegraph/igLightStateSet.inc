namespace Gap {
namespace Sg {

igMetaObject *igLightStateSet::_Meta;
igMetaField *igLightStateSet::k_lightEnables;

igMetaObject *igLightStateSet::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igLightStateSet::retrieveVTablePointer()
{
    igLightStateSet temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Sg {

void igLightStateSet::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igLightStateSet::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igLightStateAttrList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igGroup::arkRegisterInternal,
        Gap::Sg::igGroup::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igLightStateSet",
        sizeof(igLightStateSet),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igLightStateSet::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_lightEnables" };
    static igMetaField **enumStorage[] = { &k_lightEnables };
    static int offsets[] = { 32 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Attrs::igLightStateAttrList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_deepCopyMethod = 0;
        metaField->_shallowCopyMethod = 2;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

