namespace Gap {
namespace Bec {

igMetaObject *beMatCtrlSearch::_Meta;
igMetaField *beMatCtrlSearch::k_minX;
igMetaField *beMatCtrlSearch::k_maxX;
igMetaField *beMatCtrlSearch::k_matNO;
igMetaField *beMatCtrlSearch::k_parent;
igMetaField *beMatCtrlSearch::k_memberList;

igMetaObject *beMatCtrlSearch::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beMatCtrlSearch::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beMatCtrlSearch::retrieveVTablePointer()
{
    beMatCtrlSearch temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beMatCtrlSearch::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beMatCtrlSearch::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Bec::beMatCtrlSearchList::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beMatCtrlSearch",
        sizeof(beMatCtrlSearch),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beMatCtrlSearch::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_minX", "_maxX", "_matNO", "_parent", "_memberList" };
    static igMetaField **enumStorage[] = { &k_minX, &k_maxX, &k_matNO, &k_parent, &k_memberList };
    static int offsets[] = { 8, 12, 16, 20, 24 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)getClassTypeLazy();
        metaField->_refCounted = 0;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Bec::beMatCtrlSearchList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

