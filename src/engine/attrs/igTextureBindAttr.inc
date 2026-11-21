namespace Gap {
namespace Attrs {

igMetaObject *igTextureBindAttr::_Meta;
igMetaField *igTextureBindAttr::k_texture;
igMetaField *igTextureBindAttr::k_unitID;

igTextureBindAttr *igTextureBindAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igTextureBindAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igTextureBindAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTextureBindAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTextureBindAttr::retrieveVTablePointer()
{
    igTextureBindAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

igSmartPointer<igObject> *igSmartPointer_igTextureAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

namespace Gap {
namespace Attrs {

void igTextureBindAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTextureBindAttr::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igTextureAttr::arkRegister, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTextureBindAttr",
        sizeof(igTextureBindAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        arkRegisterUser,
        regFunctions
    );
}

void igTextureBindAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_texture", "_unitID" };
    static igMetaField **enumStorage[] = { &k_texture, &k_unitID };
    static int offsets[] = { 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Attrs::igTextureAttr::getClassTypeLazy();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igTextureBindAttr::synchronizeCachedUnitID;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}

void igTextureBindAttr::arkRegisterUser()
{
    userRegister();
}
}
}

