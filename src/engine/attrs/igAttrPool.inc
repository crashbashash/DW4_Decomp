namespace Gap {
namespace Attrs {

igMetaObject *igAttrPool::_Meta;
igMetaField *igAttrPool::k_metaList;
igMetaField *igAttrPool::k_nonSharableMetaList;
igMetaField *igAttrPool::k_attributeList;

igAttrPool *igAttrPool::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igAttrPool *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igAttrPool::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAttrPool::retrieveVTablePointer()
{
    igAttrPool temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

void **FUN_0013a800(void **arg0, short arg1) {
    S_temp_a0_13a800 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_13a800 *)((void *)(*arg0));
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

igSmartPointer<igObject> *igSmartPointer_igMetaObjectList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

namespace Gap {
namespace Attrs {

void igAttrPool::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAttrPool::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igMetaObjectList_EnsureRegistered, Gap::Attrs::igAttrListList::arkRegister, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAttrPool",
        sizeof(igAttrPool),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        (igMetaObjectCallback)Gap::Attrs::igAttrPool::arkRegisterUser,
        regFunctions
    );
}

void igAttrPool::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_metaList", "_nonSharableMetaList", "_attributeList" };
    static igMetaField **enumStorage[] = { &k_metaList, &k_nonSharableMetaList, &k_attributeList };
    static int offsets[] = { 8, 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igMetaObjectList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)igMetaObjectList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Attrs::igAttrListList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    igMetaObject_AddExitCallback((int)thunk_igAttrPool_UserUnregister);
}

void igAttrPool::arkRegisterUser()
{
    userRegister();
}
}
}

void thunk_igAttrPool_UserUnregister(void) {
    Gap::Attrs::igAttrPool::userUnregister();
}

