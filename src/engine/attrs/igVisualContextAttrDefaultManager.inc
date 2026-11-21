namespace Gap {
namespace Attrs {

igMetaObject *igVisualContextAttrDefaultManager::_Meta;
igMetaField *igVisualContextAttrDefaultManager::k_visualContext;

igVisualContextAttrDefaultManager *igVisualContextAttrDefaultManager::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igVisualContextAttrDefaultManager *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igVisualContextAttrDefaultManager::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igVisualContextAttrDefaultManager::retrieveVTablePointer()
{
    igVisualContextAttrDefaultManager temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

igSmartPointer<igObject> *igSmartPointer_igVisualContext_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

namespace Gap {
namespace Attrs {

void igVisualContextAttrDefaultManager::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVisualContextAttrDefaultManager::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igVisualContext_EnsureRegistered, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igAttrDefaultManager::arkRegisterInternal,
        Gap::Attrs::igAttrDefaultManager::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVisualContextAttrDefaultManager",
        sizeof(igVisualContextAttrDefaultManager),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igVisualContextAttrDefaultManager::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_visualContext" };
    static igMetaField **enumStorage[] = { &k_visualContext };
    static int offsets[] = { 8 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 1;
        metaField->_shallowCopyMethod = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

