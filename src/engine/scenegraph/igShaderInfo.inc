namespace Gap {
namespace Sg {

igShaderInfo *igShaderInfo::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igShaderInfo *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igShaderInfo::_Meta;
igMetaField *igShaderInfo::k_factoryList;

igMetaObject *igShaderInfo::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igShaderInfo::retrieveVTablePointer()
{
    igShaderInfo temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igShaderInfo::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igShaderInfo::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igShaderFactoryList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igInfo::arkRegisterInternal,
        Gap::Core::igInfo::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igShaderInfo",
        sizeof(igShaderInfo),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        thunk_FUN_001d8ab0,
        regFunctions
    );
}

void igShaderInfo::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_factoryList" };
    static igMetaField **enumStorage[] = { &k_factoryList };
    static int offsets[] = { 20 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igShaderFactoryList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    igMetaObject_AddExitCallback((int)Gap::Sg::igShaderInfo::_classDestructor);
}
}
}

void thunk_FUN_001d8ab0(void) {
    Gap::Sg::igShaderInfo::userRegister();
}

namespace Gap {
namespace Sg {

void igShaderInfo::_classDestructor() {
    userUnregister();
}
}
}

