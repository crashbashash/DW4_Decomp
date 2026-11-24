namespace Gap {
namespace Bec {

igMetaObject *beDemoKeepMes::_Meta;
igMetaField *beDemoKeepMes::k_kind;
igMetaField *beDemoKeepMes::k_sendTime;
igMetaField *beDemoKeepMes::k_groupName;
igMetaField *beDemoKeepMes::k_infoName;
igMetaField *beDemoKeepMes::k_ramNo;
igMetaField *beDemoKeepMes::k_message;
igMetaField *beDemoKeepMes::k_mesParam;

beDemoKeepMes *beDemoKeepMes::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beDemoKeepMes *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beDemoKeepMes::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beDemoKeepMes::retrieveVTablePointer()
{
    beDemoKeepMes temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beDemoKeepMes::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beDemoKeepMes::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beDemoKeepMes",
        sizeof(beDemoKeepMes),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beDemoKeepMes::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igStringMetaField_Create, igStringMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igStringMetaField_Create, igStringMetaField_Create };
    static const char *names[] = { "_kind", "_sendTime", "_groupName", "_infoName", "_ramNo", "_message", "_mesParam" };
    static igMetaField **enumStorage[] = { &k_kind, &k_sendTime, &k_groupName, &k_infoName, &k_ramNo, &k_message, &k_mesParam };
    static int offsets[] = { 8, 16, 24, 28, 32, 36, 40 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

