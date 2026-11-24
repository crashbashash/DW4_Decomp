namespace Gap {
namespace Insight {

igMetaObject *igMessageDefaultReceiver::_Meta;
igMetaField *igMessageDefaultReceiver::k_msgHandler;
igMetaField *igMessageDefaultReceiver::k_msgHandlerFunc;

igMessageDefaultReceiver *igMessageDefaultReceiver::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igMessageDefaultReceiver *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igMessageDefaultReceiver::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMessageDefaultReceiver::retrieveVTablePointer()
{
    igMessageDefaultReceiver temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMessageDefaultReceiver::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMessageDefaultReceiver::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igObject::arkRegister, 0 };

    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Insight::igMessageReceiver::arkRegisterInternal,
        Gap::Insight::igMessageReceiver::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMessageDefaultReceiver",
        sizeof(igMessageDefaultReceiver),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igMessageDefaultReceiver::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igStructMetaField::_instantiateFromPool };
    static const char *names[] = { "_msgHandler", "_msgHandlerFunc" };
    static igMetaField **enumStorage[] = { &k_msgHandler, &k_msgHandlerFunc };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igObject::getClassMeta();
    }
    {
        igStructMetaField *metaField = (igStructMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_size = 12;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

