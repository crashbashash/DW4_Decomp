namespace Gap {
namespace Bec {

igMetaObject *beNumVerInsideData::_Meta;
igMetaField *beNumVerInsideData::k_index;
igMetaField *beNumVerInsideData::k_kind;

beNumVerInsideData *beNumVerInsideData::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beNumVerInsideData *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beNumVerInsideData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beNumVerInsideData::retrieveVTablePointer()
{
    beNumVerInsideData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beNumVerInsideData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beNumVerInsideData::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beNumVerInsideData",
        sizeof(beNumVerInsideData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beNumVerInsideData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool };
    static const char *names[] = { "_index", "_kind" };
    static igMetaField **enumStorage[] = { &k_index, &k_kind };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

