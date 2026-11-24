namespace Gap {
namespace Bec {

igMetaObject *beCriVolume::_Meta;
igMetaField *beCriVolume::k_isExec;
igMetaField *beCriVolume::k_max;
igMetaField *beCriVolume::k_current;
igMetaField *beCriVolume::k_sta;
igMetaField *beCriVolume::k_end;
igMetaField *beCriVolume::k_unit;

igMetaObject *beCriVolume::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beCriVolume::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beCriVolume::retrieveVTablePointer()
{
    beCriVolume temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beCriVolume::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beCriVolume::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beCriVolume",
        sizeof(beCriVolume),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beCriVolume::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool };
    static const char *names[] = { "_isExec", "_max", "_current", "_sta", "_end", "_unit" };
    static igMetaField **enumStorage[] = { &k_isExec, &k_max, &k_current, &k_sta, &k_end, &k_unit };
    static int offsets[] = { 8, 12, 16, 20, 24, 28 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 6);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

