namespace Gap {
namespace Bec {

igMetaObject *beModelCtrlInfoHitBody::_Meta;
igMetaField *beModelCtrlInfoHitBody::k_isFirst;
igMetaField *beModelCtrlInfoHitBody::k_calcTime;
igMetaField *beModelCtrlInfoHitBody::k_count;
igMetaField *beModelCtrlInfoHitBody::k_orgAABoxList;
igMetaField *beModelCtrlInfoHitBody::k_AABoxMinList;
igMetaField *beModelCtrlInfoHitBody::k_AABoxMaxList;
igMetaField *beModelCtrlInfoHitBody::k_AABoxList;

beModelCtrlInfoHitBody *beModelCtrlInfoHitBody::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beModelCtrlInfoHitBody *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beModelCtrlInfoHitBody::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beModelCtrlInfoHitBody::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beModelCtrlInfoHitBody::retrieveVTablePointer()
{
    beModelCtrlInfoHitBody temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beModelCtrlInfoHitBody::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beModelCtrlInfoHitBody::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igAABoxList_EnsureRegistered, igVec3fList_EnsureRegistered, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beModelCtrlInfoHitBody",
        sizeof(beModelCtrlInfoHitBody),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beModelCtrlInfoHitBody::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_isFirst", "_calcTime", "_count", "_orgAABoxList", "_AABoxMinList", "_AABoxMaxList", "_AABoxList" };
    static igMetaField **enumStorage[] = { &k_isFirst, &k_calcTime, &k_count, &k_orgAABoxList, &k_AABoxMinList, &k_AABoxMaxList, &k_AABoxList };
    static int offsets[] = { 8, 16, 24, 28, 32, 36, 40 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)igAABoxList_GetOrCreateMetaObject();
        metaField->_refCounted = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)igAABoxList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

