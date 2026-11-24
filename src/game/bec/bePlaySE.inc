namespace Gap {
namespace Bec {

igMetaObject *bePlaySE::_Meta;
igMetaField *bePlaySE::k_id;
igMetaField *bePlaySE::k_time;

bePlaySE *bePlaySE::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (bePlaySE *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *bePlaySE::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *bePlaySE::retrieveVTablePointer()
{
    bePlaySE temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void bePlaySE::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *bePlaySE::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "bePlaySE",
        sizeof(bePlaySE),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void bePlaySE::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool };
    static const char *names[] = { "_id", "_time" };
    static igMetaField **enumStorage[] = { &k_id, &k_time };
    static int offsets[] = { 8, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

