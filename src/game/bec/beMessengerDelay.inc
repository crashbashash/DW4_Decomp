namespace Gap {
namespace Bec {

igMetaObject *beMessengerDelay::_Meta;
igMetaField *beMessengerDelay::k_isUse;
igMetaField *beMessengerDelay::k_sendTime;
igMetaField *beMessengerDelay::k_groupName;
igMetaField *beMessengerDelay::k_infoName;
igMetaField *beMessengerDelay::k_ramNo;
igMetaField *beMessengerDelay::k_message;
igMetaField *beMessengerDelay::k_argData;

beMessengerDelay *beMessengerDelay::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beMessengerDelay *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beMessengerDelay::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beMessengerDelay::retrieveVTablePointer()
{
    beMessengerDelay temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beMessengerDelay::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beMessengerDelay::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Bec::beMessengerArgData::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beMessengerDelay",
        sizeof(beMessengerDelay),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beMessengerDelay::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igStringMetaField_Create, igStringMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igStringMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_isUse", "_sendTime", "_groupName", "_infoName", "_ramNo", "_message", "_argData" };
    static igMetaField **enumStorage[] = { &k_isUse, &k_sendTime, &k_groupName, &k_infoName, &k_ramNo, &k_message, &k_argData };
    static int offsets[] = { 8, 16, 24, 28, 32, 36, 40 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)Gap::Bec::beMessengerArgData::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

