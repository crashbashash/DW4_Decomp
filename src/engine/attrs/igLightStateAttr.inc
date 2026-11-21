namespace Gap {
namespace Attrs {

igMetaObject *igLightStateAttr::_Meta;
igMetaField *igLightStateAttr::k_light;
igMetaField *igLightStateAttr::k_enabled;
igMetaField *igLightStateAttr::k_internal;

igLightStateAttr *igLightStateAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igLightStateAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igLightStateAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igLightStateAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igLightStateAttr::retrieveVTablePointer()
{
    igLightStateAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

ObjectRefWord *FUN_00136370(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igObject_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

namespace Gap {
namespace Attrs {

void igLightStateAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igLightStateAttr::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igLightAttr::arkRegister, Gap::Core::igObject::arkRegister, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igLightStateAttr",
        sizeof(igLightStateAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igLightStateAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_light", "_enabled", "_internal" };
    static igMetaField **enumStorage[] = { &k_light, &k_enabled, &k_internal };
    static int offsets[] = { 16, 20, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Attrs::igLightAttr::getClassTypeLazy();
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Core::igObject::getClassMeta();
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

