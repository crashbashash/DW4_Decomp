namespace Gap {
namespace Insight {

igMetaObject *igFilterMessageDispatcher::_Meta;
igMetaField *igFilterMessageDispatcher::k_defaultFilters;
igMetaField *igFilterMessageDispatcher::k_filters;

igMetaObject *igFilterMessageDispatcher::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igFilterMessageDispatcher::retrieveVTablePointer()
{
    igFilterMessageDispatcher temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igFilterMessageDispatcher::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igFilterMessageDispatcher::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Insight::igMessageFilterList::arkRegister, 0 };

    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Insight::igMessageDispatcher::arkRegisterInternal,
        Gap::Insight::igMessageDispatcher::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igFilterMessageDispatcher",
        sizeof(igFilterMessageDispatcher),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igFilterMessageDispatcher::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_defaultFilters", "_filters" };
    static igMetaField **enumStorage[] = { &k_defaultFilters, &k_filters };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Insight::igMessageFilterList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Insight::igMessageFilterList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

