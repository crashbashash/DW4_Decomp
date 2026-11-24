namespace Gap {
namespace Sg {

igSwitch *igSwitch::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igSwitch *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igSwitch::_Meta;
igMetaField *igSwitch::k_childMask;

igMetaObject *igSwitch::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igSwitch::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igSwitch::retrieveVTablePointer()
{
    igSwitch temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Sg {

void igSwitch::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igSwitch::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igBitMask::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igGroup::arkRegisterInternal,
        Gap::Sg::igGroup::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igSwitch",
        sizeof(igSwitch),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igSwitch::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_childMask" };
    static igMetaField **enumStorage[] = { &k_childMask };
    static int offsets[] = { 32 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igBitMask::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

