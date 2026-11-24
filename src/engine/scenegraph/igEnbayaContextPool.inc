namespace Gap {
namespace Sg {

igMetaObject *igEnbayaContextPool::_Meta;
igMetaField *igEnbayaContextPool::k_poolList;
igMetaField *igEnbayaContextPool::k_boneCountList;
igMetaField *igEnbayaContextPool::k_freeIndexList;

igEnbayaContextPool *igEnbayaContextPool::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igEnbayaContextPool *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igEnbayaContextPool::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igEnbayaContextPool::retrieveVTablePointer()
{
    igEnbayaContextPool temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igEnbayaContextPool::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igEnbayaContextPool::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igPointerListList_EnsureRegistered, Gap::Core::igUnsignedIntList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igEnbayaContextPool",
        sizeof(igEnbayaContextPool),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igEnbayaContextPool::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_poolList", "_boneCountList", "_freeIndexList" };
    static igMetaField **enumStorage[] = { &k_poolList, &k_boneCountList, &k_freeIndexList };
    static int offsets[] = { 8, 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igPointerListList_GetOrCreateMetaObject();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Core::igUnsignedIntList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Core::igUnsignedIntList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

