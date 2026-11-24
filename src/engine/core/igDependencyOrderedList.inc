namespace Gap {
namespace Core {

igMetaObject *igDependencyOrderedList::_Meta;
igMetaField *igDependencyOrderedList::k_objectList;
igMetaField *igDependencyOrderedList::k_dependencies;
igMetaField *igDependencyOrderedList::k_order;
igMetaField *igDependencyOrderedList::k_checkPoints;
igMetaField *igDependencyOrderedList::k_hasCircularDependencies;

igMetaObject *igDependencyOrderedList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igDependencyOrderedList::retrieveVTablePointer()
{
    igDependencyOrderedList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igDependencyOrderedList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igDependencyOrderedList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igObjectList::arkRegister, Gap::Core::igDependencyList::arkRegister, Gap::Core::igPointerList::arkRegister, igStringRefList_EnsureRegistered, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igDependencyOrderedList",
        sizeof(igDependencyOrderedList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igDependencyOrderedList::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_objectList", "_dependencies", "_order", "_checkPoints", "_hasCircularDependencies" };
    static igMetaField **enumStorage[] = { &k_objectList, &k_dependencies, &k_order, &k_checkPoints, &k_hasCircularDependencies };
    static int offsets[] = { 8, 12, 16, 20, 24 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igObjectList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Core::igDependencyList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Core::igPointerList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

